// License: MIT
// based on https://github.com/reworkcss/css-parse & https://github.com/reworkcss/css-stringify
#pragma once
#include <string>
#include <vector>
#include <regex>
#include <memory>
#include <iostream>
#include <sstream>

#include <functional>

struct StyleSheet
{
    // data objects
    struct Node
    {
        virtual std::string to_string(StyleSheet *sheet) const = 0;
    };
    using NodePtr = std::shared_ptr<Node>;
    // 等同于std::vector<Node*>
    using NodeList = std::vector<NodePtr>;
    using StringList = std::vector<std::string>;

    // 修剪掉string头尾中的 回车 换行 空格 格式 符号 并返回
    static std::string trim(const std::string& s, const std::string& whitespace = "\r\n \t")
    {
        const auto first = s.find_first_not_of(whitespace);
        if(first == std::string::npos) return "";

        const auto last = s.find_last_not_of(whitespace);
        const auto range = last - first + 1;
        return s.substr(first, range);
    }

    int level_;
    NodeList rules_;

    // --!
    std::function<std::string(const std::string&)> selector_decorator_;

    StyleSheet() : level_(0) {}

    // 生成一个给定缩进长度的string
    void indent(int level) { level_ += level; }
    std::string indent() const { std::string s; for(int i = 0; i < level_; ++i) s += ' '; return s; }

    std::string to_string(const NodeList& nodes, const std::string& delim = "\n\n")
    {
        std::string s;
        for(auto& node : nodes)
        {
            if(!s.empty()) s += delim;
            // 基类指针通过虚函数调用到派生类函数
            s += node->to_string(this);
        }
        return s;
    }
    std::string to_string() { return to_string(rules_); }

    struct SimpleNode : public Node
    {
        std::string tag_, name_;
        SimpleNode(const std::string& tag, const std::string& name) : tag_(tag), name_(name) {}
        virtual std::string to_string(StyleSheet *sheet) const { return "@" + tag_ + " " + name_ + ";"; }
    };

    struct Namespace : public SimpleNode { Namespace(const std::string& name) : SimpleNode("namespace", name) {} };
    struct Import : public SimpleNode { Import(const std::string& name) : SimpleNode("import", name) {} };
    struct Charset : public SimpleNode { Charset(const std::string& name) : SimpleNode("charset", name) {} };
    struct Comment : public Node
    {
        // 实际注释内容
        std::string text_;
        Comment(const std::string& s) : text_(s) {}
        virtual std::string to_string(StyleSheet *) const { return "/*" + text_ + "*/"; }
    };

    struct RuleSet : public SimpleNode 
    {
        std::string vendor_;
        NodeList rules_;
        RuleSet(const std::string& tag, const std::string& name, NodeList&& rules, const std::string& vendor = "") : SimpleNode(tag, name), vendor_(vendor), rules_(rules) {}
        std::string to_string(StyleSheet *sheet)  const
        {
            std::string s = "@" + vendor_ + tag_ + " " + name_ + " {\n";
            sheet->indent(1);
            for(auto rule : rules_)
            {
                s += rule->to_string(sheet);
                if(!s.empty()) s += "\n\n";
            }
            sheet->indent(-1);
            s += "\n}";
            return s;
        }
    };

    struct Media : public RuleSet { Media(const std::string& name, NodeList&& rules) : RuleSet("media", name, std::forward<NodeList>(rules)) {} };
    struct Supports : public RuleSet { Supports(const std::string& name, NodeList&& rules) : RuleSet("supports", name, std::forward<NodeList>(rules)) {} };
    struct Document : public RuleSet { Document(const std::string& name, const std::string& vendor, NodeList&& rules) : RuleSet("document", name, std::forward<NodeList>(rules), vendor) {} };
    struct Host : public RuleSet { Host(NodeList&& rules) : RuleSet("host", "", std::forward<NodeList>(rules)) {} };

    struct Declaration : public Node
    {
        std::string name_, value_;
        Declaration(const std::string& name, const std::string& value) : name_(name), value_(value) {}
        virtual std::string to_string(StyleSheet *sheet) const { return sheet->indent() + name_ + ": " + value_ + ";"; }
    };

    struct Keyframe : public Node
    {
        StringList values_;
        NodeList declarations_;

        Keyframe(StringList&& values, NodeList&& declarations) : values_(values), declarations_(declarations) {}
        std::string to_string(StyleSheet *sheet) const
        {
            std::string s;
            for(auto& val : values_)
            {
                if(!s.empty()) s += ", ";
                s += val;
            }
            s += "{\n";
            sheet->indent(1);
            s += sheet->to_string(declarations_, "\n");
            sheet->indent(-1);
            s += "\n";
            s += sheet->indent() + "}\n";
            return s;
        }
    };

    struct Keyframes : public RuleSet
    {
        Keyframes(const std::string& name, const std::string& vendor, NodeList&& keyframes) : RuleSet("keyframes", name, std::forward<NodeList>(keyframes), vendor) {}
        std::string to_string(StyleSheet *sheet) const
        {
            std::string s = "@" + vendor_ + tag_ + " " + name_ + " {\n";
            sheet->indent(1);
            s += sheet->to_string(rules_, "\n");
            sheet->indent(-1);
            s += '}';

            return s;
        }
    };

    // 选择器 + 实际内容声明
    struct Rule : public Node
    {
        StringList selectors_;
        NodeList declarations_;

        Rule(StringList&& sel, NodeList&& decls) : selectors_(sel), declarations_(decls) {}
        std::string to_string(StyleSheet *sheet) const
        {
            if(selectors_.empty() || declarations_.empty())
                return "";
            auto indent = sheet->indent();
            auto selector_decorator = sheet->selector_decorator_;
            std::string s;
            for(const auto& sel : selectors_)
            {
                if(!s.empty()) s += ",\n";
                s += indent + (selector_decorator ? selector_decorator(sel) : sel);
            }

            s += " {\n";
            sheet->indent(1);
            s += sheet->to_string(declarations_, "\n");
            sheet->indent(-1);

            s += "\n" + sheet->indent() + '}';
            return s;
        }
    };

    struct Page : public Rule
    {
        Page(StringList&& sel, NodeList&& decls) : Rule(std::forward<StringList>(sel), std::forward<NodeList>(decls)) {}
        std::string to_string(StyleSheet *sheet) const
        {
            std::string s;
            for(const auto& sel : selectors_)
            {
                if(!s.empty()) s += ", ";
                s += sel;
            }
            if(!s.empty()) s += " ";

            std::string r = "@page" + s + "{\n";
            sheet->indent(1);
            r += sheet->to_string(declarations_, "\n");
            sheet->indent(-1);
            r += "\n}";

            return r;
        }
    };

    struct Parser
    {
        using RE = std::regex;
        // /\*            /*
        // [^\*]*         匹配除了*的字符 可以出现零次或者多次
        // \*+            一个或者多个*
        // (
        //     [^/\*]       匹配除了/*的字符
        //     [^\*]*       匹配除了*的字符 可以出现零次或者多次
        //     \*+          可以出现一次或者多次的*
        // )
        // */
        const RE commentre_ = RE(R"raw(/\*[^\*]*\*+([^/\*][^\*]*\*+)*/)raw");

        // 当前匹配到css_中的指针
        long pos_;
        // 实际css存储string
        std::string css_;
        Parser(const std::string& css) : pos_(0), css_(css) {}
        
        // 剩余字符串长度
        long length() const { return css_.length() > pos_ ? css_.length() - pos_ : 0; }
        // 返回当前指针指向处为起始点偏移i位置的字符串
        char char_at(int i) const { return css_[pos_ + i]; }

        NodeList rules()
        {
            NodeList _rules;
            whitespace();
            comments(_rules);

            // 多个 selector{
            //         property: value; 
            //         ...other declaration
            //     }
            //     ......other selector
            NodePtr node;
            // 剩余字符串长度 > 0 && 选择器不能为匿名 即第一个字符不得为} && (@规则 || 选择器规则)
            while(length() > 0 && char_at(0) != '}' && ((node = atrule()) || (node = rule())))
            {
                _rules.push_back(node);
                comments(_rules);
            }

            return _rules;
        }

        // 给定正则表达式 在css文件中直接全局匹配
        bool search(const std::regex& re) { std::smatch m; return search(re, m); }
        bool search(const std::regex& re, std::smatch& m)
        {
            std::string::const_iterator first = css_.begin() + pos_, last = css_.end();
            bool found = std::regex_search(first, last, m, re);
            if(found)
            {
                const std::string& s = m[0];
                pos_ += s.length();
            }

            return found;
        }

        void error(const std::string& msg) { std::cerr << msg << std::endl; }

        template <typename N> NodePtr P(const N& node) { whitespace(); return std::dynamic_pointer_cast<Node>(node); }

        // ^    字符串开始处
        // \s*  任意数量的空白符
        // 跳过任意长空格
        bool whitespace() { static const std::regex _RE_ = RE(R"raw(^\s*)raw"); return search(_RE_); }
        // ^    字符串开始处
        // \{   { 
        // \s*  任意数量的空格
        bool open() { static const std::regex _RE_ = RE(R"raw(^\{\s*)raw"); return search(_RE_); }
        // ^    字符串开始处
        // \}   找到一个}
        bool close() { static const std::regex _RE_ = RE(R"raw(^\})raw"); return search(_RE_); }

        // 通过分隔符,来逐读取标记符
        static std::vector<std::string> split(const std::string& s, char delim)
        {
            std::vector<std::string> result;
            std::istringstream buf(s);
            for(std::string token; std::getline(buf, token, ',');) result.push_back(token);
            return result;
        }

        // 向des尾部插入src
        template <typename T>
        static void concat(std::vector<T>& des, std::vector<T>&& src) { des.insert(des.end(), std::make_move_iterator(src.begin()), std::make_move_iterator(src.end())); }

        // 找到所有注释并入vector
        NodeList comments(NodeList& rules) { return comments(&rules); }
        NodeList comments(NodeList *_rules = nullptr)
        {
            NodeList r;
            NodeList& rules = _rules ? *_rules : r;

            NodePtr c;
            while((c = comment()))
            {
                rules.push_back(c);
            }
            return rules;
        }

        NodePtr comment()
        {
            // 起始位置为/*
            if(char_at(0) != '/' || char_at(1) != '*')
                return nullptr;

            // 结尾处为*/
            size_t i = 2;
            while(i + 1 < length() && (char_at(i) != '*' || char_at(i + 1) != '/'))
                ++i;

            if(i + 1 >= length())
                return nullptr;

            i += 2;
            // pos+2 跳过/* 长度为i-2-2即为减去/**/四个字符长度
            std::string s = css_.substr(2 + pos_, i - 2 - 2);
            // 跳过注释部分
            pos_ += i;

            return P(std::make_shared<Comment>(s));
        }

        // 找到选择器
        StringList selector()
        {
            // ^        字符串开始处
            // (
            //      [^\{]+   除{以外其他的一个或者多个字符
            // )
            // 选择器名
            // 案例 
            // .body {}
            // #body {}
            // [body] {}
            // li strong {}
            static const std::regex _RE_ = RE(R"raw(^([^\{]+))raw");
            std::smatch m;
            bool found = search(_RE_, m);
            if(!found) return{};

            // 删除所有注释
            /* @fix Remove all comments from selectors
             * http://ostermiller.org/findcomment.html */
            std::string s = trim(m[0]);
            // \/\*         /*
            // (
            //     [^*]         除*以外的字符     
            //     |
            //     [\r\n]           含有一个换行或者回车
            //     |
            //     (
            //         \*+          一个或者多个*
            //         (
            //             [^*/]            匹配除了*/以外的符号    
            //             |
            //             [\r\n]           含有一个换行或者回车
            //         )
            //     )
            // )*
            // \*\/+            */
            // /g   
            // 案例
            // body{
            //     /*Hello World*/ 
            //}
            s = std::regex_replace(s, RE(R"(\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*\/+/g)"), std::string(""));
            // \s*          零个或多个空格
            // ,
            // \s*          零个或多个空格
            // 案例
            // h1, h2, h3, h4{
            //     color: green;
            // }
            s = std::regex_replace(s, RE(R"raw(\s*,\s*)raw"), std::string(","));

            return split(s, ',');
        }

        NodePtr declaration()
        {
            // property
            std::smatch mp;
            // ^                    字符串开始
            // (
            //   \*?                  可选的*号
            //   [-#/\*\w]+           "-""#""\""*""字母数字下划线或汉字"出现一次或多次
            //   (
            //      \[[0-9a-z_-]+\]    "["+0~9|a~z|_~空格+"]"
            //   )?    可选的
            // )
            // \s*                  任意多空格
            static const std::regex _RE0_ = RE(R"raw(^(\*?[-#/\*\w]+(\[[0-9a-z_-]+\])?)\s*)raw");
            bool found = search(_RE0_, mp);
            if(!found) return nullptr;

            std::string prop = trim(mp[0]);
            std::regex_replace(prop, commentre_, std::string(""));

            // ^    字符串开始处
            // :    冒号
            // \s*  零次或者多次出现的空格
            static const std::regex _RE1_ = RE(R"raw(^:\s*)raw");
            found = search(_RE1_);
            if(!found) { error("property missing ':'"); return nullptr; }

            // value
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
            std::smatch mv;
            static const std::regex _RE2_ = RE(R"raw(^((?:'(?:\\'|.)*?'|\"(?:\\\"|.)*?\"|\([^\)]*?\)|[^\};])+))raw");
            found = search(_RE2_, mv);
            if(!found) { error("property missing value"); return nullptr; }

            std::string val = trim(mv[0]);
            std::regex_replace(val, commentre_, std::string(""));

            NodePtr n = P(std::make_shared<Declaration>(prop, val));

            // ^
            // [;\s]* 零个或多个空白符或;结尾
            static const std::regex _RE3_ = RE(R"raw(^[;\s]*)raw");
            search(_RE3_);
            return n;
        }

        // 找到所有 property: value; 入list
        NodeList declarations(bool braced = true)
        {
            NodeList decls;

            if(braced && !open()) { error("missing '{'"); return{}; }
            comments(decls);

            // declarations
            // 多个property: value;声明
            NodePtr decl;
            while((decl = declaration()))
            {
                decls.push_back(decl);
                comments(decls);
            }

            if(braced && !close()) { error("missing '}'"); return{}; }

            return decls;
        }

        NodePtr keyframe()
        {
            StringList vals;

            while(true)
            {
                std::smatch m;
                bool found = search(RE(R"raw(^((\d+\.\d+|\.\d+|\d+)%?|[a-z]+)\s*)raw"), m);
                if(found)
                {
                    vals.push_back(m[1]);
                }
                search(RE(R"raw(^,\s*)raw"));
            }

            if(vals.empty()) return nullptr;

            return P(std::make_shared<Keyframe>(std::move(vals), declarations()));
        }

        NodePtr atkeyframes()
        {
            std::smatch m;
            // ^    
            // @            字符@
            // ([-\w]+)     出现一次或者多次的字符-或者字母数字下划线汉字
            // ?keyframes   可选的keyframe关键字
            //  *           紧跟零次或者多次的空格
            // 
            // 案例匹配@-moz-keyframes
            // @-moz-keyframes mymove
            // {
            //    ...
            // }
            bool found = search(RE(R"raw(^@([-\w]+)?keyframes *)raw"), m);
            if(!found) return nullptr;
            auto vendor = trim(m[1]);

            // identifier
            std::smatch mi;
            // ^
            // (
            // [-\w]+       字符-或者字母数字下划线汉字 上述字符至少出现一次或者多次
            // )            
            // \s*          可接零次或者多次的空格
            // 
            // 案例匹配mymove
            // @-moz-keyframes mymove
            // {
            //    ...
            // }
            found = search(RE(R"raw(^([-\w]+)\s*)raw"), mi);
            if(!found) { error("@keyframes missing name"); return nullptr; }
            auto name = mi[1];

            // keyframes规则后是否包裹成对的{}
            if(!open()) { error("@keyframes missing '{'"); return nullptr; }

            NodePtr frame;
            auto frames = comments();
            while((frame = keyframe()))
            {
                frames.push_back(frame);
                concat(frames, comments());
            }

            if(!close()) { error("@keyframes missing '}'"); return nullptr; }

            return P(std::make_shared<Keyframes>(name, vendor, std::move(frames)));
        }

        // --!@supports host media page document规则暂不考虑 正则表达式语法规则类似keyframes
        NodePtr atsupports()
        {
            std::smatch m;
            bool found = search(RE(R"raw(^@supports *([^{]+))raw"), m);

            if(!found) return nullptr;
            auto supports = trim(m[1]);

            if(!open()) { error("@supports missing '{'"); return nullptr; }

            auto style = comments();
            concat(style, rules());

            if(!close()) { error("@supports missing '}'"); return nullptr; }

            return P(std::make_shared<Supports>(supports, std::move(style)));
        }

        NodePtr athost()
        {
            bool found = search(RE(R"raw(^@host *)raw"));

            if(!found) return nullptr;
            if(!open()) { error("@host missing '{'"); return nullptr; }

            auto style = comments();
            concat(style, rules());

            if(!close()) { error("@host missing '}'"); return nullptr; }

            return P(std::make_shared<Host>(std::move(style)));
        }

        NodePtr atmedia()
        {
            std::smatch m;
            bool found = search(RE(R"raw(^@media *([^{]+))raw"), m);

            if(!found) return nullptr;
            auto media = trim(m[1]);

            if(!open()) { error("@media missing '{'"); return nullptr; }

            auto style = comments();
            concat(style, rules());

            if(!close()) { error("@media missing '}'"); return nullptr; }

            return P(std::make_shared<Media>(media, std::move(style)));
        }

        NodePtr atpage()
        {
            bool found = search(RE(R"raw(^@page *)raw"));
            if(!found) return nullptr;

            auto sel = selector();

            if(!open()) { error("@page missing '{'"); return nullptr; }
            auto decls = comments();

            // declarations
            NodePtr decl;
            while((decl = declaration()))
            {
                decls.push_back(decl);
                concat(decls, comments());
            }

            if(!close()) { error("@page missing '}'"); return nullptr; }

            return P(std::make_shared<Page>(std::move(sel), std::move(decls)));
        }

        NodePtr atdocument()
        {
            std::smatch m;
            bool found = search(RE(R"raw(^@([-\w]+)?document *([^{]+))raw"), m);
            if(!found) return nullptr;

            auto vendor = trim(m[1]);
            auto doc = trim(m[2]);

            if(!open()) { error("@document missing '{'"); return nullptr; }

            auto style = comments();
            concat(style, rules());

            if(!close()) { error("@document missing '}'"); return nullptr; }

            return P(std::make_shared<Document>(doc, vendor, std::move(style)));
        }

        template <typename T> NodePtr _atrule(const std::string& tag)
        {
            std::smatch m;
            // ^
            // @
            // tag      外部给出的tag字符串 外部给出的 规则 关键字
            //  *       零次或者多次的空格
            // (
            //     [^;\n]+    匹配字符串的开始 紧跟; \n者  
            // )
            // ;
            //
            // 案例 rule tag = "hello"
            // @hello okay
            // {
            // }
            bool found = search(RE("^@" + tag + " *([^;\n]+);"), m);
            if(!found) return nullptr;

            auto name = trim(m[1]);
            return P(std::make_shared<T>(name));
        }

        // 导入规则@import @charset @namespace
        NodePtr atimport() { return _atrule<Import>("import"); }
        NodePtr atcharset() { return _atrule<Charset>("charset"); }
        NodePtr atnamespace() { return _atrule<Namespace>("namespace"); }

        NodePtr atrule()
        {
            if(char_at(0) != '@') return nullptr;

            // 类似switch一路筛选
            auto  p = atkeyframes();
            if(p) return p; else p = atmedia();
            if(p) return p; else p = atsupports();
            if(p) return p; else p = atimport();
            if(p) return p; else p = atcharset();
            if(p) return p; else p = atnamespace();
            if(p) return p; else p = atdocument();
            if(p) return p; else p = atpage();
            if(p) return p; else p = athost();
            return nullptr;
        }

        NodePtr rule()
        {
            auto sel = selector();
            if(sel.empty()) { error("selector missing"); return nullptr; }

            comments();
            return P(std::make_shared<Rule>(std::move(sel), declarations()));
        }
    };

    int parse(const std::string& css)
    {
        Parser p(css);
        this->rules_ = p.rules();
        return this->rules_.size();
    }

    NodeList parse_style(const std::string& style)
    {
        Parser p(style);
        return p.declarations();
    }
};

