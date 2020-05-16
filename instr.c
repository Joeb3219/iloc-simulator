#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "instr.h"
#include "iloc.h"
#include "simulator.h"

Instruction* createInstruction(){
	Instruction* instr = malloc(sizeof(Instruction));
	instr->type = ERROR;
	instr->numArgs = 0;
	instr->args = malloc(sizeof(InstrArg*) * 6);
	instr->next = instr->last = NULL;
	instr->registersLive = 0;
	return instr;
}

void destroyInstruction(Instruction* instr){
	free(instr);
}

void destroyInstructionList(Instruction* instr){
	if(instr->next == NULL) destroyInstruction(instr);
	else{
		destroyInstructionList(instr->next);
		destroyInstruction(instr);
	}
}

Instruction* processLine(Instruction* base, char* line){
	Instruction* newInstr = createInstruction();
	decodeInstruction(line, newInstr);

	if(newInstr->type == ERROR){
		destroyInstruction(newInstr);
		return base;
	}

	base->next = newInstr;
	newInstr->last = base;
	return newInstr;
}

void findNextToken(char** str, char* buffer){
	// Get the string at the given address.
	char* rStr = *str;
	int foundLeftEdge = 0;
	int i = 0;
	while(rStr[0] != '\0'){
		// Scan through characters until we find one that isn't whitespace.
		if(!foundLeftEdge){
			if(rStr[0] == '\t' || rStr[0] == ' '){
				rStr ++;
				continue;
			}else{
				buffer[i++] = rStr[0];
				foundLeftEdge = 1;
			}
		// Now scan throug until we hit the next whitespace.
		// If we hit \0, then we'll technically be at an edge, too, and this will stop through the loop stopping.
		}else{
			if(rStr[0] == '\t' || rStr[0] == ' ') break;
			buffer[i++] = rStr[0];
		}
		// Move to next character
		rStr ++;
	}
	// Cap off our string.
	buffer[i++] = '\0';
	str[0] = rStr;
}

char* substrrep(char* str, char search, char* replacement){
	int finalSize = 0;
	int replacementLength = strlen(replacement);
	int i;
	for(i = 0; i < strlen(str); i ++){
		if(str[i] == search) finalSize += replacementLength;
		else finalSize += 1;
	}

	i = 0;
	int j = 0, k = 0;

	char* newString = malloc(sizeof(char) * (finalSize + 1));

	for(i = 0; i < strlen(str); i ++){
		if(str[i] == search){
			for(k = 0; k < replacementLength; k ++){
				newString[j ++] = replacement[k];
			}
		}else{
			newString[j ++] = str[i];
		}
	}

	newString[j] = '\0';
	return newString;
}

void decodeInstruction(char* line, Instruction* instr){
	if(line[0] == '/') return;
	int i = 0, j = 0;
	char* instructionType;
	// At most, we can have an argument that takes up the whole line.
	char buffer[strlen(line) + 1];
	InstrArg* arg;

	char *replaceCommas = substrrep(line, ',', "\t,\t");
	char *replaceEquals = substrrep(replaceCommas, '=', "\t=");
//	free(replaceCommas);
	line = substrrep(replaceEquals, '>', "> ");
//	free(replaceEquals);

	findNextToken(&line, buffer);
	instr->type = strToType(buffer);

	int processingInputs = 1;
	while(line[0] != '\0'){
		findNextToken(&line, buffer);
		if(buffer[0] == ',') continue;
		if(buffer[0] == '/') return;

		// Determine if we are now on the right side of the => sign, which means that all other arguments are outputs.
		if(strcmp(buffer, "=>") == 0){
			processingInputs = 0;
			continue;
		}

		// Build up the argument for what it is.

		arg = createInstrArg();
		arg->isInput = processingInputs;
		arg->isReg = buffer[0] == 'r';

		if(arg->isReg) arg->value = atoi(&buffer[1]);
		else arg->value = atoi(buffer);
		if(instr->numArgs >= 3) printf("Attempting to store arg w/ value %d => pos %d\n", arg->value, (instr->numArgs + 1));

		instr->args[instr->numArgs ++] = arg;
	}

}

InstrArg* createInstrArg(){
	InstrArg* arg = malloc(sizeof(InstrArg));
	arg->isInput = arg->isReg = arg->value = 0;
	return arg;
}

void destroyInstrArg(InstrArg* arg){
	free(arg);
}

void printInstruction(FILE* file, Instruction* instr){
	int i;

	fprintf(file, "%s", typeToStr(instr->type));

	InstrArg* arg;
	int printedYields = 0;
	for(i = 0; i < instr->numArgs; i ++){
		arg = instr->args[i];
		if(!arg->isInput && !printedYields){
			fprintf(file, "\t=>");
			printedYields = 1;
		}

		if(arg->isReg) fprintf(file, "\tr%d", arg->value);
		else fprintf(file, "\t%d", arg->value);
		if(i != instr->numArgs - 1){
			if(instr->args[i]->isInput == instr->args[i + 1]->isInput) fprintf(file, ",");
		}
	}
	
	fprintf(file, "\n");
}

Instruction* getInstructions(char* fileName){
	FILE* file = fopen(fileName, "r");
	if(file == NULL){
		fprintf(stderr, "No such file: %s\n", fileName);
		exit(1);
	}

	char c;
	char buff[256];
	int i = 0;
	Instruction* instruction = createInstruction();
	Instruction* head = instruction;
	while((c = fgetc(file)) != EOF){
		if(c == '\r' || c == '\n'){
			if(i == 0) continue;
			buff[i++] = '\0';
			instruction = processLine(instruction, buff);
			i = 0;
		}else{
			buff[i++] = c;
		}
	}

	fclose(file);
	return head;
}