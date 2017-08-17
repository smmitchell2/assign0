#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "da.h"
#include "cda.h"
//#include "real.h"


int main(int argc,char **argv){
    DA *a = newDA(displayInteger);
    DA *b = newDA(displayInteger);
    CDA *c = newCDA(displayInteger);
    int i;
    void *v = NULL;
    //repeated 10000 times: insertDLL(a,0,v);
    for(i = 0; i <= 10; ++i){
        v = newInteger(i);
        insertDA(a,v);
    }
    //repeated 10000 times: insertDLL(a,sizeDLL(a),v);
    for(i = 11; i <= 20; ++i){
        v = newInteger(i);
        insertDA(b,v);
    }
    //repeated 10000 times: insertDLL(a,X,v);
    /*for(i = 0; i < 10; ++i){
        //int X = rand() %9999;
        v = newInteger(i);
        //insertDLL(a,X,v);
        insertCDAfront(c,v);
    }*/
    v = newInteger(4);
    void *u = newInteger(5);
    void *y = newInteger(6);
    insertCDAfront(c,v);
    insertCDAfront(c,u);
    insertCDAfront(c,y);

    displayDA(stdout,a);
    displayDA(stdout,b);
    unionDA(a,b);

    fprintf(stdout,"\n");
    displayDA(stdout,a);
    displayDA(stdout,b);
   // fprintf(stdout,"the size is %d\n",a->size);
   fprintf(stdout,"\n");
   displayCDA(stdout,c);

}
