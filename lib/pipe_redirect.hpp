#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#ifndef _STRUCT_HPP_
#define _STRUCT_HPP_
	#include "../tools/struct.hpp"
#endif

#ifndef _ERRORHANDLER_HPP_
#define _ERRORHANDLER_HPP_
	#include "../tools/errorHandler.hpp"
#endif


int setredirectR(command * cmd, int num){
	int fd;
	fd = open(cmd->command_arr[num][cmd->sub_counter[num]-1], O_RDONLY);
	if(fd == -1){
		dir_nexist("zsh", cmd->command_arr[num][cmd->sub_counter[num]-1]);
		return -1;
	}
	--cmd->sub_counter[num];
	cmd->command_arr[num][cmd->sub_counter[num]] = nullptr;
	dup2(fd, STDIN_FILENO);
	return fd;
}

int setredirectW(command * cmd, int num){
	int fd;
	fd = open(cmd->command_arr[num][cmd->sub_counter[num]-1], O_WRONLY|O_TRUNC);
	if(fd == -1){
		fd = open(cmd->command_arr[num][cmd->sub_counter[num]-1], O_WRONLY|O_CREAT, 0644);
		if(fd == -1){
			printf("Create file failed, Abort");
			return -1;
		}
	}
	--cmd->sub_counter[num];
	cmd->command_arr[num][cmd->sub_counter[num]] = nullptr;
	dup2(fd, STDOUT_FILENO);
	return fd;
}

void recoverR(int in){
	dup2(in, STDIN_FILENO);
}

void recoverW(int out){
	dup2(out, STDOUT_FILENO);
}


