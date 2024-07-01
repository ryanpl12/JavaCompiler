# Ryan Lucero
#       CS370 Spring 2024 
#               Shaun Cooper
#                       Lab5 Makefile
#

all: lab5


lab5: lab5.l lab5.y
	lex lab5.l
	yacc -d lab5.y
	gcc lex.yy.c y.tab.c -o lab5

clean:
	rm -f lab5