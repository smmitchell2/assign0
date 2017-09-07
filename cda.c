#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cda.h"

struct cda{
	int size;
	int startIndex;
	int endIndex;
	int capacity;
	void **store;
	void(*display) (FILE *, void *);
};

/****** public methods ******/

CDA *
newCDA(void(*d)(FILE *, void *)){	
	CDA *items = malloc(sizeof(CDA));

	assert(items != 0);

	items->size = 0;
	items->startIndex = 0; 
	items->endIndex = 0; 
	items->capacity = 1;
	items->store = malloc(sizeof(void *) * items->capacity);
	
	assert(items->store != 0);

	items->display = d;
	
	return items;
}

static int
correctIndex(CDA *items, int index){
	int correctedIndex = ((index + items->capacity) % items->capacity);
	return correctedIndex;
}

static void
grow(CDA *items){

	int newCapacity = items->capacity * 2;
	int i;
	void **newArray = malloc(sizeof(void *) * newCapacity);
	
	assert(newArray != 0);

	for (i = 0; i < items->size; ++i){
		newArray[i] = getCDA(items, i);
	}
	items->startIndex = 0;
	items->endIndex = items->size;
	items->store = newArray;
	items->capacity = newCapacity;
}

static void
shrink(CDA *items){

	int newCapacity = items->capacity / 2;
	int i;
	void **newArray = malloc(sizeof(void *) * newCapacity);
	
	assert(newArray != 0);

	for (i = 0; i < items->size; ++i){
		newArray[i] = getCDA(items, i);
	}
	items->startIndex = 0;
	items->endIndex = items->size;
	items->store = newArray;
	items->capacity = newCapacity;
}

void
insertCDAfront(CDA *items, void *value){

	assert(items != 0);

	if (items->size == 0){
		insertCDAback(items, value);
		return;
	}

	if (items->size == items->capacity){
		grow(items);
	}
	
	items->startIndex = correctIndex(items, items->startIndex - 1);
	items->store[items->startIndex] = value;

	++items->size;
	return;
}

void
insertCDAback(CDA *items, void *value){

	assert(items != 0);

	if (items->size == items->capacity){
		grow(items);
	}
	items->store[items->endIndex] = value;
	items->endIndex = correctIndex(items, items->endIndex + 1);

	++items->size;
	return;
}

void *
removeCDAfront(CDA *items){

	assert(items->size > 0);
	
	if ((0.25 > (items->size-1) /(double) items->capacity) && items->capacity != 1){
		shrink(items);
	}

	void* returnItem = getCDA(items, 0);

	items->startIndex = correctIndex(items, items->startIndex + 1);

	--items->size;
	return returnItem;
}

void *
removeCDAback(CDA *items){

	assert(items->size > 0);

	if ((0.25 > (items->size-1) /(double) items->capacity) && items->capacity != 1){
		shrink(items);
	}

	void* returnItem = getCDA(items, items->size - 1);

	items->endIndex = correctIndex(items, items->endIndex - 1);

	--items->size;
	return returnItem;
}

void
unionCDA(CDA *recipient, CDA *donor){

	int i = 0;
	int donorLen = donor->size;
	while(i < donorLen){
		insertCDAback(recipient, getCDA(donor, i));
		++i;
	}
	i = 0;
	while(i < donorLen){
		removeCDAfront(donor);
		++i;
	}

	return;
}

void *
getCDA(CDA *items, int index){
	assert(index >= 0);
	assert(index < items->size);

	int correctedIndex = correctIndex(items, index + items->startIndex);
	return items->store[correctedIndex];

}

void *
setCDA(CDA *items, int index, void *value){

	assert(index >= -1);
	assert(index <= items->size);

	if (index == items->size) {
		insertCDAback(items, value);
		return 0;
	}

	else if (index == -1) {
		insertCDAfront(items, value);
		return 0;
	}

	void *oldVal = getCDA(items, index);
	int correctedIndex = correctIndex(items, index + items->startIndex);
	items->store[correctedIndex] = value;

	return oldVal;
}

void **
extractCDA(CDA *items){

	assert(items != 0);

	shrink(items);
	void **returnList = items->store;

	items->capacity = 1;
	items->size = 0;
	items->store = malloc(sizeof(void *) * items->capacity);
	
	assert(items->store != 0);

	return returnList;
}

int
sizeCDA(CDA *items){ 
	return items->size;
}

void
visualizeCDA(FILE *fp, CDA *items){

	int i = 0;

	fprintf(fp, "(");
	while(i < items->size){
		items->display(fp, getCDA(items, i));
		if (items->size > 1 && i != items->size - 1)
		{
			fprintf(fp, ",");
		}
		++i;
	}

	fprintf(fp, ")");
	fprintf(fp, "(");
	int unfillReg = items->capacity - items->size;
	fprintf(fp, "%d", unfillReg);
	fprintf(fp, ")");
}

void
displayCDA(FILE *fp, CDA *items){
	int i = 0;

	fprintf(fp, "(");
	while(i < items->size){
		items->display(fp, getCDA(items, i));
		if (items->size > 1 && i != items->size - 1)
		{
			fprintf(fp, ",");
		}
		++i;
	}

	fprintf(fp, ")");
}