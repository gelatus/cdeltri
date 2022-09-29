#ifndef _H_DELAUN
#define _H_DELAUN

///////////////////////////////////////////////////////////////////////
// PURPOSE:
// --------
// Assemble Delaunay Triangulation
//
// ARGUMENTS:
// ----------
// numpts  -> Total number of points in data set.
//
//   x     -> Vector of length numpts+3 containing X coords of all 
//            points in data set.If point is in 'list', coordinate must 
//            be normalized such that x=(x-xmin)/dmax.
//
//   y     -> Vector of length numpts+3 containing Y coords of all
//            points in data set. If point is in 'list', coordinate must
//            be normalized such that y=(y-ymin)/dmax.
//
// list    -> Integer vector of length n containing the indices of the 
//            points to be triangulated.
//            Points are ordered such that consecutive points are close
//            to one another in the X-Y plane.
//
// verts   <- Vertex array for triangulation.
//            Vertices listed in anticlockwise sequence.
//            Vertices for triangle i are found in verts(i,j) for
//            j=1,2,3 and i=1,2,...,numtri.
//            First vertex is at point of contact of first and third
//            adjacent triangles.
//
// adj     <- Adjacency array for triangulation.
//            Triangles adjacent to i are found in adj(i,j) for
//            j=1,2,3 and i=1,2,...,numtri.
//            Adjacent triangles listed in anticlockwise sequence.
//            0 denotes no adjacent triangle.
//
// pnumtri  <- Number of triangles in final triangulation. ( numtri < 2*n+1 )
//     
// ASSUMPTIONS:
// ------------
// This subroutine assumes that the X and Y coordinates have been normalized so that
// they lie in the unit square. Note: 'deltri' does this. If you call this function
// directly you should do it yourself. Remember to restore the original values before
// using the output.
//
// FUNCTIONS CALLED:
// -----------------
// triloc, edg, swap
//
// CLASSES USED:
// -------------
// Stack
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
void delaun(int numpts, int n, float x[], float y[], 
	      int list[], int stack[], int *verts[], int *adj[], 
	      int *numtri);

#endif