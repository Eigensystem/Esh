#include <unistd.h>

#ifndef _ERRORHANDLER_HPP_
#define _ERRORHANDLER_HPP_
	#include "../tools/errorHandler.hpp"
#endif

#ifndef _STRINGHANDLER_HPP_
#define _STRINGHANDLER_HPP_
	#include "../tools/stringHandler.hpp"
#endif

void cd(char ** argument, int count){
	char * buf = (char *)malloc(0x100);
	char * path = getcwd(buf, 0x100);
	bool flag;
	if(count < 2){
		char * path = getenv("HOME");
		// printf("%s", path);
		chdir(path);
	}
	else if(count > 3){
		many_argu("cd");
	}
	else if(count == 2){
		char * fst_para = argument[1];
		if(fst_para[0] == '.' && fst_para[1] == '/'){
			strcat(path, fst_para+1);
			flag = chdir(path);
		}
		else if(fst_para[0] != '.' && fst_para[0] != '~' && fst_para[0] != '/'){
			strcat(path, "/");
			strcat(path, fst_para);
			flag = chdir(path);
		}
		else if(fst_para[0] == '~'){
			char * path = getenv("HOME");
			strcat(path, fst_para+1);
			flag = chdir(path);
		}
		else if(fst_para[0] == '.' && fst_para[1] == '.'){
			int len = strlen(path);
			for(int i = len-1; i >= 0; --i){
				if(path[i] == '/'){
					path[i] = '\0';
                    break;
				}
			}
			strcat(path, fst_para+2);
			if(path[0] == '\0'){
                flag = chdir("/");
            }
            else{
                flag = chdir(path);
            }
		}
		else if(fst_para[0] == '/'){
			flag = chdir(fst_para);
		}
		else{
			flag = chdir(fst_para);
		}
		if(flag){
			dir_nexist("cd", fst_para);
		}
	}
	else{
		char * fst_para = argument[1];
		char * scd_para = argument[2];
		if(!strcmp(fst_para, path)){
			argument[1] = argument[2];
			cd(argument, 2);
		}
		else{
			cd_argu(argument[1]);
		}
	}
	free(buf);

}