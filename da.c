#include <stdio.h>
#include <stdlib.h>
#include "da.h"
#include "integer.h"

struct DA{
	void **array; 
	int capacity; 
	int size; 	  
	void (*display)(FILE *, void *); 
};

DA *newDA(void (*display)(FILE *,void *)){
	DA *a = malloc(sizeof(DA)); 
	a->array = malloc(sizeof(void *)*1);
	a->capacity = 1;
	a->size = 0;
	a->display = display;

	return a;
}

void insertDA(DA *a,void *v){
	if(a->size == a->capacity) 
	{
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	a->array[a->size++] = v;
}

void *removeDA(DA *a){
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

void *getDA(DA *a,int index){
	return a->array[index];
}

void setDA(DA *a,int index,void *value){
	if(index == a->size) {
		return insertDA(a, value);
	}

	a->array[index] = value;
}

int sizeDA(DA *a){
	return a->size;
}

void displayDA(FILE *fp,DA *a){

	int index = 0;
	fprintf(fp,"[");
	while(a->size - index > 0){
		a->display(fp,a->array[index]);
		if(index + 1 < a->size) {
			fprintf(fp, ",");
		}

		index++;
	}
	fprintf(fp, "]");

	fprintf(fp, "[%d]", a->capacity - a->size);
}