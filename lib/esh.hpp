#include <iostream>
#include <readline/readline.h>
#include "../config/config.hpp"
#include "../lib/inner_command.hpp"
// #include "../tools/stringhandler.hpp"

namespace esh{
	char * command;
	char * argv;
	int count;
	int com_len;

	bool read_command(){
		char * str = readline("> \0");
		if(str[0] == '\0' || str[0] == ' '){
			printf("\n");
			return 0;
		}
		com_len = strlen(str);
		command = strtok(str, " ");
		argv = crossfront(str + strlen(command) + 1, ' ');
		if(argv - command >= com_len){
			argv = nullptr;
		}
		return 1;
	}

	void exec_command(){
		inner_exec(command, argv, com_len);
	}

	void clear_space(){
		free(command);
		command = nullptr;
		return;
	}
}