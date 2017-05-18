#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "da.h"
//#include "real.h"


int main(int argc,char **argv){
    DA *a = newDA(displayInteger);
    DA *b = newDA(displayInteger);
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
    /*for(i = 0; i < 10000; ++i){
        int X = rand() %9999;
        v = newInteger(i);
        insertDLL(a,X,v);
    }*/
    
    displayDA(stdout,a);
    displayDA(stdout,b);
    unionDA(a,b);
    
    fprintf(stdout,"\n");
    displayDA(stdout,a);
    displayDA(stdout,b);
   // fprintf(stdout,"the size is %d\n",a->size);
}

