%{

/* 
	

	Ryan Lucero
	CS370 Spring 2024
    Lab5 CMINUS+
	2/26/2024

    This program is the implementation of syntax analysis for a subset of the CMINUS+ language features. 
    It includes declarations for types, variables, and functions, alongside control structures such as if-else statements,
    while loops, and basic input/output operations. The grammar rules defined, guide the parsing process,
    ensuring that the input code matches the expected syntax of variable declarations, function definitions, statements,
    and expressions. 
	
*/

	
#include <stdio.h>
#include <ctype.h>

int yylex(); 
extern int mydebug; //Lex var
extern int lineno; //Lex variable for line number

void yyerror (s)  
     char *s;
{
  printf ("YACC PARSE ERROR: %s syntax error on line number %d\n", s, lineno);
}

%}

%start Program

%union {
      int value;
      char * string;
}

%token <value> T_NUM
%token <string> T_ID
%token T_INT
%token T_VOID
%token T_READ
%token <string> T_STRING
%token T_IF 
%token T_ELSE
%token T_WHILE
%token T_WRITE
%token T_RET
%token T_GT
%token T_GE 
%token T_LT
%token T_LE
%token T_EQ
%token T_NE
%token T_MULT   
%token T_DIV
%token T_PLUS
%token T_MINUS


%%  

/*Beginning of Rules*/

Program : Declaration_List
        ;// Program starts

Declaration_List : Declaration 
                 | Declaration Declaration_List
        		 ;// Declaration list can be a single declaration or multiple declarations

Declaration : Var_Declaration 
            | Fun_Declaration
            ;// A declaration can be either a variable declaration or a function declaration

Var_Declaration : Type_Specifier Var_List ';'
                ;// Variable declaration specifies type and one or more variables

Var_List : T_ID
         {fprintf(stderr, "Var_LIST with value %s at line %d\n", $1, lineno);}
         | T_ID '['T_NUM ']'
         {fprintf(stderr, "Var_LIST with value %s at line %d\n", $1, lineno);} 
         | T_ID ',' Var_List
         {fprintf(stderr, "Var_LIST with value %s at line %d\n", $1, lineno);}
         | T_ID '[' T_NUM ']' ',' Var_List
         {fprintf(stderr, "Var_LIST with value %s at line %d\n", $1, lineno);}
         ; // Variable list can include single variables, arrays, or lists of variables and arrays


Type_Specifier : T_INT 
			   | T_VOID
        	   ;// Type specifier can be integer or void

Fun_Declaration : Type_Specifier T_ID '(' Params ')' Compound_Stmt
                {fprintf(stderr, "FunDec with value %s at line %d\n", $2, lineno);}
                ; // Function declaration includes type, name, parameters, and body

Params : T_VOID
        | Param_List
        ;// Parameters can be void or a list of parameter declarations


Param_List : Param
           | Param ',' Param_List
           ;// Parameter list can include single parameters or lists of parameters
           
Param : Type_Specifier T_ID 
      {fprintf(stderr, "PARAM with value %s at line %d\n", $2, lineno);}
	  | Type_Specifier T_ID  '[' ']'
      {fprintf(stderr, "PARAM with value %s at line %d\n", $2, lineno);}
      ;// Parameter can be a single variable or an array


Compound_Stmt: '{' Local_Declarations Statement_List '}'
             ;// Compound statement includes local declarations and a list of statements


Local_Declarations :  /*empty*/
                   |  Var_Declaration Local_Declarations
                   ;// Local declarations can be empty or include variable declarations


Statement_List : /*empty */
               | Statement Statement_List
               ;// Statement list can be empty or include multiple statements


Statement : Expression_Statement
        | Compound_Stmt
        | Selection_Statement
        | Iteration_Statement
        | Assignment_Statement
        | Return_Statement
        | Read_Statement
        | Write_Statement
        ;// Statements include various types like expression, compound, selection, etc.



Expression_Statement: Expression ';'
                    | ';'
                    ;// Expression statement can be an expression or an empty statement


Selection_Statement: T_IF  '(' Expression ')' Statement 
				   | T_IF  '(' Expression ')' Statement T_ELSE Statement
                   ;// Selection statement for if-then or if-then-else constructs


Iteration_Statement: T_WHILE  '(' Expression ')' Statement
                   ;// Iteration statement for while loops


Return_Statement: T_RET Expression ';'
                | T_RET  ';'
                ;// Return statement can return an expression or be void


Read_Statement: T_READ Var ';'
              ;// Read statement for reading a value into a variable


Write_Statement: T_WRITE Expression ';'
               | T_WRITE  T_STRING  ';'
               ;// Write statement can output an expression or a string


Assignment_Statement:  Var '=' Simple_Expression ';'
                    ;// Assignment statement assigns an expression to a variable


Var: T_ID '[' Expression ']'
   {fprintf(stderr, "Var with value %s at line %d\n", $1, lineno);}
   | T_ID
   {fprintf(stderr, "Var with value %s at line %d\n", $1, lineno);}
   ;// Var can be a simple variable or an array element


Expression: Simple_Expression
          ;// Expression can be a simple expression


Simple_Expression: Additive_Expression
        		 | Additive_Expression Relop Additive_Expression
        		 ;// Simple expression can be additive or involve comparisons
               
Relop: T_LT    
     | T_GT
     | T_GE
     | T_LE
     | T_EQ
     | T_NE
     ;// Relational operators for comparisons


Additive_Expression: Term
                   | Additive_Expression AddOp Term
                   ;// Additive expression can be a term or involve addition/subtraction


AddOp: T_PLUS
     | T_MINUS
     ;// Addition or subtraction operators



Term: Factor
    | Factor MultOp Factor
    ;// Term can be a factor or involve multiplication/division


MultOp: T_MULT
      | T_DIV
      ;// Multiplication or division operators


Factor: '(' Expression ')'
      | T_NUM
      | Var
      | Call
      | AddOp Factor
      ;// Factor can be an expression, number, variable, function call, or negated factor



Call: T_ID '(' Args ')'
    {fprintf(stderr, "Call with value %s at line %d\n", $1, lineno);}
    ;// Function call with optional arguments


Args: Args_List
    | /* empty */
    ;// Arguments to a function call can be empty or a list of expressions


Args_List: Expression
         |Args_List ',' Expression
         ;// Argument list can be a single expression or a list of expressions

%% /*end of rules */

int main() {
    yyparse();
}
