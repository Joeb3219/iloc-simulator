#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "iloc.h"
#include "simulator.h"

#define flagSet(A) (isFlagSet(argc, argv, A))
#define getArgOrDefault(A, B) ((getArgument(argc, argv, A) == NULL) ? B : getArgument(argc, argv, A))

char* getArgument(int argc, char** argv, char* flag){
	int i;
	for(i = 0; i < argc - 1; i ++){
		if(strcmp(argv[i], flag) == 0) return argv[i + 1];
	}
	return NULL;
}

int isFlagSet(int argc, char** argv, char* flag){
	int i;
	for(i = 0; i < argc; i ++){
		if(strcmp(argv[i], flag) == 0) return 1;
	}
	return 0;
}

void displayHelp(int argc, char** argv) {
	printf("ILOC Simulator by Joseph A. Boyle\r\n");
	printf("%s -f <fileName> <opts>\r\n", argv[0]);
	printf("-r <num>: Set the number of registers available in the simulator to num. Defaults to 10,000.\r\n");
	printf("-m <num>: Set the number of bytes available in the simulator to num. Defaults to 10,000.\r\n");
}

Arguments* loadArguments(int argc, char** argv) {
	Arguments* args = malloc(sizeof(Arguments));

	args->numRegisters = atoi(getArgOrDefault("-r", "10000"));
	args->fileName = getArgOrDefault("-f", NULL);
	args->memSize = atoi(getArgOrDefault("-m", "10000"));

	return args;
}

int main(int argc, char** argv) {
	if(flagSet("-h")) {
		displayHelp(argc, argv);
		return 0;
	}

	Arguments* args = loadArguments(argc, argv);
	return runSimulator(args);
}