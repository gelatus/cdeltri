/* $Log$ */

// Miscellaneous macros and utilities used by the deltri modules

#ifndef _H_MISC
#define _H_MISC

#define MIN(x,y)((x)<=(y) ? (x):(y))
#define MAX(x,y)((x)>=(y) ? (x):(y))
#define ROUND(x) int((x) + 0.5)
#define CEIL(x) int(x + 1.0)
#define SQ(x) ((x)*(x))
#define ABS(x) ((x) >= 0 ? (x):-(x))

#endif
