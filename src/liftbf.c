/*EKDOXH 2*/
#include <stdio.h>
#include <stdlib.h>

int STATIONS (int nfl,int nst,int n,int *ST){       /*when it returns 0=continue the combinations ,1=increase pointer(n), 2= end (has checked all the combination)*/
    int temp,k;
    temp=n;                       /*temp=temporary pointer */
    if (ST[n]!=nfl){             /*checks if where n shows, ST[n] is smaller than nfl px  {1,2,3,0,0} n=2 checks if 3=nfl */
        ST[n]++;                 /*if it isn't increase it */
        return 0;                /*it means that combinations will cotinue*/
    }
    else {                      /*if ST[n]= nfl*/
        temp=temp-1;            /*temp pointer reduses*/
        if (temp==-1){          /*if we have only one station in combination px {1,0,0},{4,0,0}*/
                if (nst>1 && nfl>1){          /*if it can do more than onestation and the higher station is >1*/
                    ST[0]=1;                  
                    ST[1]=2;
                    return 1;                 /*it means increase poiner n because from {5,0,0} -> {1,2,0}*/
                }
                else{ 
                    return 2;                  /*else all the combinations have been checked*/
                }
        }
        while (1){
            if (ST[temp]==nfl-(n-temp)){            /*checks that st[i] i=n-0 if it happens something like this {1,4,5,0}  */
                if (temp==0){                       /*if it's at the begining og ST*/
                    if (n==nst-1){                  /*px if nfl=9 kai ST={5,6,7,8,9,} we have checked all the combinations*/
                        return 2;                   /*2 means that we have checked all the combinations */
                    }
                    else                            /*px if  nfl=9 kai ST={7,8,9,0,0} => ST={1,2,3,4,0}*/
                        ST[0]=1;                    /*begins {1,2,3,4...} until ST[n+1]*/
                        k=2;
                        temp=1 ;
                        while (temp!=n+2){
                            ST[temp]= k;
                            k++;
                            temp++;
                        }
                        return 1;        /*it means increase pointer n */
                }
            }
            else {                      /*if it is like ithis {1,2,4,5,0}-> {1,3,4,5,0} */
                k=++(ST[temp]);
                while (temp!=n+1){
                        ST[temp]= k;
                        k++;
                        temp++;
                }
                return 0;             /*it means continue with combinations */             
            } 
            temp--;
        }
    }
}


int solve(int nrid,int nst,int *dests){
 int j,i,n,k,cost,sum=0,nfl,min,temp,*ST,*MINST,end,pl;
  for (i=0;i<nrid;i++){                                   /*classificates the table dests*/
        for(j=i;j>=1;j--){
            if (dests[j-1]>dests[j]){
                temp=dests[j];
                dests[j]=dests[j-1];
                dests[j-1]=temp;
            }
        }
    } 
    nfl=dests[nrid-1];                         /*highest station is the last element of dests*/
    sum=0;           
    for (i=0;i<nrid;i++){                      /*finds sum of dests and put it as min so it can return with <return min>*/
        sum+=dests[i];
    }
    if (nst==0){
        printf("No lift stops\n");
        return sum;   
    }
    if ((MINST=malloc(nst*sizeof (int)))==NULL){    /*table minst has the station with mincost*/
		return 0;
    }
    if ((ST=malloc(nst*sizeof (int)))==NULL){      /*table st will have the combination of all station*/
		return 0;
    }
    for (i=0;i<nst;i++){                         /*initialize with 0 table ST and MINST*/
        ST[i]=0;
        MINST[i]=0;
    }
    pl=0;                                       /*like a logic variable so we can know if has happened a repetion in while*/
    n=0;                                        /*pointer at table ST */
    end=0;                                      /*its value will indicate if we need to increment the pointer n or if we will continue repetitios or if we checked all the station coordinates*/
    while (end==0 || end==1){                   /*while we don't have check all the station coordinates. (STATION retun 2)  */
        end=STATIONS(nfl,nst,n,ST);              /*the next combination of stations is calculated*/
        if (end==1){                            /*if end=1 we have to increase pointer n*/
            n=n+1;
        }
        cost=0;                                /*finds cost*/
        for (j=0;j<nrid;j++){                  /*for each passenger*/
            for (i=0;i<=n;i++){                /*checks which station is closer to his destination*/
                if (dests[j]==ST[i]){          /*if is the same, cost doesn't change*/
                    break;
                }
                else if (dests[j]>ST[i]){          
                if (i<n){                            /*if we aren't at the end of ST*/
                    if (dests[j]<ST[i+1]){          /*if it is smaller than the next station ST[i+]elegxei checks which station has smaller cost*/
                        if (dests[j]-ST[i]<ST[i+1]-dests[j])   /*if cost next is bigger than previous*/        
                            cost=cost + dests[j]-ST[i];        /*adds cost of preious */
                        else 
                            cost=cost+ ST[i+1]-dests[j];       /*else adds cost of next*/
                    }
                    else if (dests[j]==ST[i+1]){       /* if is the same, cost doesn't change and stops the repetition for ST*/
                            break;
                    }
                    else {                             /*if it continues to be smaller it will be checked at the next i*/
                        continue;
                    }
                }
                else {                               /*if we are at the end of ST, then there aren't bigger station and cost is the different from dests[j] and the last station ST[n]*/
                    cost=cost+dests[j]-ST[i];
                }
                }
                else if (dests[j]<ST[i]){                   /*if ST[i] is bigger than dests[j]*/
                    if (i==0){                              /*if i=0 we are at the beggining of ST then checks that which cost is smaller*/
                        if (dests[j]<ST[i]-dests[j])        /*if station of dests[j] is more close at the ground floor*/
                            cost=cost+dests[j];
                        else                                /*if station of dests[j] is more close at the first station*/
                            cost=cost+ST[i]-dests[j];
                    }                                       /*if i!=0 then it will be checked at the previous repetition so we only need to check i=0*/
                }
            }
        }
        if  (pl==0){                                  /*if we are at the first repetition of while*/
            min=cost;                                /*put cost as min*/
            pl=1;                                    /*change pl so we can know that happened the first repetition*/
            for (i=0;i<nst;i++){                     /*put ST at MINST*/
                MINST[i]=ST[i];
            }
        }
        else{
            if (cost<min){                       /*checks that cost is smaller than min*/
                min=cost;                         /*if it is put cost as min and minst=st*/
                for (i=0;i<=n;i++){
                    MINST[i]=ST[i];
                }
            }
        }
    }
    if (sum<cost){                            /*if cost is smaller than min,then it doesn't have to make station and cost is the sum */
        printf("No lift stops");
        free (MINST);
	free (ST);
        return sum;
    }
    printf("Lift stops are:");
    for (i=0;i<nst;i++){                   /*prints station from the beggining to the end of MINST*/
        printf("%3d ",MINST[i]);
        if (i!=nst-1){                     /*if we aren't at the end of MINST*/
            if (MINST[i+1]==0)             /*if the next is 0, then all the station are printed*/
                break;
        }
    }   
    printf("\n");
    free (MINST);
    free (ST);
    return min;
}
