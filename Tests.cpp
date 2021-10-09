#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Tests.h"


int TestStack1 (struct Stack *stack) {
	assert (stack);

	//VALIDATE почему не робит?

	int ERR = OK;
	for (int i = 1; i < 9; i++) {
		//printf ("I = %d\n", i);
		char a = '0' + i;
		StackPush (stack, &a);
	}
	for (int i = 1; i < 11; i++) {
		printf ("Popping = ");
		VoidPrintConsole (StackPop (stack, &ERR), stack->size_element);
		printf ("\n");

		//printf ("Popping = %c\n", StackPop (stack, &ERR));

	}
	return OK;
}


void VoidPrintConsole (void *element, int size_element) {
	printf ("Size = %d", size_element);
	fflush (stdout);
	for (int i = 0; i < size_element; i++) {
		printf ("%c", ((char *) element)[i]);
		fflush (stdout);
	}
}


int Validate (struct Stack *stack) {
	return 1;
}


// void dumpFunction (struct Stack *stack) {
// 	printf ("========================================\n
// 			DUMP_Function is running!\n\n");
// 	printf ()
// }

// дампить только при ошибке - писать мин уровень проверок
