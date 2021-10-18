#include "tests.h"

int Fill_Ordered_Numbers (struct Stack *stack) {
	DP(printf("I'm in \"tests.cpp\"\n");)
	int n = 10;
	for (int i = 0; i < n; i++) {
		int result = StackPush (stack, &i);
		if (result != NULL) {
			printf ("Error = %d\n", result);
		}
	}
	for (int i = 0; i < n; i++) {
		int *x = (int *) calloc (1, sizeof (int));
		int result = StackTop (stack, x);
		if (result != NULL) {
			printf ("ErrorTop = %d\n", result);
		}
		printf ("%d ", *x);
	}
	return OK;
}