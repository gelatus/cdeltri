#ifndef _H_SWAP
#define _H_SWAP
///////////////////////////////////////////////////////////////////////
// PURPOSE:
// --------
// Check if point with coords (xp,yp) lies inside the circumcircle for
// the triangle with coords (x1,y1),(x2,y2),(x3,y3) using the algorithm
// or Cline and Renka which allows for roundoff errors
//
// ARGUMENTS:
// ----------
// (x1,y1)  - coords of vertices defining triangle
// (x2,y2)  - vertices listed in anticlockwise sequence and ordered
// (x3,y3)    such that p-v2-v3-v1 define a quadrilateral
//
// (xp,yp)  - coords of point to be tested
//
// RETURNS:
// -------
// Function returns 1 (true) if point lies inside circumcircle
// or 0 (false) otherwise.
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
int swap(float x1, float y1, 
	 float x2, float y2, 
	 float x3, float y3,
	 float xp, float yp);

#endif