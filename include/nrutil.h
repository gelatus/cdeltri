
#ifndef _H_NRUTIL
#define _H_NRUTIL

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/****************************** TYPES *********************************/

typedef float **matrix_t;
typedef float *vector_t;
typedef double **dmatrix_t;
typedef double *dvector_t;
typedef int   **imatrix_t;
typedef int   *ivector_t;

/*************************** FUNCTION DECLARATIONS *********************/

void nrerror(char error_text[]);
vector_t vector(int nl, int nh);
ivector_t ivector(int nl,int nh);
dvector_t dvector(int nl,int nh);
matrix_t matrix(int nrl, int nrh, int ncl, int nch);
dmatrix_t dmatrix(int nrl, int nrh, int ncl, int nch);
imatrix_t imatrix(int nrl, int nrh, int ncl, int nch);
matrix_t submatrix(matrix_t a, int oldrl, int oldrh, int oldcl, int oldch,
		   int newrl, int newcl);
void free_vector(vector_t v, int nl, int nh);
void free_ivector(ivector_t v, int nl, int nh);
void free_dvector(dvector_t v, int nl, int nh);
void free_matrix(matrix_t m, int nrl, int nrh, int ncl, int nch);
void free_dmatrix(dmatrix_t m, int nrl, int nrh, int ncl, int nch);
void free_imatrix(imatrix_t m, int nrl, int nrh, int ncl, int nch);
void free_submatrix(matrix_t b, int nrl, int nrh, int ncl, int nch);
matrix_t convert_matrix(vector_t a, int nrl, int nrh, int ncl, int nch);
void free_convert_matrix(matrix_t b, int nrl, int nrh, int ncl, int nch);

float vdot(vector_t a, int al, int ah, vector_t b, int bl, int bh);
void mvdot(matrix_t A, int rl, int rh, int cl, int ch, vector_t b, int bl, int bh,
	       vector_t u, int ul, int uh);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
