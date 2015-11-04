#include <TattyUI/script/html/t2HTMLParser.h>
#include <TattyUI/div/t2DivController.h>
//#include <TattyUI/script/css/t2CSSController.h>
#include <TattyUI/common/t2Window.h>

#include <LinearList/t3Queue.h>
#include <fstream>

#ifdef T2_HTMLPARSER_GUMBO
#include <gumbo.h>
#endif

namespace TattyUI
{
    class t2Element
    {
    public:
        t2Element(GumboNode* node) :node(node)
        {
            div = new t2Div();
        }

        GumboNode* node;
        t2Div* div;
    };

    class t2HTMLParser::t2LabelParser
    {
    public:
        void parse(const char* html);

        vector<string> cssFilePaths;

    private:
        void head(GumboNode *h);

        void body(GumboNode *b);
    };

    void t2HTMLParser::t2LabelParser::parse(const char* html)
    {
        GumboOutput* output = gumbo_parse(html);

        GumboNode *root = output->root;

        if(root->type != GUMBO_NODE_ELEMENT)
        {
            t2PrintError("html格式有误");
            return;
        }

        // find head
        GumboVector *rootChildren = &root->v.element.children;
        GumboNode *h = NULL, *b = NULL;
        for(int i = 0; i < rootChildren->length; i++)
        {
            GumboNode *child = (GumboNode *) rootChildren->data[i];
            if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD)
                h = child;
            else if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_BODY)
                b = child;
        }

        if(!h)
        {
            t2PrintError("html文件缺少<head>标签");
            return;
        }
        head(h);

        // find body
        if(!b)
        {
            t2PrintError("html文件缺少<body>标签");
            return;
        }
        body(b);

        gumbo_destroy_output(&kGumboDefaultOptions, output);
    }

    void t2HTMLParser::t2LabelParser::head(GumboNode *h)
    {
        GumboVector *headChildren = &h->v.element.children;

        for(int i = 0; i < headChildren->length; i++)
        {
            GumboNode *child = (GumboNode *) headChildren->data[i];

            // find title
            if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE)
            {
                if(child->v.element.children.length != 1)
                {
                    t2PrintError("<empty title>");
                    return;
                }

                // title无子节点
                GumboNode *title = (GumboNode *) child->v.element.children.data[0];
                if(title->type != GUMBO_NODE_TEXT && title->type != GUMBO_NODE_WHITESPACE)
                {
                    t2PrintError("标题只可为空或文字");
                    return;
                }

                t2Window::getInstance()->window->setTitle(title->v.text.text);
            }
            // find css file
            else if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_LINK)
            {
                GumboAttribute *href = gumbo_get_attribute(&child->v.element.attributes, "href");
                if(!href)
                    t2PrintError("<link>缺失href属性");

                cssFilePaths.push_back(href->value);
            }
        }
    }

    void t2HTMLParser::t2LabelParser::body(GumboNode *b)
    {
        static t3Queue<t2Element*> queue;
        t2Element* element = new t2Element(b);

        // --!这里body下有一个隐藏的div，长宽与窗口一致
        string rootID = getRootDivGlobalID();
        t2DivController::getInstance()->addDiv(rootID, element->div);
        t2DivController::getInstance()->setRoot(rootID);
        element->div->normal.width = t2GetWindowWidth();
        element->div->normal.height = t2GetWindowHeight();
        element->div->hover = element->div->normal;
        element->div->active = element->div->normal;

        queue.push(element);
        for(;;)
        {
            t2Element* e;
            if(queue.isEmpty()) e = NULL;
            else e = queue.pop();

            if(e)
            {
                GumboNode* child = e->node;
                // find div
                if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_DIV)
                {
                    t2Div *div = e->div;

                    // find className
                    GumboAttribute *className = gumbo_get_attribute(&child->v.element.attributes, "class");
                    div->className = className->value;
                    
                    // text
                    GumboNode *content = (GumboNode *) child->v.element.children.data[0];
                    if(content->type == GUMBO_NODE_TEXT || content->type == GUMBO_NODE_WHITESPACE)
                    {
                        div->normal.text = content->v.text.text;
                        div->hover.text = content->v.text.text;
                        div->active.text = content->v.text.text;
                    }
                    
                    // find id
                    // not supported
                    string id;
                    GumboAttribute *idName = gumbo_get_attribute(&child->v.element.attributes, "id");
                    if(idName)
                        div->className = idName->value;
                    else
                        id = getDivGlobalID();

                    // 新增div
                    t2DivController::getInstance()->addDiv(id, div);
                }

                t2Div *brother = NULL;
                // 将所有兄弟结点入队列
                for(int i = 0; i < child->v.element.children.length; i++)
                {
                    GumboNode *c = (GumboNode *) child->v.element.children.data[i];
                    if(c->type == GUMBO_NODE_ELEMENT && 
                        c->v.element.tag == GUMBO_TAG_DIV)
                    {
                        // 多叉树的复制
                        t2Element* element = new t2Element(c);
                        // 第一个兄弟结点
                        if(!brother)
                        {
                            // 子节点
                            e->div->child = element->div;
                            element->div->parent = e->div;
                        }
                        else
                        {
                            // 父节点
                            element->div->parent = e->div;
                            brother->next = element->div;
                        }

                        // 更新兄弟结点
                        brother = element->div;
                        queue.push(element);
                    }
                }
            }
            else
                break;
        }
    }


    // htmlParser
    t2HTMLParser::t2HTMLParser() :bLoaded(false)
    {
        parser = new t2LabelParser();
    }

    t2HTMLParser::t2HTMLParser(string& htmlPath) : bLoaded(false)
    {
        parser = new t2LabelParser();

        openFile(htmlPath);
    }

    bool t2HTMLParser::openFile(string& htmlPath)
    {
        ifstream fin(htmlPath);
        if(!fin)
        {
            printf("open file.html failed!\n");
            bLoaded = false;
            return false;
        }

        string s;
        while(getline(fin, s))
        {
            html += s;
        }

        bLoaded = true;
        return true;
    }

    void t2HTMLParser::parse()
    {
        if(!bLoaded)
            t2PrintError("html文件未被加载, 无法解析");

        parser->parse(html.c_str());

        // --!设计失误 拷贝css地址
        for(auto p : parser->cssFilePaths)
            cssFilePaths.push_back(p);
    }

    void t2HTMLParser::set(string& html)
    {
        this->html = html;
    }
}