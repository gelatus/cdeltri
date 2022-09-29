/* $Log$ */

#ifndef _H_DELTRI
#define _H_DELTRI

///////////////////////////////////////////////////////////////////////
// PURPOSE:
// --------
// Assemble Delaunay Triangulation for collection of points in the plane
//
// ARGUMENTS:
// ----------
// npts     -> Total number of points in data set.
//
//  n       -> Number of points to be triangulated <= npts.
// 
//  x       -> Vector of length npts+3 containing x coordinates of all 
//             points in the data set. The last 3 locations are used to 
//             store the x coordinates of the control points.
//
//  y       -> Vector of length npts+3 containing y coordinates of 
//             points in the data set. The last 3 locations are used to 
//             store the y coordinates of the control points.
//  
// list     -> Vector of length n containing indices of points in 
//             data set to be triangulated.
//
// verts    <- Vertex array for triangulation, vertices for each triangle.
//             are stored in counterclockwise sequence.
//             Vertices for i'th triangle j are found in verts(i,j)
//             for j=1,2,3 and i=1,2,...,numtri.
//
// adj      <- Adjacency array for triangulation
//             Triangles adjacent to to i are found in adj(i,j)
//             for j=1,2,3 and i=1,2,...,numtri.
//
// pnumtri  <- Number of triangles in final triangulation. ( numtri < 2*n+1 )
//
// SUBROUTINES CALLED:
// -------------------
// bsort, delaun
//
// SOURCE:
// -------
// S.W. Sloan (1987), A fast algorithm for constructing Delaunay
// triangulations in the plane, Adv. Eng. Software, 0, pp. 34-55
//
// LAST MODIFIED:
// --------------
// 18 May 1995	Mario Garcia
//    - FORTRAN to C translation
//
///////////////////////////////////////////////////////////////////////
void deltri(int npts, int n, float x[], float y[], 
	    int list[], int *verts[], int *adj[], 
	    int *pnumtri);

#endif
