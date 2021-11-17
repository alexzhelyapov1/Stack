#ifndef STACK_H_INCLUDED
	#define STACK_H_INCLUDED
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdint.h>

	#define LOG_LEVEL_LOG_ERRORS 
	// #define CANARY_VALUE 17446131000709551615
	// #define CANARY_VALUE 12345654321
	//#define DEBUG_PRINT // костыль, почему не работает через makeFile?

	#ifdef LOG_LEVEL_LOG_ALL
		#define DP(code) code
		#define DPR(code) {fprintf(stack->flogger, "!!!ERROR!!!	"); code}
	#else
		#define DP(code)
		#ifdef LOG_LEVEL_LOG_ERRORS
			#define DPR(code) {fprintf(stack->flogger, "!!!ERROR!!!	"); code}
		#else
			#define DPR(code) 
		#endif
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
		uint64_t canary_value = 12321;
		size_t sizeof_one_canary = sizeof (canary_value);
		size_t size_element;
		size_t log_level;
		uint64_t bad_constant = 0xDEDBAD;
		FILE *flogger;
	};


	enum Log_levels {
		RELEASE = 0, 
		LOG_ERRORS, //DPR
		LOG_ALL //DP
	};


	enum Errors {
		OK = 0,
		ERROR_ALLOC_MEMORY_IN_STACK_CTOR,
		ERROR_RESIZE_REALLOC,
		ERROR_OPEN_LOGGER_FILE,
		ERROR_TOP_EMPTY_STACK,
	};

	enum Validation_Errors {
		ERROR_OVERSIZE = 0b00001,

	};


/// Header of function for Stack
	int StackCtor (struct Stack *stack, size_t size_element, size_t log_level);
	int StackPush (struct Stack *stack, void *element);
	int StackTop (struct Stack *stack, void *element);
	int StackPop (struct Stack *stack);
	void StackFree (struct Stack *stack); /// Free all dinamic memory

#endif