# Ryan Lucero
#	CS370 Spring 2024 
#		Shaun Cooper
#			Lab4 Makefile
#

all:	lab4

lab4: 	symtable.c symtable.h lab4.y lab4.l
	lex lab4.l
	yacc -d lab4.y
	gcc symtable.c lex.yy.c y.tab.c -o lab4

clean: 	
		rm -f lab4
