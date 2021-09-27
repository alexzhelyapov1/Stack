#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct Stack {
	char *data;
	int size;
	int capacity;
};

enum Errors {
	OK = 0,
	ERR_STACKCTOR,
	ERR_STACKRESIZEUP,
	ERR_STACKPUSH,
	ERR_STACKRESIZEDOWN,
	ERR_STACKPOP
};

int StackCtor (struct Stack *stack);
int StackPush (struct Stack *stack, char element);
int StackResizeUp (struct Stack *stack);
char StackPop (struct Stack *stack, int *ERR);
int StackResizeDown (struct Stack *stack);


#endif