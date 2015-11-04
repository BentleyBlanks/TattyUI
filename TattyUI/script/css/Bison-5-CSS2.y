%pure-parser
%parse-param { class t2CSSAST* parser }

%{
  #include <iostream>
  #include <string>
  #include <stdarg.h>
  #include <cstdio>
  #include <cstdlib>
%}

%union {
    int token;

    float number;
    std::string* string;

    class t2CSSNodeSpecifier* specifier;
    class t2CSSNodeSpecifierList* specifierList;

    class t2CSSDeclaration* decl;
    class t2CSSDeclarationList* declList;

    class t2CSSExpression* expr;
    class t2CSSTerm* term;

    class t2CSSRuleset* rule;
    class t2CSSRuleList* ruleList;

    class t2CSSSimpleSelector* simpleSelector;
    class t2CSSSelector* selector;
    class t2CSSSelectorList* selectorList;
}


%{
  #include "t2CSSAST.h"

  #define YYLEX_PARAM parser->scaninfo

  /* t2CSSRuleList* root;

  int yyparse(t2CSSParser* parser); */

  void yyerror(t2CSSAST* parser, const char *s) { 
    printf("----------------------ERROR---------------------\n");
    if(!parser->root) printf("Error: Ast's root is null.\n"); 
    printf("Error content: %s.\n", s);
    printf("------------------------------------------------\n"); 
  }

%}

/* 运算符优先级 */
/* token本身含义默认为宏 */
%nonassoc LOWEST_PREC

%left UNIMPORTANT_TOK

%token WHITESPACE SGML_CD
%token TOKEN_EOF 0

%token INCLUDES
%token DASHMATCH
%token BEGINSWITH
%token ENDSWITH
%token CONTAINS

%token <string> STRING
%right <string> IDENT
%token <string> NTH

%nonassoc <string> HEX
%nonassoc <string> IDSEL

%nonassoc <string> '-'
%nonassoc <string> '+'
%nonassoc <string> '#'
%nonassoc <string> '%'
%nonassoc <string> ':'
%nonassoc <string> '.'
%nonassoc <string> '['
%nonassoc <string> '*'
%nonassoc error
%left '|'

/* Flex可解析出的所有词法token */
%token IMPORT_SYM
%token PAGE_SYM
%token MEDIA_SYM
%token FONT_FACE_SYM
%token CHARSET_SYM
%token NAMESPACE_SYM
%token WEBKIT_RULE_SYM
%token WEBKIT_DECLS_SYM
%token WEBKIT_KEYFRAME_RULE_SYM
%token WEBKIT_KEYFRAMES_SYM
%token WEBKIT_VALUE_SYM
%token WEBKIT_MEDIAQUERY_SYM
%token WEBKIT_SELECTOR_SYM
%token TOPLEFTCORNER_SYM
%token TOPLEFT_SYM
%token TOPCENTER_SYM
%token TOPRIGHT_SYM
%token TOPRIGHTCORNER_SYM
%token BOTTOMLEFTCORNER_SYM
%token BOTTOMLEFT_SYM
%token BOTTOMCENTER_SYM
%token BOTTOMRIGHT_SYM
%token BOTTOMRIGHTCORNER_SYM
%token LEFTTOP_SYM
%token LEFTMIDDLE_SYM
%token LEFTBOTTOM_SYM
%token RIGHTTOP_SYM
%token RIGHTMIDDLE_SYM
%token RIGHTBOTTOM_SYM

%token ATKEYWORD

%token IMPORTANT_SYM
%token MEDIA_ONLY
%token MEDIA_NOT
%token MEDIA_AND

%token REMS
%token QEMS
%token EMS
%token EXS
%token PXS
%token CMS
%token MMS
%token INS
%token PTS
%token PCS
%token DEGS
%token RADS
%token GRADS
%token TURNS
%token MSECS
%token SECS
%token HERTZ
%token KHERTZ
%token DIMEN
%token INVALIDDIMEN
%token PERCENTAGE
%token <number> FLOATTOKEN
%token <number> INTEGER

%token URI
%token FUNCTION
%token ANYFUNCTION
%token NOTFUNCTION
%token CALCFUNCTION
%token MINFUNCTION
%token MAXFUNCTION

%token UNICODERANGE

/* BNF范式类型 */
%type <rule> ruleset
%type <ruleList> rule_list

%type <string> property

%type <specifier> specifier
%type <specifierList> specifier_list

%type <simpleSelector> simple_selector
%type <selector> selector
%type <selectorList> selector_list

%type <string> class
%type <string> attrib
%type <string> pseudo

%type <declList> decl_list
%type <decl> declaration

%type <string> unary_operator
%type <string> operator

%type <expr> expr
%type <term> term

%type <string> element_name
%type <string> attr_name

%%
 /* 可选的字符集选择 / @import / @namemaybe_space / 普通规则集合 / @media / @page / @font_face */
stylesheet
  : maybe_space rule_list { 
      printf("stylesheet\n"); 

      parser->root = $2; 

      /* traversal(root); */
  }
  ;

  /* 格式化符集  \t\r\n\f */
maybe_space 
  : /* 空 */ %prec UNIMPORTANT_TOK
  | maybe_space WHITESPACE
  ;

  /* 单目运算符 */
unary_operator
  : '-' { $$ = new std::string("-"); }
  | '+' { $$ = new std::string("+"); }
  ;

  /* 属性名 */
property
  : IDENT maybe_space { 
      printf("property\n"); 
      $$ = $1;
  }
  ;

  /* ------------------------规则------------------------ */
  /* 逗号做分隔符 规则由{开始 }结束 中间可插入一个或多个属性声明*/
  /* 语句后需要有;结束 */
  /* -- */
rule_list
  : /* 空 */ { 
      printf("rule_list_empty\n"); 

      $$ = NULL;
  }

  | rule_list ruleset maybe_space { 
      printf("rule_list\n"); 

      t2CSSRuleList* list = new t2CSSRuleList();
      list->ruleList = $1;
      list->ruleset = $2;
      $$ = list;
  }
  ;

before_ruleset
  : /* 空 */
  ;

before_rule_opening_brace
  : /* empty */
  ;

ruleset
  : before_ruleset selector_list before_rule_opening_brace '{' maybe_space decl_list '}' { 
      printf("ruleset\n"); 

      t2CSSRuleset* ruleset = new t2CSSRuleset();
      ruleset->selectorList = $2;
      ruleset->declarationList = $6;
      $$ = ruleset;
  }
  ;

  /* ------------------------声明------------------------ */
decl_list
  : declaration ';' maybe_space { 
      printf("decl_list\n\n");

      t2CSSDeclarationList* declList = new t2CSSDeclarationList();
      declList->declarationList = NULL;
      declList->declaration = $1;
      $$ = declList;
  }

  | decl_list declaration ';' maybe_space { 
      printf("decl_list_declaration\n"); 

      t2CSSDeclarationList* declList = new t2CSSDeclarationList();
      declList->declarationList = $1;
      declList->declaration = $2;
      $$ = declList;
  }
  ;

 /* 属性声明 */
 /* 属性名之后可接格式化符 必须以;结尾 */
declaration
  : property ':' maybe_space expr { 
      printf("declaration\n"); 

      t2CSSDeclaration* decl = new t2CSSDeclaration();
      decl->property = *$1;
      decl->expression = $4;
      $$ = decl;
  }
  ;

  /* ------------------------选择器------------------------ */
selector_list
  : selector %prec UNIMPORTANT_TOK { 
      printf("selector_list\n"); 

      t2CSSSelectorList* selectorList = new t2CSSSelectorList();
      selectorList->selectorList = NULL;
      selectorList->selector = $1;
      $$ = selectorList;
  }

  | selector_list ',' maybe_space selector { 
      printf("selector_list ,\n"); 

      t2CSSSelectorList* selectorList = new t2CSSSelectorList();
      selectorList->selectorList = $1;
      selectorList->selector = $4;
      $$ = selectorList;
  }
  ;

  /* Hash代表id选择器 */
  /* <p id="intro" class="intro" href="intro">HelloWorld</p> 其中p也就是element_name都是可选的*/
  /* Hash: p#intro */
  /* class: p.intro */
  /* attrib: p[href] */
  /* pseudo: p:active */
selector
  : simple_selector { 
      printf("selector_simple\n"); 

      t2CSSSelector* selector = new t2CSSSelector();
      selector->selector = NULL;
      selector->simpleSelector = $1;
      $$ = selector;
  }

  | selector WHITESPACE { 
      printf("selector whitspace\n"); 

      t2CSSSelector* selector = new t2CSSSelector();
      selector->selector = $1;
      selector->simpleSelector = NULL;
      $$ = selector;
  }

  | selector WHITESPACE simple_selector { 
      printf("selector\n"); 

      t2CSSSelector* selector = new t2CSSSelector();
      selector->selector = $1;
      selector->simpleSelector = $3;
      $$ = selector;
  }
  ;

simple_selector
  : element_name { 
      printf("simple_selector_element_name\n"); 

      t2CSSSimpleSelector* simpleSelector = new t2CSSSimpleSelector();
      simpleSelector->elementName = *$1;
      simpleSelector->specifierList = NULL;
      $$ = simpleSelector;
  }

  | element_name specifier_list { 
      printf("simple_selector_element_name_specifier_list\n"); 

      t2CSSSimpleSelector* simpleSelector = new t2CSSSimpleSelector();
      simpleSelector->elementName = *$1;
      simpleSelector->specifierList = $2;
      $$ = simpleSelector;
  }

  | specifier_list { 
      printf("simple_selector_specifier_list\n"); 

      t2CSSSimpleSelector* simpleSelector = new t2CSSSimpleSelector();
      simpleSelector->elementName = "";
      simpleSelector->specifierList = $1;
      $$ = simpleSelector;
  }
  ; 

specifier_list
  : specifier { 
      printf("specifier_list_this\n"); 

      t2CSSNodeSpecifierList* specifierList = new t2CSSNodeSpecifierList();
      specifierList->specifier = $1;
      specifierList->specifierList = NULL;
      $$ = specifierList;
    }

  | specifier_list specifier { 
      printf("specifier_list_specifier\n");

      t2CSSNodeSpecifierList* specifierList = new t2CSSNodeSpecifierList();
      specifierList->specifier = $2;
      specifierList->specifierList = $1;
      $$ = specifierList;
  }
  ;

 /* 元素选择器 id选择器 + 其他选择器*/
specifier:
    IDSEL { 
        printf("idsel\n");
        
        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_ELEMENT;
        specifier->selectorName = *$1;

        $$ = specifier;
    }

    | HEX { 
        printf("hex\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_ID;
        specifier->selectorName = *$1;

        $$ = specifier;
    }

    | class { 
        printf("specifier\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_CLASS;
        specifier->selectorName = *$1;

        $$ = specifier;
    }

    | attrib { 
        printf("specifier\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_ATTRIB;
        specifier->selectorName = *$1;

        $$ = specifier;
    }

    | pseudo { 
        printf("specifier\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_PSEUDO;
        specifier->selectorName = *$1;

        $$ = specifier;
    }
    ;

  /* 类选择器 */
class
  : '.' IDENT { 
      printf("class\n"); 
      $$ = $2;
  }
  ;

  /* 元素名可以为* 代表所有文档中元素 */
element_name
  : IDENT { 
      printf("element_name\n"); 
      $$ = $1;
  }

  | '*'{
      $$ = new std::string("*");
  }
  ;

  /* 属性名 */
attr_name
  : IDENT maybe_space { 
      printf("attr_name\n");

      $$ = $1; 
  }
  ;

  /* 属性选择器 */
attrib
  : '[' maybe_space attr_name ']' { 
      printf("attrib\n"); 
      $$ = $3;
  }
  ;

 /* 伪类选择器 */
 /* Deprecated: Function用于处理 q:lang(no){}类的情况 */
pseudo
  : ':' IDENT { 
      printf("pseudo\n");

      $$ = $2;
  }
  ;

  /* ------------------------元类型------------------------ */
  /* 表达式 可选的单独term出现 */
expr
  : term { 
      printf("expr term\n"); 

      t2CSSExpression* expr = new t2CSSExpression();
      expr->expression = NULL;
      expr->term = $1;
      $$ = expr;
  }

  | expr operator term { 
      printf("expr operator term\n"); 

      t2CSSExpression* expr = new t2CSSExpression();
      expr->expression = $1;
      expr->term = $3;
      $$ = expr;
  }
  ;

  /* 分隔操作符 / 空格 */
operator 
  : '/' maybe_space 
  | ',' maybe_space 
  | /* 空 */
  ;

  /* 实则为表达式右值 可以为带单位的数值 或 类函数 / 字符串 / 关键字标示符 / url / 一段Unicode范围 / 十六进制色*/
  /* 不支持num+单位的表达方式 全局为像素单位 */
term:
  INTEGER maybe_space{
      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_INTERGER;
      term->value = $1;
      $$ = term; 
  }

  | FLOATTOKEN maybe_space{
      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_FLOAT;
      term->value = $1;
      $$ = term; 
  }

  | unary_operator INTEGER maybe_space { 
      printf("unary_operator INTEGER\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_UNARY_OPERATOR_INTERGER;

      if(*$1 == "+")
        term->termName = $2;
      else
        term->termName = -$2;

      $$ = term;
  }

  | unary_operator FLOATTOKEN maybe_space { 
      printf("unary_operator FLOATTOKEN\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_UNARY_OPERATOR_FLOAT;
      
      if(*$1 == "+")
        term->termName = $2;
      else
        term->termName = -$2;

      $$ = term;
  }

  | STRING maybe_space { 
      printf("STRING\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_STRING;
      term->termName = *$1;
      $$ = term;
  }

  | IDENT maybe_space { 
      printf("IDENT\n");

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_IDENT;
      term->termName = *$1;
      $$ = term;
  }

  | HEX maybe_space { 
      printf("HEX\n");

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_HEX;
      term->termName = *$1;
      $$ = term; 
  }

  | '#' maybe_space { 
      printf("#term\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_POUND_TERM;
      term->termName = *$1;
      $$ = term; 
  }

  | '%' maybe_space { 
      printf("%term\n"); 

      t2CSSTerm* term = new t2CSSTerm();
      term->termType = T2CSS_PERCENT_TERM;
      term->termName = *$1;
      $$ = term;
  }
  ;

%%
