# Ryan Lucero
# CS370 Spring 2024 
# Shaun Cooper
# Lab7 Makefile
# This Makefile compiles the lab6 program which includes a lex file, yacc file,
# and an abstract syntax tree (ast.c and ast.h) implementation for the CMINUS+ programming language.

all: lab7


lab7: lab7.l lab7.y ast.c ast.h symtable.c symtable.h
	lex lab7.l
	yacc -d lab7.y
	gcc lex.yy.c y.tab.c ast.c symtable.c -o lab7

clean:
	rm -f lab7