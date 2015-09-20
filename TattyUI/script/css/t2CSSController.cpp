#include <TattyUI/script/css/t2CSSController.h>
#include <TattyUI/script/css/t2CSSParser.h>
#include <TattyUI/div/t2DivController.h>
#include <LinearList/t3Queue.h>

namespace TattyUI
{
    t2DivController *controller = t2DivController::getInstance();

    t2CSSController::t2CSSController()
    {

    }

    t2CSSController* t2CSSController::getInstance()
    {
        static t2CSSController temp;
        return &temp;
    }

    bool t2CSSController::findByClass(vector<t2ClassSelector*> names, const string& className)
    {
        for(auto s : names)
        {
            if(s->classSelector == className)
                return true;
        }
        return false;
    }

    void t2CSSController::loadCSS(vector<string> filePaths)
    {
        // 加载所有css文件
        for(auto file : filePaths)
        {
            t2CSSParser *parser = new t2CSSParser(file);

            parser->parse();

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
                toDiv(div);

                // 将所有兄弟结点入队列
                for(t2Div* c = div->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }

    }

    void t2CSSController::toDiv(t2Div* div)
    {
        // div挂钩css
        for(auto parser : parsers)
        {
            for(auto rule : parser->ruleList)
            {
                for(auto selector : rule->classSelectors)
                {
                    // 类选择器
                    string classSelector = selector->classSelector;

                    // 伪类
                    string pseudo = selector->pseudoSelector;

                    if(!findByClass(rule->classSelectors, div->className))
                        continue;

                    if(!stricmp(pseudo.c_str(), "active"))
                        div->setStatus(T2_ACTIVE);
                    else if(!stricmp(pseudo.c_str(), "hover"))
                        div->setStatus(T2_HOVER);

                    // 属性赋值
                    t2Style& css = div->getCSS();
                    for(auto decl : rule->declarations)
                    {
                        // 应用样式至css
                        toStyle(decl, css);

                        // 将样式应用至还未赋值的状态样式
                        toStatus(decl, div);

                        // 应用样式至所有子节点
                        toChild(decl, div);
                    }
                }
            }
        }
    }

    void t2CSSController::toChild(t2Declaration* decl, t2Div* div)
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

    void t2CSSController::toStatus(t2Declaration* decl, t2Div* div)
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
            toStyle(decl, div->active);
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

    void t2CSSController::toStyle(t2Declaration* decl, t2Style& css)
    {
        string pro = decl->attribute;
        // display
        if(!stricmp(pro.c_str(), "display"))
        {
            if(!stricmp(decl->value.c_str(), "none"))
                css.display = T2_DISPLAY_NONE;
            else if(!stricmp(pro.c_str(), "block"))
                css.display = T2_DISPLAY_BLOCK;
        }
        // background
        // 设置元素的背景颜色
        else if(!stricmp(pro.c_str(), "background-color"))
        {
            css.backgroundColor.set(decl->value);
        }
        // 设置元素的背景图像
        else if(!stricmp(pro.c_str(), "background-image"))
        {
            css.backgroundImage.loadImage(decl->value);
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
            css.borderRadius = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "box-shadow"))
        {
            css.displayShadow = true;

            // 解析后部所有字符串内容
            int index = 0;
            // [^,]+        匹配除,外任何字符 可出现一次或多次
            // (?=,|;)         后接,;
            static const regex re(R"raw(([^,]+(?=,))|(,[^,]+))raw");
            smatch shadowM;
            string shadowStr = decl->value;
            while(regex_search(shadowStr, shadowM, re))
            {
                string str = shadowM[0];
                // not good
                // 删除最后一个元素前的,
                if(str.substr(0, 1) == ",")
                    str = str.substr(1, str.length() - 1);

                switch(index)
                {
                case 0:
                    css.hBoxShadow = atoi(str.c_str());
                    break;
                case 1:
                    css.vBoxShadow = atoi(str.c_str());
                    break;
                case 2:
                    css.boxShadowBlur = atoi(str.c_str());
                    break;
                case 3:
                    css.boxShadowInColor.set(str);
                    css.boxShadowInColor.a = 125;
                    break;
                    //case 4:
                    //css.boxShadowOutColor.set(str);
                    //css.boxShadowOutColor.a = 0;
                    //break;
                default:
                    t2Log("box-shadow中参数过多\n");
                    break;
                }

                index++;
                shadowStr = shadowM.suffix().str();
            }
        }
        // color
        // 规定书签的透明度[0.0f, 1.0f]
        else if(!stricmp(pro.c_str(), "opacity"))
        {
            // 作用于image及color
            css.opacity = atof(decl->value.c_str());

            css.backgroundColor.a = css.opacity * 255;

            css.textColor.a = css.opacity * 255;

            css.textShadowColor.a = css.opacity * 255;

            //css.boxShadowInColor.a = css.opacity * 255;

            //css.boxShadowOutColor.a = css.opacity * 255;
        }
        // dimension
        else if(!stricmp(pro.c_str(), "width"))
        {
            css.width = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "height"))
        {
            css.height = atoi(decl->value.c_str());
        }
        // --!maxHeight不起作用
        else if(!stricmp(pro.c_str(), "max-height"))
        {
            css.maxHeight = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "max-width"))
        {
            css.maxWidth = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "min-height"))
        {
            css.minHeight = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "min-width"))
        {
            css.minWidth = atoi(decl->value.c_str());
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
            css.fontFamily = decl->value;
        }
        // 规定文本的字体尺寸
        else if(!stricmp(pro.c_str(), "font-size"))
        {
            css.fontSize = atoi(decl->value.c_str());
        }
        // 规定字体的粗细
        else if(!stricmp(pro.c_str(), "font-weight"))
        {
            css.fontWeight = atoi(decl->value.c_str());
        }
        // margin
        else if(!stricmp(pro.c_str(), "margin"))
        {
            // 顺时针 上右下左
            // 解析后部所有字符串内容
            int index = 0;
            // [^,]+        匹配除,外任何字符 可出现一次或多次
            // (?=,|;)         后接,;
            static const regex re(R"raw(([^,]+(?=,))|(,[^,]+))raw");
            smatch marginM;
            string marginStr = decl->value;
            while(regex_search(marginStr, marginM, re))
            {
                string str = marginM[0];
                // not good
                // 删除最后一个元素前的,
                if(str.substr(0, 1) == ",")
                    str = str.substr(1, str.length() - 1);

                switch(index)
                {
                case 0:
                    css.marginTop = atoi(str.c_str());
                    break;
                case 1:
                    css.marginRight = atoi(str.c_str());
                    break;
                case 2:
                    css.marginBottom = atoi(str.c_str());
                    break;
                case 3:
                    css.marginLeft = atoi(str.c_str());
                    break;
                default:
                    t2Log("margin中参数过多\n");
                    break;
                }

                index++;
                marginStr = marginM.suffix().str();
            }
        }
        else if(!stricmp(pro.c_str(), "margin-bottom"))
        {
            css.marginBottom = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "margin-left"))
        {
            css.marginLeft = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "margin-right"))
        {
            css.marginRight = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "margin-top"))
        {
            css.marginTop = atoi(decl->value.c_str());
        }
        // padding
        else if(!stricmp(pro.c_str(), "padding"))
        {
            // 顺时针 上右下左
            // 解析后部所有字符串内容
            int index = 0;
            // [^,]+        匹配除,外任何字符 可出现一次或多次
            // (?=,|;)         后接,;
            static const regex re(R"raw(([^,]+(?=,))|(,[^,]+))raw");
            smatch paddingM;
            string paddingStr = decl->value;
            while(regex_search(paddingStr, paddingM, re))
            {
                string str = paddingM[0];
                // not good
                // 删除最后一个元素前的,
                if(str.substr(0, 1) == ",")
                    str = str.substr(1, str.length() - 1);

                switch(index)
                {
                case 0:
                    css.paddingTop = atoi(str.c_str());
                    break;
                case 1:
                    css.paddingRight = atoi(str.c_str());
                    break;
                case 2:
                    css.paddingBottom = atoi(str.c_str());
                    break;
                case 3:
                    css.paddingLeft = atoi(str.c_str());
                    break;
                default:
                    t2Log("padding中参数过多\n");
                    break;
                }

                index++;
                paddingStr = paddingM.suffix().str();
            }
        }
        else if(!stricmp(pro.c_str(), "padding-bottom"))
        {
            css.paddingBottom = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "padding-left"))
        {
            css.paddingLeft = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "padding-right"))
        {
            css.paddingRight = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "padding-top"))
        {
            css.paddingTop = atoi(decl->value.c_str());
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
            css.textColor.set(decl->value);
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
            css.hTextShadow = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "vTextShadow"))
        {
            css.vTextShadow = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "textShadowBlur"))
        {
            css.textShadowBlur = atoi(decl->value.c_str());
        }
        else if(!stricmp(pro.c_str(), "textShadowColor"))
        {
            // --!not supported
            css.textShadowColor.set(decl->value);
        }
    }
}
