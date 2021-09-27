	// записать структуру
	// сайз умножить на размер элемента и получить количчество байт
	// тип копируем по байтно
	// где указывается параметр по умолчанию
	// сделать enum
#include "Stack.h"

int StackCtor (struct Stack *stack) {
	assert (stack);

	stack->capacity = 0;
	stack->size = 0;
	if ((stack->data = (char *) calloc (stack->capacity, sizeof (char))) != NULL)
		return OK;
	else
		return ERR_STACKCTOR;
}


int StackPush (struct Stack *stack, char element) {
	assert (stack);

	if (stack->size == stack->capacity) {
		int errX = 0;
		if ((errX = StackResizeUp (stack)) == NULL) {
		}
		else {
			return ERR_STACKPUSH;
		}
	}
	stack->data[stack->size] = element;
	stack->size++;
	return OK;
}


int StackResizeUp (struct Stack *stack) {
	assert (stack);

	if (stack->capacity == 0)
		stack->capacity = 4;
	else 
		stack->capacity *= 2;
	char *oldData = stack->data;
	if ((stack->data = (char *) realloc (stack->data, stack->capacity * stack->capacity)) == NULL) {
		return ERR_STACKRESIZEUP;
	}
	else {
		RecopyData (oldData, stack);
		return OK;
	}
}


char StackPop (struct Stack *stack, int *ERR) {
	assert (stack);

	if (stack->size < 1) {
		*ERR =  ERR_STACKPOP;
		return 'x';
	}
	else {
		if (stack->size <= stack->capacity / 4) {
			if (StackResizeDown (stack)) {
				*ERR = ERR_STACKPOP;
			}
			else {
				*ERR = OK;
			}
		}
		stack->size--;

		return stack->data[stack->size];
	}
}


int StackResizeDown (struct Stack *stack) {
	assert (stack);

	stack->capacity /= 2;
	char *oldData = stack->data;
	if ((stack->data = (char *) realloc (stack->data, stack->capacity * stack->capacity)) == NULL) {
		return ERR_STACKRESIZEDOWN;
	}
	else {
		RecopyData (oldData, stack);
		return OK;
	}
}


int RecopyData (char *oldData, struct Stack *stack) {
	assert (oldData);
	assert (stack);
	assert (stack->data);


	for (int i = 0; i < stack->size; i++) {
			stack->data[i] = oldData[i];
		}

	return OK;
}