/*
    Ryan Lucero
    Lab 9 - MIPS Code Generation from AST
    CS370 Spring 2024 - Shaun Cooper
    4/30/2024

    emit.h

    This file exposes the functions that are used to generate the MIPS code from the AST.
    This file also defines the size of a word and the log of the word size.

*/


#ifndef EMIT_H
#define EMIT_H
#include "ast.h"

#define WSIZE   4
#define LOG_WSIZE 2

void EMIT(ASTnode *p, FILE* fp);
void EMIT_GLOBALS(ASTnode *p, FILE* fp);
void EMIT_STRINGS(ASTnode *p, FILE *fp);
void emit(FILE *fp, char *label, char *command, char *comment);
void emit_var(ASTnode *p, FILE *fp);
void emit_expr(ASTnode *p, FILE *fp);
void emit_stmt(ASTnode *p, FILE *fp);
void emit_if(ASTnode *p, FILE *fp);
void emit_while(ASTnode *p, FILE *fp);
void emit_assign(ASTnode *p, FILE *fp);
void emit_function(ASTnode *p, FILE *fp);
void emit_return(ASTnode *p, FILE *fp);
void emit_call(ASTnode *p, FILE *fp);
void emit_read(ASTnode *p, FILE *fp);
void emit_write(ASTnode *p, FILE *fp);



#endif