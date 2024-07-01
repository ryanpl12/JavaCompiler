     /*  This lex routine uses a counting array to match alphabeticstrings 
         and make a frequency count.
  
         The real item to notice is that yywrap() is called at EOF and then is run
         to do what we need to do.   yywrap() returns true when we have a successful 
         end to the program.  We may want to return false (0) if we want to lexing process 
         to fail 

        Ryan Lucero
		January 23, 2024
		CS370 
		lab1
   */
	int lgths[100];
	int x; // integer variable 'x' to count occurences
%%
[a-zA-Z]+	lgths[yyleng]++;
[0-9]+		x++; 
.	|
\n	;
%%
int yywrap()  // Method called by yylex 
{
	int i;
	printf("Length  No. words\n");
	for (i=1; i<100; i++) {  // For loop to iterate through lngths[]
		if (lgths[i] > 0) {
			printf("%5d%10d\n",i,lgths[i]);
		}
	}
	printf("Number of numbers: %d\n", x);  // Print out the occurences of numbers
	return(1);
}

void main()  // Calls and returns yylex function results
{  yylex();

}
