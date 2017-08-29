#include <stdlib.h>
#include <stdio.h>
#include "cda.h"
#include "queue.h"

//fifo
queue *newQueue(void (*d)(FILE *,void *)){
  queue *q = malloc(sizeof(queue));
  q->list = newCDA(d);
  return q;
}

void enqueue(queue *items,void *value){
  insertCDAfront(items->list,value);
}

void *dequeue(queue *items){
  void *r = removeCDAfront(items->list);
  return r;
}

void *peekQueue(queue *items){
  return items->list->head->value;
}

int sizeQueue(queue *items){
  return items->list->size;
}

void displayQueue(FILE *fp,queue *items){
  /*CDA *temp = items->list->head;
  fprintf(fp, "[" );
  while(temp != NULL){
    items->list->display(fp,temp->value);
    if(temp->next != NULL){fprintf(fp,",");}
    temp = temp->next;
  }
  fprintf(fp, "]");*/
}
