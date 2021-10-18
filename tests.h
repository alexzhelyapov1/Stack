#ifndef TESTS_H_INCLUDED
	#define TESTS_H_INCLUDED

	#include "stack.h"
	#include <stdio.h>
	#include <stdlib.h>

	#ifdef DEBUG_PRINT
		#define DP(code) code
	#else
		#define DP(code) 
	#endif


	int Fill_Ordered_Numbers (struct Stack *stack);
#endif 