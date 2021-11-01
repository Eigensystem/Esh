#include <stdlib.h>
#include <string.h>

char * crossfront(char * string, char ch){
	while(string[0] == ch){
		string += 1;
	}
	return string;
}

char ** string2arr(char * argv, char * command, int com_len){
	char ** argument = (char **)malloc(0x20);
	int i = 1;
	int size = 20;
	argument[0] = command;
	while(argv - command < com_len){
		char * tmp = strtok(argv, " ");
		argument[i] = tmp;
		++i;
		argv = crossfront(argv + strlen(tmp) + 1, ' ');
		if(i % 4 == 0){
			size += 0x20;
			argument = (char **)realloc(argument, size);
		}
	}
	return argument;
}

