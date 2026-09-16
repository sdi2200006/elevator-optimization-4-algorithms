int fw(int k, int j,int nrid, int *dests){              /*calculates − fw(k, ∞) + fw(k, j) + fw(j, ∞)  */
    int i,sum=0 ;                                       /*i for accessing the table*/                 
    for(i=0;i<nrid;i++){
        if (dests[i]>k)                                 /*-fw(k, ∞)*/
            sum-=dests[i]-k;
        if (dests[i]<=j && dests[i]>k){                 /*+ fw(k, j)*/
            if (dests[i]-k>j-dests[i])
                sum+=j-dests[i];                     /*adds up minimum*/
            else 
                sum+=dests[i]-k;
        }
        if (dests[i]>j)                                 /* +fw(j, ∞)*/
            sum+=dests[i] - j ;
    }
    return sum;
}
