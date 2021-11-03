#include <iostream>

void many_argu(const char * bin_name){
    printf("%s: too many arguments\n", bin_name);
}

void cd_argu(char * argu){
    printf("cd: string not in pwd: %s\n ", argu);
}

void cd_error(char * path){
    printf("cd: No such file or dictionary: %s\n", path);
}

void comd_nfount(char * bin_name){
    printf("esh: command not fount: %s\n", bin_name);
}