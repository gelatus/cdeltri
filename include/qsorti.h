#ifndef _H_QSORTI
#define _H_QSORTI

//////////////////////////////////////////////////////////////////////
// PURPOSE:
// --------
// Sort an array of integers in ascending order of their integer arrs.
// Use QuickSort algorithm.
//
// ARGUMENTS:
// ------
//  n    -> integer, number of elements in arrays
//
// list  <- list of integers sorted in ascending order of their arrs
//
// arr   <- list of integer arrs sorted in ascending order
//
// Notes:
// ------
// The basic algorithm used here is from Numerical Recipes in C
//
//////////////////////////////////////////////////////////////////////
void qsorti(int n, int list[], int key[]);

#endif