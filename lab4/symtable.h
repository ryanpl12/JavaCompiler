    /*

    symbtab.h
    Ryan Lucero
    2/4/2024
    CS370 Spring Shaun Cooper
    Lab4
    
    This is the header file intended to expose the Insert() and Search() methods as well as Struct{}.

*/
#ifndef SYMBTAB_H
#define SYMBTAB_H

struct SymbTab {
    char *symbol;
    int addr;
    struct SymbTab *next;

};

int FetchAddress(char *s);

//void Insert(char *l, int addr);
struct SymbTab *Insert(char *l, int addr);
//int Search(char *lab);
struct SymbTab *Search(char *symbol);
void Display();
void Delete(char *l);




#endif 