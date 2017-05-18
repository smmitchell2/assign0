#ifndef __CDA_INCLUDED__
#define __CDA_INCLUDED__

#include <stdio.h>

typedef struct CDA CDA;

extern CDA *newCDA(void (*d)(FILE *,void *)); 
extern void insertCDAFront(CDA *items,int index,void *value);
extern void insertCDABack(CDA *items,int index,void *value);
extern void *removeCDAFront(CDA *items,int index);
extern void *removeCDABack(CDA *items,int index);
extern void unionCDA(CDA *recipient,CDA *donor);
extern void *getCDA(CDA *items,int index);
extern void *setCDA(CDA *items,int index,void *value);
extern int sizeCDA(CDA *items);
extern void displayCDA(FILE *,CDA *items);

#endif