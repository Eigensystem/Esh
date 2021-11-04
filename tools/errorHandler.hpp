#include <string.h>
#include <iostream>

void many_argu(const char * bin_name){
    printf("%s: too many arguments\n", bin_name);
}

void cd_argu(char * argu){
    printf("cd: string not in pwd: %s\n ", argu);
}

void dir_nexist(const char * command, char * path){
    if(!strcmp(command, "ls")){
        printf("%s: cannot access to \'%s\': no such file or directory", command, path);
    }
    else if(!strcmp(command, "cd")){  
        printf("%s: No such directory: %s\n",command, path);
    }
    else{
        printf("%s: No such file or directory: %s\n",command, path);
    }
}

void comd_nfount(char * bin_name){
    printf("esh: command not fount: %s\n", bin_name);
}