#include <stdio.h>
#include <stdlib.h>
#include "cda.h"

struct CDA{
	void **array; 
	int capacity; 
	int size;
	int startIndex;
	int endIndex; 	  
	void (*display)(FILE *, void *); 
};

CDA *newCDA(void (*display)(FILE *,void *)){
	CDA *a = malloc(sizeof(CDA)); 
	a->array = malloc(sizeof(void *)*1);
	a->capacity = 1;
	a->size = 0;
	a->startIndex = 0;
	a->endIndex = 0;
	a->display = display;

	return a;
}

void insertCDAFront(CDA *a,int index,void *v){
	if(a->size == a->capacity){
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	int front = (a->startIndex + a->size) % a->capacity;
	a->array[front] = v;
}

void insertCDABack(CDA *a,int index,void *v){
	if(a->size == a->capacity){
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	a->array[a->size++] = v;
}

void *removeCDAFront(CDA *a,int index){
	if(a->size == 0){
		fprintf(stderr, "Attempting to remove from an empty array\n");
		exit(-1);
	}
	int front = (a->startIndex + a->size) % a->capacity;
	void *rv = a->array[front];
	a->array[front] = NULL;
	--a->size;
	double size = a->size;
	double capacity = a->capacity;

	if(size < capacity/4.0 && capacity > 2){
		a->capacity /= 2; 
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	return rv;
}

void *removeCDABack(CDA *a,int index){
	void *rv = a->array[a->size-1];
	if(a->size == 0){
		fprintf(stderr, "Attempting to remove from an empty array\n");
		exit(-1);
	}

	a->array[a->size-1] = NULL;
	--a->size;
	double size = a->size;
	double capacity = a->capacity;

	
	if(size < capacity/4.0 && capacity > 2){
		a->capacity /= 2; 
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	return rv;
}

void unionCDA(CDA *recipient,CDA *donor){
    
}

void *getCDA(CDA *a,int index){
	return a->array[index];
}

void setCDA(CDA *a,int index,void *value){ //fix
	if(index == a->size) {
		return insertCDA(a, value);
	}

	a->array[index] = value;
}

int sizeDA(CDA *a){
	return a->size;
}

void displayCDA(FILE *fp,CDA *a){
	int index = 0;
	fprintf(fp,"(");
	while(a->size - index > 0){
		a->display(fp,a->array[index]);
		if(index + 1 < a->size) {
			fprintf(fp, ",");
		}
		index++;
	}
	fprintf(fp, ")");

	fprintf(fp, "(%d)", a->capacity - a->size);
}