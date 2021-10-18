#ifndef STACK_H_INCLUDED
	#define STACK_H_INCLUDED
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdint.h>
	//#define DEBUG_PRINT // костыль, почему не работает через makeFile?

	#ifdef DEBUG_PRINT
		#define DP(code) code
	#else
		#define DP(code)  
	#endif

/*!
data_with_canary - pointer to memory with Canary
data - pointer to the first element
capacity - number of element fit (помещается)
sizeof_one_Canary - size of one Canary
size - number of current element
size_element - size of one element in bytes
security
*/
	struct Stack {
		void *data_with_canary;
		void *data;
		size_t capacity;
		size_t size;
		size_t sizeof_one_canary;
		size_t size_element;
		size_t log_level;
		uint64_t bad_constant = 0xDEDBAD;
	};


	enum Log_levels {
		RELEASE = 0,
		LOG_ERRORS,
		LOG_ALL
	};


	enum Errors {
		OK = 0,
		ERROR_ALLOC_MEMORY_IN_STACK_CTOR,
		ERROR_RESIZE_REALLOC
	};


/// Header of function for Stack
	int StackCtor (struct Stack *stack, size_t size_element, size_t log_level);
	int StackPush (struct Stack *stack, void *element);
	int StackTop (struct Stack *stack, void *element);
	int StackPop (struct Stack *stack);
	void StackFree (struct Stack *stack); /// Free all dinamic memory

#endif