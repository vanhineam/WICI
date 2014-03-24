//The wikipedia array implementation of a stack.
#ifndef STACK_H_
#define STACK_H_

#define STACK_SIZE 20 //20 elements maximum in the stack.

typedef struct{
	int top;
	int items[STACK_SIZE];
} stackType;

//Function prototypes.
void initializeStack(stackType * s);
void stackPush(stackType *, int x);
int stackPop(stackType *);
void printStack(stackType *);

#endif
