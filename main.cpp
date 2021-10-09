#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Stack.h"
#include "Tests.h"

int main () {
	struct Stack stack[1];
	StackCtor (stack, sizeof (char));
	IF_TESTING_MODE_ON(printf ("DEBUG!!!\n"); 
						TestStack1 (stack);)
	return 0;
}

// огромные массивы пустых стеков не занимают информацию