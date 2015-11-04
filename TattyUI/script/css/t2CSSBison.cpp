
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 4 "Bison-5-CSS2.y"

  #include <iostream>
  #include <string>
  #include <stdarg.h>
  #include <cstdio>
  #include <cstdlib>


/* Line 189 of yacc.c  */
#line 82 "t2CSSBison.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EOF = 0,
     LOWEST_PREC = 258,
     UNIMPORTANT_TOK = 259,
     WHITESPACE = 260,
     SGML_CD = 261,
     INCLUDES = 262,
     DASHMATCH = 263,
     BEGINSWITH = 264,
     ENDSWITH = 265,
     CONTAINS = 266,
     STRING = 267,
     IDENT = 268,
     NTH = 269,
     HEX = 270,
     IDSEL = 271,
     IMPORT_SYM = 272,
     PAGE_SYM = 273,
     MEDIA_SYM = 274,
     FONT_FACE_SYM = 275,
     CHARSET_SYM = 276,
     NAMESPACE_SYM = 277,
     WEBKIT_RULE_SYM = 278,
     WEBKIT_DECLS_SYM = 279,
     WEBKIT_KEYFRAME_RULE_SYM = 280,
     WEBKIT_KEYFRAMES_SYM = 281,
     WEBKIT_VALUE_SYM = 282,
     WEBKIT_MEDIAQUERY_SYM = 283,
     WEBKIT_SELECTOR_SYM = 284,
     TOPLEFTCORNER_SYM = 285,
     TOPLEFT_SYM = 286,
     TOPCENTER_SYM = 287,
     TOPRIGHT_SYM = 288,
     TOPRIGHTCORNER_SYM = 289,
     BOTTOMLEFTCORNER_SYM = 290,
     BOTTOMLEFT_SYM = 291,
     BOTTOMCENTER_SYM = 292,
     BOTTOMRIGHT_SYM = 293,
     BOTTOMRIGHTCORNER_SYM = 294,
     LEFTTOP_SYM = 295,
     LEFTMIDDLE_SYM = 296,
     LEFTBOTTOM_SYM = 297,
     RIGHTTOP_SYM = 298,
     RIGHTMIDDLE_SYM = 299,
     RIGHTBOTTOM_SYM = 300,
     ATKEYWORD = 301,
     IMPORTANT_SYM = 302,
     MEDIA_ONLY = 303,
     MEDIA_NOT = 304,
     MEDIA_AND = 305,
     REMS = 306,
     QEMS = 307,
     EMS = 308,
     EXS = 309,
     PXS = 310,
     CMS = 311,
     MMS = 312,
     INS = 313,
     PTS = 314,
     PCS = 315,
     DEGS = 316,
     RADS = 317,
     GRADS = 318,
     TURNS = 319,
     MSECS = 320,
     SECS = 321,
     HERTZ = 322,
     KHERTZ = 323,
     DIMEN = 324,
     INVALIDDIMEN = 325,
     PERCENTAGE = 326,
     FLOATTOKEN = 327,
     INTEGER = 328,
     URI = 329,
     FUNCTION = 330,
     ANYFUNCTION = 331,
     NOTFUNCTION = 332,
     CALCFUNCTION = 333,
     MINFUNCTION = 334,
     MAXFUNCTION = 335,
     UNICODERANGE = 336
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 12 "Bison-5-CSS2.y"

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



/* Line 214 of yacc.c  */
#line 225 "t2CSSBison.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 36 "Bison-5-CSS2.y"

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



/* Line 264 of yacc.c  */
#line 256 "t2CSSBison.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   95

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNRULES -- Number of states.  */
#define YYNSTATES  84

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   336

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    19,     2,    20,     2,     2,
       2,     2,    24,    18,    94,    17,    22,    96,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    21,    93,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,    25,    92,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    12,    14,    17,    18,
      22,    23,    24,    32,    36,    41,    46,    48,    53,    55,
      58,    62,    64,    67,    69,    71,    74,    76,    78,    80,
      82,    84,    87,    89,    91,    94,    99,   102,   104,   108,
     111,   114,   115,   118,   121,   125,   129,   132,   135,   138,
     141
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      98,     0,    -1,    99,   102,    -1,    -1,    99,     5,    -1,
      17,    -1,    18,    -1,    13,    99,    -1,    -1,   102,   105,
      99,    -1,    -1,    -1,   103,   108,   104,    91,    99,   106,
      92,    -1,   107,    93,    99,    -1,   106,   107,    93,    99,
      -1,   101,    21,    99,   118,    -1,   109,    -1,   108,    94,
      99,   109,    -1,   110,    -1,   109,     5,    -1,   109,     5,
     110,    -1,   114,    -1,   114,   111,    -1,   111,    -1,   112,
      -1,   111,   112,    -1,    16,    -1,    15,    -1,   113,    -1,
     116,    -1,   117,    -1,    22,    13,    -1,    13,    -1,    24,
      -1,    13,    99,    -1,    23,    99,   115,    95,    -1,    21,
      13,    -1,   120,    -1,   118,   119,   120,    -1,    96,    99,
      -1,    94,    99,    -1,    -1,    82,    99,    -1,    81,    99,
      -1,   100,    82,    99,    -1,   100,    81,    99,    -1,    12,
      99,    -1,    13,    99,    -1,    15,    99,    -1,    19,    99,
      -1,    20,    99,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   191,   191,   202,   203,   208,   209,   214,   225,   231,
     241,   245,   250,   262,   271,   284,   296,   305,   322,   331,
     340,   351,   360,   369,   380,   389,   401,   411,   421,   431,
     441,   454,   462,   467,   474,   483,   492,   502,   511,   523,
     524,   525,   531,   538,   545,   559,   573,   582,   591,   600,
     609
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "TOKEN_EOF", "error", "$undefined", "LOWEST_PREC", "UNIMPORTANT_TOK",
  "WHITESPACE", "SGML_CD", "INCLUDES", "DASHMATCH", "BEGINSWITH",
  "ENDSWITH", "CONTAINS", "STRING", "IDENT", "NTH", "HEX", "IDSEL", "'-'",
  "'+'", "'#'", "'%'", "':'", "'.'", "'['", "'*'", "'|'", "IMPORT_SYM",
  "PAGE_SYM", "MEDIA_SYM", "FONT_FACE_SYM", "CHARSET_SYM", "NAMESPACE_SYM",
  "WEBKIT_RULE_SYM", "WEBKIT_DECLS_SYM", "WEBKIT_KEYFRAME_RULE_SYM",
  "WEBKIT_KEYFRAMES_SYM", "WEBKIT_VALUE_SYM", "WEBKIT_MEDIAQUERY_SYM",
  "WEBKIT_SELECTOR_SYM", "TOPLEFTCORNER_SYM", "TOPLEFT_SYM",
  "TOPCENTER_SYM", "TOPRIGHT_SYM", "TOPRIGHTCORNER_SYM",
  "BOTTOMLEFTCORNER_SYM", "BOTTOMLEFT_SYM", "BOTTOMCENTER_SYM",
  "BOTTOMRIGHT_SYM", "BOTTOMRIGHTCORNER_SYM", "LEFTTOP_SYM",
  "LEFTMIDDLE_SYM", "LEFTBOTTOM_SYM", "RIGHTTOP_SYM", "RIGHTMIDDLE_SYM",
  "RIGHTBOTTOM_SYM", "ATKEYWORD", "IMPORTANT_SYM", "MEDIA_ONLY",
  "MEDIA_NOT", "MEDIA_AND", "REMS", "QEMS", "EMS", "EXS", "PXS", "CMS",
  "MMS", "INS", "PTS", "PCS", "DEGS", "RADS", "GRADS", "TURNS", "MSECS",
  "SECS", "HERTZ", "KHERTZ", "DIMEN", "INVALIDDIMEN", "PERCENTAGE",
  "FLOATTOKEN", "INTEGER", "URI", "FUNCTION", "ANYFUNCTION", "NOTFUNCTION",
  "CALCFUNCTION", "MINFUNCTION", "MAXFUNCTION", "UNICODERANGE", "'{'",
  "'}'", "';'", "','", "']'", "'/'", "$accept", "stylesheet",
  "maybe_space", "unary_operator", "property", "rule_list",
  "before_ruleset", "before_rule_opening_brace", "ruleset", "decl_list",
  "declaration", "selector_list", "selector", "simple_selector",
  "specifier_list", "specifier", "class", "element_name", "attr_name",
  "attrib", "pseudo", "expr", "operator", "term", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,    45,    43,    35,
      37,    58,    46,    91,    42,   124,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   123,   125,    59,    44,    93,    47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    99,    99,   100,   100,   101,   102,   102,
     103,   104,   105,   106,   106,   107,   108,   108,   109,   109,
     109,   110,   110,   110,   111,   111,   112,   112,   112,   112,
     112,   113,   114,   114,   115,   116,   117,   118,   118,   119,
     119,   119,   120,   120,   120,   120,   120,   120,   120,   120,
     120
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     2,     0,     3,
       0,     0,     7,     3,     4,     4,     1,     4,     1,     2,
       3,     1,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     4,     2,     1,     3,     2,
       2,     0,     2,     2,     3,     3,     2,     2,     2,     2,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     8,     1,     4,    10,     0,     3,    32,    27,
      26,     0,     0,     3,    33,    11,    16,    18,    23,    24,
      28,    21,    29,    30,     9,    36,    31,     0,     3,     0,
      19,    25,    22,     3,     0,     0,     3,    20,    34,    35,
      17,     0,     3,     0,     0,     0,     7,     3,    12,     0,
       3,     0,     3,    13,     3,     3,     3,     5,     6,     3,
       3,     3,     3,     0,    41,    37,    14,    46,    47,    48,
      49,    50,    43,    42,     3,     3,     3,     3,     0,    45,
      44,    40,    39,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    63,    43,     5,     6,    29,     7,    44,
      45,    15,    16,    17,    18,    19,    20,    21,    34,    22,
      23,    64,    78,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -77
static const yytype_int8 yypact[] =
{
     -77,     2,    13,   -77,   -77,    36,    19,   -77,   -77,   -77,
     -77,    -6,     6,   -77,   -77,   -57,    33,   -77,    39,   -77,
     -77,    39,   -77,   -77,    13,   -77,   -77,     7,   -77,   -41,
      19,   -77,    39,   -77,   -32,    71,   -77,   -77,    13,   -77,
      33,    18,   -77,    43,   -13,   -28,    13,   -77,   -77,   -27,
     -77,    -4,   -77,    13,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -76,   -48,   -77,    13,    13,    13,    13,
      13,    13,    13,    13,   -77,   -77,   -77,   -77,     9,    13,
      13,    13,    13,   -77
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,    -3,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
      23,   -77,    34,    38,    49,   -15,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,     3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -16
static const yytype_int8 yytable[] =
{
      42,     4,     3,    31,    24,    74,    75,    25,    54,    55,
      27,    56,     4,    57,    58,    59,    60,    31,     4,    26,
      33,    54,    55,     4,    56,    35,    57,    58,    59,    60,
      38,    42,     8,    41,     9,    10,    -2,    28,    30,    46,
      11,    12,    13,    14,    51,   -15,    76,    53,    77,    66,
      36,    67,    68,    69,     9,    10,    70,    71,    72,    73,
      11,    12,    13,    39,    47,    50,    52,    49,    37,    40,
      32,    79,    80,    81,    82,     0,     4,    61,    62,    48,
       0,    83,     0,     0,     8,     0,     9,    10,     0,     0,
      61,    62,    11,    12,    13,    14
};

static const yytype_int8 yycheck[] =
{
      13,     5,     0,    18,     7,    81,    82,    13,    12,    13,
      13,    15,     5,    17,    18,    19,    20,    32,     5,    13,
      13,    12,    13,     5,    15,    28,    17,    18,    19,    20,
      33,    13,    13,    36,    15,    16,     0,    94,     5,    42,
      21,    22,    23,    24,    47,    93,    94,    50,    96,    52,
      91,    54,    55,    56,    15,    16,    59,    60,    61,    62,
      21,    22,    23,    95,    21,    93,    93,    44,    30,    35,
      21,    74,    75,    76,    77,    -1,     5,    81,    82,    92,
      -1,    78,    -1,    -1,    13,    -1,    15,    16,    -1,    -1,
      81,    82,    21,    22,    23,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    98,    99,     0,     5,   102,   103,   105,    13,    15,
      16,    21,    22,    23,    24,   108,   109,   110,   111,   112,
     113,   114,   116,   117,    99,    13,    13,    99,    94,   104,
       5,   112,   111,    13,   115,    99,    91,   110,    99,    95,
     109,    99,    13,   101,   106,   107,    99,    21,    92,   107,
      93,    99,    93,    99,    12,    13,    15,    17,    18,    19,
      20,    81,    82,   100,   118,   120,    99,    99,    99,    99,
      99,    99,    99,    99,    81,    82,    94,    96,   119,    99,
      99,    99,    99,   120
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, parser); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, class t2CSSAST* parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    class t2CSSAST* parser;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, class t2CSSAST* parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    class t2CSSAST* parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, class t2CSSAST* parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    class t2CSSAST* parser;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, class t2CSSAST* parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    class t2CSSAST* parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (class t2CSSAST* parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (class t2CSSAST* parser)
#else
int
yyparse (parser)
    class t2CSSAST* parser;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 191 "Bison-5-CSS2.y"
    { 
      printf("stylesheet\n"); 

      parser->root = (yyvsp[(2) - (2)].ruleList); 

      /* traversal(root); */
  ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 208 "Bison-5-CSS2.y"
    { (yyval.string) = new std::string("-"); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 209 "Bison-5-CSS2.y"
    { (yyval.string) = new std::string("+"); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 214 "Bison-5-CSS2.y"
    { 
      printf("property\n"); 
      (yyval.string) = (yyvsp[(1) - (2)].string);
  ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 225 "Bison-5-CSS2.y"
    { 
      printf("rule_list_empty\n"); 

      (yyval.ruleList) = NULL;
  ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 231 "Bison-5-CSS2.y"
    { 
      printf("rule_list\n"); 

      t2CSSRuleList* list = new t2CSSRuleList();
      list->ruleList = (yyvsp[(1) - (3)].ruleList);
      list->ruleset = (yyvsp[(2) - (3)].rule);
      (yyval.ruleList) = list;
  ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 250 "Bison-5-CSS2.y"
    { 
      printf("ruleset\n"); 

      t2CSSRuleset* ruleset = new t2CSSRuleset();
      ruleset->selectorList = (yyvsp[(2) - (7)].selectorList);
      ruleset->declarationList = (yyvsp[(6) - (7)].declList);
      (yyval.rule) = ruleset;
  ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 262 "Bison-5-CSS2.y"
    { 
      printf("decl_list\n\n");

      t2CSSDeclarationList* declList = new t2CSSDeclarationList();
      declList->declarationList = NULL;
      declList->declaration = (yyvsp[(1) - (3)].decl);
      (yyval.declList) = declList;
  ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 271 "Bison-5-CSS2.y"
    { 
      printf("decl_list_declaration\n"); 

      t2CSSDeclarationList* declList = new t2CSSDeclarationList();
      declList->declarationList = (yyvsp[(1) - (4)].declList);
      declList->declaration = (yyvsp[(2) - (4)].decl);
      (yyval.declList) = declList;
  ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 284 "Bison-5-CSS2.y"
    { 
      printf("declaration\n"); 

      t2CSSDeclaration* decl = new t2CSSDeclaration();
      decl->property = *(yyvsp[(1) - (4)].string);
      decl->expression = (yyvsp[(4) - (4)].expr);
      (yyval.decl) = decl;
  ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 296 "Bison-5-CSS2.y"
    { 
      printf("selector_list\n"); 

      t2CSSSelectorList* selectorList = new t2CSSSelectorList();
      selectorList->selectorList = NULL;
      selectorList->selector = (yyvsp[(1) - (1)].selector);
      (yyval.selectorList) = selectorList;
  ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 305 "Bison-5-CSS2.y"
    { 
      printf("selector_list ,\n"); 

      t2CSSSelectorList* selectorList = new t2CSSSelectorList();
      selectorList->selectorList = (yyvsp[(1) - (4)].selectorList);
      selectorList->selector = (yyvsp[(4) - (4)].selector);
      (yyval.selectorList) = selectorList;
  ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 322 "Bison-5-CSS2.y"
    { 
      printf("selector_simple\n"); 

      t2CSSSelector* selector = new t2CSSSelector();
      selector->selector = NULL;
      selector->simpleSelector = (yyvsp[(1) - (1)].simpleSelector);
      (yyval.selector) = selector;
  ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 331 "Bison-5-CSS2.y"
    { 
      printf("selector whitspace\n"); 

      t2CSSSelector* selector = new t2CSSSelector();
      selector->selector = (yyvsp[(1) - (2)].selector);
      selector->simpleSelector = NULL;
      (yyval.selector) = selector;
  ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 340 "Bison-5-CSS2.y"
    { 
      printf("selector\n"); 

      t2CSSSelector* selector = new t2CSSSelector();
      selector->selector = (yyvsp[(1) - (3)].selector);
      selector->simpleSelector = (yyvsp[(3) - (3)].simpleSelector);
      (yyval.selector) = selector;
  ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 351 "Bison-5-CSS2.y"
    { 
      printf("simple_selector_element_name\n"); 

      t2CSSSimpleSelector* simpleSelector = new t2CSSSimpleSelector();
      simpleSelector->elementName = *(yyvsp[(1) - (1)].string);
      simpleSelector->specifierList = NULL;
      (yyval.simpleSelector) = simpleSelector;
  ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 360 "Bison-5-CSS2.y"
    { 
      printf("simple_selector_element_name_specifier_list\n"); 

      t2CSSSimpleSelector* simpleSelector = new t2CSSSimpleSelector();
      simpleSelector->elementName = *(yyvsp[(1) - (2)].string);
      simpleSelector->specifierList = (yyvsp[(2) - (2)].specifierList);
      (yyval.simpleSelector) = simpleSelector;
  ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 369 "Bison-5-CSS2.y"
    { 
      printf("simple_selector_specifier_list\n"); 

      t2CSSSimpleSelector* simpleSelector = new t2CSSSimpleSelector();
      simpleSelector->elementName = "";
      simpleSelector->specifierList = (yyvsp[(1) - (1)].specifierList);
      (yyval.simpleSelector) = simpleSelector;
  ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 380 "Bison-5-CSS2.y"
    { 
      printf("specifier_list_this\n"); 

      t2CSSNodeSpecifierList* specifierList = new t2CSSNodeSpecifierList();
      specifierList->specifier = (yyvsp[(1) - (1)].specifier);
      specifierList->specifierList = NULL;
      (yyval.specifierList) = specifierList;
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 389 "Bison-5-CSS2.y"
    { 
      printf("specifier_list_specifier\n");

      t2CSSNodeSpecifierList* specifierList = new t2CSSNodeSpecifierList();
      specifierList->specifier = (yyvsp[(2) - (2)].specifier);
      specifierList->specifierList = (yyvsp[(1) - (2)].specifierList);
      (yyval.specifierList) = specifierList;
  ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 401 "Bison-5-CSS2.y"
    { 
        printf("idsel\n");
        
        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_ELEMENT;
        specifier->selectorName = *(yyvsp[(1) - (1)].string);

        (yyval.specifier) = specifier;
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 411 "Bison-5-CSS2.y"
    { 
        printf("hex\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_ID;
        specifier->selectorName = *(yyvsp[(1) - (1)].string);

        (yyval.specifier) = specifier;
    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 421 "Bison-5-CSS2.y"
    { 
        printf("specifier\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_CLASS;
        specifier->selectorName = *(yyvsp[(1) - (1)].string);

        (yyval.specifier) = specifier;
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 431 "Bison-5-CSS2.y"
    { 
        printf("specifier\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_ATTRIB;
        specifier->selectorName = *(yyvsp[(1) - (1)].string);

        (yyval.specifier) = specifier;
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 441 "Bison-5-CSS2.y"
    { 
        printf("specifier\n"); 

        t2CSSNodeSpecifier* specifier = new t2CSSNodeSpecifier();
        specifier->type = T2CSS_PSEUDO;
        specifier->selectorName = *(yyvsp[(1) - (1)].string);

        (yyval.specifier) = specifier;
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 454 "Bison-5-CSS2.y"
    { 
      printf("class\n"); 
      (yyval.string) = (yyvsp[(2) - (2)].string);
  ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 462 "Bison-5-CSS2.y"
    { 
      printf("element_name\n"); 
      (yyval.string) = (yyvsp[(1) - (1)].string);
  ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 467 "Bison-5-CSS2.y"
    {
      (yyval.string) = new std::string("*");
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 474 "Bison-5-CSS2.y"
    { 
      printf("attr_name\n");

      (yyval.string) = (yyvsp[(1) - (2)].string); 
  ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 483 "Bison-5-CSS2.y"
    { 
      printf("attrib\n"); 
      (yyval.string) = (yyvsp[(3) - (4)].string);
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 492 "Bison-5-CSS2.y"
    { 
      printf("pseudo\n");

      (yyval.string) = (yyvsp[(2) - (2)].string);
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 502 "Bison-5-CSS2.y"
    { 
      printf("expr term\n"); 

      t2CSSExpression* expr = new t2CSSExpression();
      expr->expression = NULL;
      expr->term = (yyvsp[(1) - (1)].term);
      (yyval.expr) = expr;
  ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 511 "Bison-5-CSS2.y"
    { 
      printf("expr operator term\n"); 

      t2CSSExpression* expr = new t2CSSExpression();
      expr->expression = (yyvsp[(1) - (3)].expr);
      expr->term = (yyvsp[(3) - (3)].term);
      (yyval.expr) = expr;
  ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 531 "Bison-5-CSS2.y"
    {
      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_INTERGER;
      term->value = (yyvsp[(1) - (2)].number);
      (yyval.term) = term; 
  ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 538 "Bison-5-CSS2.y"
    {
      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_FLOAT;
      term->value = (yyvsp[(1) - (2)].number);
      (yyval.term) = term; 
  ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 545 "Bison-5-CSS2.y"
    { 
      printf("unary_operator INTEGER\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_UNARY_OPERATOR_INTERGER;

      if(*(yyvsp[(1) - (3)].string) == "+")
        term->termName = (yyvsp[(2) - (3)].number);
      else
        term->termName = -(yyvsp[(2) - (3)].number);

      (yyval.term) = term;
  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 559 "Bison-5-CSS2.y"
    { 
      printf("unary_operator FLOATTOKEN\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_UNARY_OPERATOR_FLOAT;
      
      if(*(yyvsp[(1) - (3)].string) == "+")
        term->termName = (yyvsp[(2) - (3)].number);
      else
        term->termName = -(yyvsp[(2) - (3)].number);

      (yyval.term) = term;
  ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 573 "Bison-5-CSS2.y"
    { 
      printf("STRING\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_STRING;
      term->termName = *(yyvsp[(1) - (2)].string);
      (yyval.term) = term;
  ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 582 "Bison-5-CSS2.y"
    { 
      printf("IDENT\n");

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_IDENT;
      term->termName = *(yyvsp[(1) - (2)].string);
      (yyval.term) = term;
  ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 591 "Bison-5-CSS2.y"
    { 
      printf("HEX\n");

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_HEX;
      term->termName = *(yyvsp[(1) - (2)].string);
      (yyval.term) = term; 
  ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 600 "Bison-5-CSS2.y"
    { 
      printf("#term\n"); 

      t2CSSTerm* term = new t2CSSTerm(); 
      term->termType = T2CSS_POUND_TERM;
      term->termName = *(yyvsp[(1) - (2)].string);
      (yyval.term) = term; 
  ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 609 "Bison-5-CSS2.y"
    { 
      printf("%term\n"); 

      t2CSSTerm* term = new t2CSSTerm();
      term->termType = T2CSS_PERCENT_TERM;
      term->termName = *(yyvsp[(1) - (2)].string);
      (yyval.term) = term;
  ;}
    break;



/* Line 1455 of yacc.c  */
#line 2111 "t2CSSBison.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parser, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (parser, yymsg);
	  }
	else
	  {
	    yyerror (parser, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, parser);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, parser);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 619 "Bison-5-CSS2.y"


