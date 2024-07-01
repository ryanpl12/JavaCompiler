/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                    This LEX definition is the companion to the docalc.y YACC routine which
                   is a simple calculator

                    Ryan Lucero
                    January 30, 2024
                    CS370 Spring
                    Lab4

*/
%{

int mydebug=0;  
#include "y.tab.h"
%}


%%

"int"       {return (T_INT);}

[a-zA-Z][a-zA-Z0-9_]*	{if (mydebug) fprintf(stderr,"VARIABLE found\n"); 
                        yylval.string=strdup(yytext);
                        return(VARIABLE);
                        }

[0-9][0-9]*	{if (mydebug) fprintf(stderr,"Digit found\n"); 

                       yylval.value=atoi((const char *)yytext); 
                       return(INTEGER);
                       }

[ \t]		{if (mydebug) fprintf(stderr,"Whitespace found\n");}
[;=\-+*/%&|()] 	{ if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);}
\n 		{ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                       return (*yytext);}

%%

int yywrap(void)
{ return 1;}


