	// записать структуру
	// сайз умножить на размер элемента и получить количчество байт
	// тип копируем по байтно
	// где указывается параметр по умолчанию
	// сделать enum
#include "Stack.h"

int StackCtor (struct Stack *stack) {
	assert (stack);

	stack->capacity = 4;
	stack->size = 0;
	if ((stack->data = (char *) calloc (stack->capacity, sizeof (char))) != NULL)
		return OK;
	else
		return ERR_STACKCTOR;
}


int StackPush (struct Stack *stack, char element) {
	assert (stack);

	if (stack->size == stack->capacity) {
		printf ("if (stack->size + 1 == stack->capacity), element = %c\n", element);
		int errX = 0;
		if ((errX = StackResizeUp (stack)) == NULL) {
			#ifdef DEBUG
			printf ("Element = %c, capacity = %d\n", element, stack->capacity);
			#endif
		}
		else {
			printf ("ErrRiseUp\n");
			return ERR_STACKPUSH;
		}
	}
	stack->data[stack->size] = element;
	#ifdef DEBUG
	printf ("Pushing = %c\n", stack->data[stack->size]);
	#endif
	stack->size++;
	return OK;
}


int StackResizeUp (struct Stack *stack) {
	assert (stack);

	printf ("Size = %d\n", sizeof (stack->data));
	printf ("capacity before = %d\n", stack->capacity);
	stack->capacity *= 2;
	char *oldData = stack->data;
	if ((stack->data = (char *) calloc (stack->capacity, stack->capacity)) == NULL) {
		printf ("Error StackResizeUp\n");
		printf ("RizeUp1\n");
		return ERR_STACKRESIZEUP;
	}
	else {
		for (int i = 0; i < stack->size; i++) {
			stack->data[i] = oldData[i];
			printf ("Copy i = %c\n", stack->data[i]);
		}
		printf ("capacity after = %d\n", stack->capacity);
		printf ("RizeUp2\n");
		printf ("Size = %d\n", sizeof (stack->data));
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
		if (stack->size < stack->capacity / 4) {
			if (StackResizeDown (stack)) {
				*ERR = ERR_STACKPOP;
				printf ("ERR_RISEDOWN\n");
			}
			else {
				*ERR = OK;
			}
		}
		stack->size--;

		#ifdef DEBUG
		//printf ("Size pushing = %d\n", stack->size);
		#endif

		return stack->data[stack->size];
	}
}


int StackResizeDown (struct Stack *stack) {
	assert (stack);

	stack->capacity /= 2;
	char *oldData = stack->data;
	if ((stack->data = (char *) calloc (stack->capacity, stack->capacity)) == NULL) {
		return ERR_STACKRESIZEDOWN;
	}
	else {
		for (int i = 0; i < stack->size; i++) {
			stack->data[i] = oldData[i];
			printf ("Copy i = %c\n", stack->data[i]);
		}
		return OK;
	}
}