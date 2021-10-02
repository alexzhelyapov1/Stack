#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Stack.h"

int main () {
	#ifdef DEBUG
	printf ("DEBUG!!!\n");
	#endif
	struct Stack stack[1];
	StackCtor (stack);
	TestStack1 (stack);
	return 0;
}

// огромные массивы пустых стеков не занимают информацию