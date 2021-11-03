#include <stdlib.h>
#include <string.h>

char * crossfront(char * string, char ch){
	while(string[0] == ch){
		string += 1;
	}
	return string;
}

int string2arr(char * str, char *** argument){
	int count = 0;
	int size = 0x21;
	*argument = (char **)malloc(0x21);
	if(str[0] == ' '){
		str = crossfront(str, ' ');
	}
	char * start = str;
	int length = strlen(str);
	while(str - start < length){
		char * tmp = strtok(str, " ");
		(*argument)[count] = tmp;	
		++count;
		str = crossfront(str + strlen(tmp) + 1, ' ');
		if(count % 4 == 0){
			size += 0x20;
			*argument = (char **)realloc(*argument, size);
		}
	}
	return count;
}

