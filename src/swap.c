/* $Log$ */

#include "swap.h"

int swap(float x1, float y1, 
         float x2, float y2, 
         float x3, float y3,
         float xp, float yp)
{
    float x13, y13, x23, y23, x1p, y1p, x2p, y2p, cosa, cosb, sina, sinb;
   
    x13 = x1-x3;
    y13 = y1-y3;
    x23 = x2-x3;
    y23 = y2-y3;
    x1p = x1-xp;
    y1p = y1-yp;
    x2p = x2-xp;
    y2p = y2-yp;

    cosa = x13*x23 + y13*y23;
    cosb = x2p*x1p + y1p*y2p;
   
    if ((cosa >= 0.0) && (cosb >= 0.0)) {
        return 0;
    } else if ((cosa < 0.0) && (cosb < 0.0)) {
        return 1;
    } else {
        sina = x13*y23 - x23*y13;
        sinb = x2p*y1p - x1p*y2p;
        if ((sina*cosb + sinb*cosa) < 0.0)
	        return 1;
        else
	        return 0;
    }
}
