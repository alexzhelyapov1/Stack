#include "Stack.h"
#include <cstring>


// #define MODERN_STACK do{void *data = stack -> data;	\		//как это сделать?
// 					  void *data_with_canary = stack -> data_with_canary; \
// 					  size_t sizeof_one_canary = stack -> sizeof_one_canary; \
// 					  size_t capacity = stack -> capacity; \
// 					  size_t size = stack -> size; \
// 					  size_t size_element = stack -> size_element; \
// 					  }while(false)

enum Resize_constants {
	UP = 0,
	DOWN,
	NEW
};

int StackResize (struct Stack *stack, int mode);
int StackRecopyData (struct Stack *stack, void *old_data, size_t old_capacity);


int StackCtor (struct Stack *stack, size_t size_element, size_t log_level) {
	uint64_t bad_constant = stack -> bad_constant;

	char name[] = "file_logger.txt";
	if ((stack -> flogger = fopen (name, "w")) == NULL) {
		DPR(printf ("---ERROR--- Can't open logger file!\n");)
		return ERROR_OPEN_LOGGER_FILE;
	}

	DPR(fprintf (stack -> flogger, "ERROR out is working\n");)
	size_t sizeof_one_canary = stack -> sizeof_one_canary;
	size_t capacity = stack -> capacity;

	stack -> data_with_canary = calloc (sizeof_one_canary * 2, sizeof (char));
	* ((uint64_t *) stack -> data_with_canary) = 12321; ///////asfjbadbfouabdsoufbasdfjadsfpiad fasdf
	* (uint64_t *) (&((char *) stack -> data_with_canary)[sizeof_one_canary + capacity]) = bad_constant;
	if (stack -> data_with_canary == NULL) {
		DPR(fprintf (stack -> flogger, "stack -> data_with_canary == NULL (= %d)\n", stack -> data_with_canary);)
		return ERROR_ALLOC_MEMORY_IN_STACK_CTOR;
	}
	stack -> data = stack -> data_with_canary + sizeof_one_canary;
	stack -> size = 0;
	stack -> capacity = 0;
	stack -> size_element = size_element;
	stack -> log_level = log_level;

	DP(fprintf (stack -> flogger, "+++++ StackCtor passed with OK! +++++\n");)
	return OK;
}


int StackResize (struct Stack *stack, int mode) {
	DP(fprintf(stack -> flogger, "It's Resize, oldCapacity = %d\n", stack -> capacity);)

/// Calculate new capacity in depend of arg "mode"
	size_t old_capacity = stack -> capacity;
	if (stack -> capacity == 0) {
		mode = NEW;
	}
	switch (mode) {
		case NEW:
			stack -> capacity = 4;
			break;
		case UP:
			stack -> capacity *= 2;
			break;
		case DOWN:
			stack -> capacity /= 2;
	}

/// Realloc memory
	void *old_data = stack -> data_with_canary; //занулит ли реаллок старую память при неудачной попытке?
	stack -> data_with_canary = realloc (stack -> data_with_canary, (stack -> sizeof_one_canary * 2 + stack -> capacity * stack -> size_element) * sizeof (char));

	if (stack -> data_with_canary == NULL) { // Если ошибка выделения
		stack -> data_with_canary = old_data;
		DPR(fprintf (stack -> flogger, "stack -> data_with_canary == NULL (= %d)\n", stack -> data_with_canary);)
		return ERROR_RESIZE_REALLOC;
	}
	else {	//Если все норм (recopy обазательна, т.к. канарейку надо передвинуть)
		StackRecopyData (stack, old_data, old_capacity);

		DP(fprintf (stack -> flogger, "It's Resize, newCapacity = %d\n", stack -> capacity);)
		DP(fprintf (stack -> flogger, "+++++ StackResize passed with OK! +++++\n");)
		return OK;
	}

}


int StackPush (struct Stack *stack, void *element) {

	if (!stack) {
		StackCtor (stack, sizeof (int), LOG_ERRORS);
	}
	if (stack -> size == stack -> capacity) {
		int result_of_resize = StackResize (stack, UP);
		if (result_of_resize != OK) {
			DPR(fprintf (stack -> flogger, "It's result_of_resize != NULL (= %d)\n", result_of_resize);)
			return result_of_resize;
		}
	}
	memcpy (stack -> data + stack -> size * stack -> size_element, element, stack -> size_element);
	stack -> size++;
	DP(fprintf (stack -> flogger, "+++++ StackPush passed with OK! +++++\n");) //how to do __FUNCTION__?
	return OK;
}


int StackTop (struct Stack *stack, void *element) {

	if (stack -> size == 0) {
		DPR(fprintf(stack -> flogger, "Trying to top empty stack\n");)
		return ERROR_TOP_EMPTY_STACK;
	}
	memcpy (element, stack -> data + (stack -> size - 1) * stack -> size_element, stack -> size_element);
	int result_stack_pop = StackPop (stack);
	if (result_stack_pop != OK) {
		DPR(fprintf (stack -> flogger, "result_stack_pop != NULL (= %d)\n", result_stack_pop);)
		return result_stack_pop;
	}
	DP(fprintf (stack -> flogger, "+++++ StackTop passed with OK! +++++\n");)
	return OK;
}


int StackPop (struct Stack *stack) {
	void *data = stack -> data;	\
	void *data_with_canary = stack -> data_with_canary; \
	size_t sizeof_one_canary = stack -> sizeof_one_canary; \
	size_t capacity = stack -> capacity; \
	size_t size = stack -> size; \
	size_t size_element = stack -> size_element; \


	stack -> size--;
	if (size == capacity / 4) {
		int result_of_resize = StackResize (stack, DOWN);
		if (result_of_resize != OK) {
			DPR(fprintf (stack -> flogger, "result_of_resize != NULL (= %d)\n", result_of_resize);)
			return ERROR_RESIZE_REALLOC;
		}
	}
	DP(fprintf (stack -> flogger, "+++++ StackPop passed with OK! +++++\n");)
	return OK;
}


void StackFree (struct Stack *stack) {
	stack -> capacity = 0;
	stack -> size = 0;
	fclose (stack -> flogger);
	free (stack -> data_with_canary);
	free (stack -> data);
	free (stack);
	DP(fprintf (stack -> flogger, "+++++ StackFree passed with OK! +++++\n");)
}


int ValidateStack (struct Stack *stack) {
	int all_errors = 0;
	if (stack -> capacity < stack -> size) {
		all_errors += ERROR_OVERSIZE;
	}
}

int StackRecopyData (struct Stack *stack, void *old_data, size_t old_capacity) {
	if (stack && old_data) {
		memcpy (stack -> data_with_canary, old_data, stack -> sizeof_one_canary + old_capacity * stack -> size_element);
		memcpy (stack -> data_with_canary + stack -> sizeof_one_canary + stack -> capacity, old_data + stack -> sizeof_one_canary + old_capacity, 
			   stack -> sizeof_one_canary);
		stack -> data = stack -> data_with_canary + stack -> sizeof_one_canary;
	}
	return OK;
}