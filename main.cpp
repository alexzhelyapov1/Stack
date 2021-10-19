#include <stdlib.h>
#include <stdio.h>

#include "stack.h"
#include "tests.h"
 

int main () {
	DP(printf ("-------------------------------\n");)
	DP(printf ("Good morning!!!\nProgramm is running;)\n");)
	DP(printf ("-------------------------------\n");)
	struct Stack *stack = (struct Stack *) calloc (1, sizeof (struct Stack));
	StackCtor (stack, sizeof (int), LOG_ERRORS);
	Fill_Ordered_Numbers (stack);
	return 0;
} 