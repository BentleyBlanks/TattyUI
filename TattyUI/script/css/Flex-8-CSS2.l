%{
	/* http://www.w3.org/TR/2003/WD-css3-syntax-20030813/#detailed-grammar */
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <iostream>
	#include <string> 
	#include "t2CSSBison.hpp"
	/* #include "t2CSSAST.h" */

	#define t2Token yylval->token
	/* 额外传入的parser带有Flex需要的yyscan_t信息 */
	/* yytext->yyget_text(yyscan_t) yyleng->yyget_leng(yyscan_t) */
	#define t2SaveTokenString yylval->string = new std::string(yytext, yyleng)
	#define t2SaveTokenNumber yylval->number = atof(std::string(yytext, yyleng).c_str())

	/* void t2Log(const char* string, ...){
		va_list args;
		va_start(args, string);
		vprintf(string, args);
		va_end(args);
	} */

    /* int yylex(YYSTYPE * yylval_param, yyscan_t* scan_t); */
%}

/* 前缀可同时使用自定义前缀以及yy */
/* Flex额外参数的具体类型 在yylex_init_extra时可使用到 */
%option noyywrap
%option case-insensitive
%option header-file="t2CSSLex.h"
%option reentrant 
%option bison-bridge
%option extra-type = "class t2CSSAST*"

%s mediaquery
%s forkeyword

h               [0-9a-fA-F]

nonascii        [\200-\377]

unicode         \\{h}{1,6}[ \t\r\n\f]?

escape          {unicode}|\\[ -~\200-\377]

nmstart         [_a-zA-Z]|{nonascii}|{escape}

nmchar          [_a-zA-Z0-9-]|{nonascii}|{escape}

string1         \"([\t !#$%&(-~]|\\{nl}|\'|{nonascii}|{escape})*\"

string2         \'([\t !#$%&(-~]|\\{nl}|\"|{nonascii}|{escape})*\'


ident           -?{nmstart}{nmchar}*

num             [0-9]+|[0-9]*"."[0-9]+

intnum          [0-9]+

string          {string1}|{string2}

url             ([!#$%&*-~]|{nonascii}|{escape})*

w               [ \t\r\n\f]*

nl              \n|\r\n|\r|\f

range           \?{1,6}|{h}(\?{0,5}|{h}(\?{0,4}|{h}(\?{0,3}|{h}(\?{0,2}|{h}(\??|{h})))))

nth             [\+-]?{intnum}*n([\t\r\n ]*[\+-][\t\r\n ]*{intnum})? 	

%%

%{
	class t2CSSAST* parser = yyextra; 
%}

\/\*[^*]*\*+([^/*][^*]*\*+)*\/ {/* ignore comments */ }

[ \t\r\n\f]+            { t2Token = WHITESPACE; return t2Token; }

"<!--"                  { t2Token = SGML_CD; return t2Token; }

"-->"                   { t2Token = SGML_CD; return t2Token; }

"~="                    { t2Token = INCLUDES; return t2Token; }

"|="                    { t2Token = DASHMATCH; return t2Token; }

"^="                    { t2Token = BEGINSWITH; return t2Token; }

"$="                    { t2Token = ENDSWITH; return t2Token; }

"*="                    { t2Token = CONTAINS; return t2Token; }

<mediaquery>"not"       { t2Token = MEDIA_NOT; return t2Token; }

<mediaquery>"only"      { t2Token = MEDIA_ONLY; return t2Token; }

<mediaquery>"and"       { t2Token = MEDIA_AND; return t2Token; }


{string}                { t2SaveTokenString; return STRING; }

{ident}                 { t2SaveTokenString; return IDENT; }

{nth}                   { t2SaveTokenString; return NTH; }


"#"{h}+                 { t2SaveTokenString; return HEX; }

"#"{ident}              { t2SaveTokenString; return IDSEL; }

"@import"               {BEGIN(mediaquery);  t2Token = IMPORT_SYM; return t2Token; }

"@page"                 { t2Token = PAGE_SYM; return t2Token; }

"@top-left-corner"      { t2Token = TOPLEFTCORNER_SYM; return t2Token; }

"@top-left"             { t2Token = TOPLEFT_SYM; return t2Token; }

"@top-center"           { t2Token = TOPCENTER_SYM; return t2Token; }

"@top-right"            { t2Token = TOPRIGHT_SYM; return t2Token; }

"@top-right-corner"     { t2Token = TOPRIGHTCORNER_SYM; return t2Token; }

"@bottom-left-corner"   { t2Token = BOTTOMLEFTCORNER_SYM; return t2Token; }

"@bottom-left"          { t2Token = BOTTOMLEFT_SYM; return t2Token; }

"@bottom-center"        { t2Token = BOTTOMCENTER_SYM; return t2Token; }

"@bottom-right"         { t2Token = BOTTOMRIGHT_SYM; return t2Token; }

"@bottom-right-corner"  { t2Token = BOTTOMRIGHTCORNER_SYM; return t2Token; }

"@left-top"             { t2Token = LEFTTOP_SYM; return t2Token; }

"@left-middle"          { t2Token = LEFTMIDDLE_SYM; return t2Token; }

"@left-bottom"          { t2Token = LEFTBOTTOM_SYM; return t2Token; }

"@right-top"            { t2Token = RIGHTTOP_SYM; return t2Token; }

"@right-middle"         { t2Token = RIGHTMIDDLE_SYM; return t2Token; }

"@right-bottom"         { t2Token = RIGHTBOTTOM_SYM; return t2Token; }

"@media"                {BEGIN(mediaquery);  t2Token = MEDIA_SYM; return t2Token; }

"@font-face"            { t2Token = FONT_FACE_SYM; return t2Token; }

"@charset"              { t2Token = CHARSET_SYM; return t2Token; }

"@namespace"            { t2Token = NAMESPACE_SYM; return t2Token;  }

"@-webkit-rule"         { t2Token = WEBKIT_RULE_SYM; return t2Token;  }

"@-webkit-decls"        { t2Token = WEBKIT_DECLS_SYM; return t2Token;  }

"@-webkit-value"        { t2Token = WEBKIT_VALUE_SYM; return t2Token;  }

"@-webkit-mediaquery"   {BEGIN(mediaquery);  t2Token = WEBKIT_MEDIAQUERY_SYM; return t2Token;  }

"@-webkit-selector"     { t2Token = WEBKIT_SELECTOR_SYM; return t2Token;  }

"@-webkit-keyframes"    { t2Token = WEBKIT_KEYFRAMES_SYM; return t2Token;  }

"@-webkit-keyframe-rule" { t2Token = WEBKIT_KEYFRAME_RULE_SYM; return t2Token;  }

"@"{ident}              { t2Token = ATKEYWORD; return t2Token;  }

"!"{w}"important"       { t2Token = IMPORTANT_SYM; return t2Token; }

{num}em                 { t2Token = EMS; return t2Token; }

{num}rem                { t2Token = REMS; return t2Token; }

{num}__qem              { t2Token = QEMS; return t2Token; }

{num}ex                 { t2Token = EXS; return t2Token; }

{num}px                 { t2Token = PXS; return t2Token; }

{num}cm                 { t2Token = CMS; return t2Token; }

{num}mm                 { t2Token = MMS; return t2Token; }

{num}in                 { t2Token = INS; return t2Token; }

{num}pt                 { t2Token = PTS; return t2Token; }

{num}pc                 { t2Token = PCS; return t2Token; }

{num}deg                { t2Token = DEGS; return t2Token; }

{num}rad                { t2Token = RADS; return t2Token; }

{num}grad               { t2Token = GRADS; return t2Token; }

{num}turn               { t2Token = TURNS; return t2Token; }

{num}ms                 { t2Token = MSECS; return t2Token; }

{num}s                  { t2Token = SECS; return t2Token; }

{num}Hz                 { t2Token = HERTZ; return t2Token; }

{num}kHz                { t2Token = KHERTZ; return t2Token; }

{num}{ident}            { t2Token = DIMEN; return t2Token; }

{num}{ident}\+          { t2Token = INVALIDDIMEN; return t2Token; }

{num}%+                 { t2Token = PERCENTAGE; return t2Token; }


{intnum}                { t2SaveTokenNumber; return INTEGER; }

{num}                   { t2SaveTokenNumber; return FLOATTOKEN; }


"-webkit-any("          { t2Token = ANYFUNCTION; return t2Token; }

"not("                  { t2Token = NOTFUNCTION; return t2Token; }

"url("{w}{string}{w}")" { t2Token = URI; return t2Token; }

"url("{w}{url}{w}")"    { t2Token = URI; return t2Token; }

"-webkit-calc("         { t2Token = CALCFUNCTION; return t2Token; }

"-webkit-min("          { t2Token = MINFUNCTION; return t2Token; }

"-webkit-max("          { t2Token = MAXFUNCTION; return t2Token; }

{ident}"("              { t2Token = FUNCTION; return t2Token; }


U\+{range}              { t2Token = UNICODERANGE; return t2Token; }

U\+{h}{1,6}-{h}{1,6}    { t2Token = UNICODERANGE; return t2Token; }


<mediaquery>"{"         |

<mediaquery>";"         { BEGIN(INITIAL);  t2Token = *yytext; return t2Token; }

.                       { t2Token = *yytext; return t2Token; }

%%