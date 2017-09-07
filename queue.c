#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "queue.h"
#include "cda.h"

struct queue{
	CDA *queueItems;
	void(*display) (FILE *, void *);
};

/****** public methods ******/

QUEUE *
newQUEUE(void(*d)(FILE *, void *)){

	QUEUE *items = malloc(sizeof(QUEUE));

	assert(items != 0);
	items->queueItems = newCDA(d);
	items->display = d;

	return items;
}

void
enqueue(QUEUE *items, void *value){
	insertCDAback(items->queueItems, value);
}

void *
dequeue(QUEUE *items){
	assert(sizeCDA(items->queueItems) > 0);

	return removeCDAfront(items->queueItems);
}

void * 
peekQUEUE(QUEUE *items){
	assert(sizeCDA(items->queueItems) > 0);

	return getCDA(items->queueItems, 0);
}

int 
sizeQUEUE(QUEUE *items){
	return sizeCDA(items->queueItems);
}

void
displayQUEUE(FILE *fp, QUEUE *items){
	int i = 0;
	int size = sizeCDA(items->queueItems);

	fprintf(fp, "<");
	while(i < size){
		items->display(fp, getCDA(items->queueItems, i));
		if (size > 1 && i != size - 1){
			fprintf(fp, ",");
		}
    ++i;
	}

	fprintf(fp, ">");
}

void
visualizeQUEUE(FILE *fp, QUEUE *items){
	displayCDA(fp, items->queueItems);
}