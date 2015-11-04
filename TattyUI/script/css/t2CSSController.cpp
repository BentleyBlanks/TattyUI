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

        // loop all child 
        // find if it's style is defined
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
                toNormal(div);
                toOther(div);

                // 将所有兄弟结点入队列
                for(t2Div* c = div->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }

        // 完成所有三套基本状态初始化之后进行conditionStatus的样式初始化
    }


    void t2CSSController::toNormal(t2Div* div)
    {
        // div挂钩css
        for(auto parser : parsers)
        {
            // 遍历AST 能够保证specifierList->pseudo+class / specifierList->class
            vector<t2CSSSDList*> sdList = parser->findByClass(div->className);
            for(auto sd : sdList)
            {
                t2CSSNodeSpecifierList* specifierList = sd->specifierList;
                t2CSSDeclarationList* declarationList = sd->declarationList;

                div->setStatus(T2_NORMAL);

                // 存在伪类选择器
                if(specifierList->specifier->type == T2CSS_PSEUDO)
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

    void t2CSSController::toOther(t2Div* div)
    {
        // div挂钩css
        for(auto parser : parsers)
        {
            // 遍历AST 能够保证specifierList->pseudo+class / specifierList->class
            vector<t2CSSSDList*> sdList = parser->findByClass(div->className);
            for(auto sd : sdList)
            {
                t2CSSNodeSpecifierList* specifierList = sd->specifierList;
                t2CSSDeclarationList* declarationList = sd->declarationList;

                // 存在伪类选择器
                if(specifierList->specifier->type == T2CSS_PSEUDO)
                {
                    t2CSSNodeSpecifier* pseudo = specifierList->specifier;
                    if(pseudo->selectorName == "active")
                        div->setStatus(T2_ACTIVE);
                    else if(pseudo->selectorName == "hover")
                        div->setStatus(T2_HOVER);
                }
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

    void t2CSSController::toChild(t2CSSDeclaration* decl, t2Div* div)
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
                    // 根据当前状态赋值
                    toStyle(decl, temp->normal);
                    toStyle(decl, temp->hover);
                    toStyle(decl, temp->active);
                }

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }
    }

    void t2CSSController::toStatus(t2CSSDeclaration* decl, t2Div* div)
    {
        // 覆盖当前特性至其余状态
        switch(div->getStatus())
        {
        case T2_NORMAL:
            toStyle(decl, div->active);
            toStyle(decl, div->hover);
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
        //// --!need test
        //for(auto element : controller->divTable)
        //{
        //    t2Div* div = element.second;
        //    if(!div->bActive)
        //    {
        //        div->active = div->normal;
        //    }
        //    if(!div->bHover)
        //    {
        //        div->hover = div->normal;
        //    }
        //}
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
