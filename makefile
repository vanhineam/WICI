
default: 
	@echo "make targets are: stack, table"

stack: teststack.c stack.h stack.c 
	gcc teststack.c stack.c -o teststack

table: testtable.c table.h table.c 
	gcc testtable.c table.c -o testtable

instruction: testinstructions.c instructions.c instructions.h stack.c stack.h table.c table.h
	gcc testinstructions.c instructions.c instructions.h stack.c stack.h table.c table.h -o testinstructions

cwici: main.c instructions.h instructions.c table.h table.c stack.h stack.c
	gcc main.c instructions.h instructions.c table.h table.c stack.h stack.c -o cwici
