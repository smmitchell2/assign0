#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "da.h"

struct da{
	int size;
	int capacity;
	void **store;
	void (*display) (FILE *, void *);
};

/****** public methods ******/

DA *
newDA(void (*d)(FILE *, void *)){

	DA *items = malloc(sizeof(DA));

	assert(items != 0);

	items->size = 0;
	items->capacity = 1;
	items->store = malloc(sizeof(void *) * items->capacity);
	
	assert(items->store != 0);

	items->display = d;

	return items;
}

void
insertDA(DA *items, void *value){

	assert(items != 0);

	if (items->size == items->capacity){
		items->capacity = items->capacity * 2;
		items->store = realloc(items->store, sizeof(void *) * items->capacity);
		assert(items->store != 0);
	}

	items->store[items->size] = value;

	++items->size;
	return;
}

void *
removeDA(DA *items){

	assert(items->size > 0);

	int size = items->size;

	if (( 0.25 > ((double)items->size / (double) items->capacity)) && items->capacity != 1){
		items->capacity = items->capacity / 2;
		items->store = realloc(items->store, sizeof(void *) * items->capacity);
		assert(items->store != 0);
	}

	--items->size;
	return items->store[size - 1];
}

void
unionDA(DA *recipient, DA *donor){

	int i = 0;
	int donorLen = donor->size;

	while(i < donorLen){
		insertDA(recipient, getDA(donor,i));
		++i;	
	}
	i = 0;
	while(i < donorLen){
		removeDA(donor);
		++i;
	}

	return;
}

void *
getDA(DA *items, int index){
	assert(index >= 0);
	assert(index < items->size);

	return items->store[index];
}

void *
setDA(DA *items, int index, void *value){

	assert(index >= 0);
	assert(index <= items->size);

	if (index == items->size){
		insertDA(items, value);
		return 0;
	}

	void *oldVal = getDA(items, index);
	items->store[index] = value;

	return oldVal;
}

void **
extractDA(DA *items){

	assert(items != 0);

	items->store = realloc(items->store, sizeof(void *) * items->size);
	assert(items->store != 0);

	void **returnList = items->store;

	items->capacity = 1;
	items->size = 0;
	items->store = malloc(sizeof(void *) * items->capacity);
	assert(items->store != 0);

	return returnList;
}

int
sizeDA(DA *items){
	return items->size;
}

void
visualizeDA(FILE *fp, DA *items){

	int i = 0;
	fprintf(fp, "[");
	while(i < items->size){
		items->display(fp, items->store[i]);
		if (items->size > 1 && i != items->size-1)
		{
			fprintf(fp, ",");
		}
		++i;
	}

	fprintf(fp, "]");
	fprintf(fp, "[");
	int unfillReg = items->capacity - items->size;
	fprintf(fp, "%d", unfillReg);
	fprintf(fp, "]");
}

void
displayDA(FILE *fp, DA *items){
	int i = 0;

	fprintf(fp, "[");
	while(i < items->size){
		items->display(fp, items->store[i]);
		if (items->size > 1 && i != items->size-1)
		{
			fprintf(fp, ",");
		}
		++i;
	}

	fprintf(fp, "]");
}