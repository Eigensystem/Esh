#include <stdlib.h>
#include <string.h>

int count_ch(char * str, char ch){
	int length = strlen(str);
	int count = 0;
	for(int i = 0; i < length; ++i){
		if(str[i] == ch){
			++count;
		}
	}
	return count;
}

int count_uncon(char * str, char ch){
	int length = strlen(str);
	int count = 0;
	bool flag = 0;
	for(int i = 0; i < length; ++i){
		if(str[i] == ch && flag == 0){
			++count;
			flag = 1;
		}
		else if(str[i] != ch && flag == 1){
			flag = 0;
		}
	}
	return count;
}

void string2arr(char ** argv, char * command, int count){
	char * str;
	char * tmp;
	for(int i = 0; i <= count; ++i){
		str = strtok(command, " ");
		if(str == nullptr){
			break;
		}
		argv[i] = str;
		tmp = str + strlen(str) + 1;
		while(!strcmp(tmp, " ")){
			++tmp;
		}
		command = tmp;
	}
}

char * crossfront(char * string, char ch){
	while(string[0] == ch){
		string += 1;
	}
	return string;
}
