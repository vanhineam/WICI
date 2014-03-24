
#include <stdio.h>
#include "stack.h"

int main()
{
   stackType stack;
   printf("Initializing stack.\n");
   initializeStack(&stack);

   printf("Pushing: %d\n", 3);
   stackPush(&stack, 3);

   printf("Popping...");
   int x = stackPop(&stack);
   if (x == 3)
     printf("success\n");
   else
     printf("********** ERROR\n");

   printf("Pushing: %d\n", 4);
   stackPush(&stack, 4);
   printf("Pushing: %d\n", 5);
   stackPush(&stack, 5);
   printf("Popping...");
   x = stackPop(&stack);
   if (x == 5)
     printf("success\n");
   else
     printf("********** ERROR\n");

   printf("Pushing: %d\n", 6);
   stackPush(&stack, 6);
   printf("Pushing: %d\n", 7);
   stackPush(&stack, 7);

   printf("Stack contents (should be 7,6,4):\n");
   printStack(&stack);
}
