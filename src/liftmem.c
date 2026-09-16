/*EKDOXH 3*/
#include <stdio.h>
#include <stdlib.h>
#include "fw.h"

int solve2(int nrid,int nst,int j,int *dests,int **M){
    int cost,k,min,sum,i;
    if (M[nst][j]==-1){               /*chcks that m[i][j] is not calculate from previous one repetitions*/
        if (nst==0 || j==0){          /*if it can't make stops or the biggest stop it can reach is the ground floor then everyone will walk */
            sum=0;                    /*finds the sum of cost*/
            for (i=0;i<nrid;i++){
                sum+=dests[i];
            }
            min=sum;                   /*put it as min*/
            M[nst][j]=sum;             /*put it at M[nst]][j] for the other repetitions*/
        }
        else {
            for (k=0;k<=j;k++){              
                cost=solve2(nrid,nst-1,k,dests,M)+fw( k,j,nrid,dests);
                if (k==0){                 /*at first repetion put cost as min*/
                    min=cost;
                }
                else { 
                    if (cost<min){         /*checks after the first repetition if cost is smaller than min*/
                        min=cost;          /*if it is, put it as min*/
                    }
                }       
            }
            M[nst][j]=min;                 /*put at M[nst][j]*/
        }        
        return min;                 
    }
    else {
        return M[nst][j];                  /*if m[i][j] is calculate from previous one repetitions returns it*/
    }
}


int solve(int nrid,int nst,int *dests){
    int j,i,n,m,cost=0,nfl,min,station,temp,**M;
    for (i=0;i<nrid;i++){                          /*classificates the table dests*/
        for(j=i;j>=1;j--){
            if (dests[j-1]>dests[j]){
                temp=dests[j];
                dests[j]=dests[j-1];
                dests[j-1]=temp;
            }
        }
    } 
    nfl=dests[nrid-1];                             /*highest station is the last element of dests*/
    n=nst;
    m=nfl;
	if ((M=malloc((n+1)*sizeof (int *)))==NULL){   /*makes table M[nst+1][nfl+1]*/
		return 0;
    }
	for (i=0;i<=n;i++){
		if ((M[i]=malloc((m+1)*sizeof (int)))==NULL){
			return 0;
        }
 		for (j=0;j<=m; j++){
			M[i][j] = -1;                             /*initialize with -1*/
		}
	}                                        
    for (j=0;j<=nfl;j++){
        cost= solve2(nrid,nst,j,dests,M); 
        if (j==0){                                    /*in first repetition put cost as min*/
            min=cost;
            station=0;
        }        
        else {                                       /*after the first repetition check if the cost which came back from solve2 is smaller than min*/
            if (cost<min){
                station=j;                            /*if it is smaller, put j as station(last station with min) and cost as min*/
                min=cost;
            }
        }
    }
    if (nst!=0){                                       /*if station>0 prints the last station with the minimum cost*/
        printf("Last stop at floor: %d\n",station);
    }
    else{
        printf("No lift stops\n");
    }
    for (i=0;i<=n; i++){
	free(M[i]);
    }
    free (M);
    return min;
}
