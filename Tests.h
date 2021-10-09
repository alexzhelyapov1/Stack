#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED
#include "Stack.h"

enum ErrorsTest {
	ERR_TESTSTACK1 = 1000,
	
};

int Validate (struct Stack *stack);
void VoidPrintConsole (void *element, int size_element);
void dumpFunction (struct Stack *stack);








#ifdef TESTING_MODE
	#define IF_TESTING_MODE_ON(code) code
#else
	#define IF_TESTING_MODE_ON(code)
#endif





#endif