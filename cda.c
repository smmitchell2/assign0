#include <stdio.h>
#include <stdlib.h>
#include "cda.h"

struct cda{
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

int correctIndex(CDA *a,int i){
	if(i<0){i = i + a->capacity;}
	i = (a->startIndex + a->size) % a->capacity;
	//i = (i + a->capacity) % a->capacity;
	//fprintf(stdout,"%d\n",i);
	return i;
}

//back should be (front + count - 1)%length
//after removal front (front + 1)%length
void insertCDAfront(CDA *a,void *v){ //doesnt insert correctly
	if(a->size == 0){
		insertCDAback(a,v);
		return;
	}
	if(a->size == a->capacity){
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));

	}
	a->startIndex = (a->startIndex + a->size) % a->capacity;//correctIndex(a,a->startIndex-1);
    a->array[a->startIndex] = v;
    a->size += 1;
}

void insertCDAback(CDA *a,void *v){
	if(a->size == a->capacity){
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	a->array[a->endIndex] = v;
    a->endIndex = a->endIndex+1;//correctIndex(a,a->endIndex+1);
    a->size += 1;
}

void *removeCDAfront(CDA *a){
	if(a->size == 0){
		fprintf(stderr, "Attempting to remove from an empty array\n");
		exit(-1);
	}
	//if(a->startIndex+1 == a->capacity)
	void *rv = a->array[a->startIndex];
	a->array[a->startIndex] = NULL;
	--a->size;
	a->startIndex = a->startIndex + 1;
	return rv;
	/*int front = (a->startIndex + a->size) % a->capacity;
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
	return rv;*/
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
	a->display(fp,a->array[1]);

	if(a->startIndex > a->endIndex){
		fprintf(fp,"(");
		int index = a->startIndex;
		while(index >= a->endIndex ){
			if(a->array[index] == NULL){break;}
			a->display(fp,a->array[index]);
			if(index - 1 > a->size) {
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
			if(a->array[index] == NULL){break;}
			a->display(fp,a->array[index]);
			if(index + 1 < a->size) {
				fprintf(fp, ",");
			}
			index++;
		}
		fprintf(fp, ")");
	}

}

void cdaCompleteDisplay(FILE *fp,CDA *a){
	fprintf(fp, "startIndex:%d endIndex:%d size:%d capacity:%d\n",a->startIndex,a->endIndex,a->size,a->capacity );
	int i = 0;
	while (i < a->capacity){
		if(a->array[i] == NULL){fprintf(fp,"[%d]: NULL \n",i);}
		else{
			fprintf(fp,"[%d]: ",i);
			a->display(fp,a->array[i]);
			fprintf(fp,"\n");
		}
		++i;
	}
}
