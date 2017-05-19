#include <stdlib.h>
#include <stdio.h>
#include "da.h"
#include "stack.h"

typedef struct STACK{
  DA *list;
}STACK;

//lifo
STACK *newSTACK(void (*d)(FILE *,void *)){
  STACK *s = malloc(sizeof(STACK));
  s->list = newDA(d);
  return s;
}

void push(STACK *items,void *value){
  insertDA(items->list,value);
}

void *pop(STACK *items){
  void *r = removeDA(items->list);
  return r;
}

void *peekSTACK(STACK *items){
  return getDA(items->list,0);
}

int sizeSTACK(STACK *items){
  return items->list->size;
}

void displaySTACK(FILE *fp,STACK *items){
  if(items->list->array == NULL){
        fprintf(fp,"[]");
        return;
    }
	int index = 0;
	fprintf(fp,"[");
	while(items->list->size - index > 0){
		items->list->display(fp,a->array[index]);
		if(index + 1 < items->list->size) {
			fprintf(fp, ",");
		}
		index++;
	}
	fprintf(fp, "]");
}

void displaySTACKds(FILE *fp,STACK *items){
  displayDA(fp,items->list);
}
