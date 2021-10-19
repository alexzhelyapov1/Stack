#include "tests.h"

int Fill_Ordered_Numbers (struct Stack *stack) {
	int n = 10;
	for (int i = 0; i < n; i++) {
		int result = StackPush (stack, &i);
		if (result != OK) {
			printf ("Error = %d\n", result);
		}
	}
	int *x = (int *) calloc (1, sizeof (int));
	for (int i = 0; i < n + 2; i++) {
		int result = StackTop (stack, x);
		if (result != OK) {
			printf ("\nErrorTop = %d", result);
		}
		else {
			printf ("%d ", *x);
		}
	}
	free (x);
	return OK;
}