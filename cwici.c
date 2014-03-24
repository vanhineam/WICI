/**
 * Author: Adam Van Hine
 * Username: vanhineam
 *
 * Description: File manipulation for the interpreter. This is where we read
 * in the file and send the contents of what we read to be insterted into the
 * instruction table.
 */
#include <stdio.h>
#include "instructions.h"

void discardline(FILE * fp);

int main(int argc, char* argv[])
{
	// Initialize the Instruction Table, Jump Table, and Stack
	initialize();

	// If there are too few or too many arguements print the proper usage info.
	if(argc != 2)
	{
		printf("Usage: %s filename\n", argv[0]);
	}
	else
	{
		// Open the file for reading
		FILE * file = fopen(argv[1], "r+");

		// Handle any errors
		if(file == 0)
		{
			printf("Couldn't Open file\n");
		}
		else
		{
			int address = 0;
			char opcode[OPCODE_SIZE];
			char operand[OPERAND_SIZE];

			// Read the file and get the opcode while not EOF
			while(fscanf(file, "%s", opcode) == 1)
			{
				// Check if opcode has an operand and if it does read that into the 
				// operand variable
				if(hasOperand(opcode))
				{
					if(fscanf(file, "%s", operand) != 1)
					{
						printf("Could not read operand\n");
						return 0;
					}
				}
				else
				{
					operand[0] = 0;
				}

				discardline(file);

				// Insert the instruction into the instruction table
				insertInstruction(address, opcode, operand);
				address++;
			}
		}
		// Close the file
		fclose(file);
	}
	printInstructionTable();
}

/**
 * Discards the contents until a newline or end of file is reached
 * (Helper function to the file I/O section in main)
 * 
 * @param fp filepointer
 */
void discardline(FILE * fp)
{
	int newline;
	do
	{
		newline = fgetc(fp);
	} while ((char)newline != '\n' && (newline != EOF));
}