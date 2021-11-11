#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include "../config/config.hpp"
#include "inner_command.hpp"
#include "outer_command.hpp"

#ifndef _PIPE_REDIRECT_HPP_
#define _PIPE_REDIRECT_HPP_
	#include "pipe_redirect.hpp"
#endif

#ifndef _STRINGHANDLER_HPP_
#define _STRINGHANDLER_HPP_
	#include "../tools/stringHandler.hpp"
#endif

#ifndef _ERRORHANDLER_HPP_
#define _ERRORHANDLER_HPP_
	#include "../tools/errorHandler.hpp"
#endif

#ifndef _XARGS_HPP_
#define _XARGS_HPP_
	#include "xargs.hpp"
#endif

namespace esh{
	char ** dir;
	int dir_count;
	char * work_dir;
	command * cmd;
	int savein, saveout;
	int exec_count;

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
		// dir[2] = "/usr/bin/";
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
		using_history();
		char * str = readline(buf);		//readline prompt setting : PATH_TO_HERE >
		add_history(str);
		if(str[0] == '\0'){
			return 0;
		}
		cmd = new command(str);
		return 1;
	}

	bool exec_command(int num){
		int fd;
		bool error;
		if(cmd->redirectR(num)){		//redirect stdin to file
			if((fd = setredirectR(cmd, num)) == -1){
				return 0;
			}
		}
		if(cmd->redirectW(num)){	//redirect stdout to file
			if((fd = setredirectW(cmd, num)) == -1){
				return 0;
			}
		}
		if(!strcmp(cmd->command_arr[num][0], "xargs")){	//xargs command inner processing
			xargs_processing(cmd, num);
		}
		//check & execute the inner command if the inputed commands are in it
		if(inner_exec(cmd->command_arr[num], cmd->sub_counter[num], cmd->sub_status[num])){
			;
		}
		else if(!outer_exec(cmd->command_arr[num], cmd->sub_counter[num], dir, dir_count)){
			comd_nfount(cmd->command_arr[num][0]);
			error = 1;
		}
		if(cmd->redirectR(num)){		//recover stdin if it has been changed
			recoverR(savein);
		}
		if(cmd->redirectW(num)){	//recover stdout if it has been changed
			recoverW(saveout);
		}

		close(fd);
		return 1;
	}


	int rpipe(command * cmd, int num, int count, int prev_fd){
		int fd[2];
		pid_t pid_in, pid_out;
		pid_t prev_exec_pid;
		if(cmd->redirectR(num) && count != 0){
			//error info here
			//return
		}
		else if(cmd->redirectW(num)){
			if(count != 0){
				prev_exec_pid = fork();
				if(prev_exec_pid == 0){
					dup2(prev_fd, STDIN_FILENO);
					exec_command(num);
					cmd->sub_status[num] &= 0b111101;   //set redirect_write bit to 0
					exit(0);
				}
			}
			else{       //the sub cmd is the first one
				exec_command(num);
				cmd->sub_status[num] &= 0b111101;   //set redirect_write bit to 0
			}
		}
	
		if(pipe(fd)){                                   //not succeed to start pipe
			return -1;
		}
		else{                                           //succeed to start pipe
			pid_in = fork();                            //First redirect this command's output to pipe
			if(pid_in == 0){                            //And execute the 
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				if(count != 0){
					dup2(prev_fd, STDIN_FILENO);
				}
				exec_command(num);
				if(count != 0){
					close(prev_fd);
				}
				close(fd[1]);
				exit(0);
			}
			if(count != 0){
				close(prev_fd);
			}
			if(cmd->piped(num+1)){                      //If next command is in the pipe link
				close(fd[1]);
				count = rpipe(cmd, num+1, count+1, fd[0]);
			}
			else{                                       //If this is the last one in the pipe link
				cmd->sub_status[num+1] &= 0b111110;     //set redirect_read bit to 0 and execute it
				pid_out = fork();
				if(pid_out == 0){
					close(fd[1]);
					dup2(fd[0], STDIN_FILENO);
					exec_command(num+1);
					close(fd[0]);
					exit(0);
				}
				else{                                   //Wait until the lastest command finish its executing.
					close(fd[0]);
					close(fd[1]);
					waitpid(pid_out, NULL, 0);          
					count+=2;
					return count; 
				}
			}
			return count;
		}
	}


	void start_exec(){
		exec_count = 0;
		while(exec_count < cmd->comd_counter){
			if(!cmd->piped(exec_count)){	//no pipe
				exec_command(exec_count);
				++exec_count;
			}
			else{
				int tmp = rpipe(cmd, exec_count, 0, -1);
				exec_count += tmp;
			}
		}
	}

	void clear_space(){
		printf("\n");
		fflush(stdout);
		delete cmd;
		return;
	}
}