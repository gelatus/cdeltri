#ifndef _H_EDG
#define _H_EDG

/////////////////////////////////////////////////////////////////////////
// PURPOSE:
// --------
// Find edge in triangle 'l' which is adjacent to triangle 'k'
//
// ARGUMENTS:
// ----------
//  l    -> number of triangle
//
//  k    -> number of adjacent triangle
//
//  adj  -> Adjacency array for triangulation
//          Triangles adjacent to i are found in adj[i][j] for
//          j=1,2,3
//          Adjacent triangles listed in anticlockwise sequence
//          Zero denotes no adjacent triangle
//          adj has dimensions adj[2*n+1][3] where n is the number
//          of points to be triangulated
//
// RETURNS:
// -------
// Function returns number of edge in triangle 'l' which is adjacent
// to triangle k.
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

int edg(int l, int k, int *adj[]);

#endif