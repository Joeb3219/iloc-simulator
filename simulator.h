#ifndef SIMULATOR_H_

	#define SIMULATOR_H_
	#include "iloc.h"
	#include "instr.h"

	int runSimulator(Arguments* args);

	typedef struct Machine {
		int numRegisters;
		int* registers;
		int memSize;
		unsigned char* memory;
		Instruction* instructions;
		Instruction* currentInstruction;
		int status;
	} Machine;

	typedef struct CPUInstruction {
		InstrType opcode;
		char* name;
		char* format;
		int numCycles;
		void (*function)(struct Machine* cpu);
	} CPUInstruction;

	char* typeToStr(InstrType type);
	InstrType strToType(char* str);


#endif