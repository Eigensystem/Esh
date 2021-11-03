#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cd.hpp"

//Inner function pwn & cd

bool fsoperate(char ** argument, int count){
	if(!strcmp(argument[0], "pwd")){
		if(count > 1){
			many_argu("pwd");
		}
		else{
			char * buf = (char *)malloc(0x100);
			getcwd(buf, 0x100);
			printf("%s\n", buf);
			free(buf);
		}
		return 1;
	}
	else if(!strcmp(argument[0], "cd")){
		cd(argument, count);
		return 1;
	}
	else{
		return 0;
	}
}

//Inner function echo

void echo(char ** argument, int count){
	for(int i = 1; i < count; ++i){
		printf("%s ", argument[i]);
	}
	printf("\n");
}

//Inner function exit

void sh_exit(char * command, char ** argument){
	free(command);
	free(argument);
	exit(0);
}


//The inner function entry

bool inner_exec(char ** argument, int count){
	bool flag = 0;
	if(!strcmp(argument[0], "echo")){
		echo(argument, count);
		return 1;
	}
	else if(!strcmp(argument[0], "exit")){
		sh_exit(argument[0], argument);
		return 1;
	}
	else if(fsoperate(argument, count)){
		return 1;
	}
	else{
		return 0;
	}
}
