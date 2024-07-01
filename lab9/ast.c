/* 

    Ryan Lucero
    Lab 9 - MIPS Code Generation from AST
    CS370 Spring 2024 - Shaun Cooper
    4/30/2024

    ast.c

    This file is part of the CMINUS+ compiler. This code focuses on the combination of the YACC code to
    create and handle the AST for a given CMINUS+ code. It provides the implementation for creating and manipulating the 
    Abstract Syntax Tree , which represents the parsed structure of CMINUS+ programs.
    

*/
#include <stdio.h>
#include <malloc.h>
#include "ast.h"
/* uses malloc to create an ASTnode and passes back the heap address of the newley
created node */
// PRE: Ast Node Type
// POST: PTR To heap memory and ASTnode set and all other pointers set to NULL
ASTnode *ASTCreateNode(enum ASTtype mytype)
{
    ASTnode *p;
    if (mydebug)
        fprintf(stderr, "Creating AST Node \n");
    p = (ASTnode *)malloc(sizeof(ASTnode));
    p->type = mytype;
    p->s1 = NULL;
    p->s2 = NULL;
    p->next = NULL;
    p->value = 0;
    return (p);
}
/* Helper function to print tabbing */
// PRE: Number of spaces desired
// POST: Number of spaces printed on standard output
void PT(int howmany)
{
    int space = 0;
    while(space < howmany) {
        printf(" ");
        space++;
    }
    space++; 
}
// PRE: A declaration type
// POST: A character string that is the name of the type
// Typically used in formatted printing
char *ASTtypeToString(enum AST_MY_DATA_TYPE mytype)
{
    switch (mytype)
    {
    case A_INTTYPE: return ("INT");
        break;
    
    case A_VOIDTYPE: return ("VOID");
        break; 

    default: printf("Unknown type\n"); 
        break;
    }
}
/* Print out the abstract syntax tree */
// PRE: PRT to an ASTtree
// POST: indented output using AST order printing with indentation
void ASTprint(int level, ASTnode *p)
{
    int i;
    if (p == NULL)  // Base case: If the current node is NULL, do nothing
        return;

    // Switch on the type of the current AST node to determine how to print it.
    switch (p->type)
        {
        //PRE: A variable declaration AST node
        //POST: Outputs the variable's type, name, and, if it's an array, the size. Recursively prints any children or sibling nodes
        case A_VARDEC:
            PT(level);
            // check if the variable declaration includes an array size
           if(p -> value > 0)  
           { 
            // For array variables, print the variable type, name, and size                                     LAB 7 ADDED: LEVEL AND OFFSET
            printf("Variable %s %s with array size [%d] level %d offset %d\n", ASTtypeToString(p -> my_data_type), p->name, p -> value, p->symbol->level, p->symbol->offset);
           } else {  
            // For simple variables, print the variable type and name                                     LAB 7 ADDED: LEVEL AND OFFSET
            printf("Variable %s %s level %d offset %d\n", ASTtypeToString(p -> my_data_type), p->name, p->symbol->level, p->symbol->offset);
           }
            ASTprint(level, p -> s1); // Recursively print the first child node, if any
            ASTprint(level, p -> next);  
            break;

        //PRE: A function declaration AST node
        //POST: Prints the function's return type and name, and recursively prints parameters and function body. Continues with any sibling nodes
        case A_FUNCTIONDEC:
            PT(level); 
            // Print the function's return type, name, and indicate the start of its definition                 LAB 7 ADDED: LEVEL AND OFFSET
            printf("Function %s %s level %d offset %d\n", ASTtypeToString(p -> my_data_type), p -> name, p->symbol->level, p->symbol->offset); 
            // Recursively print the function's parameters (first child)
            ASTprint(level + 1, p -> s1); 
            // Recursively print the function's body (second child)
            ASTprint(level + 1, p -> s2);  
            // Continue printing the next node at the same level, if part of a list of functions
            ASTprint(level, p-> next); 
            break;

        //PRE: A compound statement AST node
        //POST: Prints the compound structure and recursively prints local declarations and statement lists
        case A_COMPOUND: 
            PT(level); 
            printf("Compound Statement\n"); 
            //recursively print local declarations within the compound statement
            ASTprint(level + 1, p -> s1);
            //recursively print the list of statements within the compond statement
            ASTprint(level + 1, p -> s2); 
            break;

        //PRE: A write statement AST node
        //POST: Determines if writing a string or an expression and prints accordingly. Recursively handles sibling nodes
        case A_WRITE:
            PT(level); 
                //check if the write operation is for a string or an expression
                if(p -> name != NULL) 
                {
                    printf("Write String %s\n", p -> name); //print the string being written
                } else {
                    printf("Write Expression\n");
                    ASTprint(level + 1, p -> s1); //recursively print the expression being written
                }
            ASTprint(level, p-> next);
            break;

        //PRE: A numerical value AST node
        //POST: Prints the numerical value
        case A_NUM:
            PT(level); 
            printf("NUMBER value %d \n", p -> value);  // Print the number
            break; 

        //PRE: A parameter declaration AST node
        //POST: Prints parameter's type and name, including an indication of array if applicable and continues with any sibling parameter nodes
        case A_PARAM: 
            PT(level);
            if (p->value != 0)
                {
                printf("Parameter %s %s[] level %d offset %d", ASTtypeToString(p->my_data_type), p->name, p->symbol->level, p->symbol->offset);
                }
            if (p->value == 0)
                {
                printf("Parameter %s %s level %d offset %d", ASTtypeToString(p->my_data_type), p->name, p->symbol->level, p->symbol->offset);
                }
            printf("\n");
            if (p->next != NULL)
                {
            ASTprint(level, p->next);   // IF there IS a next parameter in the list, recursively print it
                }
                break;

        //PRE: An expression AST node
        //POST: Prints the type of operator in the expression and recursively prints the operands then handles different operators with specific output for each
        case A_EXPR:
            PT(level); 
            printf("EXPRESSION operator ");  
            // Switch based on the operator type to print the specific operator used in the expression
            switch(p -> operator) {
                case A_PLUS:
                    printf("+ \n");
                break;

                case A_MINUS:
                    printf("- \n");
                break; 

                case A_TIMES:
                    printf("* \n");
                break;

                 case A_DIV:
                    printf("/ \n");
                break;

                 case A_MOD:
                    printf("% \n");
                break;

                case A_EQ:
                    printf("==\n");
                break; 
                
                case A_LT:
                    printf("<\n");
                break;  

                case A_GT:
                    printf(">\n");
                break;

                case A_GE:
                    printf(">=\n");
                break;

                case A_LE:
                    printf("<= \n");
                break;

                case A_NE:
                    printf("!=\n");
                break; 

                default: 
                    printf("UNKNOWN operator in A_EXPR in ASTprint \n");
                break; 

                case A_UNMINUS:
                    printf("UNARY MINUS\n");
                
                break;
            }
            ASTprint(level + 1, p -> s1);
            ASTprint(level + 1, p -> s2); 
            break; 

        //PRE: A read statement AST node
        //POST: Prints the read statement and recursively prints the variable being read
        case A_READ:
             PT(level); 
               printf("READ STATEMENT \n");
               ASTprint(level + 1, p -> s1); //recursively print the variable being read
            break; 

        //PRE: A return statement AST node
        //POST: Prints the return statement and, if there is an expression to return, recursively prints it
        case A_RETURN:
            PT(level);
            printf("Return Statement \n");
            // If there is an expression to return then print it by calling ASTprint
            if(p -> s1 != NULL) 
            {
                ASTprint(level + 1, p -> s1);
            }
            ASTprint(level, p -> next); //continue printing statements in the function body - if any exist
        break; 

        //PRE: A variable usage AST node
        //POST: Prints the variable name and, if it's an array, recursively prints the index expression
        case A_VAR:
            PT(level);
            if(p -> s1 == NULL) 
            {
                printf("VARIABLE %s level %d offset %d\n", p -> name, p->symbol->level, p->symbol->offset); //LAB 7 ADDED:  print the variables name, level, and offset
                ASTprint(level + 1, p -> s1);
            } else {
                printf("VARIABLE %s level %d offset %d ", p -> name, p->symbol->level, p->symbol->offset); //LAB 7 ADDED:  print the variables name, level, and offset
                PT(level + 1);
                printf("\n");
                PT(level);
                printf("[\n"); // Open the array
                ASTprint(level + 2, p -> s1); //recursively print the expression used
                PT(level);
                printf("]\n"); // Close the array
            }
            break; 

        //PRE: An assignment statement AST node.
        //POST: Prints the assignment statement and recursively prints the variable and expression involved in the assignment
        case A_ASSIGN:
            PT(level);
            printf("ASSIGNMENT Statement \n");
            ASTprint(level + 1, p -> s1); //recursively print the variable being assigned to
            PT(level);
            printf(" is assigned \n");
            ASTprint(level + 1, p -> s2); //recursively print the expression being assigned
            ASTprint(level, p -> next);
  
        break;

        //PRE: A function call argument AST node
        //POST: Prints the argument and recursively prints the expression being passed as an argument
        case A_ARG:
        // Handles the printing of function call arguments in the AST
            PT(level);
            printf("CALL argument \n"); //signifies the start of an argument in a function call
            ASTprint(level + 1, p -> s1); //recursively prints the argument expression
            ASTprint(level, p -> next); //if there are more arguments in the list then recursively print the next one
        break; 

        //PRE: A while loop AST node
        //POST: Prints the while statement, the condition expression, and the loop body
        case A_WHILE:
            PT(level);
            printf("WHILE Statement \n"); //indicates the start of a while statement
            if(p -> s1 != NULL) {
                PT(level + 1);
                printf("WHILE Expression \n"); // handles the expression that acts as the loop condition
                ASTprint(level + 2, p -> s1);  //recursively prints the condition expression
            }
               if(p -> s2 != NULL) {
                PT(level + 1);
                printf("WHILE body \n"); // indicates the start of the loop bod
                ASTprint(level + 2, p -> s2); //recursively prints the statements inside the loop body
            }
            ASTprint(level, p -> next); //continues to print the next AST node at the current level
        break; 

        //PRE: An expression statement AST node
        //POST: Prints the expression statement and recursively prints the contained expression
        case A_EXPRESSIONSTMT:
            PT(level);
            printf("EXPRESSION STATEMENT \n"); // indicates the start of an expresion
            ASTprint(level + 1, p -> s1); //prints the expression
            ASTprint(level, p -> next); //continues to print the next AST node at the current level
        break; 

        //PRE: A function call AST node
        //POST: Prints the function call including the function name and recursively prints any arguments passed to the funtion
        case A_CALL:
            PT(level);
            printf("CALL STATEMENT function %s \n", p -> name );
            PT(level + 1);
            printf("( \n"); // print the opening parenthesis to indicate the start of the parenthesis
            ASTprint(level + 2, p -> s1);
            PT(level + 1);
            printf(")\n"); // print the closing parenthesis to indicate the end of the parenthesis

            break;

        //PRE: An if statement AST node
        //POST: Prints the if statement and condition expression then recursvely prints the if body and, if present, the else body
        case A_IF:
            PT(level);
            printf("IF STATEMENT\n"); // start of an if statement

            // If there is a condition expression for the if statement, print it
            if(p -> s1 != NULL)
            {
                PT(level + 1);
                printf("IF EXPRESSION \n"); // signifies the condition of the if statement
                ASTprint(level + 2, p -> s1); //prints the condition expression
            }
            // If there is a body for the if branch then print it
            if(p -> s2 -> s1 != NULL)
            {
                PT(level + 1);
                printf("IF body \n"); //start of the if body
                ASTprint(level + 2, p -> s2 -> s1); //prints the statements inside the if body
            }
            // If there is an else branch then print its body
            if(p -> s2 -> s2 != NULL)
            {
                PT(level + 1);
                printf("ELSE body\n"); //start of the else body
                ASTprint(level + 2, p -> s2 -> s2); // prints the statements inside the else body
            }
            ASTprint(level, p -> next);

            break;


        default:
            printf("unknown AST Node type %d in ASTprint\n", p->type);
        }//end of switch
    } //end of ASTprint


//PRE : PTRS to actual and formal
//POST: 0 if they are not same type or length
//      1 if they are
int check_params(ASTnode *actual, ASTnode *formals)
{
    // Base case: if both actual and formal parameters are NULL, they match
    if (actual == NULL && formals == NULL) 
    {
        return 1;
    }
    // If only one of them is NULL, they don't match
    if (actual == NULL || formals == NULL) 
    {
        return 0;
    }
    if(actual->my_data_type != formals->my_data_type)
    {
        return 0;
    }
    return(check_params(actual->next, formals->next));
}

/* dummy main program so I can compile for syntax error independently
main()
{
}
/* */