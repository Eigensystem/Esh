#include <unistd.h>
#include "../tools/errorHandler.hpp"
#include "../tools/stringhandler.hpp"

void cd(char * argv, char * command, int com_len){
    char * buf = (char *)malloc(0x100);
    bool flag;
    if(argv == nullptr){
		char * path = getenv("HOME");
		// printf("%s", path);
		chdir(path);
	}
	else if(argv != nullptr){
		char * tmp = strtok(argv, " ");
		argv = crossfront(argv + strlen(tmp) + 1, ' ');
		if(argv - command < com_len){
			many_argu("cd");
		}
		if(tmp[0] == '.' && tmp[1] == '/'){
			char * path = getcwd(buf, 0x100);
			strcat(path, tmp+1);
			flag = chdir(path);
		}
        else if(tmp[0] != '.' && tmp[0] != '~' && tmp[0] != '/'){
            char * path = getcwd(buf, 0x100);
			strcat(path, "/");
            strcat(path, tmp);
			flag = chdir(path);
        }
		else if(tmp[0] == '~' && tmp[1] == '/'){
			char * path = getenv("HOME");
			strcat(path, tmp+1);
			flag = chdir(path);
		}
        else if(tmp[0] == '.' && tmp[1] == '.'){
            char * path = getcwd(buf, 0x100);
            int len = strlen(path);
            for(int i = len-1; i >= 0; --i){
                if(path[i] == '/'){
                    path[i] = '\0';
                    break;
                }
            }
            strcat(path, tmp+2);
            flag = chdir(path);
        }
        else if(tmp[0] == '/'){
            flag = chdir(tmp);
        }

        if(flag){
            cd_error(tmp);
        }
	}
    free(buf);

}