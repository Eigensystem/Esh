#include <iostream>
#include <string.h>
#include <unistd.h>
#include <string>
#ifndef _STRUCT_HPP_
#define _STRUCT_HPP_
	#include "../tools/struct.hpp"
#endif

void xargs_processing(command * cmd, int num){
	int argc = cmd->sub_counter[num];
	for(int i = argc - 1; i > 0; --i){
		cmd->command_arr[num][i-1] = cmd->command_arr[num][i];
	}
	--cmd->sub_counter[num];
	std::string str;
	while(1){
		getline(std::cin, str);
		if(std::cin.eof()){
			break;
		}
		else{
			cmd->xargs_argu[cmd->xargs_counter] = (char *)malloc(str.length());
			strcpy(cmd->xargs_argu[cmd->xargs_counter], str.c_str());
			cmd->command_arr[num][cmd->sub_counter[num]] = cmd->xargs_argu[cmd->xargs_counter];
			cmd->command_arr[num][cmd->sub_counter[num]][str.length()-1] = '\0';
			++cmd->xargs_counter;
			++cmd->sub_counter[num];
			if(cmd->xargs_counter % 4 == 0){
				cmd->xargs_argu = (char **)realloc(cmd->xargs_argu, (cmd->xargs_counter + 4) * 0x8 + 1);
			}
			if(cmd->sub_counter[num] % 4 == 0){
				cmd->command_arr[num] = (char **)realloc(cmd->command_arr[num], (cmd->sub_counter[num] + 4) * 8 + 1);
			}
		}
	}
	cmd->command_arr[cmd->sub_counter[num]] = nullptr;
	if(cmd->sub_counter[num] % 4 == 0){
	cmd->command_arr[num] = (char **)realloc(cmd->command_arr[num], (cmd->sub_counter[num] + 4) * 8 + 1);
	}
}