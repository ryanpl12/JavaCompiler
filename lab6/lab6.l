/*                 
                    Ryan Lucero
                    January 30, 2024
                    CS370 Spring
                    Lab6

    This LEX code is responsible for tokenizing all input characters and providing them to YACC for syntax analysis. 
    The code defines token patterns for keywords, operators, identifiers, and literals, facilitating the lexical analysis 
    process of the compiler. Each pattern matches specific language constructs and returns the corresponding token to YACC. 
    Additionally, the code handles line number tracking and debug messages to aid in the development and debugging process.

*/
%{

int mydebug=0;  
int lineno = 1;

#include "ast.h"
#include "y.tab.h"
%}


%%

int   { return (T_INT);}
void  { return (T_VOID);}
read  { return (T_READ);}
string {return (T_STRING);}
if    {return (T_IF);}
else  {return (T_ELSE);}
while {return (T_WHILE);}
write {return (T_WRITE);}
return {return (T_RET);}
">"   { return (T_GT);}
">="  { return (T_GE);}
"<"   { return (T_LT);}
"<="  { return (T_LE);}
"=="  { return (T_EQ);}
"!="  { return (T_NE);}





[a-zA-Z][a-zA-Z0-9_]*	{/* tokenize ID */
                        if (mydebug) fprintf(stderr,"VARIABLE found\n"); 
                        yylval.string=strdup(yytext);
                        return(T_ID);
                        }

[0-9][0-9]*	            {if (mydebug) fprintf(stderr,"Digit found\n"); 
                        /*  Tokenize NUM */
                       yylval.value=atoi((const char *)yytext); 
                       return(T_NUM);
                       }

[ \t]		            {
                        /* Regex for TAB */
                        if (mydebug) fprintf(stderr,"Whitespace found\n");
                        }

[\;=\-+*/%&|(),\[\]{}] 	{ 
                        /* REGEx to recognize operators */
                        if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                        return (*yytext);
                        }

\n 		                {
                        /*  Recognize new-line */ 
                        if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                        lineno++;
                        }

\/\/[^\n]*              { /* Ignore any comments */}



\"[^"]*\"               { 
                        /* Recognizing strings */
                        yylval.string = strdup(yytext); 
                        return(T_STRING);
                        }


%%

int yywrap(void)
{ return 1;}


