
#include <stdio.h>
#include "table.h"

int main()
{
   tableType mytable;
   printf("Initializing table\n");
   initializeTable(&mytable);

   printf("Storing 3 into A\n");
   store(&mytable, "A", 3);
   printf("Storing 4 into B\n");
   store(&mytable, "B", 4);
   printf("Storing 5 into C\n");
   store(&mytable, "C", 5);

   printf("Retrieving A...");
   int x = retrieve(&mytable, "A");
   if (x == 3)
     printf("success\n");
   else
     printf("********** ERROR\n");

   printf("Retrieving B...");
   x = retrieve(&mytable, "B");
   if (x == 4)
     printf("success\n");
   else
     printf("********** ERROR\n");

   printf("Retrieving C...");
   x = retrieve(&mytable, "C");
   if (x == 5)
     printf("success\n");
   else
     printf("********** ERROR\n");

   printf("Retrieving B...");
   x = retrieve(&mytable, "B");
   if (x == 4)
     printf("success\n");
   else
     printf("********** ERROR\n");

   printf("Storing 24 into B\n");
   store(&mytable, "B", 24);

   printf("Retrieving B...");
   x = retrieve(&mytable, "B");
   if (x == 24)
     printf("success\n");
   else
     printf("********** ERROR\n");

   printf("Printing table...\n");
   printTable(&mytable);
}
