#include <TattyUI/script/css/t2CSSParser.h>
#include <TattyUI/common/t2Settings.h>
#include<fstream>

namespace TattyUI
{
    t2CSSParser::t2CSSParser() :pos(0), bLoaded(false)
    {

    }

    t2CSSParser::t2CSSParser(const string& cssPath) : pos(0), bLoaded(false)
    {
        openFile(cssPath);
    }

    bool t2CSSParser::openFile(const string& cssPath)
    {
        ifstream fin(cssPath);
        if(!fin)
        {
            printf("open file.css failed!\n");
            bLoaded = false;
            return false;
        }

        string s;
        while(getline(fin, s))
        {
            css += s;
        }

        //cout << css << endl;

        bLoaded = true;
        return true;
    }

    long t2CSSParser::length() const
    {
        return css.length() > pos ? css.length() - pos : 0;
    }

    bool t2CSSParser::open()
    {
        // ^    字符串开始处
        // \s*  任意数量的空白符
        // 跳过任意长空格
        static const regex re(R"raw(^\{\s*)raw");

        return search(re);
    }

    // ^    字符串开始处
    // \}   找到一个}
    bool t2CSSParser::close()
    {
        static const regex re(R"raw(^\})raw");

        return search(re);
    }

    int t2CSSParser::parse()
    {
        if(!bLoaded)
        {
            t2PrintError("file.css haven't loaded yet, can't parse!\n");
            return 0;
        }

        comments();

        rules();

        return ruleList.size();
    }

    void t2CSSParser::set(const string& css)
    {
        this->css = css;
    }

    void t2CSSParser::whitespace()
    {
        // 删除空格 删除回车
        static const regex ws(R"raw(\s*)raw"), enter(R"raw([\r\n]*)raw");

        css = regex_replace(css, ws, "");

        css = regex_replace(css, enter, "");
    }

    bool t2CSSParser::search(const regex& re)
    {
        smatch m;
        return search(m, re);
    }

    // 在已匹配完的剩余字符串中正则搜索
    bool t2CSSParser::search(smatch& m, const regex& re)
    {
       // --!抄袭自CCSSLib->css.h->line:252
       std::string::const_iterator first = css.begin() + pos, last = css.end();
       bool found = std::regex_search(first, last, m, re);
       if(found)
       {
           const std::string& s = m[0];
           // 递进已匹配字符长度
           pos += s.length();
       }

       return found;
    }

    bool t2CSSParser::classSelector(string group, t2Rule *rule)
    {
        // 筛选类选择器(.开头) 伪类选择器(除头尾以外中间有:) 元素选择器(都无)
        static const regex classSelectorRE(R"raw(^\.([^:]+))raw"), pseudoSelectorRE(R"raw(:\w+)raw");
        smatch classSelectorM, pseudoSelectorM;
        // 类选择器
        if(regex_search(group, classSelectorM, classSelectorRE))
        {
            t2ClassSelector *classSelector = new t2ClassSelector();
            // --!not good!
            string className = classSelectorM[0];
            // delete the '.' 
            className = className.substr(1, className.length());

            classSelector->classSelector = className;

            if(regex_search(group, pseudoSelectorM, pseudoSelectorRE))
            {
                // --!not good!
                string pseudoName = pseudoSelectorM[0];

                pseudoName = pseudoName.substr(1, pseudoName.length());

                // delete the ':' 
                classSelector->pseudoSelector = pseudoName;
            }

            rule->classSelectors.push_back(classSelector);

            return true;
        }
 
        return false;
    }

    bool t2CSSParser::elementSelector(string group, t2Rule *rule)
    {
        static const regex pseudoSelectorRE(R"raw(:\w+)raw"), elementSelectorRE(R"raw(^([^:]+))raw");
        smatch pseudoSelectorM, elementSelectorM;

        // 元素选择器
        if(regex_search(group, elementSelectorM, elementSelectorRE))
        {
            t2ElementSelector *elementSelector = new t2ElementSelector();

            elementSelector->elementSelector = elementSelectorM[0];

            if(regex_search(group, pseudoSelectorM, pseudoSelectorRE))
            {
                // --!not good!
                string pseudoName = pseudoSelectorM[0];

                pseudoName = pseudoName.substr(1, pseudoName.length());

                // delete the ':' 
                elementSelector->pseudoSelector = pseudoName;
            }

            rule->elementSelectors.push_back(elementSelector);

            return true;
        }
        
        return false;
    }

    bool t2CSSParser::selectors(t2Rule *rule)
    {
        // selector
        // ^        字符串开始处
        // (
        //      [^\{]+   除{以外其他的一个或者多个字符
        // )
        // \{   结尾补上开头
        // 选择器名
        // 案例 
        // .body {}
        // #body {}
        // [body] {}
        // li strong {}
        string temp = css.substr(pos, css.length());

        static const regex selectorRE(R"raw(^([^\{])+\{)raw");
        smatch selectorM;

        // 确认selector存在且规范
        if(!regex_search(temp, selectorM, selectorRE))
        {
            printf("missing selector!\n");
            return false;
        }

        // 将其中的分组选择器筛选出
        // [^,]+        匹配除,外任何字符 可出现一次或多次
        // (?=,|\{)         后接,或者{
        // h1,h2:active,.button,.button:focus{}
        static const regex groupRE(R"raw([^,]+(?=,|\{))raw");
        smatch groupM;
        string groupString = selectorM[0];
        while(regex_search(groupString, groupM, groupRE))
        {
            string allSelector = groupM[0];

            // 类选择器+伪类选择器
            classSelector(allSelector, rule);
            
            // 元素选择器+伪类选择器
            elementSelector(allSelector, rule);

            groupString = groupM.suffix().str();
        }

        return true;
    }

    void t2CSSParser::declaration(t2Rule *rule)
    {
        while(1)
        {
            t2Declaration *declaration = new t2Declaration();
            // declaration
            // property
            // ^(\*?[-#/\*\w]+(\[[0-9a-z_-]+\])?)\s*
            // ^                    字符串开始
            // (
            //   \*?                  可选的*号
            //   [-#/\*\w]+           "-""#""\""*""字母数字下划线或汉字"出现一次或多次
            //   (
            //      \[[0-9a-z_-]+\]    "["+0~9|a~z|_~空格+"]"
            //   )?    可选的
            // )
            // \s*                  任意多空格
            static const regex propertyRE(R"raw(^(\*?[-#/\*\w]+(\[[0-9a-z_-]+\])?)\s*)raw");
            smatch propertyM;

            if(!search(propertyM, propertyRE))
                // 该选择器无任何属性
                return;

            // :筛选
            // ^:\s*
            // ^    字符串开始处
            // :    冒号
            // \s*  零次或者多次出现的空格
            static const regex colonRE(R"raw(^:\s*)raw");
            smatch colonM;
            if(!search(colonM, colonRE))
            {
                printf("property: missing':'\n");
                return;
            }

            declaration->attribute = propertyM[0];

            // value筛选
            // ^((?:'(?:\\'|.)*?'|\"(?:\\\"|.)*?\"|\([^\)]*?\)|[^\};])+)
            // ^
            // (
            //    (
            //        ?:            后面的制作匹配不做捕捉
            //        '(?:\\'|.)*?'             单引号围起来的内容或者任意字符 若前方有'，那么需要以'结尾
            //        |
            //        \"(?:\\\"|.)*?\"          双引号围起来的内容或者任意字符 若前方有"，那么需要以"结尾
            //        |
            //        \([^\)]*?\)               (开始 匹配除了)以外的任意字符 字符可以出现零次或者多次[^x] 可选的)
            //        |
            //        [^\};]                    匹配除了} ;以外的任意字符
            //    )
            //    +                 可以有零个或者多个上述值出现
            // )
            static const regex valueRE(R"raw(^((?:'(?:\\'|.)*?'|\"(?:\\\"|.)*?\"|\([^\)]*?\)|[^\};])+))raw");
            smatch valurM;
            if(!search(valurM, valueRE))
            {
                printf("property: missing value!\n");
                return;
            }

            declaration->value = valurM[0];

            // ^
            // [;\s]* 零个或多个空白符或;结尾
            static const regex semicolonRE(R"raw([;\s]*)raw");
            // ;存在与否不重要 可选
            search(semicolonRE);

            rule->declarations.push_back(declaration);
        }
     }

    void t2CSSParser::rules()
    {
        // 剩余字符串长度 > 0
        while(length() > 0)
        {
            t2Rule *rule = new t2Rule();

            selectors(rule);

            // --!此处有重复 可更进
            // selector
            // ^        字符串开始处
            // (
            //      [^\{]+   除{以外其他的一个或者多个字符
            // )+
            // 选择器名
            // 案例 
            // .body {}
            // #body {}
            // [body] {}
            // li strong {}
            static const regex selectorRE(R"raw(^([^\{])+)raw");
            smatch selectorM;
            // 实际匹配处
            if(!search(selectorM, selectorRE))
            {
                printf("missing selector!\n");
                return;
            }

            //cout << selectorM[0] << endl;

            if(!open())
            {
                printf("missing '{'!\n");
                return;
            }

            declaration(rule);

            if(!close())
            {
                printf("missing '}'!\n");
                return;
            }

            ruleList.push_back(rule);
        }
    }

    void t2CSSParser::comments()
    {
        // 注释正则表达式
        // --!http://blog.ostermiller.org/find-comment
        // /\*([\n\r]|[^*]|(\*+([\n\r]|[^*/])))*\*+/
        // /\*
        // (
        // 	[\n\r]
        // 	|
        // 	[^*]    除*以外
        // 	|
        // 	(
        // 		\*+    一个或多个*
        // 		(
        // 			[\n\r]
        // 			|
        // 			[^*/]    除了*/以外
        // 		)
        // 	)
        // )*
        // \*+      一个或多个*
        // /        /
        static const regex re(R"raw(/\*([\n\r]|[^*]|(\*+([\n\r]|[^*/])))*\*+/)raw");
        
        smatch m;

        string temp = css;
        // 遍历注释
        while(regex_search(temp, m, re))
        {
            t2Comment *c = new t2Comment();

            c->text = m[0];

            commentList.push_back(c);

            // 取后缀继续 相当于逐行下潜
            temp = m.suffix().str();
        }

        // 删除注释
        css = regex_replace(css, re, "");

        // 删除空格 删除回车
        whitespace();
    }
}


