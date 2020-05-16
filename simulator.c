#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simulator.h"
#include "iloc.h"
#include "instr.h"

#define AOK 0
#define INVALID_ARGS 1

void memSetInt(Machine* machine, int addy, int n) {
	machine->memory[addy] = (n >> 24) & 0xFF;
	machine->memory[addy + 1] = (n >> 16) & 0xFF;
	machine->memory[addy + 2] = (n >> 8) & 0xFF;
	machine->memory[addy + 3] = n & 0xFF;
}

int memGetInt(Machine* machine, int addy) {
	return	machine->memory[addy] << 24 | 
			machine->memory[addy + 1] << 16 |
			machine->memory[addy + 2] << 8 |
			machine->memory[addy + 3];
}

void incrementInstruction(Machine* machine) {
	machine->currentInstruction = machine->currentInstruction->next;
}


void exec_nop(Machine* machine) {
	incrementInstruction(machine);
}

void exec_add(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 + r2;

	incrementInstruction(machine);
}

void exec_sub(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 - r2;

	incrementInstruction(machine);
}

void exec_mult(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 * r2;

	incrementInstruction(machine);
}

void exec_div(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 / r2;

	incrementInstruction(machine);
}

void exec_and(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 & r2;

	incrementInstruction(machine);
}

void exec_or(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 | r2;

	incrementInstruction(machine);
}

void exec_xor(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 ^ r2;

	incrementInstruction(machine);
}

void exec_andi(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 & c1;

	incrementInstruction(machine);
}

void exec_ori(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 | c1;

	incrementInstruction(machine);
}

void exec_xori(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 ^ c1;

	incrementInstruction(machine);
}

void exec_addi(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 + c1;

	incrementInstruction(machine);
}

void exec_subi(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 - c1;

	incrementInstruction(machine);
}

void exec_rsubi(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = c1 - r1;

	incrementInstruction(machine);
}

void exec_multi(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 * c1;

	incrementInstruction(machine);
}

void exec_divi(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 / c1;

	incrementInstruction(machine);
}

void exec_rdivi(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = c1 / r1;

	incrementInstruction(machine);
}

void exec_lshift(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 << r2;

	incrementInstruction(machine);
}

void exec_rshift(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];

	machine->registers[instruction->args[2]->value] = r1 >> r2;

	incrementInstruction(machine);
}

void exec_lshiftI(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 << c1;

	incrementInstruction(machine);
}

void exec_rshiftI(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;

	machine->registers[instruction->args[2]->value] = r1 >> c1;

	incrementInstruction(machine);
}

void exec_load(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];

	machine->registers[instruction->args[1]->value] = memGetInt(machine, r1);

	incrementInstruction(machine);
}

void exec_loadI(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	// Load the constant arg 1 into the reg at arg 2
	machine->registers[instruction->args[1]->value] = instruction->args[0]->value;

	incrementInstruction(machine);
}

void exec_loadAI(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int c1 = instruction->args[1]->value;
	
	int r2 = machine->registers[instruction->args[2]->value];

	machine->registers[r2] = memGetInt(machine, r1 + c1);

	incrementInstruction(machine);
}

void exec_loadAO(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	int r2 = machine->registers[instruction->args[1]->value];
	
	int r3 = machine->registers[instruction->args[2]->value];

	machine->registers[r3] = memGetInt(machine, r1 + r2);

	incrementInstruction(machine);
}

void exec_store(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	
	int r2 = machine->registers[instruction->args[1]->value];

	memSetInt(machine, r2, r1);
	incrementInstruction(machine);
}

void exec_i2i(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	
	machine->registers[instruction->args[1]->value] = r1;

	incrementInstruction(machine);
}

void exec_c2c(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	
	machine->registers[instruction->args[1]->value] = (r1 & 0xFF);

	incrementInstruction(machine);
}

void exec_storeAI(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	
	int r2 = machine->registers[instruction->args[1]->value];
	int c = instruction->args[2]->value;

	memSetInt(machine, r2 + c, r1);
	incrementInstruction(machine);
}

void exec_storeAO(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];	
	int r2 = machine->registers[instruction->args[1]->value];
	int r3 = machine->registers[instruction->args[2]->value];

	memSetInt(machine, r2 + r2, r1);
	incrementInstruction(machine);
}

void exec_output(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int c1 = instruction->args[0]->value;
	
	int val = memGetInt(machine, c1);

	incrementInstruction(machine);
}

void exec_outputAI(Machine* machine) {
	Instruction* instruction = machine->currentInstruction;

	int r1 = machine->registers[instruction->args[0]->value];
	
	int c = instruction->args[1]->value;

	int val = memGetInt(machine, r1 + c);

	incrementInstruction(machine);
}

#define NUM_INSTRUCTIONS 34
CPUInstruction AllInstructions[NUM_INSTRUCTIONS] = {
	{NOP, "nop", "", 1, exec_nop},
	
	{ADD, "add", "rr>r", 1, exec_add},
	{SUB, "sub", "rr>r", 1, exec_sub},
	{MULT, "mult", "rr>r", 1, exec_mult},
	{DIV, "div", "rr>r", 1, exec_div},
	{ADDI, "addI", "rc>r", 1, exec_addi},
	{SUBI, "subI", "rc>r", 1, exec_subi},
	{RSUBI, "rsubI", "rc>r", 1, exec_rsubi},
	{MULTI, "multI", "rc>r", 1, exec_multi},
	{DIVI, "divI", "rc>r", 1, exec_divi},
	{RDIVI, "rdivI", "rc>r", 1, exec_rdivi},

	{AND, "and", "rr>r", 1, exec_and},
	{OR, "or", "rr>r", 1, exec_or},
	{XOR, "xor", "rr>r", 1, exec_xor},
	{ANDI, "andI", "rc>r", 1, exec_andi},
	{ORI, "orI", "rc>r", 1, exec_ori},
	{XORI, "xorI", "rc>r", 1, exec_xori},

	{I2I, "i2i", "r>r", 1, exec_i2i},
	{C2C, "c2c", "r>r", 1, exec_c2c},
	{I2C, "i2c", "r>r", 1, exec_c2c},
	{C2I, "c2i", "r>r", 1, exec_c2c},

	{LOAD, "load", "r>r", 1, exec_load},
	{LOADI, "loadI", "c>r", 1, exec_loadI},
	{LOADAI, "loadAI", "rc>r", 1, exec_loadAI},
	{LOADAO, "loadAO", "rc>r", 1, exec_loadAO},
	
	{LSHIFT, "lshift", "rr>r", 1, exec_lshift},
	{LSHIFTI, "lshiftI", "rc>r", 1, exec_lshiftI},
	{RSHIFT, "rshift", "rr>r", 1, exec_rshift},
	{RSHIFTI, "rshiftI", "rc>r", 1, exec_rshiftI},
	
	{STOREAI, "storeAI", "r>rc", 1, exec_storeAI},
	{STORE, "store", "r>r", 1, exec_store},
	{STOREAO, "storeAO", "r>rr", 1, exec_storeAO},
	
	{OUTPUTAI, "outputAI", "rc", 1, exec_outputAI},
	{OUTPUT, "output", "c", 1, exec_output},
};


char* typeToStr(InstrType type){
	for(int i = 0; i < NUM_INSTRUCTIONS; i ++) {
		if(AllInstructions[i].opcode == type) return AllInstructions[i].name;
	}

	return "ERROR";
}

InstrType strToType(char* str){
	for(int i = 0; i < NUM_INSTRUCTIONS; i ++) {
		if(strcmp(AllInstructions[i].name, str) == 0) return AllInstructions[i].opcode;
	}

	return ERROR;
}

void verifyInstruction(Machine* machine, char* format) {
	int inputMode = 0;
	int argNum = 0;
	for(int i = 0; i < strlen(format); i ++) {
		int isReg = format[i] == 'r';
		if(format[i] == '>') {
			inputMode = 1;
			continue;
		}


		if(machine->currentInstruction->numArgs <= argNum) {
			printf("Expected at least %d args, but only found %d\r\n", argNum + 1, machine->currentInstruction->numArgs + 1);
			machine->status = INVALID_ARGS;
			return;
		}

		InstrArg* arg = machine->currentInstruction->args[argNum];
		if(arg->isInput == inputMode) {
			printf("Too many arguments on the wrong side of the yields sign\r\n");
			machine->status = INVALID_ARGS;
			return;
		}

		if(arg->isReg != isReg) {
			printf("Expected constant and received register, or vice versa\r\n");
			machine->status = INVALID_ARGS;
			return;
		}

		argNum ++;
	}
}

void exec(Machine* machine) {
	for(int i = 0; i < NUM_INSTRUCTIONS; i ++){
		if(machine->currentInstruction->type == AllInstructions[i].opcode) {
			verifyInstruction(machine, AllInstructions[i].format);

			if(machine->status != AOK) return;

			AllInstructions[i].function(machine);

			return;
		}
	}
}

Machine* createMachine(Arguments* args) {
	Machine* machine = malloc(sizeof(Machine));

	machine->numRegisters = args->numRegisters;
	machine->registers = malloc(sizeof(int) * machine->numRegisters);

	machine->memSize = args->memSize;
	machine->memory = malloc(sizeof(unsigned char) * machine->memSize);

	return machine;
}

void destroyMachine(Machine* machine) {
	free(machine->registers);

	destroyInstructionList(machine->instructions);

	free(machine);
}

int process(Machine* machine) {
	printInstruction(stdout, machine->currentInstruction);

	exec(machine);
}

int runSimulator(Arguments* args) {
	Machine* machine = createMachine(args);
	machine->instructions = getInstructions(args->fileName);
	machine->currentInstruction = machine->instructions->next;

	while(machine->currentInstruction != NULL) {
		process(machine);
		if(machine->status != AOK) {
			printf("An unexpected error occured\r\n");
			return -1;
		}
	}

	destroyMachine(machine);
	return 0;
}