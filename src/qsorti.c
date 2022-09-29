/* $Log$ */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "qsorti.h"
#include "nrutil.h"

// Here M is the size of subarrays sorted by straight insertion
// (See Chapter 8 Numerical Recipes)

#define M   7
#define SWAP(a,b) temp=(a); (a)=(b); (b)=temp;


void qsorti(int n, int list[], int key[])
{
    unsigned int i, ir = n, j, k, l=1;
    int jstack = 0, a, b, temp;
   
    int nstack = (int)(2.5*log(n));
    ivector_t istack = ivector(1,nstack); // size+1 to allow index [1,nstack]
   
    for(;;) {
      
        // Use insertion sort when keyay is small enough
      
        if(ir-l < M) {
            for(j=l+1; j<=ir; j++) {
                a = key[j];
                b = list[j];
                for(i=j-1; i>=1; i--) {
                    if(key[i] <= a) break;
                    key[i+1] = key[i];
                    list[i+1] = list[i];
                }
                key[i+1] = a;
                list[i+1] = b;
            }
            if(jstack == 0) break;
      
            // Pop stack and begin a new round of partitioning
      
            ir = istack[jstack];
            l = istack[jstack-1];
            jstack -= 2;
      
        } else {	 
            // Chose median of left, center and right elements as
            // partitioning element a. Also rekeyange so that
            // a(l+1) <= a[l] <= a(ir)
	 
            k = (l+ir) >> 1;
            SWAP(key[k],key[l+1]);
            SWAP(list[k],list[l+1]);
 
            if(key[l+1] > key[ir]) {
                SWAP(key[l+1],key[ir]);
                SWAP(list[l+1],list[ir]);
            }
        
	        if(key[l] > key[ir]) {
				SWAP(key[l],key[ir]);
				SWAP(list[l],list[ir]);
	        }
        
			if(key[l+1] > key[l]) {
			    SWAP(key[l+1],key[l]);
			    SWAP(list[l+1],list[l]);
			}
	 
			// Initialize pointers for partitioning

		    i = l+1;
		    j = ir;
	 
		    a = key[l];     // Partitioning element
		    b = list[l];
	 
		    // Innermost loop
	 
			for(;;) {
				// Scan up to find element > a
	    
				do i++; while(key[i] < a);
	    
				// Scan down to find element < a
	    
				do j--; while(key[j] > a);

				// Pointers crossed, partitioning complete
	    
				if(j < i) break;
	    
				// Exchange elements of both keyays
	    
				SWAP(key[i],key[j]);
			    SWAP(list[i],list[j]);
			}
	    
			// Insert partitioning element in both keyays
				    
			key[l] = key[j];
			key[j] = a;
			list[l] = list[j];
			list[j] = b;
			jstack += 2;
				 
			// Push pointers to larger subkeyay on stack
			// Process smaller subkeyay immediately
				 
			if(jstack > nstack) {
			    fprintf(stderr,"NSTACK to small in qsorti\n");
				free_ivector(istack,1,nstack);
			    exit(1);
			}
	 
		    if(ir-i+1 > j-l) {
		        istack[jstack] = ir;
		        istack[jstack-1] = i;
		        ir = j-1;
		    } else {
		        istack[jstack] = j-1;
		        istack[jstack-1] = l;
		        l = i;
		    }
		}
	}

	free_ivector(istack,1,nstack);
}
