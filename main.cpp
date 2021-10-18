#include <stdlib.h>
#include <stdio.h>

#include "stack.h"
#include "tests.h"
 

int main () {
	DP(printf ("URAAAAAA\n");)
	struct Stack *stack = (struct Stack *) calloc (1, sizeof (struct Stack));
	StackCtor (stack, sizeof (int), LOG_ERRORS);
	DP(printf ("We created stack structure!\n");)
	Fill_Ordered_Numbers (stack);
	return 0;
}