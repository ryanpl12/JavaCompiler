%{

/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 26 integer registers, named 'a' thru 'z'
 *
 */

/* This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
   The return type via yylval is integer 

   When we need to make yylval more complicated, we need to define a pointer type for yylval 
   and to instruct YACC to use a new type so that we can pass back better values
 
   The registers are based on 0, so we substract 'a' from each single letter we get.

   based on context, we have YACC do the correct memmory look up or the storage depending
   on position

	Ryan Lucero
	January 2024
	CS370 Spring
	Lab22

   I have fixed the UMINUS 'expr' redundacy. I declared the variable 'mydebug' through an extern declaration since it is declared in the lab22.l file. I then also added a multiplication expression to the list of symbols to be recognized 
  with its expression funxtion. 
   problems  make it so that verbose is on and off with an input argument instead of compiled in
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>

int yylex();        /*PROTOTYPE TO GET RID OF COMPILE WARNING*/

extern int mydebug;		/* Allowing varaible 'mydebug' to be used from external file */

int regs[26];
int base, debugsw;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start list

%token INTEGER
%token  VARIABLE

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */

list	:	/* empty */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;

stat	:	expr
			{ fprintf(stderr,"the anwser is %d\n", $1); }
	|	VARIABLE '=' expr
			{ regs[$1] = $3; }
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
			{ $$ = regs[$1];
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
