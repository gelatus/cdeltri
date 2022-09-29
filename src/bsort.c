/* $Log$ */

#include <math.h>
#include "bsort.h"
#include "qsorti.h"

void bsort(int n, float x[], float y[], 
             float xmin, float xmax, float ymin, float ymax, float dmax, 
             int bin[], int list[])
{
    int   i, j, k, p, ndiv;
    float factx, facty;
   
    // Compute number of bins in X and Y directions
    // Compute inverse of bin size in X and Y directions
   
    ndiv = (int)(pow(n,0.25));
    factx = (ndiv)/((xmax-xmin)*1.01/dmax);
    facty = (ndiv)/((ymax-ymin)*1.01/dmax);
   
    // Assign bin numbers to each point
   
    for(k=1; k<=n; k++) {
        p = list[k];
        i = (int)(y[p]*facty);
        j = (int)(x[p]*factx);
        if( i % 2 == 0)
	        bin[p] = i*ndiv+j+1;
        else
	        bin[p] = (i+1)*ndiv-j;
    }
   
    // Sort points in ascending sequence of bin numbers

    qsorti(n,list,bin);
}
