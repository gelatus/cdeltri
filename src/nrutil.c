
#include <stdio.h>
#include <stdlib.h>
#include "nrutil.h"

void nrerror(char error_text[])
{
  fprintf(stderr,"Numerical Recipes run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"...now exiting to system...\n");
  exit(1);
}

vector_t vector(int nl, int nh)
{
  vector_t v;
  
  v=(vector_t)malloc((unsigned) (nh-nl+1)*sizeof(float));
  if (!v) nrerror("allocation failure in vector()");
  return v-nl;
}

ivector_t ivector(int nl,int nh)
{
  int *v;

  v=(int *)malloc((unsigned) (nh-nl+1)*sizeof(int));
  if (!v) nrerror("allocation failure in ivector()");
  return v-nl;
}

dvector_t dvector(int nl,int nh)
{
  dvector_t v;
  
  v=(dvector_t)malloc((unsigned) (nh-nl+1)*sizeof(double));
  if (!v) nrerror("allocation failure in dvector()");
  return v-nl;
}



matrix_t matrix(int nrl, int nrh, int ncl, int nch)
{
  int i;
  matrix_t m;

  m=(matrix_t)malloc((unsigned) (nrh-nrl+1)*sizeof(float*));
  if (!m) nrerror("allocation failure 1 in matrix()");
  m -= nrl;
  
  for(i=nrl;i<=nrh;i++) {
    m[i]=(vector_t ) malloc((unsigned) (nch-ncl+1)*sizeof(float));
    if (!m[i]) nrerror("allocation failure 2 in matrix()");
    m[i] -= ncl;
  }
  return m;
}

dmatrix_t dmatrix(int nrl, int nrh, int ncl, int nch)
{
  int i;
  dmatrix_t m;

  m=(dmatrix_t ) malloc((unsigned) (nrh-nrl+1)*sizeof(double*));
  if (!m) nrerror("allocation failure 1 in dmatrix()");
  m -= nrl;
  
  for(i=nrl;i<=nrh;i++) {
    m[i]=(dvector_t) malloc((unsigned) (nch-ncl+1)*sizeof(double));
    if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
    m[i] -= ncl;
  }
  return m;
}

imatrix_t imatrix(int nrl, int nrh, int ncl, int nch)
{
  int i;
  imatrix_t m;
  
  m=(imatrix_t)malloc((unsigned) (nrh-nrl+1)*sizeof(int*));
  if (!m) nrerror("allocation failure 1 in imatrix()");
  m -= nrl;
  
  for(i=nrl;i<=nrh;i++) {
    m[i]=(int *)malloc((unsigned) (nch-ncl+1)*sizeof(int));
    if (!m[i]) nrerror("allocation failure 2 in imatrix()");
    m[i] -= ncl;
  }
  return m;
}



matrix_t submatrix(matrix_t a, int oldrl, int oldrh, int oldcl, int oldch,
		   int newrl, int newcl)
{
  int i,j;
  matrix_t m;
  
  m=(matrix_t ) malloc((unsigned) (oldrh-oldrl+1)*sizeof(float*));
  if (!m) nrerror("allocation failure in submatrix()");
  m -= newrl;
  
  for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+oldcl-newcl;
  
  return m;
}

void free_vector(vector_t v, int nl, int nh)
{
  free((char*) (v+nl));
}

void free_ivector(ivector_t v, int nl, int nh)
{
  free((char*) (v+nl));
}

void free_dvector(dvector_t v, int nl, int nh)
{
  free((char*) (v+nl));
}



void free_matrix(matrix_t m, int nrl, int nrh, int ncl, int nch)
{
  int i;
  
  for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
  free((char*) (m+nrl));
}

void free_dmatrix(dmatrix_t m, int nrl, int nrh, int ncl, int nch)
{
  int i;
  
  for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
  free((char*) (m+nrl));
}

void free_imatrix(imatrix_t m, int nrl, int nrh, int ncl, int nch)
{
  int i;

  for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
  free((char*) (m+nrl));
}



void free_submatrix(matrix_t b, int nrl, int nrh, int ncl, int nch)
{
  free((char*) (b+nrl));
}



matrix_t convert_matrix(vector_t a, int nrl, int nrh, int ncl, int nch)
{
  int i,j,nrow,ncol;
  matrix_t m;

  nrow=nrh-nrl+1;
  ncol=nch-ncl+1;
  m = (matrix_t ) malloc((unsigned) (nrow)*sizeof(float*));
  if (!m) nrerror("allocation failure in convert_matrix()");
  m -= nrl;
  for(i=0,j=nrl;i<=nrow-1;i++,j++) m[j]=a+ncol*i-ncl;
  return m;
}



void free_convert_matrix(matrix_t b, int nrl, int nrh, int ncl, int nch)
{
  free((char*) (b+nrl));
}

/* compute the dot product a.b */

float vdot(vector_t a, int al, int ah, vector_t b, int bl, int bh)
{
	float dp = 0;
	int   i, n = ah-al;
	
	for(i=0; i<n; i++) {
		dp += a[i+al] * b[i+bl];
	}
	
	return dp;
}

/* compute the matrix-vector product u=A.b */

void mvdot(matrix_t A, int rl, int rh, int cl, int ch, vector_t b, int bl, int bh,
	       vector_t u, int ul, int uh)
{
	int i, j;
	int m = rh - rl;
	int n = ch - cl;
	
	for(i=0; i < m; i++) {
		u[i+ul] = 0.0;
		for(j=0; j < n; j++) {
			u[i+ul] += A[i+rl][j+cl]*b[j+bl];
		}
	}
}
