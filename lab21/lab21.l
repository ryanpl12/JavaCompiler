         /* simple lex program which removes comments from a source program
            The main key is that a variable "comment" is set when the start of a comment
            is seen and then unset when the ending set is seen.  It is possible to have
            two starts closed by on end.

            Ryan Lucero
            January 30, 2024
            CS370 Spring
            lab21

            In this program I have added a new 'lineNum' variable to count the number of lines that are not comments. This variable increments only when it is recognized that it is outside of a comment. I have added a new line to print when it is recognized to be not in a comment.  
 
         */
        int comment = 0;
        int debug=1;  /* prints out debug statements if desired */
        int lineNum = 1;  /* counts the number of lines */
%%
"/*"	{
	if (comment && debug) fprintf(stderr,
		" >>>>>>>> line %d: Possible Nested comment <<<<<<<<<<\n", lineNum); 
	comment = 1;
	}

"*/"	{
          if (!comment) printf("%s",yytext); /*print out if it is not in a comment */
  	  comment = 0;
	}
  \n {if(!comment)   /* Enter ONLY IF NOT a comment*/
     printf("\n");  
       ++lineNum;  /* Increment the number of lines */
  }
.       { if (!comment) printf("%s",yytext);}



%%

int yywrap()
{ return 1;
}

void main()  /* Set main as void to avoid a return statement */
{
  yylex();
}

