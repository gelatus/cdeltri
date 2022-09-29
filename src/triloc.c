/* $Log$ */

#include "triloc.h"

int triloc(float xp, float yp, float x[], float  y[], 
           int *verts[], int *adj[], int t0)
{
    int v1, v2, i, t = t0, count=0;
   
    // Search until we find a triangle containing the point, or 
    // until we have gone outside the convex hull.
    // Since the triangle vertices are always listed in anticlockwise
    // sequence, a point can only be enclosed by a triangle if it is
    // to the left of each of its edges
   
    do {
        count = 0;
        for(i=1; i<=3; i++) {
            v1 = verts[t][i];
            v2 = verts[t][(i%3)+1];
            if ((y[v1]-yp)*(x[v2]-xp) > (x[v1]-xp)*(y[v2]-yp)) {
                t = adj[t][i];
                break;
            }
            count++;
        }
    } while(count<3 && t != 0);
	    
    return t;
}
