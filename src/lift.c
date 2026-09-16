#include <stdio.h>
#include <stdlib.h>
#include "solve.h"

int main (void){
    int nrid, nst, i, min, temp,*dests;
    scanf("%d",&nrid);                 /*reads passengers' number*/
    scanf("%d",&nst);                  /*reads stations' number*/
    if (nrid<=0 || nst<0){             /*checks nrid and nst */
        printf ("input error");
        return 1;
    }
    dests= malloc(nrid*sizeof(int)) ;  /*I create the table in which I will store where each passenger wants to go */ 
    if (dests==NULL)                   /*if the memory allocation was done correctly*/
        return 1;
    for (i=0;i<nrid;i++){              /*reads and saves where each passenger wants to go*/
        scanf("%d",dests+i);
    }
    min=solve(nrid,nst,dests);        /*calls solve */
    printf("Cost is: %d\n",min);      /*prints min_cost*/
    free(dests);                      
    return 0;
}
