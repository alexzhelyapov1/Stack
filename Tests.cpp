#include "Stack.h"


int TestStack1 (struct Stack *stack) {
	assert (stack);

	VALIDATE

	int ERR = OK;
	for (int i = 1; i < 9; i++) {
		if (StackPush (stack, '0' + i)) {
			return OK;
		}
		else {
			return ERR_TESTSTACK1;
		}
	}
	for (int i = 1; i < 11; i++) {
		printf ("Popping = %c\n", StackPop (stack, &ERR));
	}
}