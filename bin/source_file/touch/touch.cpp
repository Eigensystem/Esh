#include <iostream>
#include <filesystem>
#include <fstream>
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
        ab_argu("touch");
    }
    else{
        for(int i = 1; i < argc; ++i){
            string filepath = argv[i];
            path file(argv[i]);
            file_data * data = filepath2filedata(argv[i]);
            if(data->dir_path == nullptr){
                ofstream file;
                file.open(filepath);
                file.close();
                continue;
            }
            path path(data->dir_path);
            if(!exists(path)){
                strcat(data->dir_path, "/");
                strcat(data->dir_path, data->file_name);
                nodir_error("touch", data->dir_path);
                continue;
            }
            else if(!is_directory(path)){
                strcat(data->dir_path, "/");
                strcat(data->dir_path, data->file_name);
                nodir_error("touch", data->dir_path);
                continue;
            }
            else if(exists(file)){
                strcat(data->dir_path, "/");
                strcat(data->dir_path, data->file_name);
                file_exist(data->dir_path);
                continue;
            }
            else{
                ofstream file;
                file.open(filepath);
                file.close();
                continue;
            }
        }
    }
    return 0;
}