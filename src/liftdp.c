/*EKDOXH 4*/
#include <stdio.h>
#include <stdlib.h>
#include "fw.h"

int solve(int nrid,int nst,int *dests){
    int j,i,k,n,m,cost=0,sum=0,nfl,min,min1,min2,cost1,cost2,cost3,p,station,temp,**M,**K,*ST;
    for (i=0;i<nrid;i++){                                  /*classificates the table dests*/
        for(j=i;j>=1;j--){
            if (dests[j-1]>dests[j]){
                temp=dests[j];
                dests[j]=dests[j-1];
                dests[j-1]=temp;
            }
        }
    } 
    nfl=dests[nrid-1];                                     /*nfl is the last element at dests[]*/
    n=nst;
    m=nfl;
	if ((M=malloc((n+1)*sizeof (int *)))==NULL){            /*makes table M[nst+1][nfl+1]*/
		return 0;
    }
	for (i=0;i<=n;i++){
		if ((M[i]=malloc((m+1)*sizeof (int)))==NULL){
			return 0;
        }
 		for (j=0;j<=m; j++){
			M[i][j] = -1;                                  /*initialize with -1*/
		}
	}
    if ((K=malloc((n+1)*sizeof (int *)))==NULL){           /*makes table K[nst+1][nfl+1]*/
		return 0;
    }
	for (i=0;i<=n;i++){
		if ((K[i]=malloc((m+1)*sizeof (int)))==NULL){
			return 0;
        }
	}
    for (i=0;i<nrid;i++){                               /*FINDS SUM OF COSTS*/
        sum+=dests[i];
    }
    for (j=0;j<=nfl;j++){                              /*MINCOST=MIN(M(nst,j))  j=0 ews nfl*/
        for (i=0;i<=nst;i++){                          /*MINCOST2=MIN(M(i,j))  i=0 ews nst*/
            if (i==0 || j==0) {                       /*if it can't make stops or the biggest stop it can reach is the ground floor then everyone will walk */
                cost2=sum;
                M[i][j]=sum;
                K[i][j]=0;
            }
            else {
                for (k=0;k<=j;k++){                   /*MINCOST3=MIN(M(i-1,k))  k=0 ews j*/
                    cost3=M[i-1][k] + fw(k,j,nrid,dests);
                    if (k==0){                         /*in first repetition put cost3 as min2*/
                        min2=cost3;
                    }
                    else {                             /*after the first repetition checks if cost3 is smaller than min2*/
                        if (cost3<min2){
                            min2=cost3;                /*if it is put cost3 as min2*/
                            p=k;                       /*p has stored k for which at stop i−1 has the minimum value for M(i,j)*/
                        }
                    } 
                    if (k==j){                        /*checks that it is the last repetition and stores min2 as cost2*/
                        cost2=min2;
                    }      
                }
                M[i][j]=min2;
                K[i][j]=p;                           /*stored for each M(i,j) the value of k for which at stop i−1 has the minimum value*/
            }
            if (i==0){                               
                min1=cost2;                          /*in first repetition put cost2 as min1*/
            }
            else {                                   /*after the first repetition checks if cost2 is smaller than min1*/
                if (cost2<min1){
                    min1=cost2;
                }
            } 
            if (i==nst){                            /*checks that it is the last repetition and stores min1 as cost*/
                cost=min1;
            }    
        }
        if (j==0){                                 /*in first repetition put cost as min and station=0(j)*/
            min=cost;
            station=0;
        }        
        else {                                    /*after the first repetition checks if cost is smaller than min*/
            if (cost<min){
                station=j;                        /*if it is smaller, put j as station(which is last station with min)*/
                min=cost;
            }
        }   
    }
    for (i=0;i<=n;i++){                           /*prints table M*/
 		for (j=0;j<=m; j++){
			printf("%3d ",M[i][j]);
		}
        printf("\n");
    }
    if (nst!=0){
        if ((ST=malloc(nst*sizeof(int)))==NULL)   /*makes a table for the stations*/
            return 0;
        for (i=0;i<nst;i++){                   /*put station at table st*/
            if (i==0){                         /*at st[0] put the max station, which we found*/
                ST[i]=station;
                j=station+1;
                if (j==nfl+1)
		   j--;
            }
            else {
                ST[i]=K[nst-i+1][j];
                j=K[nst-i+1][j] +1;
            }
        }
        printf("Lift stops are:");
        for (i=nst-1;i>=0;i--){
            if (ST[i]!=0 && ST[i]!=ST[i-1])
                printf ("%3d ",ST[i]);
        }
        free (ST);
        printf("\n");
    }
    else{
        printf("No lift stops\n");
        min=sum;
    }
    for (i=0;i<=n; i++){
		free(M[i]);
                free(K[i]);
    }
    free (M);
    free(K);
    return min;
}
