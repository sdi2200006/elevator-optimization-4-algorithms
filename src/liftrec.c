/*EKDOXH 1*/
#include <stdio.h>
#include <stdlib.h>
#include "fw.h"

int solve2(int nrid,int nst,int j,int *dests){
    int cost,k,min,i,sum;
    if (nst==0){                                    /*if nst=0 cost=sum*/
        sum=0;
        for (i=0;i<nrid;i++){                      /*finds sum of dests and put it as min so it can return with <return min>*/
            sum+=dests[i];
        }
        min=sum;
    }
    else {
        for (k=0;k<=j;k++){        
            cost=solve2(nrid,nst-1,k,dests)+fw( k,j,nrid,dests);   /*calls herself*/
            if (k==0){                                             /*at first repetition put cost as min*/
                min=cost;
            }
            else {
                if (cost<min){                   /*checks after the firts repetition if min>cost which returned*/
                    min=cost;                    /*if it is saves it as min*/
                }
            }
        }
    }
    return min;
}

int solve(int nrid,int nst,int *dests){
    int j,i,cost=0,nfl,min,station,temp;
    for (i=0;i<nrid;i++){
        for(j=i;j>=1;j--){                       /*classificates the table dests*/
            if (dests[j-1]>dests[j]){
                temp=dests[j];
                dests[j]=dests[j-1];
                dests[j-1]=temp;
            }
        }
    }
    nfl=dests[nrid-1];                            /*highest station is the last element of dests*/
    for (j=0;j<=nfl;j++){
        cost= solve2(nrid,nst,j,dests);
        if (j==0)                                  /*put as min the first cost*/
            min=cost;
        else {
            if (cost<min){                         /*checks if the min is bigger than the cost which returned at the last repetition*/
                station=j;                         /*if it is,saves j which is the last station with the minimum cost*/
                min=cost;                          /*and saves cost*/
            }
        }
    }
    if (nst!=0){                                    /*if station>0*/
        printf("Last stop at floor: %d\n",station); /*prints the last station with minimum cost*/
    }
    else{                                            /*if stations=0*/
        printf("No lift stops\n");                   /*prints that there were not stations*/
    }
    return min;                                      /*returns the minimum cost*/
}
