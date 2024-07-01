%{

/* 
	
    Ryan Lucero
    Lab 9 - MIPS Code Generation from AST
    CS370 Spring 2024 - Shaun Cooper
    4/30/2024

    lab9.y
    

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
#include <string.h>
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

%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start Program

%union {
      int value;
      char * string;
      ASTnode *node; 
      enum AST_MY_DATA_TYPE d_type; 
      enum AST_OPERATORS operator; 
}

/* Token definitions*/ 
%token <value> T_NUM
%token <string> T_ID
%token <string> T_STRING
%token T_INT
%token T_VOID
%token T_READ
%token T_IF 
%token T_ELSE
%token T_WHILE
%token T_WRITE
%token T_RET
%token T_LT
%token T_GT
%token T_GE 
%token T_LE
%token T_EQ
%token T_NE
 

%type <node> Declaration_List Declaration Var_Declaration Var_List
%type <node> Fun_Declaration Params Compound_Stmt Local_Declarations Statement_List Statement
%type <node> Write_Statement Expression Simple_Expression Additive_Expression Term Factor
%type <node> Call Var Param_List Param Read_Statement Return_Statement Assignment_Statement
%type <node> Expression_Statement Iteration_Statement Args Args_List Selection_Statement
%type <d_type>  Type_Specifier 
%type <operator> AddOp MultOp Relop

%% 

/*Beginning of Rules*/

Program : Declaration_List {PROGRAM = $1; }  
        ;// Program starts

Declaration_List : Declaration
                   { $$ = $1; }
                 | Declaration Declaration_List
                 { 
                    $$ = $1; // the current declaration becomes the head of the list
                    $$ -> next = $2; //link the current declaration to the rest of the list
                 }
                 ; // Declaration list can be a single declaration or multiple declarations
                 
Declaration : Var_Declaration  { $$ = $1;}
            | Fun_Declaration   { $$ = $1;}
            ;// A declaration can be either a variable declaration or a function declaration

Var_Declaration : Type_Specifier Var_List ';'
                { 
                  ASTnode *p = $2;  //set p to the head of the variable list
                  while(p != NULL) {
                    p -> my_data_type = $1; //assign the type
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
                  $$ = $2; //the result is the head of the variable list
                }
                ;// Variable declaration specifies type and one or more variables

Var_List : T_ID
         { 
          $$ = ASTCreateNode (A_VARDEC); 
          $$-> name = $1; //set name
         }
         | T_ID '['T_NUM ']' 
         { 
          $$ = ASTCreateNode (A_VARDEC);
          $$-> name = $1;  //set name
          $$ -> value = $3; //set value
         }
         | T_ID ',' Var_List
         {
          $$ = ASTCreateNode (A_VARDEC);
          $$ -> name = $1; //set name
          $$ -> s1 = $3;  //set s1 to var_list
         }
         | T_ID '[' T_NUM ']' ',' Var_List
         { 
          $$ = ASTCreateNode (A_VARDEC); 
          $$-> name = $1; //set name
          $$ -> value = $3; //set value to value in []
          $$ -> s1 = $6; //set s1 to var_list
         }
         ; // Variable list can include single variables, arrays, or lists of variables and arrays

Type_Specifier : T_INT 
               { $$ = A_INTTYPE;}
               | T_VOID
               { $$ = A_VOIDTYPE;}
               ;// Type specifier can be integer or void

Fun_Declaration : Type_Specifier T_ID 
                { //check to see if function has been defined
                  if(Search($2, LEVEL, 0) != NULL){
                    //id has already been used -- BARF
                    yyerror($2);
                    yyerror("Function name already in use");
                    exit(1);
                  }

                  // not in symbol table -> install it
                  Insert($2, $1, SYM_FUNCTION, LEVEL, 0, 0);  //insert the function into the symbol table

                  GOFFSET = OFFSET; //set the global offset to the current offset
                  OFFSET = 2; //reset the offset for the function
                  maxoffset = OFFSET; //set the max offset to the current offset

                }
                '(' Params ')' 
                {Search($2, LEVEL, 0)->fparms = $5;}
                Compound_Stmt
                { $$ = ASTCreateNode(A_FUNCTIONDEC); 
                  $$ -> name = $2; //set name
                  $$ -> my_data_type = $1;  //ser data type
                  $$ -> s1 = $5; //set s1 to be calue in ()
                  $$ -> s2 = $8; //set s2 to be compound_stmt
                  $$->symbol = Search($2, LEVEL, 0);  //set symbol to the function name
                  
                  $$->symbol->offset = maxoffset; //set the offset of the function

                  Search($2, LEVEL, 0) -> offset = maxoffset; //set the offset of the function
                  OFFSET = GOFFSET; //resets the offset for global variables
                }
                ;// Function declaration includes type, name, parameters, and body

Params : T_VOID { $$ = NULL; }
       | Param_List {$$ = $1; }
       ;// Parameters can be void or a list of parameter declarations
 
Param_List : Param {$$ = $1; }
           | Param ',' Param_List 
           {
            $$ = $1; //pass one parameter up
            $$ -> next = $3; // if more than 1 parameter, set next to param_list
           }
           ;// Parameter list can include single parameters or lists of parameters
           
Param : Type_Specifier T_ID    
      { 
        if(Search($2, LEVEL+1, 0) != NULL)    //check to see if the parameter has already been defined
        {
          yyerror($2);
          yyerror("parameter already used");  
          exit(1);    //exit if the parameter has already been defined
        }

       $$ = ASTCreateNode(A_PARAM); //create node for parameter
       $$ -> value = 0;
       $$ -> name = $2; //set parameter name
       $$ -> my_data_type = $1; //set parameter type
       $$->symbol=Insert($$->name, $$->my_data_type, SYM_SCALAR, LEVEL+1, 1, OFFSET); //insert the parameter into the symbol table

       OFFSET = OFFSET + 1;

      }
      | Type_Specifier T_ID '[' ']'
      {  
        if(Search($2, LEVEL+1, 0) != NULL){ //check to see if the parameter has already been defined
          yyerror($2);
          yyerror("parameter already used");
          exit(1);  //exit if the parameter has already been defined
        }

       $$ = ASTCreateNode(A_PARAM); // create node for array parameter
       $$ -> my_data_type = $1; //set data type of parameter
       $$ -> name = $2;  //set name of parameter
       $$ -> value = 1; //set value of parameter

       $$->symbol=Insert($$->name, $$->my_data_type, SYM_ARRAY, LEVEL+1, 1, OFFSET);  //insert the parameter into the symbol table

        OFFSET = OFFSET + 1;
      }
      ;// Parameter can be a single variable or an array

Compound_Stmt:'{' { LEVEL ++; }
                  Local_Declarations Statement_List '}'
             {
               $$ = ASTCreateNode(A_COMPOUND); //create node for a compound statement
               $$ -> s1 = $3; // send upsteam s1 with local declarations
               $$ -> s2 = $4; // send upstream s2 with statement list
               if(mydebug)Display();
            //we set the maxoffset 
               if(OFFSET > maxoffset) maxoffset = OFFSET;
               OFFSET -= Delete(LEVEL); 
               LEVEL --;
             }
             ;// Compound statement includes local declarations and a list of statements

Local_Declarations : /*empty*/{ $$ = NULL; }
                   | Var_Declaration Local_Declarations
                   { 
                    $$ = $1; // upstream recieves current var declarations
                    $$ -> next = $2; //link to local declarations
                   }
                   ;// Local declarations can be empty or include variable declarations

Statement_List : /*empty */ {$$ = NULL;}
               | Statement Statement_List
               { 
                $$ = $1; //upstream gets current statement
                $$ -> next = $2;  //link next statement in list
               }
                
               ;// Statement list can be empty or include multiple statements

Statement : Expression_Statement 
          {$$ = $1; }
          | Compound_Stmt 
          {$$ = $1; }
          | Selection_Statement 
          {$$ = $1; }
          | Iteration_Statement 
          {$$ = $1; }
          | Assignment_Statement 
          {$$ = $1; }
          | Return_Statement 
          {$$ = $1; }
          | Read_Statement 
          {$$ = $1; }
          | Write_Statement 
          {$$ = $1; }
          ; // Statements include various types like expression, compound, selection, etc.

Expression_Statement: Expression ';'
                    {
                     $$ = ASTCreateNode(A_EXPRESSIONSTMT); // create an expression statement node
                     $$ -> s1 = $1; //upstream gets the expression
                    }
                    | ';'
                    { 
                      $$ = ASTCreateNode(A_EXPRESSIONSTMT);
                      $$ -> s1 = NULL; //upstream get no expression
                    }
                    ;// Expression statement can be an expression or an empty statement

Selection_Statement: T_IF  '(' Expression ')' Statement 
                   {
                    $$ = ASTCreateNode(A_IF); // Create an if statement node
                    $$ -> s1 = $3; // sends upstream s1 with expression
                    $$ -> s2 = ASTCreateNode(A_IF); //create 'then' statement node
                    $$ ->s2 -> s1 = $5; //upstream gets the 'then' statement
                    $$ -> s2 -> s2 = NULL; //no else

                   }
                   | T_IF  '(' Expression ')' Statement T_ELSE Statement
                   {
                    $$ = ASTCreateNode(A_IF); // Create an if statement node
                    $$ -> s1 = $3; // sends upstream s1 with expression
                    $$ -> s2 = ASTCreateNode(A_IF); //create 'then' statement node
                    $$ -> s2 -> s1 = $5; //upstream gets the 'then' statement
                    $$ -> s2 -> s2 = $7; //else statement gets set to s2->s2

                   }                   

                   ;// Selection statement for if-then or if-then-else constructs

Iteration_Statement: T_WHILE  '(' Expression ')' Statement
                   { 
                     $$ = ASTCreateNode(A_WHILE); // create a while loop node
                     $$ -> s1 = $3; //upstream gets the loop condition
                     $$ -> s2 = $5; //upstream gets loop body
                   }
                   ;// Iteration statement for while loops

Return_Statement: T_RET ';'
                {
                  $$ = ASTCreateNode(A_RETURN); //create a return statement node
                  $$ -> s1 = NULL;  // no return value
                }
                | T_RET  Expression ';'
                {
                  $$ = ASTCreateNode(A_RETURN); //create a return statement node
                  $$ -> s1 = $2; //pass up the expression to return
                }
                ;// Return statement can return an expression or be void

Read_Statement: T_READ Var ';'
              { 
                $$ = ASTCreateNode(A_READ); //create a read statement node
                $$ -> s1 = $2; //upstream gets the varible to read into
              }
              ;// Read statement for reading a value into a variable

Write_Statement: T_WRITE Expression ';'
                        { 
                          $$ = ASTCreateNode(A_WRITE); //create a write statement node
                          $$ -> s1 = $2; //pass up the expression to write
                        }
               
                | T_WRITE  T_STRING  ';'
                        {
                          $$ = ASTCreateNode(A_WRITE); //create a write statement node
                          $$ -> name = $2; //pass up the string to write
                        }
                ;// Write statement can output an expression or a string

Assignment_Statement:  Var '=' Simple_Expression ';'
                    {
                    if($1->my_data_type != $3->my_data_type){ //check to see if the data types match
                      yyerror("Assignment types do not match");
                      exit(1);  //exit if the data types do not match
                    }
                      $$ = ASTCreateNode(A_ASSIGN); //create an assignment statement node
                      $$ -> s1 = $1; //set upstream s1 to the variable to assign
                      $$ -> s2 = $3; // set upstream s2 to the expression to assign
                      $$ -> name = CreateTemp();  //create a temporary name
                      $$ -> symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);    //insert the temporary name into the symbol table
                      OFFSET = OFFSET + 1;

                    }
                    ;// Assignment statement assigns an expression to a variable


Var: T_ID 
   { 
     struct SymbTab *p; //create a symbol table pointer
     p = Search($1, LEVEL, 1);  //search for the variable name
     if(p == NULL)    //if the variable name is not found
     {
      //  a reference to a variable not in the symbol table
      yyerror($1);
      yyerror("Symbol used but not defined");
      exit(1);  //exit the program
     }

     if(p->SubType != SYM_SCALAR)
      {
      //  a reference to a NON SCALAR variable
      yyerror($1);
      yyerror("Symbol must be a SCALAR");
      exit(1);  
     }
     $$ = ASTCreateNode(A_VAR); //create a variable node
     $$ -> name = $1; //set name
     $$ -> s1 = NULL; //indicates not an array
     $$ -> symbol = p;  //set symbol to the variable name
     $$ -> my_data_type = p -> Declared_Type; //set data type
   }
   | T_ID '[' Expression ']'
   { 
    struct SymbTab *p;  //create a symbol table pointer
     p = Search($1, LEVEL, 1);  //search for the array name
     if(p == NULL)  //if the array name is not found
     {
      //  a reference to a variable not in the symbol table
      yyerror($1);
      yyerror("Symbol used but not defined");
      exit(1);  //exit the program
     }

     if(p->SubType != SYM_ARRAY)  //if the array name is not found
      {
      //  a reference to a NON SCALAR variable
      yyerror($1);
      yyerror("Symbol must be a ARRAY");
      exit(1);  //exit the program
     }
     $$ = ASTCreateNode(A_VAR); //create a variable node
     $$ -> name = $1; //set name
     $$ -> symbol = p;
     $$ -> s1 = $3; //passes up he index expression of the array
     $$ -> my_data_type = p -> Declared_Type; //set data type
   }
   ;// Var can be a simple variable or an array element

Expression: Simple_Expression {$$ = $1;}
          ;// Expression can be a simple expression 


Simple_Expression: Additive_Expression {$$ = $1;}
                 | Additive_Expression Relop Additive_Expression 
                  {
                  if($1 -> my_data_type != $3 -> my_data_type) {  //check to see if the data types match
                    yyerror("Type mismatch");
                    exit(1);  //exit if the data types do not match
                  }
                  $$ = ASTCreateNode(A_EXPR); 
                  $$ -> s1 = $1; 
                  $$ -> s2 = $3;  
                  $$ -> operator = $2;  
                  $$ -> my_data_type = $1 -> my_data_type;  //set data type
                  $$ -> name = CreateTemp();    //create a temporary name
                  $$ -> symbol = Insert($$ -> name, $1-> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); //insert the temporary name into the symbol table
                  OFFSET = OFFSET + 1; 

                  }
                 ; 
               
Relop:    T_LT { $$ = A_LT;} 
        | T_GT { $$ = A_GT;}
        | T_GE { $$ = A_GE;}
        | T_LE { $$ = A_LE;}
        | T_EQ { $$ = A_EQ;}
        | T_NE { $$ = A_NE;}
        ;// Relational operators for comparisons

Additive_Expression: Term {$$ = $1; }
                   | Additive_Expression AddOp Term 
                   { 
                     if($1->my_data_type != $3 -> my_data_type)
                     {
                      yyerror("type mismatch");
                      exit(1);
                     }
                     $$ = ASTCreateNode(A_EXPR); //create an expression node for addition/subtraction
                     $$ -> s1 = $1; //pass up left side 
                     $$ -> s2 = $3; //pass up right side
                     $$ -> operator = $2;  // pass up operator
                     $$ -> name = CreateTemp(); //create a temporary name
                     $$ -> symbol = Insert($$->name,$1->my_data_type,SYM_SCALAR, LEVEL, 1, OFFSET);   //insert the temporary name into the symbol table
                     OFFSET = OFFSET+1;
                   }
                   ; // Additive expression can be a term or involve addition/subtraction

AddOp: '+' {$$ = A_PLUS;}
     | '-' {$$ = A_MINUS;}
     ;// Addition or subtraction operators

Term: Factor {$$ = $1; }
    | Term MultOp Factor 
    {
      if($1->my_data_type != $3 -> my_data_type){
        yyerror("Type mismatch term");
        exit(1);
      }
     $$ = ASTCreateNode(A_EXPR); //create an expression node for multiplication/division/modulus
     $$ -> s1 = $1; //pass up left side 
     $$ -> s2 = $3; //pass up right side
     $$ -> operator = $2;  // pass up operator
     $$ -> my_data_type = $1 -> my_data_type; //set data type
     $$ -> name = CreateTemp();   //create a temporary name
     $$ -> symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); //insert the temporary name into the symbol table
     OFFSET = OFFSET + 1;
     } 
    ;// Term can be a factor or involve multiplication/division

MultOp: '*' {$$ = A_TIMES;}
      | '/' {$$ = A_DIV;}
      | '%' {$$ = A_MOD;}
      ; // Multiplication or division operators

Factor: '(' Expression ')' {$$ = $2;}
      | T_NUM 
        { 
          $$ = ASTCreateNode(A_NUM); //create a num node
          $$ -> value = $1; //set value and pass up
          $$ -> my_data_type = A_INTTYPE; //set data type
        }
      | Var {$$ = $1;}
      | Call {$$ = $1;}
      | '-' Factor
      {
        if($2 -> my_data_type != A_INTTYPE)
        {
         yyerror("Type mismatch unary minus");
         exit(1);
        }
          $$ = ASTCreateNode(A_EXPR);     // create a new node
          $$ -> s1 = $2;                  // set the factor
          $$ -> operator = A_UNMINUS;       // set the operator to unary for ASTprint
          $$ -> name = CreateTemp();
          $$ -> my_data_type = A_INTTYPE;
          $$ -> symbol = Insert($$ -> name, $2 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
          OFFSET = OFFSET + 1;
        }
      ; // Factor can be an expression, number, variable, function call, or negated factor

Call: T_ID '(' Args ')'
    { 
      struct SymbTab *p;    //create a symbol table pointer
      p = Search($1, 0 , 0);  //search for the function name
      if(p==NULL){    //if the function name is not found
        //function name not known
        yyerror($1);
        yyerror("function name not defined"); 
        exit(1);  //exit the program
      }
      //name is there but is it a FUNCTION

      if(p->SubType != SYM_FUNCTION){   //if the function name is not found
        //function name not known
        yyerror($1);
        yyerror("is not defined as a function"); 
        exit(1);  //exit the program
      }

      //check to see if the formal and actual parameters match
      if(check_params($3, p->fparms) == 0){   //if the parameters do not match
        yyerror($1);
        yyerror("Actual and Formals do not match"); 
        exit(1);  //exit the program
      } else {

      $$ = ASTCreateNode(A_CALL); //create a function call node
      $$ -> name = $1; //set name and pass up
      $$ -> s1 = $3;  //set s1 to the arguments in ()
      $$ -> symbol = p; //set symbol to the function name
      $$ -> my_data_type = p -> Declared_Type;  //set data type to the function name
      }
    }
    ; // Function call with optional arguments

Args: Args_List
    { $$ = $1;}
    | /* empty */
    {$$ = NULL;}
    ; // Arguments to a function call can be empty or a list of expressions

Args_List: Expression
         { 
            $$ = ASTCreateNode(A_ARG); //create an arg node
            $$ -> s1 = $1 ; //set s1 to expression being passed as an argument
            $$ -> my_data_type = $1 -> my_data_type;  //set data type
            $$ -> name = CreateTemp();  //create a temporary name
            $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);  //insert the temporary name into the symbol table
            OFFSET = OFFSET + 1; 
         }
         | Expression ',' Args_List
         { 
            $$ = ASTCreateNode(A_ARG); //create a function arg node
            $$ -> s1 = $1; //set s1 to expression being passed as an argument
            $$ -> next = $3; //Link to the next argument in the list
            $$ -> my_data_type = $1 -> my_data_type;  //set data type
            $$ -> name = CreateTemp();  //create a temporary name
            $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);  //insert the temporary name into the symbol table
            OFFSET = OFFSET + 1;
         }
         ;// Argument list can be a single expression or a list of expressions

%% /*end of rules */

int main(int argc, char *argv[]) {
    FILE *fp;
    //read our input arguments
    int i;
    char s[100];

    //  option -d for debug
    //  option -o next argument is output file
    for(i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-d") == 0){mydebug = 1;}
        if(strcmp(argv[i], "-o") == 0)
        { //we have file input
          strcpy(s, argv[i+1]);
          strcat(s, ".asm");
        }
    }

    //now open the file that is refernced by s

    fp = fopen(s, "w");
    if(fp == NULL)
    {
        printf("Could not open file %s\n", s);
        exit(1);
    }

    yyparse();
    if(mydebug)printf("\nFinished Parsing\n\n\n");
    // we know that global variable PROGRAM has a ptr to the top of the tree

    if(mydebug)Display();
    if(mydebug) printf("\n\n AST PRINT \n\n");
    if(mydebug) ASTprint(0, PROGRAM); 

    EMIT(PROGRAM, fp);
}
