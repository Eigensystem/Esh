#include <iostream>
#include <readline/readline.h>
#include <fcntl.h>
#include "../config/config.hpp"
#include "inner_command.hpp"
#include "outer_command.hpp"

#ifndef _STRINGHANDLER_HPP_
#define _STRINGHANDLER_HPP_
    #include "../tools/stringHandler.hpp"
#endif

#ifndef _ERRORHANDLER_HPP_
#define _ERRORHANDLER_HPP_
    #include "../tools/errorHandler.hpp"
#endif

namespace esh{
	char ** dir;
	int dir_count;
	char * work_dir;
	command * cmd;
	int savein, saveout;

	void start_config(){
		dir = (char **)malloc(0x20);
		char * buf = (char *)malloc(0x100);
		readlink("/proc/self/exe", buf, 0x100);
		char * tmp = buf + strlen(buf) - 3;
		tmp[0] = '\0';
		strcat(buf, "bin/");
		tmp = (char *)malloc(strlen(buf));
		strcpy(tmp, buf);
		dir[0] = tmp;
		dir[1] = nullptr;
		strcpy(buf, getenv("HOME"));
		chdir(buf);
		free(buf);
		dir_count = 2;
		savein = dup(STDIN_FILENO);
		saveout = dup(STDOUT_FILENO);
	}

	bool read_command(){
		char * buf = (char *)malloc(0x100);
		char * work_dir = getcwd(buf, 0x100);
		if(dir[1] != nullptr){
			free(dir[1]);
		}
		dir[1] = work_dir;
		strcat(buf, " > \0");
		char * str = readline(buf);		//readline prompt setting : PATH_TO_HERE >
		if(str[0] == '\0'){
			return 0;
		}
		cmd = new command(str);
		return 1;
	}

	bool exec_command(int num){
		int fd;
		if(cmd->sub_status[num] & 0b1){
			fd = open(cmd->command_arr[num][cmd->sub_counter[num]-1], O_RDONLY);
			if(fd == -1){
				dir_nexist("zsh", cmd->command_arr[num][cmd->sub_counter[num]-1]);
				return 0;
			}
			--cmd->sub_counter[num];
			dup2(fd, STDIN_FILENO);
		}
		if(cmd->sub_status[num] & 0b10){
			fd = open(cmd->command_arr[num][cmd->sub_counter[num]-1], O_WRONLY|O_TRUNC);
			if(fd == -1){
				fd = open(cmd->command_arr[num][cmd->sub_counter[num]-1], O_WRONLY|O_CREAT, 0644);
			}
			std::cout << fd << std::endl;
			--cmd->sub_counter[num];
			cmd->command_arr[num][cmd->sub_counter[num]] = nullptr;
			dup2(fd, STDOUT_FILENO);
		}
		if(inner_exec(cmd->command_arr[num], cmd->sub_counter[num], cmd->sub_status[num])){
			if(cmd->sub_status[num] & 0b1){
				dup2(savein, STDIN_FILENO);
			}
			if(cmd->sub_status[num] & 0b10){
				dup2(saveout, STDOUT_FILENO);
			}
			close(fd);
			return 1;
		}
		if(!outer_exec(cmd->command_arr[num], cmd->sub_counter[num], dir, dir_count)){
			comd_nfount(cmd->command_arr[num][0]);
		}
		if(cmd->sub_status[num] & 0b1){
			dup2(savein, STDIN_FILENO);
		}
		if(cmd->sub_status[num] & 0b10){
			dup2(saveout, STDOUT_FILENO);
		}
		close(fd);
		return 1;
	}

	void clear_space(){
		delete cmd;
		return;
	}
}