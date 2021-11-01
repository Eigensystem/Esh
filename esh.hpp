#include <iostream>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <filesystem>
#include "config.hpp"
#include "inner_command.hpp"

namespace esh{
	// void read_config(char * filename){
	// 	FILE *fp;
	// 	char * str = (char *)malloc(100);
	// 	fp = fopen(filename, "r");
	// 	do{
	// 		str = fgets(str, 100, fp);

	// 	}while(str);
	// }
	char ** argv;
	int count;

	void read_command(){
		count = 0;
		char * str;
		int len, len_cal = 0;
		int size = 0x20;
		argv = (char **)malloc(0x21);
		char * command = readline("> \0");
		len = strlen(command);
		while(len_cal < len){
			str = strtok(command + len_cal, " ");
			len_cal += strlen(str)+1;
			argv[count] = str;
			++count;
			if(count % 4 == 0){
				size += 0x20;
				argv = (char **)realloc(argv, size);
			}
		}
	}

	void inner_exec(char * command){
		if(!strcmp(command, "echo")){
			echo(argv, count);
		}
		else if(!strcmp(command, "exit")){
			sh_exit(argv, count);
		}
		// else if(command == ""){

		// }
	}

	void exec_command(){
		char * command = argv[0];
		inner_exec(command);
	}

	void clear_space(){
		free(argv[0]);
		free(argv);
		argv = nullptr;
		return;
	}
}