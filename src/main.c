
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nrutil.h"
#include "deltri.h"

void parse_row(char *row, char *delim, float *px, float *py);

// Maximum number of input lines to process
#define MAX_LINES 100

int main(int argc, char **argv)
{
    int npts = MAX_LINES, numtri = 0;
    ivector_t list;
    imatrix_t adj, verts;
    vector_t xa, ya;

    // check the name of the input file
    if (argc !=3 ) {
        fprintf(stderr, "Usage: deltri <input-file> <output-file>\n");
        exit(1);
    }

    // Open the input file
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        fprintf(stderr, "Unable to open %s  for input.\n", argv[1]);
        exit(1);
    }

    // Read the data, line by line, store coordinates
    // in arrays xa, ya
    xa = vector(1, MAX_LINES+3);
    ya = vector(1, MAX_LINES+3);
    list = ivector(1,MAX_LINES);

    char buf[1024] = {0x0};
    float x, y;
    int n = 0;
    fprintf(stderr, "Reading data points from file %s\n", argv[1]);
    while (fgets(buf, sizeof(buf), in)) {
        parse_row(buf, ",", &x, &y);
        n++;
        xa[n] = x;
        ya[n] = y;
        list[n] = n;
    }
    fprintf(stderr, "Read %d data points from file %s\n", n, argv[1]);
    fclose(in);

    // Need to allocate matrices of max_verts_size = 2*n+1 rows
    // to hold vertex and adjacency triplets
    int max_verts_size = 2*n+1;
    adj = imatrix(1,max_verts_size,1,3);
    verts = imatrix(1,max_verts_size,1,3);

    // Call deltri to generate the triangulation
    deltri(npts,n,xa,ya,list,verts,adj,&numtri);

    fprintf(stderr,"Triangulation complete. Triangle count: %d\n", numtri);

    // Write output file
    FILE *out = fopen(argv[2],"w");
    if (!out) {
        fprintf(stderr, "Unable to open %s  for output.\n", argv[2]);
        exit(1);
    }

    // Write the vertex points along with their indices
    fprintf(stderr, "Writing triangulation data to file: %s\n", argv[2]);

    fprintf(out, "[Vertices]\n");
    for (int i=1; i<=n; ++i) {
        fprintf(out, "%d %f %f\n",i,xa[i],ya[i]);
    }
    fprintf(out, "\n");

    // Write the triangle faces
    fprintf(out, "[Faces]\n");
    for (int i=1; i<=numtri; ++i) {
        ivector_t va = verts[i];
        fprintf(out, "%d %d %d %d\n", i, va[1], va[2], va[3]);
    }
    fprintf(out, "\n");

    // Write the adjacency list
    fprintf(out, "[Adjacency]\n");
    for (int i=1; i<=numtri; ++i) {
        ivector_t va = adj[i];
        fprintf(out, "%d %d %d %d\n", i, va[1], va[2], va[3]);
    }

    // Clean up 
    fprintf(stderr, "Cleaning up allocated memory\n");
    free_vector(xa, 1, MAX_LINES+3);
    free_vector(ya, 1, MAX_LINES+3);
    free_ivector(list, 1, MAX_LINES);
    free_imatrix(adj,1,max_verts_size,1,3);
    free_imatrix(verts,1,max_verts_size,1,3);

    fprintf(stderr, "Done\n");

    return 0;
}

/**
 * @brief read the first two entries in each row and assign to x and y
 * 
 * @param row -> the input row 
 * @param delim -> the column delimiter (usually , or TAB)
 * @param x <- the x coordinate 
 * @param y <- the y coordinate
 */
void parse_row(char *row, char *delim, float *px, float *py)
{
    char *tok; // store parsed tokens

    // Get X coordinate
    tok = strtok(row, delim);
    if (tok == NULL) {
        fprintf(stderr,"Error parsing input file for x value\n");
        exit(1);
    }
    *px = atof(tok);

    // Get Y coordinate
    tok = strtok(NULL, delim);
    if (tok == NULL) {
        fprintf(stderr,"Error parsing input file for y value\n");
        exit(1);
    }
    *py = atof(tok);
}