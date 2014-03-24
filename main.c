#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>

#include "instructions.h"

// "Private" methods to break up our work here.
static void readInstructions(FILE * fp);
static void discardline(FILE * fp);
static void execute();

int main(int argc, char * argv[]){
    //First things first. Open the input file.
    FILE *fp;
    int i = 0;
        
    if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL) {
      printf("File open failed.\nUsage: %s <input file>\n",argv[0]);
      exit(1);
    }

    // initialize the symbol table, jump table and stack to 0
    // method will be in instructions.c

    // read the input file and prepare structures
    readInstructions(fp);

    // Close the file.
    fclose(fp); 

    // Begin to interpret
    execute();

    // All done, how about some debugging output...
    printf("\nSymbol Table\n");
    printf("------------\n");
    printSymbolTable();

    printf("\nProgram halted\n");
}

void readInstructions(FILE * fp)
{
}

void execute()
{
}


// discard rest of line (good for comments)
void discardline(FILE * fp)
{
    int newline;
    do
    {
        newline = fgetc(fp);
    } while ((char)newline != '\n' && (newline != EOF));
}
