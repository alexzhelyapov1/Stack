#include "Stack.h"

int main () {
	#ifdef DEBUG
	printf ("DEBUG!!!\n");
	#endif
	struct Stack stack[1];
	int ERR = OK;
	StackCtor (stack);
	for (int i = 1; i < 9; i++) {
		StackPush (stack, '0' + i);
	}
	for (int i = 1; i < 11; i++) {
		printf ("Popping = %c\n", StackPop (stack, &ERR));
	}
	return 0;
}

// огромные массивы пустых стеков не занимают информацию