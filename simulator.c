#include <stdlib.h>
#include <stdio.h>
#include "simulator.h"
#include "iloc.h"
#include "instr.h"

Machine* createMachine(Arguments* args) {
	Machine* machine = malloc(sizeof(Machine));

	machine->numRegisters = args->numRegisters;
	machine->registers = malloc(sizeof(int) * machine->numRegisters);

	return machine;
}

void destroyMachine(Machine* machine) {
	free(machine->registers);

	destroyInstructionList(machine->instructions);

	free(machine);
}

int process(Machine* machine) {
	printInstruction(stdout, machine->currentInstruction);
	machine->currentInstruction = machine->currentInstruction->next;
}

int runSimulator(Arguments* args) {
	Machine* machine = createMachine(args);
	machine->instructions = getInstructions(args->fileName);
	machine->currentInstruction = machine->instructions;

	while(machine->currentInstruction != NULL) {
		process(machine);
	}

	destroyMachine(machine);
	return 0;
}