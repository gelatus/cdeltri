
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Place item on LIFO stack and increment stack size
 * 
 * @param item [in] Item to be placed at the top of LIFO stack
 * @param maxstk [in] Maximum size of the stack
 * @param topstk [in,out] Pointer indicating current size of the stack. Will increment as items are added.
 * @param stack [in,out] LIFO stack. Integer array indexed [1,maxstack]
 */
void push(int item, int maxstk, int *topstk, int stack[])
{
    *topstk += 1;
    if (*topstk > maxstk) {
        fprintf(stderr, "*** ERROR IN SUBROUTINE PUSH ***\n*** STACK OVERFLOW ***\n");
        exit(1);
    }

    stack[*topstk] = item;
}

/**
 * @brief Remove item from LIFO stack and decrement stack size
 * 
 * @param topstk [in,out] Pointer indicating current size of the stack
 * @param stack [in] LIFO stack. Integer array indexed [1,maxstack]
 * @return int 
 */
int pop(int *topstk, int stack[])
{
    int i = *topstk;
    if (i <= 0) {
        fprintf(stderr, "*** ERROR IN SUBROUTINE PUSH ***\n*** STACK UNDERFLOW ***\n");
        exit(1);
    }

    int val = stack[i--];
    *topstk = i;
    return val;
}
