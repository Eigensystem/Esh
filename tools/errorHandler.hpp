#include <iostream>

void many_argu(const char * bin_name){
    printf("%s: too many arguments\n", bin_name);
}

void cd_argu(char * argu){
    printf("cd: string not in pwd: %s", argu);
}