/*
    Ryan Lucero
    CS370 Spring 2024 Shaun Cooper
    2/16/2024
    Lab4 Symbol Table

    In this program I have added the method FetchAddress. This method is soley responsible for locating and returning the memory 
    location of a variable if it is stored in the symbol table.

*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "symtable.h"

/*
struct SymbTab {
    char *symbol;
    int addr;
    struct SymbTab *next;
};
*/

struct SymbTab *first, *last;

int size = 0;       //How many variables are in list

struct SymbTab *Insert(char *symbol, int address);
struct SymbTab *Search(char *symbol);

//void Insert(char *l, int addr);
void Display();
void Delete(char *l);
//int Search(char *lab);

/*
int main() 
{
    int op, addr;
    char la[100];
    do {
        printf("\n\tSYMBOL TABLE IMPLEMENTATION\n");
        printf("\n\t1.INSERT\n\t2.DISPLAY\n\t3.DELETE\n\t4.SEARCH\n\t5.END\n");
        printf("\n\tEnter your option : ");
        scanf("%d", &op);
        switch (op) {
            case 1:
            //Insert case with interction outside function
                printf("\n\tEnter the symbol : ");
                scanf("%s", la);    //Scanning for symbol
                printf("\n\tEnter the address : ");
                scanf("%d", &addr); //Scaning for address
                printf("\n\tSymbol inserted\n"); //Moved my print to outside function to allow printing to occur only when insertion happens.
                Insert(la, addr);
                break;
            case 2:
            //Display case
                Display();
                break;
            case 3:
            //Delete case
                printf("\n\tEnter the symbol to be deleted : ");
                scanf("%s", la);    //Scanning for symbol to delete
                Delete(la);
                break;
            case 4:
            //Search case
                printf("\n\tEnter the symbol to be searched : ");
                scanf("%s", la);    //Scanning for symbol to seach
                struct SymbTab *result = Search(la);
                printf("\n\tSearch Result:");
                if (result != NULL) // Check if the result is not NULL, which means symbol was found
                printf("\n\tThe symbol is present in the symbol table\n");
                else
                printf("\n\tThe symbol is not present in the symbol table\n");
                break;
            case 5:
                exit(0);
        }
    } while (op < 6);
    return 0;
}   //End main
*/

/*
    PRECONDITION -> symbol must be valid. Address must be an integer
    POSTCONDITION -> If the symbol did not previously exist in the symbol table, 
    it is added with the specified address, and the size of the symbol table is
    incremented by one. A pointer to the newly inserted symbol table entry is returned

*/
struct SymbTab *Insert(char *symbol, int address) 
{
    if (Search(symbol) != NULL) {   // Checking if symbol is already in Sym Table
        printf("\n\tThe symbol exists already in the symbol table\n\tDuplicate can't be inserted\n");
        exit(EXIT_FAILURE);     //ADDED EXIT AS PER INSTRUCTIONS
    }   //End if

    else{
        struct SymbTab *p;
        p = (struct SymbTab *)malloc(sizeof(*p));
        p->symbol = strdup(symbol); // Duplicate the symbol string
        p->addr = address;
    
        if (size == 0) {    //Empty list = initialize pointer
            first = p;
            last = p;
        } else {    //Otherwise append to list
            last->next = p;
            last = p;
        }

    size++;
    return p;
    }   //End of else


}   //End of Insert

/*
    No preconition.
    POSTCONDITION -> The current contents of the symbol table are printed
    to output. Each entry's symbol and address are displayed. 

*/

void Display() 
{
    struct SymbTab *p = first;
    printf("\n\tSYMBOL\t\tADDRESS\n");
    while (p != NULL) {         //While loop instead of for since local variables have been removed and now using pointer
        printf("\t%s\t\t%d\n", p->symbol, p->addr);
        p = p->next;
    }   // End of while

}   //End of display

/*
    PRECONDITION -> valid non-null pointer 
    POSTCONDITION -> If the symbol is found in the symbol table,
    a pointer to the symbol table entry is returned.

*/

struct SymbTab *Search(char *symbol) {
    //int i, flag = 0;
    struct SymbTab *p;
    p = first;
    while (p != NULL) {             //While loop instead of for loop to handle pointer parameter
        if (strcmp(p->symbol, symbol) == 0) {   //Compare the symbol being pointed to, to the symbol parameter
            return p; // Symbol found
        }
        p = p->next;  // continue to search
    }
    return NULL; // Symbl not found

}   //End of Search

/*
    PRECONDITION -> l must be valid non null pointer
    POSTCONDITION -> If the symbol is found in the symbol table, it is removed, 
    and the size of the symbol table is decremented by one. If the symbol is not
    found, the symbol table remains unchanged. After deleting, the updated 
    contents of the symbol table are displayed.

*/

void Delete(char *l) {
    struct SymbTab *p, *q;
    p = first;
    if (Search(l) == NULL)  //Determine if character is even in symbol table
        printf("\n\tSymbol not found\n");
    else        //Else delete
    {           //Continue with deletion
        if (strcmp(first->symbol, l) == 0) {    //If the l symbol is the first symbol in the list
            first = first->next;
        } else {        //If symbol not at beginning 
            q = p->next;
            while (q != NULL && strcmp(q->symbol, l) != 0) {    //Search for node to delete   
                p = p->next;
                q = q->next;
            }
            if (q != NULL) {        //If node was not found
                if (q == last) {
                    last = p;
                    p->next = NULL;
                } else {            //If its in the middle of list
                    p->next = q->next;
                }
            }
        }
        size--;
        printf("\n\tAfter Deletion: \n");
        Display();
    }   //End else 
}   //End of Delete


int FetchAddress(char *s) {
    struct SymbTab *p;
    /*p = Search(s);
    p = first;
    if(Search(s) != NULL){
        printf("");
        return 0;
    }
    return p -> addr;
    */
   p = first;
   while(p != NULL){                    /*When p is within the range of the symbol table: */
    if(strcmp(p->symbol, s) == 0){      /*Compare the value of *p with the symbol requested*/
        return p -> addr;               /*return the address of p*/
    }
     p = p -> next;                     /*Failed == move p to the next variable*/
   }    //END OF WHILE
   fprintf(stderr, "EXIT\n");           /*Symbol not present*/
   exit(1);
}       //END OF FetchAddress