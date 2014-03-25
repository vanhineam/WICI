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
static int isNotHalt(char* opcode);
static int getOpNum(char* opcode);

int main(int argc, char * argv[]){
    //First things first. Open the input file.
    FILE *fp;
    int i = 0;
    clock_t begin, end;
    double time_spent;
        
    if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL) {
      printf("File open failed.\nUsage: %s <input file>\n",argv[0]);
      exit(1);
    }

    // initialize the symbol table, jump table and stack to 0
    // method will be in instructions.c
    initialize();

    // read the input file and prepare structures
    readInstructions(fp);

    // Close the file.
    fclose(fp); 

    //printInstructionTable();

    begin = clock();
    // Begin to interpret
    execute();
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    // All done, how about some debugging output...
    printf("\nSymbol Table\n");
    printf("------------\n");
    printSymbolTable();

    printf("\nProgram halted\n");

    printf("\nTotal Runtime:%d\n", time_spent);
}

void readInstructions(FILE * fp)
{
    int address = 0;
    char opcode[OPCODE_SIZE];
    char operand[OPERAND_SIZE];

    // Read the file and get the opcode while not EOF
    while(fscanf(fp, "%s", opcode) == 1)
    {
        // Check if opcode has an operand and if it does read that into the 
        // operand variable
        if(hasOperand(opcode))
        {
            if(fscanf(fp, "%s", operand) != 1)
            {
                printf("Could not read operand\n");
                exit(1);
            }
        }
        else
        {
            operand[0] = 0;
        }

        discardline(fp);

        // Insert the instruction into the instruction table
        insertInstruction(address, opcode, operand);
        address++;
    }
}

/**
 * Execute is the loop that runs all of the commands from the file
 */
void execute()
{
    int pc = 0;
    char opcode[OPCODE_SIZE];
    char operand[OPERAND_SIZE];

    // Execution loop "While not is not halt"
    while(isNotHalt(opcode))
    {
        fetchInstruction(pc, opcode, operand);

        switch(getOpNum(opcode))
        {
            case 0:
                pc = nop(pc);
                break;
            case 1:
                pc = add(pc);
                break;
            case 2:
                pc = sub(pc);
                break;
            case 3:
                pc = mul(pc);
                break;
            case 4:
                pc = divide(pc);
                break;
            case 5:
                pc = get(pc, operand);
                break;
            case 6:
                pc = put(pc, operand);
                break;
            case 7:
                pc = push(pc, operand);
                break;
            case 8:
                pc = pop(pc, operand);
                break;
            case 9:
                pc = not(pc);
                break;
            case 10:
                pc = and(pc);
                break;
            case 11:
                pc = or(pc);
                break;
            case 12:
                pc = testeq(pc);
                break;
            case 13:
                pc = testne(pc);
                break;
            case 14:
                pc = testlt(pc);
                break;
            case 15:
                pc = testle(pc);
                break;
            case 16:
                pc = testgt(pc);
                break;
            case 17:
                pc = testge(pc);
                break;
            case 18:
                pc = jump(pc, operand);
                break;
            case 19:
                pc = jf(pc, operand);
                break;
        }
    }
}

/**
 * Tests to see if the passed opcode is a halt
 * Helper method for the execution loop
 * 
 * @param  opcode The string to be tested
 * @return        0 if it is a halt; 1 if it is not;
 */
int isNotHalt(char* opcode)
{
    if(getOpNum(opcode) == 20)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

/**
 * Given an opcode it returns the number associated with this opcode.
 * @param  opcode String of what opcode it is
 * @return        Number associated with the opcode
 */
int getOpNum(char* opcode)
{
    if(strcmp(opcode,"nop") == 0)
    {
        return NOP;
    }
    else if(strcmp(opcode, "add") == 0)
    {
        return ADD;
    }
    else if(strcmp(opcode, "sub") == 0)
    {
        return SUB;
    }
    else if(strcmp(opcode, "mul") == 0)
    {
        return MUL;
    }
    else if(strcmp(opcode, "div") == 0)
    {
        return DIVIDE;
    }
    else if(strcmp(opcode, "get") == 0)
    {
        return GET;
    }
    else if(strcmp(opcode, "put") == 0)
    {
        return PUT;
    }
    else if(strcmp(opcode, "push") == 0)
    {
        return PUSH;
    }
    else if(strcmp(opcode, "pop") == 0)
    {
        return POP;
    }
    else if(strcmp(opcode, "not") == 0)
    {
        return NOT;
    }
    else if(strcmp(opcode, "and") == 0)
    {
        return AND;
    }
    else if(strcmp(opcode, "or") == 0)
    {
        return OR;
    }
    else if(strcmp(opcode, "tsteq") == 0)
    {
        return TESTEQ;
    }
    else if(strcmp(opcode, "tstne") == 0)
    {
        return TESTNE;
    }
    else if(strcmp(opcode, "tstlt") == 0)
    {
        return TESTLT;
    }
    else if(strcmp(opcode, "tstle") == 0)
    {
        return TESTLE;
    }
    else if(strcmp(opcode, "tstgt") == 0)
    {
        return TESTGT;
    }
    else if(strcmp(opcode, "tstge") == 0)
    {
        return TESTGE;
    }
    else if(strcmp(opcode, "j") == 0)
    {
        return JUMP;
    }
    else if(strcmp(opcode, "jf") == 0)
    {
        return JF;
    }
    else if(strcmp(opcode, "halt") ==0)
    {
        return HALT;
    }
}

/**
 * Discards all info until it reaches a new line
 * @param fp The file to look at.
 */
void discardline(FILE * fp)
{
    int newline;
    do
    {
        newline = fgetc(fp);
    } while ((char)newline != '\n' && (newline != EOF));
}
