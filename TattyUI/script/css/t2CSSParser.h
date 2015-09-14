#ifndef T2_CSSPARSER_H
#define T2_CSSPARSER_H

#include <string>
#include <vector>
#include <regex>

namespace TattyUI
{
    using namespace std;

    class t2Declaration
    {
    public:
        // 属性名 属性值
        string attribute;
        string value;
    };

    class t2Comment
    {
    public:
        string text;
    };

    // selector
    class t2PseudoSelector
    {
    public:
        // 伪类选择器
        string pseudoSelector;
    };

    class t2ClassSelector :public t2PseudoSelector
    {
    public:
        // 类选择器
        string classSelector;
    };

    class t2ElementSelector :public t2PseudoSelector
    {
    public:
        // 元素选择器
        string elementSelector;
    };

    class t2Rule
    {
    public:
        // 类选择器
        vector<t2ClassSelector*> classSelectors;

        // 元素选择器
        vector<t2ElementSelector*> elementSelectors;

        vector<t2Declaration*> declarations;
    };

    class t2CSSParser
    {
    public:
        t2CSSParser();
        t2CSSParser(const string& cssPath);

        bool openFile(const string& cssPath);

        int parse();

        void set(const string& css);

        string css;

        vector<t2Comment*> commentList;

        vector<t2Rule*> ruleList;

    protected:
        void whitespace();

        bool open();

        bool close();

        // 找到待匹配字符串并跳过之
        bool search(const regex& re);

        bool search(smatch& m, const regex& re);

        // 找到所有rule -> property: value; 入list
        void rules();

        // 找到所有注释删除，并入vector
        void comments();

        // 只做匹配，不更进pos
        bool selectors(t2Rule *rule);

        void declaration(t2Rule *rule);

        // 剩余字符串长度
        long length() const;

        bool classSelector(string group, t2Rule *rule);

        bool elementSelector(string group, t2Rule *rule);

        // 当前遍历到的字符串位置
        long pos;

        bool bLoaded;
    };
}



#endif