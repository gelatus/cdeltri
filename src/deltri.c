/* $Log$ */

#include <stdlib.h>
#include "deltri.h"
#include "delaun.h"
#include "bsort.h"
#include "misc.h"
#include "nrutil.h"

void deltri(int npts, int n, float x[], float y[], 
            int list[], int *verts[], int *adj[], 
            int *pnumtri)
{
    float xmin, xmax, ymin, ymax, dmax, fact;
    int   i, p;
   
    // Allocate workspace (for bin sort and stack)
    // Note add 1 slot since algorithms assume 
    // array is indexed [1,npts]
   
    ivector_t bin = ivector(1,npts);
   
    // Compute min and max coords for x and y
    // Compute maximum overall span
   
    p = list[1];
    xmin = x[p];
    xmax = xmin;
    ymin = y[p];
    ymax = ymin;
    for(i=2; i<=n; i++) {
        p = list[i];
        xmin = MIN(xmin,x[p]);
        xmax = MAX(xmax,x[p]);
        ymin = MIN(ymin,y[p]);
        ymax = MAX(ymax,y[p]);
    }
    dmax = MAX(xmax-xmin, ymax-ymin);
   
    // Normalize x and y coordinates of points so that they lie in 
    // the unit square
   
    fact = 1.0/dmax;
    for(i=1; i<=n; i++) {
        p = list[i];
        x[p] = (x[p]-xmin)*fact;
        y[p] = (y[p]-ymin)*fact;
    }
   
    // Bin-sort the points (performance optimization)
   
    bsort(n,x,y,xmin,xmax,ymin,ymax,dmax,bin,list);
   
    // Compute delaunay triangulation

    delaun(npts, n, x, y, list, bin, verts, adj, pnumtri);
   
    // Reset x and y coords to their original values
   
    for(i=1; i<=n; i++) {
        p = list[i];
        x[p] = x[p]*dmax + xmin;
        y[p] = y[p]*dmax + ymin;
    }

    free_ivector(bin,1,npts);
}
