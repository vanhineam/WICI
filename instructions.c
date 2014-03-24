/**
 * Author: Adam Van Hine
 * Username: vanhineam
 *
 * Description: The instruction table and instruction logic for the WIC
 * Interpreter. This is where we define the structs for the instruction type
 * and the instruction table. We also add the ability to print the tables 
 * at any time.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instructions.h"
#include "table.h"
#include "stack.h"

#define INSTR_TABLE_SIZE 100

typedef struct {
  char opcode[OPCODE_SIZE];
  char operand[OPERAND_SIZE];
} instructionType;

typedef struct
{
  instructionType instructions[INSTR_TABLE_SIZE];
  int instructionCount;
} instructionTable;


// These 4 are "private" making them only accessible via public function
static instructionTable instrTable;
static tableType symbolTable;   //for variables and values
static tableType jumpTable;     //for labels
static stackType stack;         //for stack operations 

// This one is public so main can use it.
void initialize()
{
 instrTable.instructionCount = 0; 
 initializeTable(&symbolTable);
 initializeTable(&jumpTable);
 initializeStack(&stack);
}

void printSymbolTable()
{
  printTable(&symbolTable);
}

void printInstructionTable()
{
  int i;
  for(i = 0; i < instrTable.instructionCount; i++)
  {
    if(hasOperand(instrTable.instructions[i].opcode))
    {
      printf("%s %s\n", instrTable.instructions[i].opcode,
             instrTable.instructions[i].operand);
    }
    else
    {
      printf("%s\n", instrTable.instructions[i].opcode);
    }
  }
}

int fetchInstruction(int address, char * opcode, char * operand)
{
  return 1;
}

void insertInstruction(int address, char * opcode, char * operand)
{
  instructionType instr;
  strncpy(instr.opcode, opcode, OPCODE_SIZE);
  strncpy(instr.operand, operand, OPERAND_SIZE);
  instrTable.instructions[address] = instr;
  instrTable.instructionCount++;
}

int hasOperand(char * opcode)
{
  if(strcmp(opcode, "get") == 0){return 1;}
  else if(strcmp(opcode, "put") == 0){return 1;}
  else if(strcmp(opcode, "push") == 0){return 1;}
  else if(strcmp(opcode, "pop") == 0){return 1;}
  else if(strcmp(opcode, "j") == 0){return 1;}
  else if(strcmp(opcode, "jf") == 0){return 1;}

  else if (strcmp(opcode, "nop") == 0){return 0;}
  else if (strcmp(opcode, "add") == 0){return 0;}
  else if (strcmp(opcode, "sub") == 0){return 0;}
  else if (strcmp(opcode, "mul") == 0){return 0;}
  else if (strcmp(opcode, "div") == 0){return 0;}
  else if (strcmp(opcode, "and") == 0){return 0;}
  else if (strcmp(opcode, "not") == 0){return 0;}
  else if (strcmp(opcode, "or") == 0){return 0;}
  else if (strcmp(opcode, "tsteq") == 0){return 0;}
  else if (strcmp(opcode, "tstne") == 0){return 0;}
  else if (strcmp(opcode, "tstlt") == 0){return 0;}
  else if (strcmp(opcode, "tstle") == 0){return 0;}
  else if (strcmp(opcode, "tstgt") == 0){return 0;}
  else if (strcmp(opcode, "tstge") == 0){return 0;}
  else if (strcmp(opcode, "halt") == 0){return 0;}

  else { return 1; } // must be a label!!
}

//**********************************************************************
// Begin opcode function section.
//**********************************************************************
//Functions for various instructions go here. 
/**
int nop(int pc) { return pc + 1; }

int add(int pc){
  int rop = stackPop(&stack);
  int lop = stackPop(&stack);
  stackPush(&stack, lop + rop);
  return pc + 1;
}

int divide(int pc)
{
  int rop = stackPop(&stack);
  int lop = stackPop(&stack);
  if(rop == 0)
  {
    fprintf(stderr, "Can't divide by 0");
    exit(0);
  }
  else
  {
    stackPush(&stack, lop/rop);
  }
  return pc + 1;
}

int sub(int pc)
{
  int rop = stackPop(&stack);
  int rop = stackPop(&stack);
  stackPush(&stack, lop - rop);
  return pc + 1;
}

int mul(int pc)
{
  int rop = stackPop(&stack);
  int lop = stackPop(&stack);
  stackPush(&stack, lop * rop);
  return pc + 1;
}

int get(int pc, char * operand)
{
  int val;
  char numstring[10];
  char * endptr;

  printf("enter %s > ", operand);

  fgets(numstring, 10, stdin);

  val = strtol(numstring, &endptr, 10);
  if(*endptr != '\n')
  {
    printf("Some characters in the string are not base 10 digits.");
    while(*endptr !='\n')
    {
      endptr++;
    }
    get(pc, operand);
  }
  else
  {
    store(&symbolTable, operand, val);
  }

  return pc + 1;
}

int put(int pc, char * operand)
{
  val = retrieve(&symbolTable, operand);
  printf("%s = %d", operand, val);
}

int push(int pc, char * operand)
{
  int numResult;
  char* charResult;
  if(isdigit(*operand))
  {
    numResult = atoi(*operand);
    stachPush(&stack, numResult);
  }
  else
  {
    charResult = retrieve(&symbolTable, operand);
    stackPush(&stack, charResult);
  }
  return pc + 1;
}

int pop(int pc, char * operand)
{
  int var = stackPop(&stack);
  store(&symbolTable, operand, var);
  return pc + 1;
}
**/
/**
int not(int pc);
int and(int pc);
int or(int pc);
int testeq(int pc);
int testne(int pc);
int testlt(int pc);
int testle(int pc);
int testgt(int pc);
int testge(int pc);
int jump(int pc, char * operand);
int jf(int pc, char * operand);
int halt(int pc);
**/