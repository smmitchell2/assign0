#include <stdio.h>
#include <stdlib.h>

#ifndef __DA_INCLUDED__
#define __DA_INCLUDED__

typedef struct DA DA;

extern DA *newDA(void (*display)(FILE *,void *));
extern void insertDA(DA *a,void *v);
extern void *removeDA(DA *a);
extern void unionDA(DA *recipient, DA *donor);
extern void *getDA(DA *a,int index);
extern void setDA(DA *a,int index,void *value);
extern int sizeDA(DA *a);
extern void displayDA(FILE *,DA *a);

#endif