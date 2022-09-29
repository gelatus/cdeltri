#ifndef _H_STACK
#define _H_STACK

/**
 * @brief Place item on LIFO stack and increment stack size
 * 
 * @param item [in] Item to be placed at the top of LIFO stack
 * @param maxstk [in] Maximum size of the stack
 * @param topstk [in,out] Pointer indicating current size of the stack. Will increment as items are added.
 * @param stack [in,out] LIFO stack. Integer array indexed [1,maxstack]
 */
void push(int item, int maxstk, int *topstk, int stack[]);

/**
 * @brief Remove item from LIFO stack and decrement stack size
 * 
 * @param topstk [in,out] Pointer indicating current size of the stack
 * @param stack [in] LIFO stack. Integer array indexed [1,maxstack]
 * @return int 
 */
int pop(int *topstk, int stack[]);

#endif
