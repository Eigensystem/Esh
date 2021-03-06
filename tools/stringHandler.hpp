#include <stdlib.h>
#include <string.h>

#ifndef _STRUCT_HPP_
#define _STRUCT_HPP_
    #include "struct.hpp"
#endif

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

file_data * filepath2filedata(char * filepath){
	int i;
	file_data * file = (file_data *)malloc(sizeof(struct file_data));
	bool flag = 0;
	for(i = strlen(filepath)-1; i >= 0; --i){
		if(filepath[i] == '/'){
			filepath[i] = '\0';
			flag = 1;
			break;
		}
	}
	if(!flag){
		file->dir_path = nullptr;
		file->file_name = filepath;
	}
	else{
		file->dir_path = filepath;
		file->file_name = filepath + i + 1;
	}
	return file;
}
