#ifndef SIMULATOR_H_

	#define SIMULATOR_H_
	#include "iloc.h"
	#include "instr.h"

	int runSimulator(Arguments* args);

	typedef struct Machine {
		int numRegisters;
		int* registers;
		Instruction* instructions;
		Instruction* currentInstruction;
	} Machine;

#endif