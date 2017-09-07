#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include"stack.h"
#include"da.h"

struct stack{
	DA *stackItems;
	void(*display) (FILE *, void *);
};

/****** public methods ******/

STACK *
newSTACK(void(*d)(FILE *, void *)){

	STACK *items = malloc(sizeof(STACK));

	assert(items != 0);
	items->stackItems = newDA(d);
	items->display = d;
	
	return items;
}

void
push(STACK *items, void *value){
	insertDA(items->stackItems, value);
}

void *
pop(STACK *items){
	assert(sizeDA(items->stackItems) > 0);

	return removeDA(items->stackItems);
}

void *
peekSTACK(STACK *items){
	assert(sizeDA(items->stackItems) > 0);

	return getDA(items->stackItems, sizeDA(items->stackItems) - 1);
}

int 
sizeSTACK(STACK *items){
	return sizeDA(items->stackItems);
}

void
displaySTACK(FILE *fp, STACK *items){
	int size = sizeDA(items->stackItems);
  int i = size-1;
	fprintf(fp, "|");
	while(i >= 0){
		items->display(fp, getDA(items->stackItems,i));
		if (i < size && i != 0){
			fprintf(fp, ",");
		}
    --i;
	}

	fprintf(fp, "|");
}

void
visualizeSTACK(FILE *fp, STACK *items){
	displayDA(fp, items->stackItems);
}