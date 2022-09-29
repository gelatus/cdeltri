#ifndef _H_TRILOC
#define _H_TRILOC

///////////////////////////////////////////////////////////////////////
// PURPOSE:
// --------
// Locate triangle which encloses point with coords (xp,yp) using 
// Lawson's search.
// 
// ARGUMENTS:
// ----------
// (xp,yp)  -> X-Y coordinates of point
// 
//  x       -> float array of length npts+3 containing x coordinates of all 
//            points in the data set. The last 3 locations are used to 
//            store the x coordinates of the supertriangle vertices
//
//  y       -> float array of length npts+3 containing y coordinates of 
//            points in the data set. The last 3 locations are used to 
//            store the y coordinates of the supertriangle vertices
//
// verts    -> vertex array for triangulation, vertices for each triangle
//            are stored in counterclockwise sequence
//
// adj      -> adjacency array for triangulation
//
// t0       -> index of triangle at which search starts
//
// RETURNS:
// --------
// Function returns index of triangle containing point (xp,yp) 
// or zero if point is outside the convex hull
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
// 19 May 1995  Mario Garcia
//    - Return 0 if point outside convex hull
//
///////////////////////////////////////////////////////////////////////
int triloc(float xp, float yp, float *x, float *y, 
	   int **verts, int **adj, int t0);

#endif