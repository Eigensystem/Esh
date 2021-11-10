#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <vector>
#include <algorithm>
#ifndef __ERRORHANDLER_HPP_
#define __ERRORHANDLER_HPP_
    #include "../../../tools/errorHandler.hpp"
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
    vector<string> files;
    for(auto & it:list){
        string filename = it.path().filename();
        filename = filename.substr(0, filename.length());
        if(filename[0] == '.'){
            continue;
        }
        files.push_back(filename);
        // cout << filename << endl;
    }
    sort(files.begin(), files.end());
    int size = files.size();
    for(int i = 0; i < size; ++i){
        cout << files[i].c_str() << endl;
    }
    cout << endl;
    return 1;
}