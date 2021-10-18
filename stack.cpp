// struct Stack {
// 	void *data_with_canary;
// 	void *data;
// 	size_t capacity;
// 	size_t size;
// 	size_t sizeof_one_canary;
// 	size_t size_element;
// 	size_t log_level;
// }; 

#include "Stack.h"
#include <cstring>
#define MODERN_STACK do{void *data = stack->data;	\
					  void *data_with_canary = stack->data_with_canary; \
					  size_t sizeof_one_canary = stack->sizeof_one_canary; \
					  size_t capacity = stack->capacity; \
					  size_t size = stack->size; \
					  size_t size_element = stack->size_element; \
					  }while(false)

enum Resize_constants {
	UP = 0,
	DOWN,
	NEW
};

int StackResize (struct Stack *stack, int mode);




int StackCtor (struct Stack *stack, size_t size_element, size_t log_level) {
	uint64_t bad_constant = stack->bad_constant;

	stack->sizeof_one_canary = sizeof (uint64_t);
	size_t sizeof_one_canary = stack->sizeof_one_canary;
	size_t capacity = stack->capacity;
	stack->data_with_canary = calloc (sizeof_one_canary * 2, sizeof (char));
	* ((uint64_t *) stack->data_with_canary) = bad_constant;
	* (uint64_t *) (&((char *) stack->data_with_canary)[sizeof_one_canary + capacity]) = bad_constant;
	if (stack->data_with_canary == NULL) {
		return ERROR_ALLOC_MEMORY_IN_STACK_CTOR;
	}
	stack->data = stack->data_with_canary + sizeof_one_canary;
	stack->size = 0;
	stack->capacity = 0;
	stack->size_element = size_element;
	stack->log_level = log_level;
}


int StackResize (struct Stack *stack, int mode) {
	if (stack->capacity == 0) {
		mode = NEW;
	}
	switch (mode) {
		case NEW:
			stack->capacity = 4;
			break;
		case UP:
			stack->capacity *= 2;
			break;
		case DOWN:
			stack->capacity /= 2;
	}

	void * old_data = stack->data_with_canary; //занулит ли реаллок старую память при неудачной попытке?
	size_t old_capacity = stack->capacity;
	stack->data_with_canary = realloc (stack->data_with_canary, (stack->sizeof_one_canary * 2 + stack->capacity * stack->size_element) * sizeof (char));
	if (stack->data_with_canary == NULL) {
		stack->data_with_canary = old_data;
		return ERROR_RESIZE_REALLOC;
	}
	else {
		memcpy (stack->data_with_canary, old_data, stack->sizeof_one_canary + old_capacity * stack->size_element);
		memcpy (stack->data_with_canary + stack->sizeof_one_canary + stack->capacity, old_data + stack->sizeof_one_canary + old_capacity, 
			   stack->sizeof_one_canary);
		stack->data = stack->data_with_canary + stack->sizeof_one_canary;
		DP(printf ("It's Resize, newCapacity = %d\n", stack->capacity);)
		return OK;
	}

}


int StackPush (struct Stack *stack, void *element) {
	int size = stack->size;
	int capacity = stack->capacity;

	DP(printf ("It's StackPush\n");)
	if (size == capacity) {
		DP(printf ("It's size = capacity\n");)
		int result_of_resize = StackResize (stack, UP);
		if (result_of_resize != NULL) {
			DP(printf ("It's result_of_resize != NULL\n");)
			return result_of_resize;
		}
	}
	memcpy (stack->data + size, element, stack->size_element);
	stack->size++;
	return OK;
}


int StackTop (struct Stack *stack, void *element) {
	//MODERN_STACK
	void *data = stack->data;	\
	void *data_with_canary = stack->data_with_canary; \
	size_t sizeof_one_canary = stack->sizeof_one_canary; \
	size_t capacity = stack->capacity; \
	size_t size = stack->size; \
	size_t size_element = stack->size_element; \

	DP(printf ("-It's In stack top\n");)
	memcpy (element, data + (size - 1) * size_element, size_element);
	DP(printf ("It's After memcpy\n");)
	int result_stack_pop = StackPop (stack);
	if (result_stack_pop != NULL) {
		DP(printf ("---It's error in result_stack_pop\n");)
		return result_stack_pop;
	}
	DP(printf ("-It's OK StackTop\n");)
	return OK;
}


int StackPop (struct Stack *stack) {
	void *data = stack->data;	\
	void *data_with_canary = stack->data_with_canary; \
	size_t sizeof_one_canary = stack->sizeof_one_canary; \
	size_t capacity = stack->capacity; \
	size_t size = stack->size; \
	size_t size_element = stack->size_element; \


	stack->size--;
	if (size == capacity / 4) {
		int result_of_resize = StackResize (stack, DOWN);
		if (result_of_resize != NULL) {
			return ERROR_RESIZE_REALLOC;
		}
	}
	return OK;
}


void StackFree (struct Stack *stack) {
	stack->capacity = 0;
	stack->size = 0;
	free (stack->data_with_canary);
	free (stack->data);
	free (stack);
}