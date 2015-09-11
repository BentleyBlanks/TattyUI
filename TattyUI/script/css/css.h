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
  using NodeList = std::vector<NodePtr>;
  using StringList = std::vector<std::string>;

  static std::string trim(const std::string& s, const std::string& whitespace = "\r\n \t")
  {
      const auto first = s.find_first_not_of(whitespace);
      if (first == std::string::npos) return "";

      const auto last = s.find_last_not_of(whitespace);
      const auto range = last - first + 1;
      return s.substr(first, range);
  }

  int level_;
  NodeList rules_;

  std::function<std::string(const std::string&)> selector_decorator_;

  StyleSheet(): level_(0) {}

  void indent(int level) { level_ += level; } 
  std::string indent() const { std::string s; for (int i=0; i<level_; ++i) s += ' '; return s; }

  std::string to_string(const NodeList& nodes, const std::string& delim = "\n\n")
  {
    std::string s;
    for (auto& node: nodes) {
      if (!s.empty()) s += delim;
      s += node->to_string(this);
    }
    return s;
  }
  std::string to_string() { return to_string(rules_); }

  struct SimpleNode: public Node
  {
    std::string tag_, name_;
    SimpleNode(const std::string& tag, const std::string& name): tag_(tag), name_(name) {}
    virtual std::string to_string(StyleSheet *sheet) const { return "@" + tag_ +  " " + name_ + ";"; }
  };

  struct Namespace: public SimpleNode { Namespace(const std::string& name): SimpleNode("namespace", name) {} };
  struct Import: public SimpleNode { Import(const std::string& name): SimpleNode("import", name) {} };
  struct Charset: public SimpleNode { Charset(const std::string& name): SimpleNode("charset", name) {} };
  struct Comment: public Node
  {
    std::string text_;
    Comment(const std::string& s) : text_(s) {}
    virtual std::string to_string(StyleSheet *) const { return "/*" + text_ + "*/"; }
  }; 

  struct RuleSet: public SimpleNode
  {
    std::string vendor_;
    NodeList rules_;
    RuleSet(const std::string& tag, const std::string& name, NodeList&& rules, const std::string& vendor=""): SimpleNode(tag, name), vendor_(vendor), rules_(rules) {}
    std::string to_string(StyleSheet *sheet)  const
    {
      std::string s = "@" + vendor_ + tag_ + " " + name_ + " {\n";
      sheet->indent(1); 
      for (auto rule: rules_) {
        s += rule->to_string(sheet);
        if (! s.empty()) s += "\n\n";
      }
      sheet->indent(-1); 
      s += "\n}";
      return s;
    } 
  };

  struct Media: public RuleSet { Media(const std::string& name, NodeList&& rules): RuleSet("media", name, std::forward<NodeList>(rules)) {} };
  struct Supports: public RuleSet { Supports(const std::string& name, NodeList&& rules): RuleSet("supports", name, std::forward<NodeList>(rules)) {} };
  struct Document: public RuleSet { Document(const std::string& name, const std::string& vendor, NodeList&& rules): RuleSet("document", name, std::forward<NodeList>(rules), vendor) {} };
  struct Host: public RuleSet { Host(NodeList&& rules): RuleSet("host", "", std::forward<NodeList>(rules)) {} };

  struct Declaration: public Node
  {
    std::string name_, value_;
    Declaration(const std::string& name, const std::string& value): name_(name), value_(value) {}
    virtual std::string to_string(StyleSheet *sheet) const { return sheet->indent() + name_ + ": " + value_ + ";"; }
  };

  struct Keyframe: public Node 
  {
    StringList values_;
    NodeList declarations_;

    Keyframe(StringList&& values, NodeList&& declarations): values_(values), declarations_(declarations) {}
    std::string to_string(StyleSheet *sheet) const
    {
      std::string s;
      for (auto& val: values_) {
        if (!s.empty()) s += ", ";
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
  
  struct Keyframes: public RuleSet
  { 
    Keyframes(const std::string& name, const std::string& vendor, NodeList&& keyframes): RuleSet("keyframes", name, std::forward<NodeList>(keyframes), vendor) {} 
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

  struct Rule: public Node
  {
    StringList selectors_;
    NodeList declarations_;

    Rule(StringList&& sel, NodeList&& decls): selectors_(sel), declarations_(decls) {}
    std::string to_string(StyleSheet *sheet) const 
    {
      if (selectors_.empty() || declarations_.empty()) 
        return "";
      auto indent = sheet->indent();
      auto selector_decorator = sheet->selector_decorator_;
      std::string s;
      for (const auto& sel: selectors_) {
        if (!s.empty()) s += ",\n";
        s += indent + (selector_decorator? selector_decorator(sel): sel);
      }

      s += " {\n";
      sheet->indent(1);
      s += sheet->to_string(declarations_, "\n");
      sheet->indent(-1);

      s += "\n" + sheet->indent() + '}';
      return s;
    }
  };

  struct Page: public Rule
  {
    Page(StringList&& sel, NodeList&& decls): Rule(std::forward<StringList>(sel), std::forward<NodeList>(decls)) {}
    std::string to_string(StyleSheet *sheet) const
    {
      std::string s;
      for (const auto& sel: selectors_) {
        if (!s.empty()) s += ", ";
        s += sel;
      }
      if (!s.empty()) s += " ";
      
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
    const RE commentre_ = RE(R"raw(/\*[^\*]*\*+([^/\*][^\*]*\*+)*/)raw");

    long pos_;
    std::string css_;
    Parser(const std::string& css): pos_(0), css_(css) {}

    long length() const { return css_.length() > pos_? css_.length() - pos_ : 0; }
    char char_at(int i) const { return css_[pos_ + i]; }

    NodeList rules()
    {
      NodeList _rules;
      whitespace();
      comments(_rules);

      NodePtr node;
      while (length() > 0  && char_at(0) != '}' && ((node = atrule()) || (node = rule()))) {
        _rules.push_back(node);
        comments(_rules);
      }

      return _rules;
    }

    bool search(const std::regex& re) { std::smatch m; return search(re, m); }
    bool search(const std::regex& re, std::smatch& m)
    {
      std::string::const_iterator first = css_.begin() + pos_, last = css_.end();
      bool found = std::regex_search(first, last, m, re);
      if (found) {
        const std::string& s = m[0];
        pos_ += s.length();
      }

      return found;
    }

    void error(const std::string& msg) { std::cerr << msg << std::endl; }

    template <typename N> NodePtr P(const N& node) { whitespace(); return std::dynamic_pointer_cast<Node>(node); }

    bool whitespace() { static const std::regex _RE_ = RE(R"raw(^\s*)raw"); return search(_RE_); }
    bool open() { static const std::regex _RE_ = RE(R"raw(^\{\s*)raw"); return search(_RE_); }
    bool close() { static const std::regex _RE_ = RE(R"raw(^\})raw"); return search(_RE_); }

    static std::vector<std::string> split(const std::string& s, char delim) 
    {
      std::vector<std::string> result;
      std::istringstream buf(s);
      for(std::string token; std::getline(buf, token, ','); ) result.push_back(token);
      return result;
    }

    template <typename T>
    static void concat(std::vector<T>& des, std::vector<T>&& src) { des.insert(des.end(), std::make_move_iterator(src.begin()), std::make_move_iterator(src.end()));}

    NodeList comments(NodeList& rules) { return comments(&rules); }
    NodeList comments(NodeList *_rules = nullptr)
    {
      NodeList r;
      NodeList& rules = _rules? *_rules: r;

      NodePtr c;
      while ((c = comment())) {
        rules.push_back(c);
      }
      return rules;
    }

    NodePtr comment() 
    {
      if (char_at(0) != '/' || char_at(1) != '*')
        return nullptr;
       
      size_t i = 2;
      while (i+1 < length() && (char_at(i) != '*' || char_at(i+1) != '/'))
        ++i;

      if (i+1 >= length())
        return nullptr;

      i += 2;
      std::string s = css_.substr(2 + pos_, i - 2 - 2);
      pos_ += i;

      return P(std::make_shared<Comment>(s));
    }

    StringList selector() 
    {
      static const std::regex _RE_ = RE(R"raw(^([^\{]+))raw");
      std::smatch m;
      bool found = search(_RE_, m);
      if (!found) return {};

      /* @fix Remove all comments from selectors
       * http://ostermiller.org/findcomment.html */
      std::string s = trim(m[0]);
      s = std::regex_replace(s, RE(R"raw(\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*\/+/g"), std::string(""));
      s = std::regex_replace(s, RE(R"raw(\s*,\s*)raw"), std::string(","));

      return split(s, ',');
    }
    
    NodePtr declaration() 
    {
      // prop
      std::smatch mp; 
      static const std::regex _RE0_ = RE(R"raw(^(\*?[-#/\*\w]+(\[[0-9a-z_-]+\])?)\s*)raw");
      bool found =  search(_RE0_, mp);
      if (!found) return nullptr;
      
      std::string prop = trim(mp[0]);
      std::regex_replace(prop, commentre_, std::string(""));
  
      // :
      static const std::regex _RE1_ = RE(R"raw(^:\s*)raw");
      found = search(_RE1_);
      if (!found) { error("property missing ':'"); return nullptr; }

      // val
      std::smatch mv;
      static const std::regex _RE2_ = RE(R"raw(^((?:'(?:\\'|.)*?'|\"(?:\\\"|.)*?\"|\([^\)]*?\)|[^\};])+))raw");
      found = search(_RE2_, mv);
      if (!found) { error("property missing value"); return nullptr; }

      std::string val = trim(mv[0]);
      std::regex_replace(val, commentre_, std::string(""));

      NodePtr n = P(std::make_shared<Declaration>(prop, val));

      // ;
      static const std::regex _RE3_ = RE(R"raw(^[;\s]*)raw");
      search(_RE3_);
      return n;
    }

    NodeList declarations(bool braced = true) 
    {
      NodeList decls;

      if (braced && !open()) { error("missing '{'"); return {}; }
      comments(decls);

      // declarations
      NodePtr decl;
      while ((decl = declaration())) {
        decls.push_back(decl);
        comments(decls);
      }

      if (braced && !close()) { error("missing '}'"); return {}; }

      return decls;
    }

    NodePtr keyframe() 
    {
      StringList vals;
      
      while (true) {
        std::smatch m; 
        bool found =  search(RE(R"raw(^((\d+\.\d+|\.\d+|\d+)%?|[a-z]+)\s*)raw"), m);
        if (found) {
          vals.push_back(m[1]);
        }
        search(RE(R"raw(^,\s*)raw"));
      } 
  
      if (vals.empty()) return nullptr;

      return P(std::make_shared<Keyframe>(std::move(vals), declarations()));
    }

    NodePtr atkeyframes() 
    {
      std::smatch m; 
      bool found =  search(RE(R"raw(^@([-\w]+)?keyframes *)raw"), m);
      if (!found) return nullptr;
      auto vendor = trim(m[1]);
  
      // identifier
      std::smatch mi;
      found = search(RE(R"raw(^([-\w]+)\s*)raw"), mi);
      if (!found) { error("@keyframes missing name"); return nullptr; }
      auto name = mi[1];
  
      if (!open()) { error("@keyframes missing '{'"); return nullptr; }
  
      NodePtr frame;
      auto frames = comments();
      while ((frame = keyframe())) {
        frames.push_back(frame);
        concat(frames, comments());
      }
  
      if (!close()) { error("@keyframes missing '}'"); return nullptr; }
  
      return P(std::make_shared<Keyframes>(name, vendor, std::move(frames)));
    }
  
    NodePtr atsupports() 
    {
      std::smatch m; 
      bool found =  search(RE(R"raw(^@supports *([^{]+))raw"), m);

      if (!found) return nullptr;
      auto supports = trim(m[1]);
  
      if (!open()) { error("@supports missing '{'"); return nullptr; }
  
      auto style = comments();
      concat(style, rules());
  
      if (!close()) { error("@supports missing '}'"); return nullptr; }
  
      return P(std::make_shared<Supports>(supports, std::move(style)));
    }
  
    NodePtr athost() 
    {
      bool found =  search(RE(R"raw(^@host *)raw"));
  
      if (!found) return nullptr;
      if (!open()) { error("@host missing '{'"); return nullptr; }
  
      auto style = comments();
      concat(style, rules());
  
      if (!close()) { error("@host missing '}'"); return nullptr; }
  
      return P(std::make_shared<Host>(std::move(style)));
    }

    NodePtr atmedia() 
    {
      std::smatch m; 
      bool found =  search(RE(R"raw(^@media *([^{]+))raw"), m);

      if (!found) return nullptr;
      auto media = trim(m[1]);
  
      if (!open()) { error("@media missing '{'"); return nullptr; }
  
      auto style = comments();
      concat(style, rules());
  
      if (!close()) { error("@media missing '}'"); return nullptr; }
  
      return P(std::make_shared<Media>(media, std::move(style)));
    }

    NodePtr atpage() 
    {
      bool found =  search(RE(R"raw(^@page *)raw"));
      if (!found) return nullptr;
  
      auto sel = selector();
  
      if (!open()) { error("@page missing '{'"); return nullptr; }
      auto decls = comments();
  
      // declarations
      NodePtr decl;
      while ((decl = declaration())) {
        decls.push_back(decl);
        concat(decls, comments());
      }
  
      if (!close()) { error("@page missing '}'"); return nullptr; }
  
      return P(std::make_shared<Page>(std::move(sel), std::move(decls)));
    }

    NodePtr atdocument() 
    {
      std::smatch m; 
      bool found =  search(RE(R"raw(^@([-\w]+)?document *([^{]+))raw"), m);
      if (!found) return nullptr;
  
      auto vendor = trim(m[1]);
      auto doc = trim(m[2]);
  
      if (!open()) { error("@document missing '{'"); return nullptr; }
  
      auto style = comments();
      concat(style, rules());
  
      if (!close()) { error("@document missing '}'"); return nullptr; }
  
      return P(std::make_shared<Document>(doc, vendor, std::move(style)));
    }
  
    template <typename T> NodePtr _atrule(const std::string& tag)
    {
      std::smatch m; 
      bool found =  search(RE("^@" + tag + " *([^;\n]+);"), m);
      if (!found) return nullptr;
      
      auto name = trim(m[1]);
      return P(std::make_shared<T>(name));
    }

    NodePtr atimport() { return _atrule<Import>("import"); }
    NodePtr atcharset() { return _atrule<Charset>("charset"); }
    NodePtr atnamespace() { return _atrule<Namespace>("namespace"); }

    NodePtr atrule() 
    {
      if (char_at(0) != '@') return nullptr;

      auto  p = atkeyframes();
      if (p) return p; else p = atmedia();
      if (p) return p; else p = atsupports();
      if (p) return p; else p = atimport();
      if (p) return p; else p = atcharset();
      if (p) return p; else p = atnamespace();
      if (p) return p; else p = atdocument();
      if (p) return p; else p = atpage();
      if (p) return p; else p = athost();
      return nullptr;
    }

    NodePtr rule() 
    {
      auto sel = selector();
      if (sel.empty()) { error("selector missing"); return nullptr; }

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

