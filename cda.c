#include <stdio.h>
#include <stdlib.h>
#include "cda.h"

typedef struct CDA{
	void **array;
	int capacity;
	int size;
	int startIndex;
	int endIndex;
	void (*display)(FILE *, void *);
}CDA;

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

void insertCDAfront(CDA *a,void *v){ //doesnt insert correctly
	if(a->size == 0){
		a->array[0] = v;
		++a->size;
		return;
	}
	if(a->size == a->capacity){
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
		int front = (a->startIndex + a->size) % a->capacity;
		a->array[front] = v;
		a->startIndex = front;
		++a->size;
		return;
	}
	if(a->size < a->capacity){
		a->array[a->size+1] = v;
		++a->size;
		return;
		}

}

void insertCDAback(CDA *a,void *v){
	if(a->size == a->capacity){
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	int back = a->startIndex + a->size;
	a->array[back] = v;
	a->size++;
	a->endIndex = back;
}

void *removeCDAfront(CDA *a){
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
	a->startIndex = (a->startIndex + a->size) % a->capacity;
	return rv;
}

void *removeCDAback(CDA *a){
	void *rv = a->array[a->endIndex];
	if(a->size == 0){
		fprintf(stderr, "Attempting to remove from an empty array\n");
		exit(-1);
	}

	a->array[a->endIndex] = NULL;
	--a->size;
	double size = a->size;
	double capacity = a->capacity;
	if(size < capacity/4.0 && capacity > 2){
		a->capacity /= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	a->endIndex = a->startIndex + a->size;
	return rv;
}

void unionCDA(CDA *recipient,CDA *donor){
	for(int i = 0;i<=donor->size;++i){
    	void *rm = removeCDAfront(donor);
		insertCDAback(recipient,rm);
	}
}

void *getCDA(CDA *a,int index){
	return a->array[index];
}

void *setCDA(CDA *a,int index,void *value){ //fix
	if(index == a->size) {
		insertCDAfront(a,value);
		return value;
	}

	a->array[index] = value;
	return value;
}

void **extractCDA(CDA *items){
	return items->array;
}

int sizeCDA(CDA *a){
	return a->size;
}

void visualizeCDA(FILE *fp,CDA *a){
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

void displayCDA(FILE *fp,CDA *a){

	fprintf(fp, "startIndex:%d endIndex:%d size:%d capacity:%d\n",a->startIndex,a->endIndex,a->size,a->capacity );
	//a->display(fp,a->array[1]);

	if(a->startIndex > a->endIndex){
		fprintf(fp,"(");
		int index = a->startIndex;
		while(index >= a->endIndex ){
			a->display(fp,a->array[index]);
			if(index + 1 < a->size) {
				fprintf(fp, ",");
			}
			index--;
		}
		fprintf(fp, ")");
	}
  //if(a->startIndex <= a->endIndex)
	else{
		int index = a->startIndex;
		fprintf(fp,"(");
		while(index <= a->endIndex ){
			a->display(fp,a->array[index]);
			if(index + 1 < a->size) {
				fprintf(fp, ",");
			}
			index++;
		}
		fprintf(fp, ")");
	}

}
