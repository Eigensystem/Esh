#include <filesystem>
#include <unistd.h>

#ifndef _LS_HPP_
#define _LS_HPP_
    #include "ls.hpp"
#endif

using namespace std;
using namespace std::filesystem;
int main(int argc, char * argv[]){
    char * buf = (char *)malloc(0x100);
    char * work_dir;
    if(argc == 1){
        work_dir = getcwd(buf, 0x100);
        showdir(work_dir, work_dir);
    }
    else if(argc == 2){
        char * argument1 = argv[1];
        char * origin = getcwd(buf, 0x100);
        chdir(argument1);
        work_dir = getcwd(buf, 0x100);
        showdir(work_dir, argument1);
        chdir(origin);
    }
    else{
        char * origin = getcwd(buf, 0x100);
        for(int i = 1; i < argc; ++i){
            chdir(argv[i]);
            work_dir = getcwd(buf, 0x100);
            printf("%s:\n", argv[i]);
            showdir(work_dir, argv[i]);
        }
        chdir(origin);
    }
}