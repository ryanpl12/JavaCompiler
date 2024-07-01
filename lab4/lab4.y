%{

/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 26 integer registers, named 'a' thru 'z'
 *
 */

/* 

	Ryan Lucero
	2/16/2024
	CS370 Spring
	Lab4

   > In this code I have added to the DECL method. I have added a search the symbol table to ensure present variables. If passed, the variable is passed to Insert.
   > I have also ensured the proper use of variables. In the VARIABLE assignment method, I am have esnured that the variable is present in the symbol table prior to assinging its location in memory.
   > 

*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "symtable.h"
#define LIMIT 3

int yylex();        /*PROTOTYPE TO GET RID OF COMPILE WARNING*/

extern int mydebug;		/* Allowing varaible 'mydebug' to be used from external file */

int regs[LIMIT];
int base, debugsw;
int cou = 0;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start P

%union {
      int value;
      char * string;

}

%token <value> INTEGER
%token <string> VARIABLE
%token T_INT

%type<value>	expr

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */

P : DECLS list
  ;

DECLS : DECLS DECL 
	  | /*empty*/
	  ;

DECL : T_INT VARIABLE ';' '\n'
	{	//Search symtavle if in ther ethen BARF
		//check to see if there is room in m REGS  array vs LIMIT
		// else Insert($2, ONEUP); ONEUP++
		//if(search(variable) == 1) BARG
		//display to check limit vs regs
		//else (insert() ONEUP++)

		if(Search($2) != NULL){
			fprintf(stderr, "Symbol is already in the the table.\n");
			fprintf(stderr, "Cannot insert duplicates.\n");
		}
		if(cou >= LIMIT){
				
				fprintf(stderr, "There is not enough room in the symbol table\n");
				fprintf(stderr, "Cannot insert anymore variables into symbol table\n");
		}
		else if (Search($2) == NULL){
			Insert(($2), cou);
			cou++;		
			Display();
		}
	}
	 ;

list	:	/* empty */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;

stat	:	expr
			{ 	
				fprintf(stderr,"the anwser is %d\n", $1); }
	|	VARIABLE '=' expr
			{ 	
				//If $1 is not in symtable - BARF
				//if(Search($1) == 0) - BARF
				//else
				if(Search($1) == NULL){
					fprintf(stderr, "Symbol is not in table\n");
				}
				else{
					regs[FetchAddress($1)] = $3; 
				}
			}
	;

expr	:	'(' expr ')'
			{ $$ = $2; }
	|	expr '-' expr
			{ $$ = $1 - $3; }
	|	expr '+' expr
			{ $$ = $1 + $3; }
	|	expr '/' expr
			{ $$ = $1 / $3; }
	|	expr '*' expr
			{ $$ = $1 * $3; }
	|	expr '%' expr
			{ $$ = $1 % $3; }
	|	expr '&' expr
			{ $$ = $1 & $3; }
	|	expr '|' expr
			{ $$ = $1 | $3; }
	|	'-' expr	%prec UMINUS
			{ $$ = -$2; }
	|	VARIABLE
			{ 
				if(Search($1) == NULL){
				fprintf(stderr, "Undeclared VARIABLE.\n");
				fprintf(stderr, "Setting to 0.\n");
				fprintf(stderr, "Therefore ");
				$$ = 0;

			}else{
				$$ = regs[FetchAddress($1)];
			}
		if(mydebug)
			 fprintf(stderr,"found a variable value =%d\n",$1); }
	|	INTEGER {$$=$1;
		if(mydebug)
			 fprintf(stderr,"found an integer\n");}
	;



%%	/* end of rules, start of program */

int main()
{ yyparse();
}
