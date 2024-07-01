/*   


    Ryan Lucero
    Lab 7
    ast.h
    4/10/2024
    CS370 Shaun Cooper


   This header file defines the stuctures and enums required for the AST.
   These delarations are responsible for the creation and handling of the AST
   for the provided CMINUS+ program source code. Additionally, it declares utility
   functions for node creation, AST traversal, and printing.

*/

#include<stdio.h>
#include<malloc.h>
#include "symtable.h"

#ifndef AST_H
#define AST_H
int mydebug;

/* define the enumerated types for the AST.  THis is used to tell us what 
sort of production rule we came across */

enum ASTtype {
   A_FUNCTIONDEC,
   A_VARDEC,
	A_COMPOUND,
   A_WRITE,
   A_NUM,
   A_PARAM,
   A_EXPR,
   A_READ,
   A_RETURN,
   A_IF,
   A_WHILE,
   A_CALL,
   A_ASSIGN,
   A_ARG,
   A_EXPRESSIONSTMT,
   A_VAR, 
   A_UNMINUS  
};

// Math Operators

enum AST_OPERATORS {
   A_PLUS,
   A_MINUS,
   A_TIMES,
   A_DIV,
   A_LE,
   A_LT,
   A_GE,
   A_GT,
   A_EQ,
   A_NE,
   A_MOD
  
};

enum AST_MY_DATA_TYPE {
   A_INTTYPE,
   A_VOIDTYPE

};

/* define a type AST node which will hold pointers to AST structs that will
   allow us to represent the parsed code 
*/

typedef struct ASTnodetype
{
     enum ASTtype type;
     enum AST_OPERATORS operator;
     char * name;
     int value;
     enum AST_MY_DATA_TYPE my_data_type;
     struct SymbTab *symbol;  /* pointer to symbol table entry for variable/function references */
     struct ASTnodetype *s1,*s2, *next ; /* used for holding IF and WHILE components -- not very descriptive */
} ASTnode;


/* uses malloc to create an ASTnode and passes back the heap address of the newley created node */
ASTnode *ASTCreateNode(enum ASTtype mytype);

void PT(int howmany);


/*  Print out the abstract syntax tree */
void ASTprint(int level,ASTnode *p);

/* parameter checking */
int check_params(ASTnode *actual, ASTnode *formals);

#endif // of AST_H