#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cd.hpp"

//Inner function pwn & cd

void fsoperate(char * command, char * argv, int com_len){
	if(!strcmp(command, "pwd")){
		if(argv != nullptr){
			many_argu("pwd");
			return;
		}
		else{
			char * buf = (char *)malloc(0x100);
			getcwd(buf, 0x100);
			printf("%s\n", buf);
			free(buf);
		}
	}
	else if(!strcmp(command, "cd")){
		cd(argv, command, com_len);
	}
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
