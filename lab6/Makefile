# Ryan Lucero
# CS370 Spring 2024 
# Shaun Cooper
# Lab6 Makefile
# This Makefile compiles the lab6 program which includes a lex file, yacc file,
# and an abstract syntax tree (ast.c and ast.h) implementation for the CMINUS+ programming language.

all: lab6


lab6: lab6.l lab6.y ast.c ast.h
	lex lab6.l
	yacc -d lab6.y
	gcc lex.yy.c y.tab.c ast.c -o lab6

clean:
	rm -f lab6