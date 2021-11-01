#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../tools/errorHandler.hpp"
#include "../tools/stringhandler.hpp"
char * workspace;

//File system operations

void fsoperate(char * command, char * argv, int com_len){
	char * buf = (char *)malloc(0x100);
	if(!strcmp(command, "pwd")){
		if(argv != nullptr){
			many_argu("pwd");
			return;
		}
		else{
			getcwd(buf, 0x100);
			printf("%s\n", buf);
		}
	}
	else if(!strcmp(command, "cd")){
		if(argv == nullptr){
			char * path = getenv("HOME");
			printf("%s", path);
			chdir(path);
		}
		else if(argv != nullptr){
			char * tmp = strtok(argv, " ");
			argv = crossfront(argv + strlen(tmp) + 1, ' ');
			if(argv - command < com_len){
				many_argu("cd");
			}
			if(tmp[0] == '.' && tmp[1] == '/'){
				char * path = getcwd(buf, 0x100);
				strcat(path, tmp+1);
				chdir(path);
			}
			else if(tmp[0] == '~' && tmp[1] == '/'){
				char * path = getenv("HOME");
				strcat(path, tmp+1);
				chdir(path);
			}
		}
	}
	free(buf);
}

//Inner function echo

void echo(char * command, char * argv, int com_len){
	while(argv - command < com_len){
		char * tmp = strtok(argv, " ");
		argv = crossfront(argv + strlen(tmp) + 1, ' ');
		printf("%s ", tmp);
	}
	printf("\n");
}

//Inner function exit

void sh_exit(char * command){
	free(command);
	exit(0);
}


//The inner function entry

void inner_exec(char * command, char * argv, int com_len){
	if(!strcmp(command, "echo")){
		echo(command, argv, com_len);
	}
	else if(!strcmp(command, "exit")){
		sh_exit(command);
	}
	else{
		fsoperate(command, argv, com_len);
	}
}
