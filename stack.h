#include "da.h"
#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

typedef struct STACK STACK;

STACK *newSTACK(void (*d)(FILE *d,void *));   //constructor
void push(STACK *items,void *value);         //stores a generic value
void *pop(STACK *items);                     //returns a generic value
void *peekSTACK(STACK *items);               //returns a generic value
int sizeSTACK(STACK *items);
void displaySTACK(FILE *fp,STACK *items);
extern void displaySTACKds(FILE *,STACK *items);

#endif
