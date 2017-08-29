#include <stdio.h>
#include <stdlib.h>
#include "da.h"


struct da{
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
	if(a->size == a->capacity){
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

void unionDA(DA *recipient, DA *donor){
    if(recipient->size == 0 && donor->size == 0){return;}
    else if(recipient->size == 0 && donor->size != 0){
        recipient = donor;
        donor->size = 0;
        donor = NULL;
    }
    else if(recipient->size != 0 && donor->size == 0){return;}
    else{
        int i = 0;
        while(i < donor->size){
            insertDA(recipient,donor->array[i]);
            ++i;
        }
        i = 0;
        donor->array = NULL;
		donor->capacity = 1;
		donor->size = 0;
        /*while(i < donor->size){
            void *pointless = NULL;
            pointless = removeDA(donor);
            ++i;
        }*/
    }
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

void **extractDA(DA *items){
	return items->array;
}

int sizeDA(DA *a){
	return a->size;
}

void visualizeDA(FILE *fp,DA *a){
	if(a->array == NULL){
			fprintf(fp,"[]");
	fprintf(fp, "[%d]", a->capacity - a->size);
			return;
	}
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

void displayDA(FILE *fp,DA *a){
    if(a->array == NULL){
        fprintf(fp,"[]");
		//fprintf(fp, "[%d]", a->capacity - a->size);
        return;
    }
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
	//fprintf(fp, "[%d]", a->capacity - a->size);
}
