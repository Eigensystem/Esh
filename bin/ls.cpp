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
    char * work_dir = getcwd(buf, 0x100);
    if(argc == 1){
        showdir(work_dir, work_dir);
    }
}