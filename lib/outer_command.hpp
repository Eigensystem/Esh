#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#ifndef _STRINGHANDLER_HPP_
#define _STRINGHANDLER_HPP_
    #include "../tools/stringHandler.hpp"
#endif


bool outer_exec(char ** argument, int count, char ** dir, int dir_count){
    struct stat *buf = (struct stat *)malloc(sizeof(struct stat));
    char * path = (char *)malloc(0x100);
    for(int i = 0; i < dir_count; ++i){
        strcpy(path, dir[i]);
        strcat(path, argument[0]);
        printf("%s", path);
        bool flag = stat(path, buf);
        if(flag){
            continue;
        }
        else{
            int pid = fork();
            if(pid == 0){   //child thread
                execvp(path, argument);
                exit(0);
            }
            else{       //father thread
                waitpid(pid, NULL, 0);
            }
            free(buf);
            return 1;
        }
    }
    free(buf);
    return 0;
}