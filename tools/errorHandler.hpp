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
        printf("%s: cannot access to \'%s\': no such file or directory\n", command, path);
    }
    else if(!strcmp(command, "cd")){  
        printf("%s: No such directory: %s\n",command, path);
    }
    else{
        printf("%s: No such file or directory: %s\n",command, path);
    }
}

void is_dir_error(char * path){
    printf("cat: %s: is a directory\n", path);
}

void comd_nfount(char * bin_name){
    printf("esh: command not fount: %s\n", bin_name);
}

void ab_argu(const char * bin_name){
    printf("%s: argument absence\n", bin_name);
}

void nodir_error(const char * command, char * path){
    if(!strcmp(command, "touch")){
        printf("%s: can not create \"%s\": no such file or directory\n", command, path);
    }
    else{
        printf("%s: can not create directory \"%s\": no such file or directory\n", command, path);
    }
}

void file_exist(char * path){
    printf("mkdir: can not create directory \"%s\": file has existed\n", path);
}