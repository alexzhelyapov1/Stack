#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define DEBUG
#define USE_VALIDATION
#define TESTING_MODE


#ifdef USE_VALIDATION
#define VALIDATE ;
#else
#define VALIDATE ;
#endif




struct Stack {
	void *data;
	int size;
	int capacity;
	int size_element;
};//error

enum Errors { // подписать каждый
	OK = 0,
	ERR_STACKCTOR,
	ERR_STACKRESIZEUP,
	ERR_STACKPUSH,
	ERR_STACKRESIZEDOWN,
	ERR_STACKPOP
};


enum ErrorsTest {
	ERR_TESTSTACK1 = 100
};


int StackCtor (struct Stack *stack);
int StackPush (struct Stack *stack, char element);
void *StackPop (struct Stack *stack, int *ERR);
int StackDistruct (struct Stack *stack);
void StackDump (const struct Stack *stack);

#ifdef DEBUG
int TestStack1 (struct Stack *stack);
#endif


#endif