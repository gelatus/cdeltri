#ifndef _H_BSORT
#define _H_BSORT

//////////////////////////////////////////////////////////////////////
// PURPOSE:
// --------
// Sort points such that consecutive points are close to one another in
// the x-y plane using a bin sort
//
// ARGUMENTS:
// ----------
//   n   -> Total number of points to be triangulated.
//          n <= npts where npts is the total number of pts in data set
//
//   x   -> X coordinates of points to be triangulated
//
//   y   -> Y coordinates of points to be triangulated
//
// xmin  -> Min x coord of points in list
//
// xmax  -> Max x coord of points in list
//
// ymin  -> Min y coord of points in list
//
// ymax  -> Max y coord of points in list
//
// dmax  -> Maximum span: dmax = MAX(xmax-xmin,ymax-ymin)
//
// bin   <- Bin numbers for each point to be triangulated
//
// list  <- List of points to be triangulated.
//          Points ordered such that consecutive points are close to
//          one another in the x-y plane
//
// SUBROUTINES CALLED:
// -------------------
// qsorti
//
// SOURCE:
// -------
// S.W. Sloan (1987), A fast algorithm for constructing Delaunay
// triangulations in the plane, Adv. Eng. Software, 0, pp. 34-55
//
// LAST MODIFIED:
// --------------
// 18 May 1995	Mario Garcia
//    - FORTRAN to C++ translation
//
///////////////////////////////////////////////////////////////////////
void bsort(int n, float x[], float y[], 
	   float xmin, float xmax, float ymin, float ymax, float dmax, 
	   int bin[], int list[]);


#endif