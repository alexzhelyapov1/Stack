#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Stack.h"

int StackResize (struct Stack *stack, int mlt);
int RecopyData (void *oldData, struct Stack *stack);

enum STACK_PARAMS {

};


int StackCtor (struct Stack *stack) {
	assert (stack);

	VALIDATE

	stack->capacity = 0;
	stack->size = 0;
	stack->size_element = sizeof (char);
		return OK;
}


int StackPush (struct Stack *stack, void *element) {
	assert (stack);

	VALIDATE

	if (stack->size == stack->capacity) {
		int errX = 0;
		if ((errX = StackResize (stack, 2)) != NULL) { // аргумент нового размера и в одну функйию
			return ERR_STACKPUSH;

		}
	}
	// memcpy
	for (int i = 0; i < stack->size_element; i++) {
		*((char *) (stack->data[stack->size * stack->size_element] + i)) = *((char *) element);
	}
	stack->size++;
	return OK;
}


int StackResize (struct Stack *stack, int mlt) {
	assert (stack);

	VALIDATE

	if (stack->capacity == 0)
		stack->capacity = 4;
	else {
		if (mlt == 2)
			stack->capacity *= mlt;
		else
			stack->capacity /= (-mlt);
	}
	void *oldData = stack->data;
	if ((stack->data = (void *) realloc (stack->data, stack->capacity * stack->size_element)) == NULL) {
		return ERR_STACKRESIZEUP;
	}
	else {
		RecopyData (oldData, stack);
		return OK;
	}
}


void *StackPop (struct Stack *stack, int *ERR) {
	assert (stack);

	VALIDATE


	if (stack->size < 1) {
		*ERR =  ERR_STACKPOP;
		char posion[10] = "xxxxxxxxx";
		return (void *) posion;
	}
	else {
		if (stack->size <= stack->capacity / 4) {
			if (StackResize (stack, -2)) {
				*ERR = ERR_STACKPOP;
			}
			else {
				*ERR = OK;
			}
		}
		stack->size--;
		return stack->data[stack->size * stack->size_element];
	}
}


int RecopyData (void *oldData, struct Stack *stack) {//strncpy memcpy
	assert (oldData);
	assert (stack);
	assert (stack->data);

	VALIDATE

	for (int i = 0; i < stack->size * stack->size_element; i++) {
		char *newData = (char *) stack->data;
		char *oldData1 = (char *) oldData;
		newData[i] = oldData[i];
	}
	return OK;
}

void StackDump (const struct Stack *stack) {
	printf ("Data (pointer) = %d\n", stack->data);
	printf ("Size = %d\n", stack->size);
	printf ("Capacity = %d\n", stack->capacity);
}
// //влидация
// VALIDATE()

// validate -> dump -> file
