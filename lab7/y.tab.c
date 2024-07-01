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
#line 1 "lab7.y" /* yacc.c:339  */


/* 
	
    Ryan Lucero
    Lab 7
    lab7.y
    4/10/2024
    CS370 Shaun Cooper

    LAB 7: 
    This YACC file is a continuation of the CMINUS+ compiler from Lab 6. In this iteration, 
    I've introduced a comprehensive symbol table to manage scopes, variables, and function declarations more effectively. 
    Notable enhancements include dynamic handling of scopes through level and offset management, checks for 
    type consistency and variable/function existence before use, and more error handling mechanisms. 
    

    This YACC file is part of the compiler for the CMINUS+ programming language. It defines the grammar of CMINUS+, 
    including the syntax for variable and function declarations, statements, expressions, etc.  
    The grammar rules are implemented to construct an abstract syntax tree for a given program in CMINUS+. 
    Each rule in the grammar is accompanied by actions that create and link AST nodes, generating the hierarchy 
    structure of the provided programs source code. I have introduced the enhancements which include he integration of abstract syntax
    tree generation, expanding the grammar to support a broader range of language features.


*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ast.h"
#include "symtable.h"



ASTnode *PROGRAM;

int yylex(); // added yylex() with int variable to be able to call yywrap from lex file
extern int mydebug; //from lex
extern int lineno; //from lex 

int LEVEL = 0; //global context variable to know how deep we are
int OFFSET = 0; //global variable for accumilation needed runtime space
int GOFFSET = 0; //global variable for accumilation global variable offset
int maxoffset = 0; //the largest offset needed of the current function


void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("YACC PARSE ERROR: %s syntax error on line number %d\n", s, lineno);
}


#line 123 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
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
    T_NUM = 258,
    T_ID = 259,
    T_STRING = 260,
    T_INT = 261,
    T_VOID = 262,
    T_READ = 263,
    T_IF = 264,
    T_ELSE = 265,
    T_WHILE = 266,
    T_WRITE = 267,
    T_RET = 268,
    T_LT = 269,
    T_GT = 270,
    T_GE = 271,
    T_LE = 272,
    T_EQ = 273,
    T_NE = 274
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_ID 259
#define T_STRING 260
#define T_INT 261
#define T_VOID 262
#define T_READ 263
#define T_IF 264
#define T_ELSE 265
#define T_WHILE 266
#define T_WRITE 267
#define T_RET 268
#define T_LT 269
#define T_GT 270
#define T_GE 271
#define T_LE 272
#define T_EQ 273
#define T_NE 274

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 61 "lab7.y" /* yacc.c:355  */

      int value;
      char * string;
      ASTnode *node; 
      enum AST_MY_DATA_TYPE d_type; 
      enum AST_OPERATORS operator; 

#line 209 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 226 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    33,     2,     2,
      24,    25,    31,    29,    23,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    20,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    21,     2,    22,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   104,   106,   113,   114,   117,   149,   154,
     160,   166,   175,   177,   182,   199,   181,   213,   214,   217,
     218,   225,   243,   262,   262,   276,   277,   284,   285,   293,
     295,   297,   299,   301,   303,   305,   307,   311,   316,   323,
     332,   344,   352,   357,   364,   371,   377,   384,   401,   426,
     453,   457,   458,   476,   477,   478,   479,   480,   481,   484,
     485,   502,   503,   506,   507,   524,   525,   526,   529,   530,
     536,   537,   538,   546,   581,   584,   587,   596
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_NUM", "T_ID", "T_STRING", "T_INT",
  "T_VOID", "T_READ", "T_IF", "T_ELSE", "T_WHILE", "T_WRITE", "T_RET",
  "T_LT", "T_GT", "T_GE", "T_LE", "T_EQ", "T_NE", "';'", "'['", "']'",
  "','", "'('", "')'", "'{'", "'}'", "'='", "'+'", "'-'", "'*'", "'/'",
  "'%'", "$accept", "Program", "Declaration_List", "Declaration",
  "Var_Declaration", "Var_List", "Type_Specifier", "Fun_Declaration",
  "$@1", "$@2", "Params", "Param_List", "Param", "Compound_Stmt", "$@3",
  "Local_Declarations", "Statement_List", "Statement",
  "Expression_Statement", "Selection_Statement", "Iteration_Statement",
  "Return_Statement", "Read_Statement", "Write_Statement",
  "Assignment_Statement", "Var", "Expression", "Simple_Expression",
  "Relop", "Additive_Expression", "AddOp", "Term", "MultOp", "Factor",
  "Call", "Args", "Args_List", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      59,    91,    93,    44,    40,    41,   123,   125,    61,    43,
      45,    42,    47,    37
};
# endif

#define YYPACT_NINF -114

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-114)))

#define YYTABLE_NINF -18

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       2,  -114,  -114,    13,  -114,     2,  -114,    37,  -114,  -114,
    -114,    29,    12,    51,    64,    45,  -114,    48,    39,  -114,
      40,    57,    56,    78,    60,  -114,    63,    64,    62,  -114,
       2,  -114,    67,    65,  -114,  -114,  -114,  -114,     2,     2,
      64,     7,  -114,  -114,    19,    86,    68,    69,    18,    31,
    -114,    35,    35,  -114,    70,     7,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,    66,    75,  -114,    58,    25,  -114,  -114,
      35,    35,    77,    76,    35,    35,    79,  -114,    80,  -114,
      81,    82,  -114,  -114,  -114,    35,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,    35,    35,  -114,  -114,  -114,
      35,    83,    85,    84,  -114,  -114,    87,    88,  -114,  -114,
    -114,  -114,    90,    34,    25,  -114,  -114,    35,  -114,     7,
       7,  -114,  -114,    92,  -114,     7,  -114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,     0,     2,     3,     5,     0,     6,     1,
       4,     8,     0,     0,     0,     0,     7,     0,     8,    10,
       0,     9,    13,     0,     0,    18,    19,     0,    21,    15,
       0,    11,     0,     0,    20,    22,    23,    16,    25,    25,
       0,    27,    26,    69,    48,     0,     0,     0,     0,     0,
      38,     0,     0,    30,     0,    27,    29,    31,    32,    34,
      35,    36,    33,    70,     0,    50,    51,    59,    63,    71,
       0,    75,    48,     0,     0,     0,     0,    70,     0,    42,
       0,     0,    72,    24,    28,     0,    37,    53,    54,    55,
      56,    57,    58,    61,    62,     0,     0,    65,    66,    67,
       0,     0,    76,     0,    74,    44,     0,     0,    46,    45,
      43,    68,     0,    52,    60,    64,    49,     0,    73,     0,
       0,    47,    77,    39,    41,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -114,  -114,    98,  -114,    28,     3,     6,  -114,  -114,  -114,
    -114,    74,  -114,    73,  -114,    72,    59,  -113,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,   -41,   -46,    30,  -114,    21,
    -114,    22,  -114,   -51,  -114,  -114,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,     7,     8,    15,    33,
      24,    25,    26,    53,    38,    41,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    77,    64,    65,    95,    66,
      96,    67,   100,    68,    69,   103,   104
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      63,    82,    78,    80,    73,    81,   123,   124,     1,     2,
      43,    44,   126,     9,    63,    45,    46,    19,    47,    48,
      49,    43,    44,    76,   101,   102,    23,    50,   106,   107,
      31,    51,    16,    36,    43,    44,    23,    52,    43,    44,
      70,    11,    51,    71,    40,    40,     1,    22,    52,   115,
      13,    79,    14,   -14,    17,    51,    97,    98,    99,    51,
      13,    52,    14,    93,    94,    52,    39,    39,    18,    20,
      21,   102,    87,    88,    89,    90,    91,    92,    63,    63,
      27,   -17,    28,    32,    63,    29,    30,    93,    94,    35,
      72,    36,    74,    75,    85,    86,   105,    83,    70,   108,
     109,   110,   125,    10,    34,   116,    37,   111,   117,   118,
     121,    42,   119,   120,    84,   112,   113,   122,   114
};

static const yytype_uint8 yycheck[] =
{
      41,    52,    48,    49,    45,    51,   119,   120,     6,     7,
       3,     4,   125,     0,    55,     8,     9,    14,    11,    12,
      13,     3,     4,     5,    70,    71,    20,    20,    74,    75,
      27,    24,    20,    26,     3,     4,    30,    30,     3,     4,
      21,     4,    24,    24,    38,    39,     6,     7,    30,   100,
      21,    20,    23,    24,     3,    24,    31,    32,    33,    24,
      21,    30,    23,    29,    30,    30,    38,    39,     4,    24,
      22,   117,    14,    15,    16,    17,    18,    19,   119,   120,
      23,    25,     4,    21,   125,    25,    23,    29,    30,    22,
       4,    26,    24,    24,    28,    20,    20,    27,    21,    20,
      20,    20,    10,     5,    30,    22,    33,    25,    23,    25,
      20,    39,    25,    25,    55,    85,    95,   117,    96
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    35,    36,    37,    38,    40,    41,     0,
      36,     4,    39,    21,    23,    42,    20,     3,     4,    39,
      24,    22,     7,    40,    44,    45,    46,    23,     4,    25,
      23,    39,    21,    43,    45,    22,    26,    47,    48,    38,
      40,    49,    49,     3,     4,     8,     9,    11,    12,    13,
      20,    24,    30,    47,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    63,    65,    67,    68,
      21,    24,     4,    59,    24,    24,     5,    59,    60,    20,
      60,    60,    67,    27,    50,    28,    20,    14,    15,    16,
      17,    18,    19,    29,    30,    62,    64,    31,    32,    33,
      66,    60,    60,    69,    70,    20,    60,    60,    20,    20,
      20,    25,    61,    63,    65,    67,    22,    23,    25,    25,
      25,    20,    70,    51,    51,    10,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    39,    39,
      39,    39,    40,    40,    42,    43,    41,    44,    44,    45,
      45,    46,    46,    48,    47,    49,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    57,    57,    58,    59,    59,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    67,    67,
      67,    67,    67,    68,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     4,
       3,     6,     1,     1,     0,     0,     8,     1,     1,     1,
       3,     2,     4,     0,     5,     0,     2,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     5,
       7,     5,     2,     3,     3,     3,     3,     4,     1,     4,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     2,     4,     1,     0,     1,     3
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
#line 101 "lab7.y" /* yacc.c:1646  */
    {PROGRAM = (yyvsp[0].node); }
#line 1392 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 105 "lab7.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 107 "lab7.y" /* yacc.c:1646  */
    { 
                    (yyval.node) = (yyvsp[-1].node); // the current declaration becomes the head of the list
                    (yyval.node) -> next = (yyvsp[0].node); //link the current declaration to the rest of the list
                 }
#line 1407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 113 "lab7.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 1413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 114 "lab7.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 1419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 118 "lab7.y" /* yacc.c:1646  */
    { 
                  ASTnode *p = (yyvsp[-1].node);  //set p to the head of the variable list
                  while(p != NULL) {
                    p -> my_data_type = (yyvsp[-2].d_type); //assign the type
                     //set the variable to s1
                    if(Search(p->name, LEVEL, 0) != NULL)
                    {
                      //symbol already defined -- BARF
                      yyerror(p->name);
                      yyerror("Symbol already defined");
                      exit(1);
                    }
                    //it was not in the sumbol table
                    if(p -> value == 0)
                    {
                      //we have scalar
                      p->symbol = Insert(p->name, p->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);   //insert the scalar into the symbol table
                      OFFSET = OFFSET + 1; 
                    } else
                    {
                      //we have array
                    p->symbol = Insert(p->name, p->my_data_type, SYM_ARRAY, LEVEL, p->value, OFFSET); //insert the array into the symbol table
                      OFFSET = OFFSET + p->value; 
                    }
                    
                  p = p -> s1;
                  }
                  (yyval.node) = (yyvsp[-1].node); //the result is the head of the variable list
                }
#line 1453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 150 "lab7.y" /* yacc.c:1646  */
    { 
          (yyval.node) = ASTCreateNode (A_VARDEC); 
          (yyval.node)-> name = (yyvsp[0].string); //set name
         }
#line 1462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 155 "lab7.y" /* yacc.c:1646  */
    { 
          (yyval.node) = ASTCreateNode (A_VARDEC);
          (yyval.node)-> name = (yyvsp[-3].string);  //set name
          (yyval.node) -> value = (yyvsp[-1].value); //set value
         }
#line 1472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 161 "lab7.y" /* yacc.c:1646  */
    {
          (yyval.node) = ASTCreateNode (A_VARDEC);
          (yyval.node) -> name = (yyvsp[-2].string); //set name
          (yyval.node) -> s1 = (yyvsp[0].node);  //set s1 to var_list
         }
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 167 "lab7.y" /* yacc.c:1646  */
    { 
          (yyval.node) = ASTCreateNode (A_VARDEC); 
          (yyval.node)-> name = (yyvsp[-5].string); //set name
          (yyval.node) -> value = (yyvsp[-3].value); //set value to value in []
          (yyval.node) -> s1 = (yyvsp[0].node); //set s1 to var_list
         }
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 176 "lab7.y" /* yacc.c:1646  */
    { (yyval.d_type) = A_INTTYPE;}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 178 "lab7.y" /* yacc.c:1646  */
    { (yyval.d_type) = A_VOIDTYPE;}
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 182 "lab7.y" /* yacc.c:1646  */
    { //check to see if function has been defined
                  if(Search((yyvsp[0].string), LEVEL, 0) != NULL){
                    //id has already been used -- BARF
                    yyerror((yyvsp[0].string));
                    yyerror("Function name already in use");
                    exit(1);
                  }

                  // not in symbol table -> install it
                  Insert((yyvsp[0].string), (yyvsp[-1].d_type), SYM_FUNCTION, LEVEL, 0, 0);  //insert the function into the symbol table

                  GOFFSET = OFFSET; //set the global offset to the current offset
                  OFFSET = 2; //reset the offset for the function
                  maxoffset = OFFSET; //set the max offset to the current offset

                }
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 199 "lab7.y" /* yacc.c:1646  */
    {Search((yyvsp[-4].string), LEVEL, 0)->fparms = (yyvsp[-1].node);}
#line 1532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 201 "lab7.y" /* yacc.c:1646  */
    { (yyval.node) = ASTCreateNode(A_FUNCTIONDEC); 
                  (yyval.node) -> name = (yyvsp[-6].string); //set name
                  (yyval.node) -> my_data_type = (yyvsp[-7].d_type);  //ser data type
                  (yyval.node) -> s1 = (yyvsp[-3].node); //set s1 to be calue in ()
                  (yyval.node) -> s2 = (yyvsp[0].node); //set s2 to be compound_stmt
                  (yyval.node)->symbol = Search((yyvsp[-6].string), LEVEL, 0);  //set symbol to the function name

                  Search((yyvsp[-6].string), LEVEL, 0) -> offset = maxoffset; //set the offset of the function
                  OFFSET = GOFFSET; //resets the offset for global variables
                }
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 213 "lab7.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 214 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 217 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 219 "lab7.y" /* yacc.c:1646  */
    {
            (yyval.node) = (yyvsp[-2].node); //pass one parameter up
            (yyval.node) -> next = (yyvsp[0].node); // if more than 1 parameter, set next to param_list
           }
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 226 "lab7.y" /* yacc.c:1646  */
    { 
        if(Search((yyvsp[0].string), LEVEL+1, 0) != NULL)    //check to see if the parameter has already been defined
        {
          yyerror((yyvsp[0].string));
          yyerror("parameter already used");  
          exit(1);    //exit if the parameter has already been defined
        }

       (yyval.node) = ASTCreateNode(A_PARAM); //create node for parameter
       (yyval.node) -> value = 0;
       (yyval.node) -> name = (yyvsp[0].string); //set parameter name
       (yyval.node) -> my_data_type = (yyvsp[-1].d_type); //set parameter type
       (yyval.node)->symbol=Insert((yyval.node)->name, (yyval.node)->my_data_type, SYM_SCALAR, LEVEL+1, 1, OFFSET); //insert the parameter into the symbol table

       OFFSET = OFFSET + 1;

      }
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 244 "lab7.y" /* yacc.c:1646  */
    {  
        if(Search((yyvsp[-2].string), LEVEL+1, 0) != NULL){ //check to see if the parameter has already been defined
          yyerror((yyvsp[-2].string));
          yyerror("parameter already used");
          exit(1);  //exit if the parameter has already been defined
        }

       (yyval.node) = ASTCreateNode(A_PARAM); // create node for array parameter
       (yyval.node) -> my_data_type = (yyvsp[-3].d_type); //set data type of parameter
       (yyval.node) -> name = (yyvsp[-2].string);  //set name of parameter
       (yyval.node) -> value = 1; //set value of parameter

       (yyval.node)->symbol=Insert((yyval.node)->name, (yyval.node)->my_data_type, SYM_ARRAY, LEVEL+1, 1, OFFSET);  //insert the parameter into the symbol table

        OFFSET = OFFSET + 1;
      }
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 262 "lab7.y" /* yacc.c:1646  */
    { LEVEL ++; }
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 264 "lab7.y" /* yacc.c:1646  */
    {
               (yyval.node) = ASTCreateNode(A_COMPOUND); //create node for a compound statement
               (yyval.node) -> s1 = (yyvsp[-2].node); // send upsteam s1 with local declarations
               (yyval.node) -> s2 = (yyvsp[-1].node); // send upstream s2 with statement list
               Display();
            //we set the maxoffset 
               if(OFFSET > maxoffset) maxoffset = OFFSET;
               OFFSET -= Delete(LEVEL); 
               LEVEL --;
             }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 276 "lab7.y" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 278 "lab7.y" /* yacc.c:1646  */
    { 
                    (yyval.node) = (yyvsp[-1].node); // upstream recieves current var declarations
                    (yyval.node) -> next = (yyvsp[0].node); //link to local declarations
                   }
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 284 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 286 "lab7.y" /* yacc.c:1646  */
    { 
                (yyval.node) = (yyvsp[-1].node); //upstream gets current statement
                (yyval.node) -> next = (yyvsp[0].node);  //link next statement in list
               }
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 294 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 296 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 298 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 300 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 302 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 304 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 306 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 308 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 312 "lab7.y" /* yacc.c:1646  */
    {
                     (yyval.node) = ASTCreateNode(A_EXPRESSIONSTMT); // create an expression statement node
                     (yyval.node) -> s1 = (yyvsp[-1].node); //upstream gets the expression
                    }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 317 "lab7.y" /* yacc.c:1646  */
    { 
                      (yyval.node) = ASTCreateNode(A_EXPRESSIONSTMT);
                      (yyval.node) -> s1 = NULL; //upstream get no expression
                    }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 324 "lab7.y" /* yacc.c:1646  */
    {
                    (yyval.node) = ASTCreateNode(A_IF); // Create an if statement node
                    (yyval.node) -> s1 = (yyvsp[-2].node); // sends upstream s1 with expression
                    (yyval.node) -> s2 = ASTCreateNode(A_IF); //create 'then' statement node
                    (yyval.node) ->s2 -> s1 = (yyvsp[0].node); //upstream gets the 'then' statement
                    (yyval.node) -> s2 -> s2 = NULL; //no else

                   }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 333 "lab7.y" /* yacc.c:1646  */
    {
                    (yyval.node) = ASTCreateNode(A_IF); // Create an if statement node
                    (yyval.node) -> s1 = (yyvsp[-4].node); // sends upstream s1 with expression
                    (yyval.node) -> s2 = ASTCreateNode(A_IF); //create 'then' statement node
                    (yyval.node) -> s2 -> s1 = (yyvsp[-2].node); //upstream gets the 'then' statement
                    (yyval.node) -> s2 -> s2 = (yyvsp[0].node); //else statement gets set to s2->s2

                   }
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 345 "lab7.y" /* yacc.c:1646  */
    { 
                     (yyval.node) = ASTCreateNode(A_WHILE); // create a while loop node
                     (yyval.node) -> s1 = (yyvsp[-2].node); //upstream gets the loop condition
                     (yyval.node) -> s2 = (yyvsp[0].node); //upstream gets loop body
                   }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 353 "lab7.y" /* yacc.c:1646  */
    {
                  (yyval.node) = ASTCreateNode(A_RETURN); //create a return statement node
                  (yyval.node) -> s1 = NULL;  // no return value
                }
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 358 "lab7.y" /* yacc.c:1646  */
    {
                  (yyval.node) = ASTCreateNode(A_RETURN); //create a return statement node
                  (yyval.node) -> s1 = (yyvsp[-1].node); //pass up the expression to return
                }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 365 "lab7.y" /* yacc.c:1646  */
    { 
                (yyval.node) = ASTCreateNode(A_READ); //create a read statement node
                (yyval.node) -> s1 = (yyvsp[-1].node); //upstream gets the varible to read into
              }
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 372 "lab7.y" /* yacc.c:1646  */
    { 
                          (yyval.node) = ASTCreateNode(A_WRITE); //create a write statement node
                          (yyval.node) -> s1 = (yyvsp[-1].node); //pass up the expression to write
                        }
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 378 "lab7.y" /* yacc.c:1646  */
    {
                          (yyval.node) = ASTCreateNode(A_WRITE); //create a write statement node
                          (yyval.node) -> name = (yyvsp[-1].string); //pass up the string to write
                        }
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 385 "lab7.y" /* yacc.c:1646  */
    {
                    if((yyvsp[-3].node)->my_data_type != (yyvsp[-1].node)->my_data_type){ //check to see if the data types match
                      yyerror("Assignment types do not match");
                      exit(1);  //exit if the data types do not match
                    }
                      (yyval.node) = ASTCreateNode(A_ASSIGN); //create an assignment statement node
                      (yyval.node) -> s1 = (yyvsp[-3].node); //set upstream s1 to the variable to assign
                      (yyval.node) -> s2 = (yyvsp[-1].node); // set upstream s2 to the expression to assign
                      (yyval.node) -> name = CreateTemp();  //create a temporary name
                      (yyval.node) -> symbol = Insert((yyval.node)->name, (yyvsp[-3].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);    //insert the temporary name into the symbol table
                      OFFSET = OFFSET + 1;

                    }
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 402 "lab7.y" /* yacc.c:1646  */
    { 
     struct SymbTab *p; //create a symbol table pointer
     p = Search((yyvsp[0].string), LEVEL, 1);  //search for the variable name
     if(p == NULL)    //if the variable name is not found
     {
      //  a reference to a variable not in the symbol table
      yyerror((yyvsp[0].string));
      yyerror("Symbol used but not defined");
      exit(1);  //exit the program
     }

     if(p->SubType != SYM_SCALAR)
      {
      //  a reference to a NON SCALAR variable
      yyerror((yyvsp[0].string));
      yyerror("Symbol must be a SCALAR");
      exit(1);  
     }
     (yyval.node) = ASTCreateNode(A_VAR); //create a variable node
     (yyval.node) -> name = (yyvsp[0].string); //set name
     (yyval.node) -> s1 = NULL; //indicates not an array
     (yyval.node) -> symbol = p;  //set symbol to the variable name
     (yyval.node) -> my_data_type = p -> Declared_Type; //set data type
   }
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 427 "lab7.y" /* yacc.c:1646  */
    { 
    struct SymbTab *p;  //create a symbol table pointer
     p = Search((yyvsp[-3].string), LEVEL, 1);  //search for the array name
     if(p == NULL)  //if the array name is not found
     {
      //  a reference to a variable not in the symbol table
      yyerror((yyvsp[-3].string));
      yyerror("Symbol used but not defined");
      exit(1);  //exit the program
     }

     if(p->SubType != SYM_ARRAY)  //if the array name is not found
      {
      //  a reference to a NON SCALAR variable
      yyerror((yyvsp[-3].string));
      yyerror("Symbol must be a ARRAY");
      exit(1);  //exit the program
     }
     (yyval.node) = ASTCreateNode(A_VAR); //create a variable node
     (yyval.node) -> name = (yyvsp[-3].string); //set name
     (yyval.node) -> symbol = p;
     (yyval.node) -> s1 = (yyvsp[-1].node); //passes up he index expression of the array
     (yyval.node) -> my_data_type = p -> Declared_Type; //set data type
   }
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 453 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 457 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 459 "lab7.y" /* yacc.c:1646  */
    {
                  if((yyvsp[-2].node) -> my_data_type != (yyvsp[0].node) -> my_data_type) {  //check to see if the data types match
                    yyerror("Type mismatch");
                    exit(1);  //exit if the data types do not match
                  }
                  (yyval.node) = ASTCreateNode(A_EXPR); 
                  (yyval.node) -> s1 = (yyvsp[-2].node); 
                  (yyval.node) -> s2 = (yyvsp[0].node);  
                  (yyval.node) -> operator = (yyvsp[-1].operator);  
                  (yyval.node) -> my_data_type = (yyvsp[-2].node) -> my_data_type;  //set data type
                  (yyval.node) -> name = CreateTemp();    //create a temporary name
                  (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[-2].node)-> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); //insert the temporary name into the symbol table
                  OFFSET = OFFSET + 1; 

                  }
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 476 "lab7.y" /* yacc.c:1646  */
    { (yyval.operator) = A_LT;}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 477 "lab7.y" /* yacc.c:1646  */
    { (yyval.operator) = A_GT;}
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 478 "lab7.y" /* yacc.c:1646  */
    { (yyval.operator) = A_GE;}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 479 "lab7.y" /* yacc.c:1646  */
    { (yyval.operator) = A_LE;}
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 480 "lab7.y" /* yacc.c:1646  */
    { (yyval.operator) = A_EQ;}
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 481 "lab7.y" /* yacc.c:1646  */
    { (yyval.operator) = A_NE;}
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 484 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 486 "lab7.y" /* yacc.c:1646  */
    { 
                     if((yyvsp[-2].node)->my_data_type != (yyvsp[0].node) -> my_data_type)
                     {
                      yyerror("type mismatch");
                      exit(1);
                     }
                     (yyval.node) = ASTCreateNode(A_EXPR); //create an expression node for addition/subtraction
                     (yyval.node) -> s1 = (yyvsp[-2].node); //pass up left side 
                     (yyval.node) -> s2 = (yyvsp[0].node); //pass up right side
                     (yyval.node) -> operator = (yyvsp[-1].operator);  // pass up operator
                     (yyval.node) -> name = CreateTemp(); //create a temporary name
                     (yyval.node) -> symbol = Insert((yyval.node)->name,(yyvsp[-2].node)->my_data_type,SYM_SCALAR, LEVEL, 1, OFFSET);   //insert the temporary name into the symbol table
                     OFFSET = OFFSET+1;
                   }
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 502 "lab7.y" /* yacc.c:1646  */
    {(yyval.operator) = A_PLUS;}
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 503 "lab7.y" /* yacc.c:1646  */
    {(yyval.operator) = A_MINUS;}
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 506 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 508 "lab7.y" /* yacc.c:1646  */
    {
      if((yyvsp[-2].node)->my_data_type != (yyvsp[0].node) -> my_data_type){
        yyerror("Type mismatch term");
        exit(1);
      }
     (yyval.node) = ASTCreateNode(A_EXPR); //create an expression node for multiplication/division/modulus
     (yyval.node) -> s1 = (yyvsp[-2].node); //pass up left side 
     (yyval.node) -> s2 = (yyvsp[0].node); //pass up right side
     (yyval.node) -> operator = (yyvsp[-1].operator);  // pass up operator
     (yyval.node) -> my_data_type = (yyvsp[-2].node) -> my_data_type; //set data type
     (yyval.node) -> name = CreateTemp();   //create a temporary name
     (yyval.node) -> symbol = Insert((yyval.node)->name, (yyvsp[-2].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); //insert the temporary name into the symbol table
     OFFSET = OFFSET + 1;
     }
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 524 "lab7.y" /* yacc.c:1646  */
    {(yyval.operator) = A_TIMES;}
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 525 "lab7.y" /* yacc.c:1646  */
    {(yyval.operator) = A_DIV;}
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 526 "lab7.y" /* yacc.c:1646  */
    {(yyval.operator) = A_MOD;}
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 529 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 531 "lab7.y" /* yacc.c:1646  */
    { 
          (yyval.node) = ASTCreateNode(A_NUM); //create a num node
          (yyval.node) -> value = (yyvsp[0].value); //set value and pass up
          (yyval.node) -> my_data_type = A_INTTYPE; //set data type
        }
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 536 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 537 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 539 "lab7.y" /* yacc.c:1646  */
    {
        (yyval.node) = ASTCreateNode(A_EXPR); //create an expression node for negative num
        (yyval.node) -> s1 = (yyvsp[0].node); //set s1 to factor
        (yyval.node) -> operator = A_UNMINUS; //set operator to unary minus
      }
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 547 "lab7.y" /* yacc.c:1646  */
    { 
      struct SymbTab *p;    //create a symbol table pointer
      p = Search((yyvsp[-3].string), 0 , 0);  //search for the function name
      if(p==NULL){    //if the function name is not found
        //function name not known
        yyerror((yyvsp[-3].string));
        yyerror("function name not defined"); 
        exit(1);  //exit the program
      }
      //name is there but is it a FUNCTION

      if(p->SubType != SYM_FUNCTION){   //if the function name is not found
        //function name not known
        yyerror((yyvsp[-3].string));
        yyerror("is not defined as a function"); 
        exit(1);  //exit the program
      }

      //check to see if the formal and actual parameters match
      if(check_params((yyvsp[-1].node), p->fparms) == 0){   //if the parameters do not match
        yyerror((yyvsp[-3].string));
        yyerror("Actual and Formals do not match"); 
        exit(1);  //exit the program
      } else {

      (yyval.node) = ASTCreateNode(A_CALL); //create a function call node
      (yyval.node) -> name = (yyvsp[-3].string); //set name and pass up
      (yyval.node) -> s1 = (yyvsp[-1].node);  //set s1 to the arguments in ()
      (yyval.node) -> symbol = p; //set symbol to the function name
      (yyval.node) -> my_data_type = p -> Declared_Type;  //set data type to the function name
      }
    }
#line 2114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 582 "lab7.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 2120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 584 "lab7.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 2126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 588 "lab7.y" /* yacc.c:1646  */
    { 
            (yyval.node) = ASTCreateNode(A_ARG); //create an arg node
            (yyval.node) -> s1 = (yyvsp[0].node) ; //set s1 to expression being passed as an argument
            (yyval.node) -> my_data_type = (yyvsp[0].node) -> my_data_type;  //set data type
            (yyval.node) -> name = CreateTemp();  //create a temporary name
            (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[0].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);  //insert the temporary name into the symbol table
            OFFSET = OFFSET + 1; 
         }
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 597 "lab7.y" /* yacc.c:1646  */
    { 
            (yyval.node) = ASTCreateNode(A_ARG); //create a function arg node
            (yyval.node) -> s1 = (yyvsp[-2].node); //set s1 to expression being passed as an argument
            (yyval.node) -> next = (yyvsp[0].node); //Link to the next argument in the list
            (yyval.node) -> my_data_type = (yyvsp[-2].node) -> my_data_type;  //set data type
            (yyval.node) -> name = CreateTemp();  //create a temporary name
            (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[-2].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);  //insert the temporary name into the symbol table
            OFFSET = OFFSET + 1;
         }
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2157 "y.tab.c" /* yacc.c:1646  */
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
#line 608 "lab7.y" /* yacc.c:1906  */
 /*end of rules */

int main() {
    yyparse();
    printf("\nFinished Parsing\n\n\n");
    Display();
    printf("\n\n AST PRINT \n\n");
    ASTprint(0, PROGRAM); 
}
