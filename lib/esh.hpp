#include <iostream>
#include <readline/readline.h>
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
	int count;
	char ** argument;
	char ** dir;
	int dir_count;
	char * work_dir;

	void start_config(){
		dir = (char **)malloc(0x20);
		char * buf = (char *)malloc(0x100);
		work_dir = getcwd(buf, 0x100);
		strcat(work_dir, "/");
		char * tmp = (char *)malloc(strlen(work_dir)+1);
		strcpy(tmp, work_dir);
		work_dir = tmp;
		dir[0] = work_dir;
		readlink("/proc/self/exe", buf, 0x100);
		tmp = buf + strlen(buf) - 3;
		tmp[0] = '\0';
		strcat(buf, "bin/");
		tmp = (char *)malloc(strlen(buf));
		strcpy(tmp, buf);
		dir[1] = tmp;
		strcpy(buf, getenv("HOME"));
		chdir(buf);
		free(buf);
		dir_count = 2;
	}

	bool read_command(){
		char * buf = (char *)malloc(0x100);
		char * path = getcwd(buf, 0x100);
		strcat(buf, " > \0");
		char * str = readline(buf);		//readline prompt setting : PATH_TO_HERE >
		if(str[0] == '\0'){
			return 0;
		}
		count = string2arr(str, &argument);	
		return 1;
	}

	void exec_command(){
		bool flag = inner_exec(argument, count);
		if(flag){
			return;
		}
		flag = outer_exec(argument, count, dir, dir_count);
		if(!flag){
			comd_nfount(argument[0]);
		}
	}

	void clear_space(){
		free(argument[0]);
		free(argument);
		return;
	}
}