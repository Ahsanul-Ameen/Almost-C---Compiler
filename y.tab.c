/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "1605047.y" /* yacc.c:339  */

#include "1605047_SymbolTable.h"
#define YYSTYPE SymbolInfo*

using pss = pair < string, string >;
using dsim = deque < SymbolInfo* >;
using ds = deque < string >;
using vs = vector < string >;
using dss = deque < pss >;

extern int yylineno; /* from lexer */
int yyparse(void);
int yylex(void);
extern FILE *yyin;

FILE *fp;
//FILE *errorFile = fopen("1605047_error.txt", "w");
FILE *logFile = fopen("log.txt", "w");

int line_count = 1;
int error_count = 0;
SymbolTable *symbolTable = new SymbolTable(97, logFile);

void yyerror(const char *str) {
	fprintf(stderr, "Line no %d: %s\t(inside yyerror)\n\n", line_count, str);
}

int labelCount = 0, tempCount = 0;
template <typename T> string toString(T n) { stringstream ss; ss << n; return ss.str(); }

dsim paramList, argList, decList;
//paramList contains(name thakle save kore , type such as Identifier, declaration type such as void int float)
//decList contains(name like a/b/x/arr, type:ID/IDa, decType: int/float)
//------------------------------------------------------------------------
ds varDeclaration, funcVarDeclaration;//all variables created from newTemp are pushed here serially
dss arrVarDeclaration;	//all array variables
string currentFunction;	//currentFunction...need to be explained
map < string, bool > decLaredVar;
map < string, string > arrayMap;

template<typename T> ostream&
operator<<(ostream& os, const vector<T> &t) { unsigned n = t.size(); for(int i = 0; i < n; i++) os<<t[i]<<" "; return os; }
template<typename T, typename TT>
ostream& operator<<(ostream &os, const pair<T,TT> &t) { return os<<"("<<t.first<<", "<<t.second<<")"; }


char *newLabel()	//return format L0 / L1
{
	char *lb = new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()		//return format t0 / t3
{
	char *t = new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

//void optimization(FILE *asmcode);
string definedVariables();
string definedArrays();
string defineProcRINTLN();
void printICG(string icg);
void printOptimizedICG(string nonOptimizedICG);

//--------------------------------------------------------------------------

#line 144 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    DO = 262,
    BREAK = 263,
    INT = 264,
    CHAR = 265,
    FLOAT = 266,
    DOUBLE = 267,
    VOID = 268,
    RETURN = 269,
    SWITCH = 270,
    CASE = 271,
    DEFAULT = 272,
    CONTINUE = 273,
    CONST_INT = 274,
    CONST_FLOAT = 275,
    CONST_CHAR = 276,
    ADDOP = 277,
    MULOP = 278,
    INCOP = 279,
    DECOP = 280,
    RELOP = 281,
    ASSIGNOP = 282,
    LOGICOP = 283,
    BITOP = 284,
    NOT = 285,
    LPAREN = 286,
    RPAREN = 287,
    LCURL = 288,
    RCURL = 289,
    LTHIRD = 290,
    RTHIRD = 291,
    COMMA = 292,
    SEMICOLON = 293,
    ID = 294,
    STRING = 295,
    PRINTLN = 296,
    LOWER_THAN_ELSE = 297
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define CONST_INT 274
#define CONST_FLOAT 275
#define CONST_CHAR 276
#define ADDOP 277
#define MULOP 278
#define INCOP 279
#define DECOP 280
#define RELOP 281
#define ASSIGNOP 282
#define LOGICOP 283
#define BITOP 284
#define NOT 285
#define LPAREN 286
#define RPAREN 287
#define LCURL 288
#define RCURL 289
#define LTHIRD 290
#define RTHIRD 291
#define COMMA 292
#define SEMICOLON 293
#define ID 294
#define STRING 295
#define PRINTLN 296
#define LOWER_THAN_ELSE 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 279 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    98,    98,   116,   123,   133,   141,   148,   158,   192,
     217,   217,   312,   312,   386,   393,   400,   407,   416,   416,
     433,   449,   479,   485,   491,   499,   506,   514,   521,   532,
     539,   549,   556,   563,   570,   594,   615,   638,   661,   677,
     699,   705,   716,   731,   773,   782,   809,   818,   866,   875,
     923,   932,   959,   968,  1022,  1043,  1061,  1073,  1101,  1152,
    1161,  1173,  1185,  1205,  1228,  1235,  1243,  1251
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "CONST_INT", "CONST_FLOAT", "CONST_CHAR",
  "ADDOP", "MULOP", "INCOP", "DECOP", "RELOP", "ASSIGNOP", "LOGICOP",
  "BITOP", "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD",
  "COMMA", "SEMICOLON", "ID", "STRING", "PRINTLN", "LOWER_THAN_ELSE",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "@1", "@2", "parameter_list", "compound_statement",
  "$@3", "var_declaration", "type_specifier", "declaration_list",
  "statements", "statement", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF -67

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-67)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      33,   -67,   -67,   -67,    17,    33,   -67,   -67,   -67,   -67,
     -36,   -67,   -67,    16,    18,     3,   -14,   -19,   -67,   -15,
     -13,     9,    14,    10,   -67,    25,    29,    33,   -67,   -67,
      54,    41,   -67,   -67,    25,    42,    50,   -67,   100,   -67,
     -67,   -67,    64,    69,    77,    68,   -67,   -67,    68,    68,
      68,   -67,    22,    79,   -67,   -67,    73,    63,   -67,   -67,
       5,    51,   -67,    87,    58,    93,   -67,   -67,    68,    40,
      68,    80,    67,   -67,   -67,    85,    68,    68,    82,    88,
     -67,   -67,   -67,   -67,    68,   -67,    68,    68,    68,    68,
      92,    40,    94,   -67,   -67,   -67,    95,    91,    89,    97,
     -67,   -67,    93,   110,   -67,   100,    68,   100,   -67,    68,
     -67,    96,   131,   104,   -67,   -67,   -67,   100,   100,   -67,
     -67
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    22,    23,    24,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    27,     0,     0,     0,     0,    21,    12,
       0,    17,     0,    25,     9,     0,    10,     0,    16,    28,
       0,    18,    13,     8,     0,    15,     0,    20,     0,    11,
      14,    26,     0,     0,     0,     0,    60,    61,     0,     0,
       0,    40,    42,     0,    33,    31,     0,     0,    29,    32,
      57,     0,    44,    46,    48,    50,    52,    56,     0,     0,
       0,     0,    57,    54,    55,     0,    65,     0,     0,    27,
      19,    30,    62,    63,     0,    41,     0,     0,     0,     0,
       0,     0,     0,    39,    59,    67,     0,    64,     0,     0,
      45,    47,    51,    49,    53,     0,     0,     0,    58,     0,
      43,     0,    35,     0,    37,    66,    38,     0,     0,    36,
      34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   132,   -67,   -67,   -67,   -67,   -67,   -12,
     -67,    26,     6,   -67,   -67,   -53,   -54,   -48,   -43,   -66,
      56,    52,    57,   -40,   -67,   -67,   -67
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    34,    25,    20,    54,
      38,    55,    56,    14,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    96,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      72,    72,    71,    13,    81,    22,    10,    75,    73,    74,
      95,    10,     1,    32,     2,    91,     3,    11,   100,    26,
      23,    21,    39,    24,    27,    90,     9,    92,    72,    82,
      83,     9,    84,    35,    98,    19,    72,   106,    72,    72,
      72,    72,     1,   115,     2,    30,     3,    15,    28,   104,
      29,    16,   112,    76,   114,    17,    18,    77,    31,    46,
      47,    72,    48,   113,   119,   120,    42,    33,    43,    44,
      49,    50,     1,    36,     2,    37,     3,    45,    51,    52,
      87,    40,    46,    47,    88,    48,    41,    46,    47,    85,
      48,    82,    83,    49,    50,    68,    31,    80,    49,    50,
      69,    51,    52,    42,    53,    43,    44,    52,    70,     1,
      78,     2,    79,     3,    45,    86,    89,    94,    93,    46,
      47,    99,    48,    16,   105,   110,   107,   108,   109,   111,
      49,    50,    87,    31,   116,   117,   118,    12,    51,    52,
     103,    53,   101,     0,   102
};

static const yytype_int8 yycheck[] =
{
      48,    49,    45,    39,    57,    19,     0,    50,    48,    49,
      76,     5,     9,    25,    11,    69,    13,     0,    84,    32,
      39,    15,    34,    38,    37,    68,     0,    70,    76,    24,
      25,     5,    27,    27,    77,    32,    84,    91,    86,    87,
      88,    89,     9,   109,    11,    35,    13,    31,    39,    89,
      36,    35,   105,    31,   107,    37,    38,    35,    33,    19,
      20,   109,    22,   106,   117,   118,     3,    38,     5,     6,
      30,    31,     9,    19,    11,    34,    13,    14,    38,    39,
      22,    39,    19,    20,    26,    22,    36,    19,    20,    38,
      22,    24,    25,    30,    31,    31,    33,    34,    30,    31,
      31,    38,    39,     3,    41,     5,     6,    39,    31,     9,
      31,    11,    39,    13,    14,    28,    23,    32,    38,    19,
      20,    39,    22,    35,    32,    36,    32,    32,    37,    32,
      30,    31,    22,    33,    38,     4,    32,     5,    38,    39,
      88,    41,    86,    -1,    87
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    11,    13,    44,    45,    46,    47,    48,    54,
      55,     0,    46,    39,    56,    31,    35,    37,    38,    32,
      51,    55,    19,    39,    38,    50,    32,    37,    39,    36,
      35,    33,    52,    38,    49,    55,    19,    34,    53,    52,
      39,    36,     3,     5,     6,    14,    19,    20,    22,    30,
      31,    38,    39,    41,    52,    54,    55,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    31,    31,
      31,    61,    60,    66,    66,    61,    31,    35,    31,    39,
      34,    58,    24,    25,    27,    38,    28,    22,    26,    23,
      61,    59,    61,    38,    32,    62,    68,    69,    61,    39,
      62,    63,    65,    64,    66,    32,    59,    32,    32,    37,
      36,    32,    58,    61,    58,    62,    38,     4,    32,    58,
      58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    47,    47,
      49,    48,    50,    48,    51,    51,    51,    51,    53,    52,
      52,    54,    55,    55,    55,    56,    56,    56,    56,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    66,    67,    67,    67,
      67,    67,    67,    67,    68,    68,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       2,     3,     1,     1,     1,     3,     6,     1,     4,     1,
       2,     1,     1,     1,     7,     5,     7,     5,     5,     3,
       1,     2,     1,     4,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     2,     2,     1,     1,     4,     3,
       1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 98 "1605047.y" /* yacc.c:1646  */
    {	//okay.... asm baki ache
					//write your code/action in this block in all the similar blocks below
					if(!error_count) {
						string icg = ".MODEL SMALL\n\.STACK 100H\n\.DATA\n";
						icg += definedVariables();
						icg += definedArrays();
						icg += ".CODE\n" + (yyvsp[0])->getAsmCode();//eikahne vitor theke code ra berate eshe bondi hoye jabe...
						icg += defineProcRINTLN();
						icg += "\t\tEND MAIN\n";
						printICG(icg);
						printOptimizedICG(icg);
					} else {
						cerr << "#[errors.....Segmentation Fault.....during code compilation]" << endl;
					}
				}
#line 1462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 116 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done..ymm
						//fprintf(logFile, "At line no: %d program : program unit\n\n", line_count);
						(yyval) = new SymbolInfo();
						(yyval)->setName((yyvsp[-1])->getName() + "\n" + (yyvsp[0])->getName());//newline added for simplicity?
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
						(yyval)->setAsmCode((yyvsp[-1])->getAsmCode() + (yyvsp[0])->getAsmCode());
					}
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 123 "1605047.y" /* yacc.c:1646  */
    {
						//fprintf(logFile, "At line no: %d program : unit\n\n", line_count);
						(yyval) = new SymbolInfo();
						(yyval)->setName((yyvsp[0])->getName());
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
						(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
					}
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 133 "1605047.y" /* yacc.c:1646  */
    {		//okay...asm done
					//fprintf(logFile, "At line no: %d unit : var_declaration\n\n", line_count);
					(yyval) = new SymbolInfo();
					(yyval)->setName((yyvsp[0])->getName() + "\n");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					funcVarDeclaration.clear(); // keno korlam??
					(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
				}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 141 "1605047.y" /* yacc.c:1646  */
    {
			 		//fprintf(logFile, "At line no: %d unit : func_declaration\n\n", line_count);
			 		(yyval) = new SymbolInfo();
					(yyval)->setName((yyvsp[0])->getName() + "\n");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
			 	}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 148 "1605047.y" /* yacc.c:1646  */
    {
			 		//fprintf(logFile, "At line no: %d unit : func_definition\n\n", line_count);
			 		(yyval) = new SymbolInfo();
					(yyval)->setName((yyvsp[0])->getName() + "\n");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
			 	}
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 158 "1605047.y" /* yacc.c:1646  */
    {	//okay...asm done...contains no asm actually
											//fprintf(logFile, "At line no: %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n", line_count);
											(yyval) = new SymbolInfo();
											SymbolInfo *symfo = symbolTable->lookUp((yyvsp[-4])->getName());
											if(symfo) {	//previously declared though redundant but okay for our grammar
										 		if(symfo->getFunctionDetails()->getParamCount() != paramList.size()) {
										 			error_count++;
										 			fprintf(logFile, "Error at line %d: Invalid number of parameters\n\n", line_count);
										 		} else {
										 			deque<string> paramTypeTempList = symfo->getFunctionDetails()->getArgTypeList();
													for(int i = 0; i < paramList.size(); i++) {
														if(paramList[i]->getDeclareType() != paramTypeTempList[i]) {
															error_count++;
															fprintf(logFile, "Error at line %d: Type Mismatch \n",line_count);
															break;
														}
													}
													if((yyvsp[-5])->getName() != symfo->getFunctionDetails()->getReturnType()) {
															error_count++;
															fprintf(logFile,"Error at line %d: Return Type Mismatch \n\n",line_count);
													}
										 		}
											} else {
												symbolTable->insert((yyvsp[-4])->getName(), "ID", "Function");
												symfo = symbolTable->lookUp((yyvsp[-4])->getName());
												for(int i = 0; i < paramList.size(); i++)
													symfo->getFunctionDetails()->addParameter(paramList[i]->getName(), paramList[i]->getDeclareType());
												symfo->getFunctionDetails()->setReturnType((yyvsp[-5])->getName());
											}
											(yyval)->setName((yyvsp[-5])->getName()+" "+(yyvsp[-4])->getName()+"("+(yyvsp[-2])->getName()+");");
											//fprintf(logFile, "%s\n\n", $1->getName().c_str());
											//clear parameter list
											paramList.clear();
										}
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 192 "1605047.y" /* yacc.c:1646  */
    {
									 		//fprintf(logFile, "At line no: %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n", line_count);
									 		(yyval) = new SymbolInfo();
											SymbolInfo *symfo = symbolTable->lookUp((yyvsp[-3])->getName());
											if(symfo) {
												if(symfo->getFunctionDetails()->getParamCount()) {
													error_count++;
													fprintf(logFile, "Error at line %d:  Invalid number of parameters \n\n", line_count);
												}
												if(symfo->getFunctionDetails()->getReturnType() !=  (yyvsp[-4])->getName()) {
													error_count++;
													fprintf(logFile, "Error at line %d: Return Type Mismatch \n\n", line_count);
												}
											} else {
												symbolTable->insert((yyvsp[-3])->getName(), "ID", "Function");
												symfo = symbolTable->lookUp((yyvsp[-3])->getName());
												symfo->getFunctionDetails()->setReturnType((yyvsp[-4])->getName());
											}
											(yyval)->setName((yyvsp[-4])->getName() + " " + (yyvsp[-3])->getName() + "();");
											//fprintf(logFile, "%s\n\n", $$->getName().c_str());
											//clear parameter list redundant...anyway
											paramList.clear();
									 	}
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 217 "1605047.y" /* yacc.c:1646  */
    { //okay....asm done
										(yyval) = new SymbolInfo();
										SymbolInfo *symfo = symbolTable->lookUp((yyvsp[-3])->getName());
										if(symfo) {
											if(!symfo->getFunctionDetails()->isDefined1()) {
												(yyval)->setDeclareType(symfo->getFunctionDetails()->getReturnType());
												if(paramList.size() != symfo->getFunctionDetails()->getParamCount()) {
													error_count++;
													fprintf(logFile, "Error at line %d: Invalid number of parameters\n\n", line_count);
												}
												else {
													//cout<<symfo->getFunctionDetails()->getArgTypeList().size() << " " << paramList.size()<<endl;
													ds paramTypeList = symfo->getFunctionDetails()->getArgTypeList();
													for(int i = 0; i < paramList.size(); i++) {
														if(paramList[i]->getDeclareType() != paramTypeList[i]) {
															error_count++;
															fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
															break;
														}
													}
													if(symfo->getFunctionDetails()->getReturnType() != (yyvsp[-4])->getName()) {
															error_count++;
															fprintf(logFile,"Error at line %d: Return Type Mismatch\n\n", line_count);
													}
												}
												symfo->getFunctionDetails()->clearFunction();
												for(int i = 0; i < paramList.size(); i++) {
													string procName = paramList[i]->getName() + toString(symbolTable->getNextScopeID());
													//cout<<procName<<endl;
													symfo->getFunctionDetails()->addParameter(procName, paramList[i]->getDeclareType());
												}
												symfo->getFunctionDetails()->setIsDefined(true);
											} else {
												error_count++;
												fprintf(logFile, "Error at line %d:  Multiple defination of function\t%s\n\n", line_count, (yyvsp[-3])->getName().c_str());
											}
										} else {
											symbolTable->insert((yyvsp[-3])->getName(), "ID", "Function");
											symfo = symbolTable->lookUp((yyvsp[-3])->getName());
											symfo->getFunctionDetails()->setIsDefined();
											for(int i = 0; i < paramList.size(); i++){
												string procName = paramList[i]->getName() + toString(symbolTable->getNextScopeID());
												//cout<<procName<<endl;
												symfo->getFunctionDetails()->addParameter(procName, paramList[i]->getDeclareType());
											}
											symfo->getFunctionDetails()->setReturnType((yyvsp[-4])->getName());
										}
										//cout<<"### : "+$2->getName() + "_FunRetVar"<<endl;
										if((yyvsp[-4])->getName() != "void ") {
											varDeclaration.push_back((yyvsp[-3])->getName() + "_FunRetVar");
											decLaredVar[(yyvsp[-3])->getName() + "_FunRetVar"] = true;
										}
										currentFunction = (yyvsp[-3])->getName();
										//cout<<currentFunction<<endl;
									}
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 271 "1605047.y" /* yacc.c:1646  */
    {	//code kora holo
										//fprintf(logFile, "At line no: %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n", line_count);
										(yyval)->setName((yyvsp[-6])->getName() + " " + (yyvsp[-5])->getName() + "(" + (yyvsp[-3])->getName() + ")" + (yyvsp[0])->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										string codeSegment = (yyvsp[-5])->getName() + " PROC\n";
										if((yyvsp[-5])->getName() == "main") {
											codeSegment += "\tMOV AX, @DATA\n";
											codeSegment += "\tMOV DS, AX\n\n";
											codeSegment += (yyvsp[0])->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											codeSegment += "\n\tMOV AH, 4CH\n";
											codeSegment += "\tINT 21H\n";
											codeSegment += "main ENDP\n";
											(yyval)->setAsmCode(codeSegment);
										}
										else {
											SymbolInfo *symfo = symbolTable->lookUp((yyvsp[-5])->getName());
											for(int i = 0; i < funcVarDeclaration.size(); i++) {
												symfo->getFunctionDetails()->addFuncVar(funcVarDeclaration[i]);
											}
											funcVarDeclaration.clear();
											codeSegment += "\tPUSH AX\n";
											codeSegment += "\tPUSH BX\n";
											codeSegment += "\tPUSH CX\n";
											codeSegment += "\tPUSH DX\n";
											ds tempParamList = symfo->getFunctionDetails()->getArgList();
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPUSH " + tempParamList[i] + "\n";
											ds tempVarList = symfo->getFunctionDetails()->getFuncVarList();
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPUSH " + tempVarList[i] + "\n";
											codeSegment += (yyvsp[0])->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPOP " + tempVarList[tempVarList.size()-1-i] + "\n";
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPOP " + tempParamList[tempParamList.size()-1-i] + "\n";
											codeSegment += "\tPOP DX\n";
											codeSegment += "\tPOP CX\n";
											codeSegment += "\tPOP BX\n";
											codeSegment += "\tPOP AX\n";
											codeSegment += "\tret\n";
											(yyval)->setAsmCode(codeSegment + (yyvsp[-5])->getName() + " ENDP\n\n");
										}
									}
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 312 "1605047.y" /* yacc.c:1646  */
    {	//okay totally
										(yyval) = new SymbolInfo();
										SymbolInfo *symfo = symbolTable->lookUp((yyvsp[-2])->getName());
										if(!symfo){	//doesn't declared yet
											symbolTable->insert((yyvsp[-2])->getName(), "ID", "Function");
											symfo = symbolTable->lookUp((yyvsp[-2])->getName());
											symfo->getFunctionDetails()->setIsDefined();
											symfo->getFunctionDetails()->setReturnType((yyvsp[-3])->getName());
										}
										else if(!symfo->getFunctionDetails()->isDefined1()) { //doesn't defined yet
											if(symfo->getFunctionDetails()->getParamCount()) {
												error_count++;
												fprintf(logFile, "Error at line %d:  Invalid number of parameters\n\n", line_count);
											}
											if((yyvsp[-3])->getName() != symfo->getFunctionDetails()->getReturnType()) {
												error_count++;
												fprintf(logFile, "Error at line %d: Return Type Mismatch\n\n", line_count);
											}
											symfo->getFunctionDetails()->setIsDefined();
										}
										else {
											error_count++;
											fprintf(logFile, "Error at line %d:  Multiple defination of function %s\n\n", line_count, (yyvsp[-2])->getName().c_str());
										}
										(yyvsp[-3])->setName((yyvsp[-3])->getName() + " " + (yyvsp[-2])->getName() + "()");
										if((yyvsp[-3])->getName() != "void ") {
											varDeclaration.push_back((yyvsp[-2])->getName() + "_FunRetVar");
											decLaredVar[(yyvsp[-2])->getName() + "_FunRetVar"] = true;
										}
										currentFunction = (yyvsp[-2])->getName();

									}
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 343 "1605047.y" /* yacc.c:1646  */
    {	//code kora holo
										//fprintf(logFile, "At line no: %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n", line_count);
										(yyval)->setName((yyvsp[-5])->getName() + (yyvsp[0])->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());

										string codeSegment = (yyvsp[-4])->getName() + " PROC\n";
										if((yyvsp[-4])->getName() == "main") {
											codeSegment += "\tMOV AX, @DATA\n";
											codeSegment += "\tMOV DS, AX\n\n";
											codeSegment += (yyvsp[0])->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											codeSegment += "\n\tMOV AH, 4CH\n";
											codeSegment += "\tINT 21H\n";
											codeSegment += "main ENDP\n";
											(yyval)->setAsmCode(codeSegment);
										} else {
											SymbolInfo *symfo = symbolTable->lookUp((yyvsp[-4])->getName());
											for(int i = 0; i < funcVarDeclaration.size(); i++) {
												symfo->getFunctionDetails()->addFuncVar(funcVarDeclaration[i]);
											}
											funcVarDeclaration.clear();
											codeSegment += "\tPUSH AX\n";
											codeSegment += "\tPUSH BX\n";
											codeSegment += "\tPUSH CX\n";
											codeSegment += "\tPUSH DX\n";
											ds tempParamList = symfo->getFunctionDetails()->getArgList();
											ds tempVarList = symfo->getFunctionDetails()->getFuncVarList();
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPUSH " + tempParamList[i] + "\n";
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPUSH " + tempVarList[i] + "\n";
											codeSegment += (yyvsp[0])->getAsmCode();
											codeSegment += "RETURN_LABEL_" + currentFunction + ":\n";
											for(int i = 0; i < tempVarList.size(); i++) codeSegment += "\tPOP " + tempVarList[tempVarList.size()-1-i] + "\n";
											for(int i = 0; i < tempParamList.size(); i++) codeSegment += "\tPOP " + tempParamList[tempParamList.size()-1-i] + "\n";
											codeSegment += "\tPOP DX\n";
											codeSegment += "\tPOP CX\n";
											codeSegment += "\tPOP BX\n";
											codeSegment += "\tPOP AX\n";
											codeSegment += "\tret\n";
											(yyval)->setAsmCode(codeSegment + (yyvsp[-4])->getName() + " ENDP\n\n");
										}
								  }
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 386 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done
										//fprintf(logFile, "At line no: %d parameter_list : parameter_list COMMA type_specifier ID\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName((yyvsp[-3])->getName() + ", " + (yyvsp[-1])->getName()+" "+(yyvsp[0])->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo((yyvsp[0])->getName(), "ID", (yyvsp[-1])->getName()));
									}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 393 "1605047.y" /* yacc.c:1646  */
    {
						    		//fprintf(logFile, "At line no: %d parameter_list : parameter_list COMMA type_specifier\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName((yyvsp[-2])->getName()+", "+(yyvsp[0])->getName());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo("", "ID", (yyvsp[0])->getName()));
						   		}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 400 "1605047.y" /* yacc.c:1646  */
    {
										//fprintf(logFile, "At line no: %d parameter_list : type_specifier ID\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName((yyvsp[-1])->getName() + " " + (yyvsp[0])->getName());
						 				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo((yyvsp[0])->getName(), "ID", (yyvsp[-1])->getName()));
									}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 407 "1605047.y" /* yacc.c:1646  */
    {
										//fprintf(logFile, "At line no: %d parameter_list : type_specifier\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName((yyvsp[0])->getName()+" ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										paramList.push_back(new SymbolInfo("", "ID", (yyvsp[0])->getName()));
									}
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 416 "1605047.y" /* yacc.c:1646  */
    {		//okay....asm done
												symbolTable->enterScope();
												for(int i = 0; i < paramList.size(); i++) {
													symbolTable->insert(paramList[i]->getName(), "ID", paramList[i]->getDeclareType());
													varDeclaration.push_back(paramList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
												}
												//clear the paramList
												paramList.clear();
											}
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 424 "1605047.y" /* yacc.c:1646  */
    {
												//fprintf(logFile, "At line no: %d compound_statement : LCURL statements RCURL\n\n", line_count);
												(yyval) = new SymbolInfo();
												(yyval)->setName("{\n" + (yyvsp[-1])->getName() + "\n}");
												//fprintf(logFile, "%s\n\n", $$->getName().c_str());
												(yyval)->setAsmCode((yyvsp[-1])->getAsmCode());
												//symbolTable->printAllScopeTable();
												symbolTable->exitScope();
											}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 433 "1605047.y" /* yacc.c:1646  */
    {
												symbolTable->enterScope();
												for(int i = 0; i < paramList.size(); i++) {
													symbolTable->insert(paramList[i]->getName(), "ID", paramList[i]->getDeclareType());
													varDeclaration.push_back(paramList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
												}
												//clear the paramList
												paramList.clear();
												//fprintf(logFile, "At line no: %d compound_statement : LCURL RCURL\n\n{}\n\n", line_count);
												(yyval) = new SymbolInfo();
												(yyval)->setName("{}");
												//symbolTable->printAllScopeTable();
												symbolTable->exitScope();
				 		    			}
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 449 "1605047.y" /* yacc.c:1646  */
    {		//okay....updated and asm done
						//fprintf(logFile, "At line no: %d var_declaration : type_specifier declaration_list SEMICOLON\n\n",line_count);
						if((yyvsp[-2])->getName() == "void "){
							error_count++;
							fprintf(logFile, "Error at line %d: TYpe specifier can not be void\n\n", line_count);
						} else for(int i = 0; i < decList.size(); i++) {
							if(symbolTable->lookUpCurrentScope(decList[i]->getName())) { //previously declared
								error_count++;
								fprintf(logFile, "Error at line %d:  Multiple Declaration of %s \n\n", line_count, decList[i]->getName().c_str());
							} else if(decList[i]->getType().length() >= 3) {		//eita kintu update korsi IDarray_length format theke ID array_lenght
								string arrType = decList[i]->getType().substr(0, 2);
								string arrLength = decList[i]->getType().substr(2);
								arrVarDeclaration.push_back({decList[i]->getName() + toString(symbolTable->getCurrentScopeID()), arrLength});
								decList[i]->setType(arrType);
								symbolTable->insert(decList[i]->getName(), decList[i]->getType(), (yyvsp[-2])->getName() + "array");
								//cout<<$1->getName() + "array"<<endl; // format be like int array or float array
							} else {
								funcVarDeclaration.push_back(decList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
								symbolTable->insert(decList[i]->getName(), decList[i]->getType(), (yyvsp[-2])->getName());
								varDeclaration.push_back(decList[i]->getName() + toString(symbolTable->getCurrentScopeID()));
							}
						}
						(yyval) = new SymbolInfo();
						(yyval)->setName((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + ";");
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
						//clear the decList
						decList.clear();
					}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 479 "1605047.y" /* yacc.c:1646  */
    {		//okay.....asm done
										//fprintf(logFile, "At line no: %d type_specifier : INT\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName("int ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
									}
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 485 "1605047.y" /* yacc.c:1646  */
    {
										//fprintf(logFile, "At line no: %d type_specifier : FLOAT\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName("float ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				 					}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 491 "1605047.y" /* yacc.c:1646  */
    {
										//fprintf(logFile, "At line no: %d type_specifier : VOID\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName("void ");
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				 					}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 499 "1605047.y" /* yacc.c:1646  */
    {		//okay.....updated and asm done
							//fprintf(logFile, "At line no: %d declaration_list : declaration_list COMMA ID\n\n", line_count);
							(yyval) = new SymbolInfo();
							(yyval)->setName((yyvsp[-2])->getName() + "," + (yyvsp[0])->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							decList.push_back(new SymbolInfo((yyvsp[0])->getName(), "ID"));
						}
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 506 "1605047.y" /* yacc.c:1646  */
    {
	 		  				//fprintf(logFile, "At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n", line_count);
								(yyval) = new SymbolInfo();
								(yyval)->setName((yyvsp[-5])->getName() + "," + (yyvsp[-3])->getName() + "[" + (yyvsp[-1])->getName() + "]");
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								//decList.push_back(new SymbolInfo($3->getName(), "array")); //....eita change korlam nicherta use kortesi
								decList.push_back(new SymbolInfo((yyvsp[-3])->getName(), "ID" + (yyvsp[-1])->getName()));
 		  				}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 514 "1605047.y" /* yacc.c:1646  */
    {
	 		  				//fprintf(logFile, "At line no: %d declaration_list : ID\n\n", line_count);
								(yyval) = new SymbolInfo();
								(yyval)->setName((yyvsp[0])->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
			   				decList.push_back(new SymbolInfo((yyvsp[0])->getName(), "ID"));
 		  				}
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 521 "1605047.y" /* yacc.c:1646  */
    {
	 		  				//fprintf(logFile, "At line no: %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n%s\n\n", line_count, $3->getName().c_str());
								(yyval) = new SymbolInfo();
				   				(yyval)->setName((yyvsp[-3])->getName() + "[" + (yyvsp[-1])->getName() + "]");
				   				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				   				//decList.push_back(new SymbolInfo($1->getName(), "array")); //....eita change korlam nicherta use kortesi
									decList.push_back(new SymbolInfo((yyvsp[-3])->getName(), "ID" + (yyvsp[-1])->getName()));
 		  				}
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 532 "1605047.y" /* yacc.c:1646  */
    {		//okay....asm done
								//fprintf(logFile, "\nAt line no: %d statements : statement\n\n",line_count);
								(yyval) = new SymbolInfo();
								(yyval)->setName((yyvsp[0])->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
							}
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 539 "1605047.y" /* yacc.c:1646  */
    {
								//fprintf(logFile, "At line no: %d statements : statements statement\n\n", line_count);
								(yyval) = new SymbolInfo();
								(yyval)->setName((yyvsp[-1])->getName() + "\n" + (yyvsp[0])->getName());
				   			//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				   			(yyval)->setAsmCode((yyvsp[-1])->getAsmCode() + (yyvsp[0])->getAsmCode());
			   			}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 549 "1605047.y" /* yacc.c:1646  */
    {	//okay.....asm done
								//fprintf(logFile, "At line no: %d statement : var_declaration\n\n", line_count);
								(yyval) = new SymbolInfo();
								(yyval)->setName((yyvsp[0])->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								//extra ASM is not needed...done using deque varDeclaration, arrVarDeclaration etc...
							}
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 556 "1605047.y" /* yacc.c:1646  */
    { //okay
			  				//fprintf(logFile, "At line no: %d statement : expression_statement\n\n", line_count);
			  				(yyval) = new SymbolInfo();
								(yyval)->setName((yyvsp[0])->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
			  			}
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 563 "1605047.y" /* yacc.c:1646  */
    { //okay
				 				//fprintf(logFile, "At line no: %d statement : compound_statement\n\n", line_count);
				 				(yyval) = new SymbolInfo();
								(yyval)->setName((yyvsp[0])->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
			  			}
#line 2050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 570 "1605047.y" /* yacc.c:1646  */
    { //okay
			  				//fprintf(logFile, "At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n", line_count);
			  				(yyval) = new SymbolInfo();
								(yyval)->setName("for(" + (yyvsp[-4])->getName() + " " + (yyvsp[-3])->getName() + " " + (yyvsp[-2])->getName() + ")\n" + (yyvsp[-2])->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								if((yyvsp[-4])->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d:  Type Mismatch\n\n", line_count);
								} else {
									string loopLabel = (string)newLabel(), endLabel = (string)newLabel();
									string codeSegment = (yyvsp[-4])->getAsmCode(); //$3's code at first, which is already done by assigning $$=$3
									codeSegment += loopLabel + ":\n";//create two labels and append one of them in $$->code
									codeSegment += (yyvsp[-3])->getAsmCode();
									codeSegment += "\tMOV AX, " + (yyvsp[-3])->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";//compare $4's symbol with 0
									codeSegment += "\tJE " + endLabel + "\n";//if equal jump to 2nd label
									codeSegment += (yyvsp[0])->getAsmCode();//	append $7's code
									codeSegment += (yyvsp[-2])->getAsmCode();//	append $5's code
									//cout<<loopLabel<<endl;
									codeSegment += "\tJMP " + loopLabel + "\n";
									codeSegment += endLabel + ":\n";//append the second label in the code
									(yyval)->setAsmCode(codeSegment);
								}
	  					}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 594 "1605047.y" /* yacc.c:1646  */
    { //okay
			  				//fprintf(logFile, "At line no: %d statement : IF LPAREN expression RPAREN statement\n\n",line_count);
			  				(yyval) = new SymbolInfo();
			  				if((yyvsp[-2])->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n",line_count);
									(yyval)->setDeclareType("int ");
								} else {
									string endifLabel = (string)newLabel();
									//cout<<endifLabel<<endl;
									string codeSegment = (yyvsp[-2])->getAsmCode();
									codeSegment += "\tMOV AX, " + (yyvsp[-2])->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";
									codeSegment += "\tJE " + endifLabel + "\n";
									codeSegment += (yyvsp[0])->getAsmCode();
									codeSegment += endifLabel + ":\n";
									(yyval)->setAsmCode(codeSegment);
								}
								(yyval)->setName("if(" + (yyvsp[-2])->getName() + ")\n" + (yyvsp[0])->getName());
  							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
  						}
#line 2105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 615 "1605047.y" /* yacc.c:1646  */
    { // contains shift-reduce conflicts  //okay
			  				//fprintf(logFile, "At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n", line_count);
			  				(yyval) = new SymbolInfo();
								if((yyvsp[-4])->getDeclareType() == "void "){
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									(yyval)->setDeclareType("int ");
								} else {
									string elseLabel = (string)newLabel(), endifLabel = (string)newLabel();
									string codeSegment = (yyvsp[-4])->getAsmCode();
									codeSegment += "\tMOV AX, " + (yyvsp[-4])->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";
									codeSegment += "\tJE " + elseLabel + "\n";
									codeSegment += (yyvsp[-2])->getAsmCode();
									codeSegment += "\tJMP " + endifLabel + "\n";
									codeSegment += elseLabel + ":\n";
									codeSegment += (yyvsp[0])->getAsmCode();
									codeSegment += endifLabel + ":\n";
									(yyval)->setAsmCode(codeSegment);
								}
								(yyval)->setName("if(" + (yyvsp[-4])->getName() + ")\n" + (yyvsp[-2])->getName() + "\nelse\n" + (yyvsp[0])->getName());
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
			  			}
#line 2133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 638 "1605047.y" /* yacc.c:1646  */
    { //okay
			  				//fprintf(logFile, "At line no: %d statement : WHILE LPAREN expression RPAREN statement\n\n", line_count);
			  				(yyval) = new SymbolInfo();
						  	if((yyvsp[-2])->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									(yyval)->setDeclareType("int ");
								} else {
									string whileLabel = (string)newLabel();
									string endWhileLabel = (string)newLabel();
									string codeSegment = whileLabel + ":\n";
								  codeSegment += (yyvsp[-2])->getAsmCode();
									codeSegment += "\tMOV AX, " + (yyvsp[-2])->getAsmSymbol() + "\n";
									codeSegment += "\tCMP AX, 0\n";
									codeSegment += "\tJE " + endWhileLabel + "\n";
									codeSegment += (yyvsp[0])->getAsmCode();
									codeSegment += "\tJMP " + whileLabel + "\n";
									codeSegment += endWhileLabel + ":\n";
									(yyval)->setAsmCode(codeSegment);
								}
						  	(yyval)->setName("while(" + (yyvsp[-2])->getName() + ")\n" + (yyvsp[0])->getName());
			  				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
  						}
#line 2161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 661 "1605047.y" /* yacc.c:1646  */
    {	//okay
			  				//fprintf(logFile, "At line no: %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n", line_count);
			  				(yyval) = new SymbolInfo();
								(yyval)->setName("\n(" + (yyvsp[-2])->getName() + ")");
			  				//fprintf(logFile, "%s;\n\n", $$->getName().c_str());
								// write code for printing an ID. You may assume that ID is an integer variable.
								if(symbolTable->getScopeID((yyvsp[-2])->getName()) == -1) {
									error_count++;
									fprintf(logFile, "Error at Line %d: Undeclared Variable: %s\n\n", line_count, (yyvsp[-2])->getName());
								}
								else{
									string assembledID = (yyvsp[-2])->getName() + toString(symbolTable->getScopeID((yyvsp[-2])->getName()));
									string codeSegment = "\tMOV AX, " + assembledID + "\n";
									(yyval)->setAsmCode(codeSegment + "\tCALL PRINTLN\n");
								}
			  			}
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 677 "1605047.y" /* yacc.c:1646  */
    { //okay
			  				//fprintf(logFile, "At line no: %d statement : RETURN expression SEMICOLON\n\n", line_count);
			  				(yyval) = new SymbolInfo();
								(yyval)->setName("return " + (yyvsp[-1])->getName() + ";");
								//fprintf(logFile, "%s\n\n", $$->getName().c_str());
								if((yyvsp[-1])->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									(yyval)->setDeclareType("int ");
								} else {
									string codeSegment = (yyvsp[-1])->getAsmCode();
									codeSegment += "\tMOV AX, " + (yyvsp[-1])->getAsmSymbol() + "\n";
									//cout<<":::: "<<currentFunction<<" expression:::: "<<$2->getName()<<endl;
									string calleeRetVal = currentFunction + "_FunRetVar";
									if(decLaredVar.find(calleeRetVal) != decLaredVar.end())codeSegment += "\tMOV " + currentFunction + "_FunRetVar, AX\n"; // return na korle actually can't reach here
									codeSegment += "\tJMP RETURN_LABEL_" + currentFunction + "\n";
									(yyval)->setAsmCode(codeSegment);
								}
							}
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 699 "1605047.y" /* yacc.c:1646  */
    {		//okay....asm done
													//fprintf(logFile, "At line no: %d expression_statement : SEMICOLON\n\n", line_count);
													(yyval) = new SymbolInfo();
													(yyval)->setName(";");
													//fprintf(logFile, "%s\n\n", $$->getName().c_str());
												}
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 705 "1605047.y" /* yacc.c:1646  */
    {
													//fprintf(logFile, "At line no: %d expression_statement : expression SEMICOLON\n\n", line_count);
													(yyval) = new SymbolInfo();
													(yyval)->setName((yyvsp[-1])->getName() + ";");
													//fprintf(logFile, "%s\n\n", $$->getName().c_str());
													(yyval)->setAsmCode((yyvsp[-1])->getAsmCode());
													(yyval)->setAsmSymbol((yyvsp[-1])->getAsmSymbol());
												}
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 716 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done
					//fprintf(logFile, "At line no: %d variable : ID\n\n", line_count);
					(yyval) = new SymbolInfo();
					if(!symbolTable->lookUp((yyvsp[0])->getName()) || (symbolTable->lookUp((yyvsp[0])->getName())->getDeclareType() == "int array" || symbolTable->lookUp((yyvsp[0])->getName())->getDeclareType() == "float array")) {//exist kore na...ir array type
						error_count++;
						fprintf(logFile, "Error at line %d: Undeclared Variable / Non array assigning on array: %s\n\n", line_count, (yyvsp[0])->getName().c_str());
					} else if(symbolTable->lookUp((yyvsp[0])->getName())) {
						(yyval)->setDeclareType(symbolTable->lookUp((yyvsp[0])->getName())->getDeclareType());
						(yyval)->setAsmSymbol( (yyvsp[0])->getName() + toString(symbolTable->getScopeID((yyvsp[0])->getName())));
					}
					(yyval)->setName((yyvsp[0])->getName());
					(yyval)->setType("notarray");
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					//cout<<line_count<<":  "<<$$->getName()<<" "<<$$->getAsmCode()<< " " << $$->getAsmSymbol()<<" "<< $$->getType()<<endl;
				}
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 731 "1605047.y" /* yacc.c:1646  */
    {
	 				//fprintf(logFile, "At line no: %d variable : ID LTHIRD expression RTHIRD\n\n", line_count);
	 				(yyval) = new SymbolInfo();
					//$$->setType("array");
					if(!symbolTable->lookUp((yyvsp[-3])->getName())) {
						error_count++;
						fprintf(logFile, "Error at line %d: Undeclared Variable: %s\n\n", line_count, (yyvsp[-3])->getName().c_str());
					}
					if((yyvsp[-1])->getDeclareType() != "int ") {
						error_count++;
						fprintf(logFile, "Error at line %d: Non-integer Array Index\n\n", line_count);
					}
					if(symbolTable->lookUp((yyvsp[-3])->getName())) {
						if(symbolTable->lookUp((yyvsp[-3])->getName())->getDeclareType() != "int array" &&
							symbolTable->lookUp((yyvsp[-3])->getName())->getDeclareType() != "float array") {
							error_count++;
							fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
						} else {
							if(symbolTable->lookUp((yyvsp[-3])->getName())->getDeclareType() == "int array") (yyvsp[-3])->setDeclareType("int ");
							if(symbolTable->lookUp((yyvsp[-3])->getName())->getDeclareType() == "float array") (yyvsp[-3])->setDeclareType("float ");
							(yyval)->setDeclareType((yyvsp[-3])->getDeclareType());
							//assembled
							(yyval)->setAsmCode((yyvsp[-1])->getAsmCode() + "\tMOV BX, " + (yyvsp[-1])->getAsmSymbol() + "\n" + "\tADD BX, BX\n");
							(yyval)->setAsmSymbol((yyvsp[-3])->getName() + toString(symbolTable->getScopeID((yyvsp[-3])->getName())));
							//map e BX er indx ta save kore rakhbo.............cause BX harai jacche
							string tempo = (string)newTemp();
							varDeclaration.push_back(tempo);
							(yyval)->setAsmCode((yyval)->getAsmCode() + "\tMOV " + tempo + ", BX\n");// temp variable
							//SymbolInfo* diye mapping hobe....anyway multiple array at multiple scope with same name can cause harm...not sure
							arrayMap[(yyvsp[-3])->getName() + "[" + (yyvsp[-1])->getName() + "]" + "array"] = tempo;// chine rakhlam
						}
					}
	 				(yyval)->setName((yyvsp[-3])->getName() + "[" + (yyvsp[-1])->getName() + "]");
					//cout<<arrayMap[$$->getName()]<<endl;
					(yyval)->setType("array");
					//cout<<line_count<< " " + $$->getAsmCode()<<" "<<$$->getAsmSymbol()<<endl;

	 				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
	 			}
#line 2294 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 773 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done
					//fprintf(logFile, "At line no: %d expression : logic_expression\n\n", line_count);
					(yyval) = new SymbolInfo();
					(yyval)->setName((yyvsp[0])->getName());
					(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
					(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
				}
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 782 "1605047.y" /* yacc.c:1646  */
    {
					//fprintf(logFile, "At line no: %d expression : variable ASSIGNOP logic_expression\n\n", line_count);
					(yyval) = new SymbolInfo();
				  if((yyvsp[0])->getDeclareType() == "void " || (symbolTable->lookUp((yyvsp[-2])->getName()) && (symbolTable->lookUp((yyvsp[-2])->getName())->getDeclareType() != (yyvsp[0])->getDeclareType()))) {
						error_count++;
						fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
						if((yyvsp[0])->getDeclareType() == "void ") (yyval)->setDeclareType("int ");
					} else {
						string codeSegment = (yyvsp[-2])->getAsmCode() + (yyvsp[0])->getAsmCode() + "\tMOV AX, " + (yyvsp[0])->getAsmSymbol()+"\n";
						if((yyvsp[-2])->getType() == "notarray")
							codeSegment += "\tMOV " + (yyvsp[-2])->getAsmSymbol() + ", AX\n";
						else {
							if(arrayMap.find((yyvsp[-2])->getName() + (yyvsp[-2])->getType()) != arrayMap.end())	//update korlam
								codeSegment += "\tMOV BX, " + arrayMap[(yyvsp[-2])->getName() + (yyvsp[-2])->getType()] + "\n"; // MOV BX, temp ; BX ke update kore dilum
							else cout<<(yyvsp[-2])->getName()<<endl;
							codeSegment += "\tMOV " + (yyvsp[-2])->getAsmSymbol() + "[BX], AX\n";
						}
						(yyval)->setAsmCode(codeSegment);
						(yyval)->setAsmSymbol((yyvsp[-2])->getAsmSymbol());
					}
					(yyval)->setDeclareType((yyvsp[-2])->getDeclareType());
					(yyval)->setName((yyvsp[-2])->getName() + "=" + (yyvsp[0])->getName());
					//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				}
#line 2337 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 809 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done
										//fprintf(logFile, "At line no: %d logic_expression : rel_expression\n\n", line_count);
										(yyval) = new SymbolInfo();
										(yyval)->setName((yyvsp[0])->getName());
										(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
										//fprintf(logFile, "%s\n\n", $$->getName().c_str());
										(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
										(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
									}
#line 2351 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 818 "1605047.y" /* yacc.c:1646  */
    {
					 					//fprintf(logFile, "At line no: %d logic_expression : rel_expression LOGICOP rel_expression\n\n", line_count);
					 					(yyval) = new SymbolInfo();
					 					if((yyvsp[-2])->getDeclareType()!= "int " || (yyvsp[0])->getDeclareType()!= "int ") { // float is not accepted in our assumption
											error_count++;
											fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
											//cout<<"#debug("<<14<<")"<<endl;
											(yyval)->setDeclareType("int ");
										} else {
											string codeSegment = (yyvsp[-2])->getAsmCode() + (yyvsp[0])->getAsmCode();
											char *assignLabel = newLabel();
											char *endLabel = newLabel();
											char *tempSymbol = newTemp();
											if((yyvsp[-1])->getName() == "&&") {
												codeSegment += "\tMOV AX, " + (yyvsp[-2])->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV AX, " + (yyvsp[0])->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV " + (string)tempSymbol + ", 1\n";
												codeSegment += "\tJMP " + (string)endLabel + "\n";
												codeSegment += (string)assignLabel + ": ";
												codeSegment += "\tMOV " + (string)tempSymbol + ", 0\n";
												codeSegment += (string)endLabel + ": ";
											} else if((yyvsp[-1])->getName() == "||") {
												codeSegment += "\tMOV AX, " + (yyvsp[-2])->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJNE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV AX, " + (yyvsp[0])->getAsmSymbol() + "\n";
												codeSegment += "\tCMP AX, 0\n";
												codeSegment += "\tJNE " + (string)assignLabel + "\n";
												codeSegment += "\tMOV " + (string)tempSymbol + ", 0\n";
												codeSegment += "\tJMP " + (string)endLabel + "\n";
												codeSegment += (string)assignLabel + ":\n\tMOV " + (string)tempSymbol + ", 1\n";
												codeSegment += (string)endLabel + ":\n";
											}
											(yyval)->setAsmCode(codeSegment);
											(yyval)->setAsmSymbol(tempSymbol);
											varDeclaration.push_back(tempSymbol);
										}
							 			(yyval)->setDeclareType("int ");
							(yyval)->setName((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
		 				}
#line 2401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 866 "1605047.y" /* yacc.c:1646  */
    {	 //okay....asm done
						//fprintf(logFile, "At line no: %d rel_expression : simple_expression\n\n", line_count);
						(yyval) = new SymbolInfo();
						(yyval)->setName((yyvsp[0])->getName());
						(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
						(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
						(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
#line 2415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 875 "1605047.y" /* yacc.c:1646  */
    {
						//fprintf(logFile, "At line no: %d rel_expression : simple_expression RELOP simple_expression\n\n", line_count);
						(yyval) = new SymbolInfo();
						if((yyvsp[-2])->getDeclareType() == "void " || (yyvsp[0])->getDeclareType() == "void ") {
							error_count++;
							fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
							(yyval)->setDeclareType("int ");
						} else {
							string codeSegment = (yyvsp[-2])->getAsmCode() + (yyvsp[0])->getAsmCode();
							codeSegment += "\tMOV AX, " + (yyvsp[-2])->getAsmSymbol() + "\n";
							codeSegment += "\tCMP AX, " + (yyvsp[0])->getAsmSymbol() + "\n";
							char *tempSymbol = newTemp();
							char *assignLabel = newLabel();
							char *endLabel = newLabel();
							if((yyvsp[-1])->getName() == "<") {
								codeSegment += "\tJL " + (string)assignLabel + "\n";
							}
							else if((yyvsp[-1])->getName() == "<=") {
								codeSegment += "\tJLE " + (string)assignLabel + "\n";
								//cout<<(string)assignLabel<<endl;
							}
							else if((yyvsp[-1])->getName() == ">") {
								codeSegment += "\tJG " + (string)assignLabel + "\n";
							}
							else if((yyvsp[-1])->getName() == ">=") {
								codeSegment += "\tJGE " + (string)assignLabel + "\n";
							}
							else if((yyvsp[-1])->getName() == "==") {
								codeSegment += "\tJE " + (string)assignLabel + "\n";
							}
							else{
								codeSegment += "\tJNE " + (string)assignLabel + "\n";
							}
							codeSegment += "\tMOV " + string(tempSymbol) +", 0\n";
							codeSegment += "\tJMP " + string(endLabel) +"\n";
							codeSegment += (string)assignLabel + ":\n\tMOV " + string(tempSymbol) + ", 1\n";
							codeSegment += string(endLabel) + ":\n";
							(yyval)->setAsmCode(codeSegment);
							(yyval)->setAsmSymbol(tempSymbol);
							varDeclaration.push_back(tempSymbol);
						}
			 			(yyval)->setDeclareType("int ");
						(yyval)->setName((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName());
						//fprintf(logFile, "%s\n\n", $$->getName().c_str());
					}
#line 2465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 923 "1605047.y" /* yacc.c:1646  */
    {	//okay.....asm done
							//fprintf(logFile, "At line no: %d simple_expression : term\n\n", line_count);
							(yyval) = new SymbolInfo();
							(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
							(yyval)->setName((yyvsp[0])->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
							(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
						}
#line 2479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 932 "1605047.y" /* yacc.c:1646  */
    {
								//fprintf(logFile, "At line no: %d simple_expression : simple_expression ADDOP term\n\n", line_count);
								(yyval)= new SymbolInfo();
								if((yyvsp[-2])->getDeclareType() == "void " || (yyvsp[0])->getDeclareType() == "void ") {
									error_count++;
									fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
									(yyval)->setDeclareType("int ");
								} else if((yyvsp[-2])->getDeclareType() == "float " || (yyvsp[0])->getDeclareType() == "float ") {
									(yyval)->setDeclareType("float ");
								} else (yyval)->setDeclareType("int ");
								(yyval)->setName((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName());
			  				//fprintf(logFile, "%s\n", $$->getName().c_str());
								string codeSegment = (yyvsp[-2])->getAsmCode() + (yyvsp[0])->getAsmCode();
								codeSegment += "\tMOV AX, " + (yyvsp[-2])->getAsmSymbol() + "\n";
								char *tempSymbol = newTemp();
								if((yyvsp[-1])->getName() == "+")
									codeSegment += "\tADD AX, " + (yyvsp[0])->getAsmSymbol() + "\n";
								else
									codeSegment += "\tSUB AX, " + (yyvsp[0])->getAsmSymbol() + "\n";
								codeSegment += "\tMOV " + string(tempSymbol) + ", AX\n";
								(yyval)->setAsmCode(codeSegment);
								(yyval)->setAsmSymbol(tempSymbol);
								varDeclaration.push_back(tempSymbol);
		  				}
#line 2508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 959 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done
				//fprintf(logFile, "At line no: %d term : unary_expression\n\n", line_count);
				(yyval) = new SymbolInfo();
				(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
				(yyval)->setName((yyvsp[0])->getName());
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
				(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
			}
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 968 "1605047.y" /* yacc.c:1646  */
    {
					//fprintf(logFile, "At line no: %d term : term MULOP unary_expression\n\n", line_count);
		 			(yyval) = new SymbolInfo();
		 			if((yyvsp[-2])->getDeclareType() == "void " || (yyvsp[0])->getDeclareType() == "void ") {
					 	error_count++;
					 	fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
					 	(yyval)->setDeclareType("int ");
					} else if((yyvsp[-1])->getName() == "%" && ((yyvsp[-2])->getDeclareType() != "int " || (yyvsp[0])->getDeclareType() != "int ")) {
						error_count++;
						fprintf(logFile, "Error at line %d: Integer operand on modulus operator\n\n", line_count);
						(yyval)->setDeclareType("int ");
					} else if((yyvsp[-1])->getName() == "/") {
						if((yyvsp[-2])->getDeclareType() == "void " || (yyvsp[0])->getDeclareType() == "void ") {
							error_count++;
							fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
							(yyval)->setDeclareType("int ");
						} else if((yyvsp[-2])->getDeclareType() == "int " && (yyvsp[0])->getDeclareType() == "int ")
							(yyval)->setDeclareType("int ");
						else (yyval)->setDeclareType("float ");
					} else if((yyvsp[-2])->getDeclareType() == "float " || (yyvsp[0])->getDeclareType() == "float ")
						 	(yyval)->setDeclareType("float ");
					else (yyval)->setDeclareType("int ");

					(yyval)->setName((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName());
     			//fprintf(logFile, "%s\n", $$->getName().c_str());
					if(!((yyvsp[-2])->getDeclareType() == "void " || (yyvsp[0])->getDeclareType() == "void ")) {
						string codeSegment = (yyvsp[-2])->getAsmCode() + (yyvsp[0])->getAsmCode();
						codeSegment += "\tMOV AX, " + (yyvsp[-2])->getAsmSymbol() + "\n";
						codeSegment += "\tMOV BX, " + (yyvsp[0])->getAsmSymbol() + "\n";
						char *tempSymbol = newTemp();
						if((yyvsp[-1])->getName() == "*"){
							codeSegment += "\tMUL BX\n";
							codeSegment += "\tMOV "+ string(tempSymbol) + ", AX\n";
						}
						else if((yyvsp[-1])->getName() == "/"){
							// clear dx, perform 'div bx' and mov ax to temp
							codeSegment += "\tMOV DX, 0\n";
							codeSegment += "\tDIV BX\n";
							codeSegment += "\tMOV " + string(tempSymbol) + ", AX\n";
						}
						else{
							// clear dx, perform 'div bx' and mov dx to temp
							codeSegment += "\tMOV DX, 0\n";
							codeSegment += "\tDIV BX\n";
							codeSegment += "\tMOV " + string(tempSymbol) + ", DX\n";
						}
						(yyval)->setAsmSymbol(tempSymbol);
						(yyval)->setAsmCode(codeSegment);
						varDeclaration.push_back(tempSymbol);
					}
     		}
#line 2578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1022 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done
							//fprintf(logFile, "At line no: %d unary_expression : ADDOP unary_expression\n\n", line_count);
							(yyval) = new SymbolInfo();
							if((yyvsp[0])->getDeclareType() == "void "){
								error_count++;
								fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
								//cout<<"#debug("<<20<<")"<<endl;
								(yyval)->setDeclareType("int ");
							} else {
								(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
								string codeSegment = (yyvsp[0])->getAsmCode();
								if((yyvsp[-1])->getName() == "-") {
									codeSegment += "\tMOV AX, " + (yyval)->getAsmSymbol() + "\n\tNEG AX\n";
									codeSegment += "\tMOV " + (yyval)->getAsmSymbol() + ", AX\n";
								}
								(yyval)->setAsmCode(codeSegment);
								(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
							}
							(yyval)->setName((yyvsp[-1])->getName() + (yyvsp[0])->getName());
							//fprintf(logFile, "%s%s\n", $$->getName().c_str());
						}
#line 2604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1043 "1605047.y" /* yacc.c:1646  */
    {
		 					//fprintf(logFile, "At line no: %d unary_expression : NOT unary_expression\n\n", line_count);
							(yyval) = new SymbolInfo();
							if((yyvsp[0])->getDeclareType() == "void "){
								error_count++;
								fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
								(yyval)->setDeclareType("int ");
							} else {
								(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
								string codeSegment = (yyvsp[0])->getAsmCode();
								codeSegment += "\tMOV AX, " + (yyval)->getAsmSymbol() + "\n\tNOT AX\n";
								codeSegment += "\tMOV " + (yyval)->getAsmSymbol() + ", AX\n";
								(yyval)->setAsmCode(codeSegment);
								(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
							}
							(yyval)->setName("!" + (yyvsp[0])->getName());
							//fprintf(logFile, "!%s\n\n", $$->getName().c_str());
		 				}
#line 2627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1061 "1605047.y" /* yacc.c:1646  */
    {
		 					//fprintf(logFile, "At line no: %d unary_expression : factor\n\n", line_count);
							(yyval) = new SymbolInfo();
							(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
							(yyval)->setName((yyvsp[0])->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
							(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
		 				}
#line 2641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1073 "1605047.y" /* yacc.c:1646  */
    {	//okay.....asm done
				//ERROR declared here.....
				///if($1->getDeclareType() == "int array")$1->setName("error"); // kind of error recovery....but we consider no error in input.c file
				//fprintf(logFile, "At line no: %d factor : variable\n\n", line_count);
				(yyval) = new SymbolInfo();
				(yyval)->setName((yyvsp[0])->getName());
				(yyval)->setDeclareType((yyvsp[0])->getDeclareType());
				//why we do that here
				string str = "";
				for(int i = 0; i < (yyval)->getName().size(); i++)
					if((yyval)->getName()[i] == '[')break;
					else str += (yyval)->getName()[i];
				(yyval)->setName(str);
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());

				//generate assembly code
				string codeSegment = (yyvsp[0])->getAsmCode();
				if((yyvsp[0])->getType() == "notarray") {
					(yyval)->setAsmSymbol((yyvsp[0])->getAsmSymbol());
				} else {
					char *tempSymbol = newTemp();
					codeSegment += "\tMOV AX, " + (yyvsp[0])->getAsmSymbol() + "[BX]\n";
					codeSegment += "\tMOV " + string(tempSymbol) + ", AX\n";
					(yyval)->setAsmSymbol(tempSymbol);
					varDeclaration.push_back(tempSymbol);
				}
				(yyval)->setAsmCode(codeSegment);
			}
#line 2674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1101 "1605047.y" /* yacc.c:1646  */
    {
				//fprintf(logFile, "At line no: %d factor : ID LPAREN argument_list RPAREN\n\n", line_count);
				SymbolInfo* symfo = symbolTable->lookUp((yyvsp[-3])->getName());
				if(!symfo) { //nai
					error_count++;
					fprintf(logFile, "Error at line %d:  Undefined Function\n\n", line_count);
					(yyval)->setDeclareType("int ");
				}
				else if(!symfo->getFunctionDetails()) { //ache but func na
					error_count++;
					fprintf(logFile, "Error at line %d:  Not A Function\n\n", line_count);
					(yyval)->setDeclareType("int ");
				}
				else if(!symfo->getFunctionDetails()->isDefined1()) {
					error_count++;
					fprintf(logFile, "Error at line %d: Undeclared Function\n\n", line_count);
				} else {
					int num = symfo->getFunctionDetails()->getParamCount();
					(yyval)->setDeclareType(symfo->getFunctionDetails()->getReturnType());
					if(num != argList.size()) {
						error_count++;
						fprintf(logFile, "Error at line %d: Invalid number of arguments\n\n", line_count);
					} else{
						ds tempVarList = symbolTable->lookUp((yyvsp[-3])->getName())->getFunctionDetails()->getFuncVarList();
						ds tempParamTypeList = symbolTable->lookUp((yyvsp[-3])->getName())->getFunctionDetails()->getArgTypeList();
						ds tempParamList = symbolTable->lookUp((yyvsp[-3])->getName())->getFunctionDetails()->getArgList();
						string codeSegment = (yyvsp[-1])->getAsmCode();
						for(int i = 0; i < argList.size(); i++) {
							codeSegment += "\tMOV AX, " + argList[i]->getAsmSymbol() + "\n";
							codeSegment += "\tMOV " + tempParamList[i] + ", AX\n";
							if(argList[i]->getDeclareType() != tempParamTypeList[i]){
								error_count++;
								fprintf(logFile, "Error at line %d: Type Mismatch\n\n", line_count);
								break;
							}
						}
						codeSegment += "\tCALL " + (yyvsp[-3])->getName() + "\n";
						string calleeRetVal = (yyvsp[-3])->getName() + "_FunRetVar";
						if(decLaredVar.find(calleeRetVal) != decLaredVar.end()) 	codeSegment += "\tMOV AX, " + calleeRetVal + "\n";
						//codeSegment += "\tMOV AX, " + $1->getName() + "_FunRetVar\n";
						string tempSymbol = (string)newTemp();
						codeSegment += "\tMOV " + tempSymbol + ", AX\n";
						(yyval)->setAsmSymbol(tempSymbol);
						(yyval)->setAsmCode(codeSegment);
						varDeclaration.push_back(tempSymbol);
					}
				}
				argList.clear();
				(yyval)->setName((yyvsp[-3])->getName() + "( " + (yyvsp[-1])->getName() + " )");
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
			}
#line 2730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1152 "1605047.y" /* yacc.c:1646  */
    {
				//fprintf(logFile, "At line no: %d factor : LPAREN expression RPAREN\n\n", line_count);
				(yyval) = new SymbolInfo();
				(yyval)->setDeclareType((yyvsp[-1])->getDeclareType());
				(yyval)->setName("(" + (yyvsp[-1])->getName() + ")");
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				(yyval)->setAsmCode((yyvsp[-1])->getAsmCode());
				(yyval)->setAsmSymbol((yyvsp[-1])->getAsmSymbol());
			}
#line 2744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1161 "1605047.y" /* yacc.c:1646  */
    {
				//fprintf(logFile, "At line no: %d factor : CONST_INT\n\n", line_count);
				(yyval) = new SymbolInfo();
				(yyval)->setDeclareType("int ");
				(yyval)->setName((yyvsp[0])->getName());
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "\tMOV " + tempSymbol + ", " + (yyvsp[0])->getName() + "\n";
				(yyval)->setAsmCode(codeSegment);
				(yyval)->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
#line 2761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1173 "1605047.y" /* yacc.c:1646  */
    {
				//fprintf(logFile, "At line no: %d factor : CONST_FLOAT\n\n", line_count);
				(yyval) = new SymbolInfo();
				(yyval)->setDeclareType("float ");
				(yyval)->setName((yyvsp[0])->getName());
				//fprintf(logFile, "%s\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "\tMOV " + tempSymbol + ", " + (yyvsp[0])->getName() + "\n";
				(yyval)->setAsmCode(codeSegment);
				(yyval)->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
#line 2778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1185 "1605047.y" /* yacc.c:1646  */
    {
				//fprintf(logFile, "At line no: %d factor : variable INCOP\n\n", line_count);
				(yyval) = new SymbolInfo();
				(yyval)->setDeclareType((yyvsp[-1])->getDeclareType());
				(yyval)->setName((yyvsp[-1])->getName() + "++");
				//fprintf(logFile, "%s++\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "";
				if((yyvsp[-1])->getType() == "array") {
					codeSegment += "\tMOV AX, " + (yyvsp[-1])->getAsmSymbol() + "[BX]\n";
					codeSegment += "\tMOV "+ tempSymbol + ", AX\n";
					codeSegment += "\tINC AX\n";
					codeSegment += "\tMOV " + (yyvsp[-1])->getAsmSymbol() + "[BX], AX\n";
				} else {
					codeSegment += "\tMOV AX, " + (yyvsp[-1])->getAsmSymbol() + "\n\tMOV " + tempSymbol + ", AX\n\tINC " + (yyvsp[-1])->getAsmSymbol() + "\n";
				}
				(yyval)->setAsmCode(codeSegment);
				(yyval)->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
#line 2803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1205 "1605047.y" /* yacc.c:1646  */
    {
				//fprintf(logFile, "At line no: %d factor : variable DECOP\n\n", line_count);
				(yyval) = new SymbolInfo();
				(yyval)->setDeclareType((yyvsp[-1])->getDeclareType());
				(yyval)->setName((yyvsp[-1])->getName() + "--");
				//fprintf(logFile, "%s--\n\n", $$->getName().c_str());
				string tempSymbol = (string)newTemp();
				string codeSegment = "";
				if((yyvsp[-1])->getType() == "array") {
					codeSegment += "\tMOV AX, " + (yyvsp[-1])->getAsmSymbol() + "[BX]\n";
					codeSegment += "\tMOV "+ tempSymbol + ", AX\n";
					codeSegment += "\tDEC AX\n";
					codeSegment += "\tMOV " + (yyvsp[-1])->getAsmSymbol() + "[BX], AX\n";
				} else {
					codeSegment += "\tMOV AX, " + (yyvsp[-1])->getAsmSymbol() + "\n\tMOV " + tempSymbol + ", AX\n\tDEC " + (yyvsp[-1])->getAsmSymbol() + "\n";
				}
				(yyval)->setAsmCode(codeSegment);
				(yyval)->setAsmSymbol(tempSymbol);
				varDeclaration.push_back(tempSymbol);
			}
#line 2828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1228 "1605047.y" /* yacc.c:1646  */
    {  //okay...asm done
									//chanded
									////fprintf(logFile, "At line no: %d argument_list : arguments\n\n", line_count);
									(yyval) = new SymbolInfo();
									(yyval)->setName((yyvsp[0])->getName());
									(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
								}
#line 2840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1235 "1605047.y" /* yacc.c:1646  */
    {
					  			(yyval) = new SymbolInfo();
					  			(yyval)->setName("");
					  			//fprintf(logFile, "At line no: %d argument_list : \n\n", line_count);
					  		}
#line 2850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1243 "1605047.y" /* yacc.c:1646  */
    {	//okay....asm done
							//fprintf(logFile, "At line no: %d argument_list : argument_list COMMA logic_expression\n\n", line_count);
							(yyval) = new SymbolInfo();
							(yyval)->setName((yyvsp[-2])->getName() + " , " + (yyvsp[0])->getName());
							//fprintf(logFile, "%s, %s\n\n", $1->getName().c_str(), $3->getName().c_str());
							argList.push_back((yyvsp[0])); //new argument as a logic_expression...size and type matter kore only
							(yyval)->setAsmCode((yyvsp[-2])->getAsmCode() + (yyvsp[0])->getAsmCode());
						}
#line 2863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1251 "1605047.y" /* yacc.c:1646  */
    {
							//fprintf(logFile, "At line no: %d argument_list : logic_expression\n\n", line_count);
							(yyval) = new SymbolInfo();
							(yyval)->setName((yyvsp[0])->getName());
							//fprintf(logFile, "%s\n\n", $$->getName().c_str());
							argList.push_back((yyvsp[0]));	//first argument
			      	(yyval)->setAsmCode((yyvsp[0])->getAsmCode());
		      	}
#line 2876 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2880 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
                      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 1263 "1605047.y" /* yacc.c:1906  */



int main(int argc,char *argv[]) {

	if(!(fp = fopen(argv[1], "r"))) {
		printf("Please provide input file name and try again\n\n");
		exit(1);
	}

	yyin = fp;
	yyparse();

	//fprintf(logFile, "\n\n\n\nSymbol Table: \n");
	//symbolTable->printAllScopeTable();
	line_count--;
	fprintf(logFile, "\nTotal Lines : %d \n\n", line_count);
	fprintf(logFile, "Total Errors : %d \n\n", error_count);


	fclose(logFile);
	//fclose(errorFile);

	return 0;
}

string definedVariables() {
	string vars = "";
	for(int i = 0; i < varDeclaration.size(); i++) {
		vars += "\t" + varDeclaration[i] + " dw ?\n";
	}
	return vars;
}

string definedArrays() {
	string arrays = "";
	for(int i = 0; i < arrVarDeclaration.size(); i++) {
		arrays += "\t" + arrVarDeclaration[i].first + " dw " + arrVarDeclaration[i].second + " dup(?)\n";
	}
	return arrays;
}

string defineProcRINTLN() {
	return
	"\nPRINTLN PROC\n"
	"\tPUSH AX\n"
	"\tPUSH BX\n"
	"\tPUSH CX\n"
	"\tPUSH DX\n"
	"\tCMP AX,0\n"
	"\tJGE BEGIN\n"
	"\tPUSH AX\n"
	"\tMOV DX, '-'\n"
	"\tMOV AH, 2\n"
	"\tINT 21H\n"
	"\tPOP AX\n"
	"\tNEG AX\n"
	"BEGIN:\n"
	"\tXOR CX, CX\n"
	"\tMOV BX, 10\n"
	"REPEAT:\n"
	"\tXOR DX, DX\n"
	"\tDIV BX\n"
	"\tPUSH DX\n"
	"\tINC CX\n"
	"\tOR AX, AX\n"
	"\tJNE REPEAT\n"
	"\tMOV AH, 2\n"
	"PRINT_LOOP:\n"
	"\tPOP DX\n"
	"\tADD DX, 30H\n"
	"\tINT 21H\n"
	"\tLOOP PRINT_LOOP\n"
	"\tMOV AH, 2\n"
	"\tMOV DX, 10\n"
	"\tINT 21H\n"
	"\tMOV DX, 13\n"
	"\tINT 21H\n"
	"\tPOP DX\n"
	"\tPOP CX\n"
	"\tPOP BX\n"
	"\tPOP AX\n"
	"\tret\n"
	"PRINTLN ENDP\n";
}

void printICG(string icg) {
	ofstream asmOut;
	asmOut.open("code.asm");
	asmOut << "TITLE PGMx.x: ASSEMLY(8086) INTERMIDIATE CODE GENERATED(without PeepHole optimization) FOR C PROGRAM PROVIDED\n" << endl;
	asmOut << icg << endl;
	asmOut.close();
}

string removeWS(string str) {
	stringstream ss(str);
	string temp = "";
	while(ss >> str)temp = (temp == "")? str : temp + " " + str;
	return temp;
}

vs split_string(string str, string _dlm) {
    vs tokens; size_t prev = 0, pos = 0;
    do {
        pos = str.find(_dlm, prev);
        if (pos == string::npos) pos = str.size();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + _dlm.size();
    } while (pos < str.size() && prev < str.size());
    return tokens;
}

//MOV t0, 0
//MOV AX, t0.........eitype e optimize korle problem hoite pare...cause t0 use hoitese kina jani na
bool isAllDigits(const std::string &str) {	//ignored..not used at all
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

bool pushPeep(string s1, string s2, string s3) {
	vs token1 = split_string(removeWS(s1), " ");
	vs token2 = split_string(removeWS(s2), " ");
	vs token3 = split_string(removeWS(s3), " ");
	//cout<<token1<<"|"<<token2<<"|"<<token3<<"|"<<endl;
  return (token1.size() == 2 && token2.size() == 1 && token2[0][token2[0].size()-1] == ':' && token3.size() == 2 && token1[0] == "PUSH" && token3[0] == "POP" && token1[1] == token3[1]);
}

bool moveConflict(string s1, string s2) {
	vs token1 = split_string(removeWS(s1), " ");
	vs token2 = split_string(removeWS(s2), " ");
	return (token1.size() == 3 && token2.size() == 3 && token1[0] == "MOV" && token2[0] == "MOV" && token1[1] == (token2[2] + ",") && (token1[2] + ",") == token2[1]);
}

bool jumpConflict(string s1, string s2) {
	vs token1 = split_string(removeWS(s1), " ");
	vs token2 = split_string(removeWS(s2), " ");
	return token1.size() == 2 && token1[0] == "JMP" && token2.size() == 1 && (token1[1] + ":") == token2[0];
}

void printOptimizedICG(string nonOptimizedICG) {
	ifstream asmIn("code.asm");
	ofstream optOut("Code.asm");
	string currentLine;
	vs codeSegment;
	while(getline(asmIn, currentLine)) {

		if(codeSegment.empty())
		{
			codeSegment.push_back(currentLine);
		}
		else if(codeSegment.size() == 1)
		{
			if(moveConflict(codeSegment[codeSegment.size() - 1], currentLine));
			else if(jumpConflict(codeSegment[codeSegment.size() - 1], currentLine)) {
				codeSegment.pop_back();
				codeSegment.push_back(currentLine);
			} else codeSegment.push_back(currentLine);
		}
		else if(codeSegment.size() >= 2)
		{
			if(moveConflict(codeSegment.back(), currentLine));
			else if(jumpConflict(codeSegment[codeSegment.size() - 1], currentLine)) {
				codeSegment.pop_back();
				codeSegment.push_back(currentLine);
			} else if( pushPeep(codeSegment[codeSegment.size()-2], codeSegment[codeSegment.size()-1], currentLine) ) {
				codeSegment[codeSegment.size()-2] = codeSegment[codeSegment.size()-1];
				codeSegment.pop_back();
			} else codeSegment.push_back(currentLine);
		}

	}

	optOut << "TITLE PGMopt.opt: ASSEMLY(8086) INTERMIDIATE CODE GENERATED(with PeepHole optimization) FOR C PROGRAM PROVIDED\n" << endl;
	for(int i = 1; i < codeSegment.size(); i++) {
		optOut << codeSegment[i] << endl;
	}
	asmIn.close();
	optOut.close();
}
