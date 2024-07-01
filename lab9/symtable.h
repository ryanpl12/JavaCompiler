/*  
    Ryan Lucero
    Lab 9 - MIPS Code Generation from AST
    CS370 Spring 2024 - Shaun Cooper
    4/30/2024

    symtable.h

    Exposure of the symbol table and the functions that are used to manipulate the symbol table.
*/

    


#ifndef _SYMTAB 
#define _SYMTAB

#include "ast.h"

enum  SYMBOL_SUBTYPE
{
   SYM_SCALAR,
   SYM_ARRAY,
   SYM_FUNCTION
   // missing for array as parameter
};

void Display();
int Delete();


struct SymbTab
{
     char *name;
     int offset; /* from activation record boundary */
     int mysize;  /* number of words this item is 1 or more */
     int level;  /* the level where we found the variable */
     enum AST_MY_DATA_TYPE Declared_Type;  /* the type of the symbol */
     struct SymbTab *symbol;    /*the pointer to the symbol*/
     int SubType;  /* the subtype of the symbol */
     ASTnode * fparms; /* pointer to parameters of the function in the AST */

     struct SymbTab *next;
};


struct SymbTab * Insert(char *name, enum AST_MY_DATA_TYPE my_assigned_type , enum  SYMBOL_SUBTYPE sub_type, int  level, int mysize, int offset);

struct SymbTab * Search(char name[], int level, int recur );


static struct SymbTab *first=NULL;   /* global pointers into the symbol table */

char * CreateTemp();
char * createLabel();


#endif

