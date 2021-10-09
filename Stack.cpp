#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <mem.h>
#include <string.h>
#include "Stack.h"
#include "Tests.h"

int StackResize (struct Stack *stack, int mlt);
int RecopyData (void *oldData, struct Stack *stack); // убрать функцию

enum STACK_PARAMS {

};


int StackCtor (struct Stack *stack, int size_element) {
	assert (stack);

	VALIDATE(Validate (stack);)
	stack->size_element = size_element;
	stack->capacity = 0;
	stack->size = 0;
	return OK;
}


int StackPush (struct Stack *stack, void *element) {
	assert (stack);


	// for (int i = 0; i < stack->size_element; i++) {
	// 	putchar (((char *) element)[i]);
	// }
	//printf (" Prishol\n");


	VALIDATE(Validate (stack);)

	if (stack->size == stack->capacity) {
		int errX = 0;
		if ((errX = StackResize (stack, 2)) != NULL) { // аргумент нового размера и в одну функйию
			return ERR_STACKPUSH;

		}
	}
	memcpy (((char *) stack->data + stack->size * stack->size_element), element, stack->size_element);

	// char temple[1000] = {}; // если так инициализируем, все зануляется?
	// memcpy (((char *) temple), element, stack->size_element);
	// for (int i = 0; i < stack->size_element; i++) {
	// 	putchar (temple[i]);
	// }
	// printf (" enddddd\n");

	stack->size++;
	return OK;
}


int StackResize (struct Stack *stack, int mlt) {
	assert (stack);

	VALIDATE(Validate (stack);)
	// printf ("Stack Resize !\n");
	if (stack->capacity == 0){
		// printf ("The first\n");
		stack->capacity = 4;
	}
	else {
		if (mlt == 2)
			stack->capacity *= mlt;
		else
			stack->capacity /= (-mlt);
	}
	void *oldData = stack->data;
	//printf ("Before\n");
	//stack->data = (void *) realloc (stack->data, stack->capacity * stack->size_element); //в чем ошибка?
	//printf ("After\n");
	stack->data = (void *) calloc (stack->capacity, stack->size_element);
	if (stack->data == NULL) {
		printf ("ERR_STACKRESIZEUP\n");
		stack->data = oldData;
		return ERR_STACKRESIZEUP;
	}
	else {
		// printf ("else\n");
		if (oldData != stack->data) {
			// printf ("RecopyCall\n");
			RecopyData (oldData, stack);
		}
		return OK;
	}
}


void *StackPop (struct Stack *stack, int *ERR) {
	assert (stack);

	VALIDATE(Validate (stack);)
	//if (level = SECURITY_LOG) /// логирую
	


	if (stack->size < 1) {
		*ERR =  ERR_STACKPOP;
		char poison[10] = "xxxxxxxxx";
		return (void *) poison;
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
		return (void *) (((char *) stack->data)[stack->size * stack->size_element]);
	}
}


int RecopyData (void *oldData, struct Stack *stack) {//strncpy memcpy
	assert (oldData);
	assert (stack);
	assert (stack->data);

	VALIDATE(Validate (stack);)
	char *newData = (char *) stack->data;
	char *oldData1 = (char *) oldData;

	// printf ("Stack->size = %d\n", stack->size);
	memcpy (newData, oldData1, stack->size * stack->size_element);
	// for (int i = 0; i < stack->size * stack->size_element; i++) {
	// 	newData[i] = oldData[i];
	// }
	return OK;
}

void StackDump (const struct Stack *stack) {
	printf ("Data (pointer) = %d\n", stack->data);
	printf ("Size = %llg\n", stack->size);
	printf ("Capacity = %llg\n", stack->capacity);
}
// //влидация
// VALIDATE(Validate (stack);)()

// Validate(Validate (stack);) -> dump -> file

// __FILE__ __FUNCTION__ __LINE__
// dump