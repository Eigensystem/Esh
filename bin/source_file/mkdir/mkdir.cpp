#include <iostream>
#include <filesystem>
#ifndef _ERRORHANDLER_HPP_
#define _ERRORHANDLER_HPP_
    #include "../../../tools/errorHandler.hpp"
#endif

#ifndef _STRINGHANDLER_HPP
#define _STRINGHANDLER_HPP_
    #include "../../../tools/stringHandler.hpp"
#endif

using namespace std;
using namespace std::filesystem;

int main(int argc, char * argv[]){
    if(argc == 1){
        ab_argu("mkdir");
    }
    else{
        for(int i = 1; i < argc; ++i){
            path file(argv[i]);
            file_data * data = filepath2filedata(argv[i]);
            if(data->dir_path == nullptr){
                create_directory(file);
                continue;
            }
            path path(data->dir_path);
            if(!exists(path)){
                strcat(data->dir_path, "/");
                strcat(data->dir_path, data->file_name);
                nodir_error("mkdir", data->dir_path);
                continue;
            }
            else if(!is_directory(path)){
                strcat(data->dir_path, "/");
                strcat(data->dir_path, data->file_name);
                nodir_error("mkdir", data->dir_path);
                continue;
            }
            else if(exists(file)){
                continue;
            }
            else{
                create_directory(file);
                continue;
            }
        }
    }
}