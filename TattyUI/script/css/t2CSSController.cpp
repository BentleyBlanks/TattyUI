#include <TattyUI/script/css/t2CSSController.h>
#include <TattyUI/script/css/t2CSSParser.h>
#include <TattyUI/div/t2DivController.h>
#include <LinearList/t3Queue.h>

namespace TattyUI
{
    // 删除给定字符串前后的""和''
    string deleteQuotationMarks(string str)
    {
        if(str[0] == '\'' || str[0] == '\"')
            return str.substr(1, str.length() - 2);
        else
            return "";
    }

    t2DivController *controller = t2DivController::getInstance();

    t2CSSController::t2CSSController()
    {

    }

    t2CSSController* t2CSSController::getInstance()
    {
        static t2CSSController temp;
        return &temp;
    }

    void t2CSSController::loadCSS(vector<string> filePaths)
    {
        // 加载所有css文件
        for(auto file : filePaths)
        {
            t2CSSParser *parser = new t2CSSParser(file);

            parser->parse();

            // optional
            if(parser->ast)
                parser->ast->saveAsDot();

            parsers.push_back(parser);
        }

        // 正常三种状态的css初始化
        toDiv();

        // 在完成正常三种状态下的样式初始化之后才开始condition状态初始化
        //toDivCondition();
    }

    void t2CSSController::toDiv()
    {
        t3Queue<t2Div*> queue;
        t2Div* root = controller->getRoot();
        if(!root)
        {
            t2PrintError("Please set root first!");
            return;
        }

        queue.push(root);
        for(;;)
        {
            t2Div* div;
            if(queue.isEmpty()) div = NULL;
            else div = queue.pop();

            if(div)
            {
                // 预先完成Normal状态初始化 后接剩余状态初始化
                normalStyle(div, true);
                conditionStyle(div, true);

                normalStyle(div, false);
                conditionStyle(div, false);

                // 将所有兄弟结点入队列
                for(t2Div* c = div->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }
    }

    void t2CSSController::toDivCondition()
    {
        t3Queue<t2Div*> queue;
        t2Div* root = controller->getRoot();
        if(!root)
        {
            t2PrintError("Please set root first!");
            return;
        }

        queue.push(root);
        for(;;)
        {
            t2Div* div;
            if(queue.isEmpty()) div = NULL;
            else div = queue.pop();

            if(div)
            {
                // 预先完成Normal状态初始化 后接剩余状态初始化
                conditionStyle(div, true);
                conditionStyle(div, false);

                // 将所有兄弟结点入队列
                for(t2Div* c = div->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }
    }

    // 不解析conditionStyle
    void t2CSSController::normalStyle(t2Div* div, bool isNormal)
    {
        // div挂钩css
        for(auto parser : parsers)
        {
            // 遍历AST 能够保证specifierList->pseudo+class / specifierList->class
            vector<t2CSSSSDList*> sdList = parser->findByClass(div->className);
            for(auto sd : sdList)
            {
                t2CSSSelector* selector = sd->selector;
                t2CSSNodeSpecifierList* specifierList = sd->specifierList;
                t2CSSDeclarationList* declarationList = sd->declarationList;

                // 跳过条件选择器列表
                if(selector->selector)
                    continue;

                // 条件选择器依赖于当前div状态选项
                div->setStatus(T2_NORMAL);

                // 存在伪类选择器
                if(specifierList->specifier->type == T2CSS_PSEUDO && !isNormal)
                {
                    t2CSSNodeSpecifier* pseudo = specifierList->specifier;
                    if(pseudo->selectorName == "active")
                        div->setStatus(T2_ACTIVE);
                    else if(pseudo->selectorName == "hover")
                        div->setStatus(T2_HOVER);
                }
                else if(specifierList->specifier->type == T2CSS_CLASS && isNormal)
                    div->setStatus(T2_NORMAL);
                else
                    continue;


                // 样式应用
                t2Style& css = div->getCSS();
                while(declarationList)
                {
                    t2CSSDeclaration* decl;
                    // 此声明需存在 且 无不支持的语法存在
                    if((decl = declarationList->declaration) && parser->checkDeclaration(decl))
                    {
                        // 应用样式至css
                        toStyle(decl, css);

                        // 将样式应用至还未赋值的状态样式
                        toStatus(decl, div);

                        // 应用样式至所有子节点
                        toChild(decl, div);
                    }

                    declarationList = declarationList->declarationList;
                }
            }
        }
    }

    // 不解析normalStyle
    void t2CSSController::conditionStyle(t2Div* div, bool isNormal)
    {
        // div挂钩css
        for(auto parser : parsers)
        {
            // 遍历AST 能够保证specifierList->pseudo+class / specifierList->class
            vector<t2CSSSSDList*> sdList = parser->findByClass(div->className);
            for(auto sd : sdList)
            {
                t2CSSSelector* selector = sd->selector;
                t2CSSNodeSpecifierList* specifierList = sd->specifierList;
                t2CSSDeclarationList* declarationList = sd->declarationList;

                // 只解析条件选择器列表
                if(!selector->selector)
                    continue;

                // 条件选择器依赖于当前div状态选项
                div->setStatus(T2_NORMAL);

                // 存在伪类选择器
                if(specifierList->specifier->type == T2CSS_PSEUDO && !isNormal)
                {
                    t2CSSNodeSpecifier* pseudo = specifierList->specifier;
                    if(pseudo->selectorName == "active")
                        div->setStatus(T2_ACTIVE);
                    else if(pseudo->selectorName == "hover")
                        div->setStatus(T2_HOVER);
                }
                else if(specifierList->specifier->type == T2CSS_CLASS && isNormal)
                    div->setStatus(T2_NORMAL);
                else
                    continue;

                // 条件选择器列表 单一选择器直接跳过完成下一步初始化
                while((selector = selector->selector) && (specifierList = selector->simpleSelector->specifierList))
                {
                    t2Div* temp = NULL;
                    t2CSSNodeSpecifier *slFirstPart = specifierList->specifier, *slSecondPart = NULL;

                    // 置空当前div条件表
                    if(div->hasCondition())
                        div->deleteCondition();

                    if(!parser->checkSpecifierList(specifierList, &slFirstPart, &slSecondPart))
                        continue;

                    // 通过语法检测 因此slFirstPart必定为非空
                    if(slFirstPart && slSecondPart)
                    {
                        if(temp = t2DivController::getInstance()->find(slSecondPart->selectorName))
                        {
                            if(slFirstPart->selectorName == "hover")
                                div->addCondition(temp, T2_HOVER);
                            else if(slFirstPart->selectorName == "active")
                                div->addCondition(temp, T2_ACTIVE);
                        }
                    }
                    else
                    {
                        if(temp = t2DivController::getInstance()->find(slFirstPart->selectorName))
                            div->addCondition(temp, T2_NORMAL);
                    }
                }

                // 样式应用
                t2Style& css = div->getConditionCSS();
                while(declarationList)
                {
                    t2CSSDeclaration* decl;
                    // 此声明需存在 且 无不支持的语法存在
                    if((decl = declarationList->declaration) && parser->checkDeclaration(decl))
                    {
                        // 应用样式至css
                        toStyle(decl, css);

                        // 应用condition样式至还未赋值的状态样式
                        toStatus(decl, div, true);

                        // 应用condition样式至所有子节点
                        toChild(decl, div, true);
                    }

                    declarationList = declarationList->declarationList;
                }
            }
        }
    }


    //void t2CSSController::toOther(t2Div* div)
    //{
    //    // div挂钩css
    //    for(auto parser : parsers)
    //    {
    //        // 遍历AST 能够保证specifierList->pseudo+class / specifierList->class
    //        vector<t2CSSSSDList*> sdList = parser->findByClass(div->className);
    //        for(auto sd : sdList)
    //        {
    //            t2CSSSelector* selector = sd->selector;
    //            t2CSSNodeSpecifierList* specifierList = sd->specifierList;
    //            t2CSSDeclarationList* declarationList = sd->declarationList;
    //
    //            // 存在伪类选择器
    //            if(specifierList->specifier->type == T2CSS_PSEUDO)
    //            {
    //                t2CSSNodeSpecifier* pseudo = specifierList->specifier;
    //                if(pseudo->selectorName == "active")
    //                    div->setStatus(T2_ACTIVE);
    //                else if(pseudo->selectorName == "hover")
    //                    div->setStatus(T2_HOVER);
    //            }
    //            else
    //                continue;
    //
    //
    //
    //            // 样式应用
    //            t2Style& css = div->getCSS();
    //            while(declarationList)
    //            {
    //                t2CSSDeclaration* decl;
    //                // 此声明需存在 且 无不支持的语法存在
    //                if((decl = declarationList->declaration) && parser->checkDeclaration(decl))
    //                {
    //                    // 应用样式至css
    //                    toStyle(decl, css);
    //
    //                    // 将样式应用至还未赋值的状态样式
    //                    toStatus(decl, div);
    //
    //                    // 应用样式至所有子节点
    //                    toChild(decl, div);
    //                }
    //
    //                declarationList = declarationList->declarationList;
    //            }
    //        }
    //    }
    //}

    //void t2CSSController::toCondition(t2Div* div)
    //{
    //    // div挂钩css
    //    for(auto parser : parsers)
    //    {
    //        // 查找selector后接非空selector的根selector
    //        vector<t2CSSSDList*> sdList = parser->findSDByClass(div->className);
    //
    //        // condition样式初始化
    //
    //        // 事件注册
    //
    //        for(auto sd : sdList)
    //        {
    //            // 因条件样式只控制最后面的选择器 因此选取AST支线中Selector的第一个SpecifierList即可
    //            t2CSSSelector* selector = sd->selector;
    //            // 下列三项当中任意一项为空都无需进行样式解析
    //            if(!selector || !selector->simpleSelector || !selector->simpleSelector->specifierList)
    //                continue;
    //
    //            // 条件样式中最后一个选择器
    //            // 例如.a .b .c中的.c
    //            t2CSSNodeSpecifierList* specifierList = selector->simpleSelector->specifierList;
    //            t2CSSDeclarationList* declarationList = sd->declarationList;
    //
    //            // 存在伪类选择器 就根据指定状态初始化conditionStatus
    //            // 事件注册中被控制者的状态
    //            if(specifierList->specifier->type == T2CSS_PSEUDO)
    //            {
    //                t2CSSNodeSpecifier* pseudo = specifierList->specifier;
    //                if(pseudo->selectorName == "active")
    //                {
    //                    
    //                   
    //                }
    //                else if(pseudo->selectorName == "hover")
    //                {
    //                    
    //                }
    //            }
    //            else
    //            {
    //                
    //            }
    //
    //            // 解析整个选择器剩余部分 注册至事件驱动器中
    //
    //            // 样式应用
    //            div->setStatus(T2_CONDITION);
    //            t2Style& css = div->getCSS();
    //            while(declarationList)
    //            {
    //                t2CSSDeclaration* decl;
    //                // 此声明需存在 且 无不支持的语法存在
    //                if((decl = declarationList->declaration) && parser->checkDeclaration(decl))
    //                {
    //                    // 应用样式至css
    //                    toStyle(decl, css);
    //
    //                    // 应用condition样式至所有子节点的condition上
    //                    toChild(decl, div, true);
    //                }
    //
    //                declarationList = declarationList->declarationList;
    //            }
    //        }
    //
    //    }
    //}

void t2CSSController::toChild(t2CSSDeclaration* decl, t2Div* div, bool isCondition)
{
        // 覆盖其所有子类型内容
        // --!层序遍历
        t2Div* root = div;

        t3Queue<t2Div*> queue;
        if(!root) return;

        queue.push(root);
        for(;;)
        {
            t2Div* temp;

            if(queue.isEmpty()) temp = NULL;
            else temp = queue.pop();
            if(temp)
            {
                if(temp != root)
                {
                    if(!isCondition)
                    {
                        switch(div->getStatus())
                        {
                        case T2_NORMAL:
                            // 根据当前状态赋值
                            toStyle(decl, temp->normal);
                            toStyle(decl, temp->hover);
                            toStyle(decl, temp->active);

                            toStyle(decl, temp->normalCondition);
                            toStyle(decl, temp->hoverCondition);
                            toStyle(decl, temp->activeCondition);
                            break;

                        case T2_HOVER:
                            toStyle(decl, temp->hover);
                            toStyle(decl, temp->hoverCondition);
                            break;

                        case T2_ACTIVE:
                            toStyle(decl, temp->active);
                            toStyle(decl, temp->activeCondition);
                        }
                    }
                    else
                    {
                        toStyle(decl, temp->normalCondition);
                        toStyle(decl, temp->hoverCondition);
                        toStyle(decl, temp->activeCondition);
                    }
                }

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }
    }

    void t2CSSController::toStatus(t2CSSDeclaration* decl, t2Div* div, bool isCondition)
    {
        if(!isCondition)
        {
            // 覆盖当前特性至其余状态
            switch(div->getStatus())
            {
            case T2_NORMAL:
                toStyle(decl, div->active);
                toStyle(decl, div->hover);

                toStyle(decl, div->normalCondition);
                toStyle(decl, div->activeCondition);
                toStyle(decl, div->hoverCondition);
                break;

            case T2_ACTIVE:
                //toStyle(decl, div->normal);
                //toStyle(decl, div->hover);
                toStyle(decl, div->activeCondition);
                break;

            case T2_HOVER:
                toStyle(decl, div->hoverCondition);
                //toStyle(decl, div->active);
                //toStyle(decl, div->normal);
                break;
            }
        }
        else
        {
            // 覆盖当前特性至其余状态
            switch(div->getStatus())
            {
            case T2_NORMAL:
                toStyle(decl, div->activeCondition);
                toStyle(decl, div->hoverCondition);
                break;

            case T2_ACTIVE:
                //toStyle(decl, div->normal);
                //toStyle(decl, div->hover);
                break;

            case T2_HOVER:
                //toStyle(decl, div->active);
                //toStyle(decl, div->normal);
                break;
            }
        }
    }

    void t2CSSController::toStyle(t2CSSDeclaration* decl, t2Style& css)
    {
        string pro = decl->property;
        t2CSSExpression* expr = decl->expression;
        // 通用的expr首个value指针
        t2CSSTerm *term = expr->term;
        // display
        if(!stricmp(pro.c_str(), "display"))
        {
            // 只取第一个表达式
            if(term->isKeyword())
            {
                if(term->termName == "none")
                    css.display = T2_DISPLAY_NONE;
                else if(term->termName == "block")
                    css.display = T2_DISPLAY_BLOCK;
            }
        }
        // background
        else if(!stricmp(pro.c_str(), "background"))
        {
            // --!unsupported
        }
        // 设置元素的背景颜色
        else if(!stricmp(pro.c_str(), "background-color"))
        {
            // 颜色名 / 十六进制色 / rgb()暂不支持
            if(term->isColor())
                css.backgroundColor.set(term->termName);
        }
        // 设置元素的背景图像
        else if(!stricmp(pro.c_str(), "background-image"))
        {
            if(term->isString())
                css.backgroundImage.loadImage(deleteQuotationMarks(term->termName));
        }
        // --!目前为全局填充
        // 设置背景图像的开始位置
        else if(!stricmp(pro.c_str(), "background-position"))
        {
            // --!not supported
        }
        // 规定背景图片的尺寸
        else if(!stricmp(pro.c_str(), "background-size"))
        {
            // --!not supported
        }
        // border
        // 设置所有四个 border-*-radius 属性
        else if(!stricmp(pro.c_str(), "border-radius"))
        {
            if(term->isNumber())
                css.borderRadius = term->value;
        }
        else if(!stricmp(pro.c_str(), "box-shadow"))
        {
            css.displayShadow = true;

            // 只取expression列表中前四个参数
            int index = 0;
            while(expr)
            { 
                term = expr->term;

                switch(index)
                {
                case 3:
                    if(term->isNumber())
                        css.hBoxShadow = term->value;
                    break;
                case 2:
                    if(term->isNumber())
                        css.vBoxShadow = term->value;
                    break;
                case 1:
                    if(term->isNumber())
                        css.boxShadowBlur = term->value;
                    break;
                case 0:
                    if(term->isColor())
                    {
                        css.boxShadowInColor.set(term->termName);
                        css.boxShadowInColor.a = 125;
                    }
                    break;
                default:
                    t2Log("box-shadow中参数过多\n");
                    break;
                }

                index++;
                expr = expr->expression;
            }
        }
        // color
        // 规定书签的透明度[0.0f, 1.0f]
        else if(!stricmp(pro.c_str(), "opacity"))
        {
            if(term->isNumber())
                // 作用于image及color
                css.opacity = term->value;

            css.backgroundColor.a = css.opacity * 255;

            css.textColor.a = css.opacity * 255;

            css.textShadowColor.a = css.opacity * 255;

            //css.boxShadowInColor.a = css.opacity * 255;

            //css.boxShadowOutColor.a = css.opacity * 255;
        }
        // dimension
        else if(!stricmp(pro.c_str(), "width"))
        {
            if(term->isNumber())
                css.width = term->value;
        }
        else if(!stricmp(pro.c_str(), "height"))
        {
            if(term->isNumber())
                css.height = term->value;
        }
        // --!maxHeight不起作用
        else if(!stricmp(pro.c_str(), "max-height"))
        {
            if(term->isNumber())
                css.maxHeight = term->value;
        }
        else if(!stricmp(pro.c_str(), "max-width"))
        {
            if(term->isNumber())
                css.maxWidth = term->value;
        }
        else if(!stricmp(pro.c_str(), "min-height"))
        {
            if(term->isNumber())
                css.minHeight = term->value;
        }
        else if(!stricmp(pro.c_str(), "min-width"))
        {
            if(term->isNumber())
                css.minWidth = term->value;
        }
        // flexible box
        // 规定如何对齐框的子元素
        else if(!stricmp(pro.c_str(), "box-align"))
        {
            // --!not supported
        }
        // 规定当超出父元素框的空间时，是否换行显示
        else if(!stricmp(pro.c_str(), "box-lines"))
        {
            // --!not supported
        }
        // 规定框的子元素是否应水平或垂直排列
        else if(!stricmp(pro.c_str(), "box-orient"))
        {
            // --!not supported
        }
        // font
        // 规定文本的字体系列
        else if(!stricmp(pro.c_str(), "font-family"))
        {
            while(expr)
            {
                term = expr->term;

                // 目前不支持关键字形式
                if(term->isString())
                    // 删除前后双引号赋值
                    css.fontFamily = deleteQuotationMarks(term->termName);
                else if(term->isKeyword())
                    t2Log("Unsupported: font-family属性后不支持非字符串的语法");
                else
                    t2PrintError("font-family属性后紧跟未知语法");

                expr = expr->expression;
            }
        }
        // 规定文本的字体尺寸
        else if(!stricmp(pro.c_str(), "font-size"))
        {
            if(term->isNumber())
                css.fontSize = term->value;
        }
        // 规定字体的粗细
        else if(!stricmp(pro.c_str(), "font-weight"))
        {
            if(term->isNumber())
                css.fontWeight = term->value;
        }
        // margin
        else if(!stricmp(pro.c_str(), "margin"))
        {
            // 顺时针 上右下左
            // 只取expression列表中前四个参数(倒序)
            int index = 0;
            while(expr)
            {
                term = expr->term;

                switch(index)
                {
                case 3:
                    if(term->isNumber())
                        css.marginTop = term->value;
                    break;
                case 2:
                    if(term->isNumber())
                        css.marginRight = term->value;
                    break;
                case 1:
                    if(term->isNumber())
                        css.marginBottom = term->value;
                    break;
                case 0:
                    if(term->isNumber())
                        css.marginLeft = term->value;
                    break;
                default:
                    t2Log("margin中参数过多\n");
                    break;
                }

                index++;
                expr = expr->expression;
            }
        }
        else if(!stricmp(pro.c_str(), "margin-bottom"))
        {
            if(term->isNumber())
                css.marginBottom = term->value;
        }
        else if(!stricmp(pro.c_str(), "margin-left"))
        {
            if(term->isNumber())
                css.marginLeft = term->value;
        }
        else if(!stricmp(pro.c_str(), "margin-right"))
        {
            if(term->isNumber())
                css.marginRight = term->value;
        }
        else if(!stricmp(pro.c_str(), "margin-top"))
        {
            if(term->isNumber())
                css.marginTop = term->value;
        }
        // padding
        else if(!stricmp(pro.c_str(), "padding"))
        {
            // 顺时针 上右下左
            int index = 0;
            while(expr)
            {
                term = expr->term;

                switch(index)
                {
                case 3:
                    if(term->isNumber())
                        css.paddingTop = term->value;
                    break;
                case 2:
                    if(term->isNumber())
                        css.paddingRight = term->value;
                    break;
                case 1:
                    if(term->isNumber())
                        css.paddingBottom = term->value;
                    break;
                case 0:
                    if(term->isNumber())
                        css.paddingLeft = term->value;
                    break;
                default:
                    t2Log("margin中参数过多\n");
                    break;
                }

                index++;
                expr = expr->expression;
            }
        }
        else if(!stricmp(pro.c_str(), "padding-bottom"))
        {
            if(term->isNumber())
                css.paddingBottom = term->value;
        }
        else if(!stricmp(pro.c_str(), "padding-left"))
        {
            if(term->isNumber())
                css.paddingLeft = term->value;
        }
        else if(!stricmp(pro.c_str(), "padding-right"))
        {
            if(term->isNumber())
                css.paddingRight = term->value;
        }
        else if(!stricmp(pro.c_str(), "padding-top"))
        {
            if(term->isNumber())
                css.paddingTop = term->value;
        }
        // position
        // --!暂不支持
        else if(!stricmp(pro.c_str(), "z-index"))
        {
            // --!not supported
        }
        // text
        // 设置文本的颜色
        else if(!stricmp(pro.c_str(), "color"))
        {
            // 颜色名 / 十六进制色 / rgb()暂不支持
            if(term->isColor())
                css.textColor.set(term->termName);
        }
        // 设置字符间距
        else if(!stricmp(pro.c_str(), "letter-spacing"))
        {
            // --!not supported
        }
        // 设置行高
        else if(!stricmp(pro.c_str(), "line-height"))
        {
            // --!not supported
        }
        // 规定文本的水平对齐方式
        else if(!stricmp(pro.c_str(), "text-align"))
        {

        }
        // 设置单词间距
        else if(!stricmp(pro.c_str(), "word-spacing"))
        {
            // --! not sure
        }
        // text-shadow
        else if(!stricmp(pro.c_str(), "hTextShadow"))
        {
            if(term->isNumber())
                css.hTextShadow = term->value;
        }
        else if(!stricmp(pro.c_str(), "vTextShadow"))
        {
            if(term->isNumber())
                css.vTextShadow = term->value;
        }
        else if(!stricmp(pro.c_str(), "textShadowBlur"))
        {
            if(term->isNumber())
                css.textShadowBlur = term->value;
        }
        else if(!stricmp(pro.c_str(), "textShadowColor"))
        {
            // --!not supported
            // 颜色名 / 十六进制色 / rgb()暂不支持
            if(term->isColor())
                css.textShadowColor.set(term->termName);
        }
    }
}
