/* $Log$ */

#include <stdlib.h>
#include <stdio.h>
#include "delaun.h"
#include "stack.h"
#include "triloc.h"
#include "edg.h"
#include "swap.h"


void delaun(int numpts, int n, float x[], float y[], 
              int list[], int stack[], int *verts[], int *adj[], 
              int *pnumtri)
{
    float  xp, yp;
    int    i, p, v1, v2, v3, l, r, a, b, c, t, tstrt, tstop, era,erb, erl;
    int    numtri, maxstk, topstk;
   
    // Define vertex and adjacency list for supertriangle
   
    v1 = numpts + 1;
    v2 = numpts + 2;
    v3 = numpts + 3;
    verts[1][1] = v1;
    verts[1][2] = v2;
    verts[1][3] = v3;
    adj[1][1] = 0;
    adj[1][2] = 0;
    adj[1][3] = 0;
   
    // Set coords of supertriangle
   
    x[v1] = -100.0;
    x[v2] =  100.0;
    x[v3] =  0.0;
    y[v1] = -100.0;
    y[v2] = -100.0;
    y[v3] =  100.0;
   
    // Loop over each point
   
    numtri = 1;
    topstk = 0;
    maxstk = numpts;
    for(i=1; i<=n; i++) {
        p  = list[i];
        xp = x[p];
        yp = y[p];
      
        // Locate triangle containing point
      
        t = triloc(xp, yp, x, y, verts, adj, numtri);
      
        // Create new vertex and adjacency lists for triangle t
      
        a = adj[t][1];
        b = adj[t][2];
        c = adj[t][3];
        v1 = verts[t][1];
        v2 = verts[t][2];
        v3 = verts[t][3];
        verts[t][1] = p;
        verts[t][2] = v1;
        verts[t][3] = v2;
        adj[t][1] = numtri+2;
        adj[t][2] = a;
        adj[t][3] = numtri+1;
      
        // Create new triangles
      
        numtri++;
        verts[numtri][1] = p;
        verts[numtri][2] = v2;
        verts[numtri][3] = v3;
        adj[numtri][1] = t;
        adj[numtri][2] = b;
        adj[numtri][3] = numtri+1;
      
        numtri++;
        verts[numtri][1] = p;
        verts[numtri][2] = v3;
        verts[numtri][3] = v1;
        adj[numtri][1] = numtri-1;
        adj[numtri][2] = c;
        adj[numtri][3] = t;
      
        // put each edge of triangle t on stack
        // store triangles on left side of each edge
        // update adjacency lists for adjacent triangles
        // adjacency list for element a does not need to be updated
      
        if ( a != 0 ) {
            push(t, maxstk, &topstk, stack);
        }
        if ( b != 0 ) {
            adj[b][edg(b,t,adj)] = numtri-1;
            push(numtri-1, maxstk, &topstk, stack);
        }
        if ( c != 0 ) {
            adj[c][edg(c,t,adj)] = numtri;
            push(numtri, maxstk, &topstk, stack);
        }
      
        // Loop while stack is not empty
      
        while ( topstk > 0 ) {
            l = pop(&topstk, stack);
            r = adj[l][2];
	 
            // Check if new point is in circumcircle for triangle r
	 
            erl = edg(r,l,adj);
            era = (erl % 3) + 1;
	        erb = (era % 3) + 1;
	        v1 = verts[r][erl];
	        v2 = verts[r][era];
	        v3 = verts[r][erb];
	 
            if ( swap(x[v1],y[v1],x[v2],y[v2],x[v3],y[v3],xp,yp) ) {
	    
	            // New point is inside circumcircle for triangle r
	            // Swap diagonal for convex quad. formed by p-v2-v3-v1
	    
	            a = adj[r][era];
	            b = adj[r][erb];
	            c = adj[l][3];
	    
	            // Update vertex and adjacency list for triangle l
	    
	            verts[l][3] = v3;
	            adj[l][2] = a;
	            adj[l][3] = r;
	    
	            // Update vertex and adjacency list for triangle r
	    
	            verts[r][1] = p;
	            verts[r][2] = v3;
	            verts[r][3] = v1;
	            adj[r][1] = l;
	            adj[r][2] = b;
	            adj[r][3] = c;
	    
	            // Put edges l-a and r-b on stack
	            // Update adjacency lists for triangles a and c
	    
	            if ( a != 0 ) {
	                adj[a][edg(a,r,adj)] = l;
	                push(l, maxstk, &topstk, stack);
	            }
	            if ( b != 0 ) {
	                push(r, maxstk, &topstk, stack);
	            }
	            if ( c != 0 ) {
	                adj[c][edg(c,l,adj)] = r;
                }

            }

        } /* while (!stack.isEmpty()) */

   }  /* for(i=1; i<=n; i++) */
   
    // Check consistency of triangulation
	    
    if(numtri != 2*n+1) {
        fprintf(stderr, "*** Error in subroutine delaun    ***\n");
        fprintf(stderr, "*** Incorrect # of triangles formed ***\n");
        exit(1);
    }
   
    // Remove all triangles containing supertriangle vertices
    // Find first triangle to be deleted (triangle t)
    // Update adjacency lists for triangles adjacent to t
   
    for(t=1; t<=numtri; t++) {
        if((verts[t][1] > numpts) || (verts[t][2] > numpts) || (verts[t][3] > numpts)) 
        {
            for(i=1; i<=3; i++) {
                a = adj[t][i];
                if( a != 0 ) adj[a][edg(a,t,adj)] = 0;
            }
            break;
        }
    }
   
    tstrt  = t+1;
    tstop  = numtri;
    numtri = t-1;

    // Remove triangles
   
    for(t=tstrt; t<=tstop; t++) {
        if((verts[t][1] > numpts) ||
           (verts[t][2] > numpts) ||
	       (verts[t][3] > numpts)) 
        {
            // Triangle t is to be deleted
            // Update adjacency lists for triangles adjacent to t
	 
            for(i=1; i<=3; i++) {
                a = adj[t][i];
                if( a != 0 )  adj[a][edg(a,t,adj)] = 0;
            }

        } else {
            // Triangle t is not to be deleted
            // Put triangle t in place of triangle numtri-1
            // Update adjacency lists for triangles adjacent to t
	 
            numtri++;
            for(i=1; i<=3; i++) {
                a = adj[t][i];
                adj[numtri][i] = a;
                verts[numtri][i] = verts[t][i];
                if( a != 0) adj[a][edg(a,t,adj)] = numtri;
            }
        }
    }

    // Copy value of numtri for output
    *pnumtri = numtri;
}
