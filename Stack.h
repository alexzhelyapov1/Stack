#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define DEBUG
#define USE_VALIDATION
#define TESTING_MODE


// #ifdef USE_VALIDATION
// #define VALIDATE ;
// #else
// #define VALIDATE ;
// #endif

struct Stack {
	void *data;
	size_t size;
	size_t capacity;
	int size_element;
	int security_level;
};//error

enum Errors { // подписать каждый
	OK = 0,
	ERR_STACKCTOR,
	ERR_STACKRESIZEUP,
	ERR_STACKPUSH,
	ERR_STACKRESIZEDOWN,
	ERR_STACKPOP
};


int StackCtor (struct Stack *stack, int size_element);
int StackPush (struct Stack *stack, void *element);
void *StackPop (struct Stack *stack, int *ERR);
int StackDistruct (struct Stack *stack);
void StackDump (const struct Stack *stack);

#ifdef DEBUG
int TestStack1 (struct Stack *stack);
#endif


#ifndef USE_VALIDATION
#define VALIDATE(code) 
#else
#define VALIDATE(code) code
#endif


#endif