/* $Log$ */

#include <stdio.h>
#include <stdlib.h>
#include "edg.h"

int edg(int l, int k, int *adj[])
{
    int i;
   
    for(i=1; i<=3; i++) {
        if(adj[l][i] == k)
        return i;
    }
   
    fprintf(stderr, "*** Error in function edg ***\n*** Elements not adjacent ***\n");
    exit(1);
   
    return -1;  // just to make the compiler happy
}
