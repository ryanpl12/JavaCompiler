# Ryan Lucero
# CS370 Spring 2024 
# Shaun Cooper
# Labb9: CMINUS+ Compiler
# This Makefile compiles the lab9 program which includes a lex file, yacc file,
# and an abstract syntax tree (ast.c and ast.h) implementation for the CMINUS+ programming language.
# The symtable.c and symtable.h files are used to implement a symbol table for the CMINUS+ language.
# The emit.c and emit.h files are used to generate MIPS assembly code for the CMINUS+ language.

all: lab9


lab9: lab9.l lab9.y ast.c symtable.c  emit.c
	lex lab9.l
	yacc -d lab9.y
	gcc lex.yy.c y.tab.c ast.c symtable.c emit.c -o lab9

clean:
	rm -f lab9