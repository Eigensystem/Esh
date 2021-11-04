#include <iostream>
#include <filesystem>
#include <unistd.h>
#ifndef __ERRORHANDLER_HPP_
#define __ERRORHANDLER_HPP_
    #include "../tools/errorHandler.hpp"
#endif

using namespace std;
using namespace std::filesystem;
bool showdir(char * dir, char * comd_dir){
    path path(dir);
    if(!exists(path)){
        dir_nexist("ls", comd_dir);
        return 0;
    }
    directory_entry entry(path);
    if(entry.status().type() != file_type::directory){
        printf(comd_dir);
        return 0;
    }
    directory_iterator list(path);
    for(auto & it:list){
        cout << it.path().filename() << endl;
    }
    return 1;
}