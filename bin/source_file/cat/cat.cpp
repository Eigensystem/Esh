#include "cat.hpp"
#include <unistd.h>
#include <filesystem>
#ifndef __STRINGHANDLER_HPP_
#define __STRINGHANDLER_HPP_
    #include "../../../tools/stringHandler.hpp"
#endif

#ifndef __ERRORHANDLER_HPP_
#define __ERRORHANDLER_HPP_
    #include "../../../tools/errorHandler.hpp"
#endif

using namespace std;
using namespace std::filesystem;

int main(int argc, char * argv[]){
	char * buf = (char *)malloc(0x100);
	char * origin = getcwd(buf, 0x100);
	char * work_dir;

	if(argc == 1){
		string str = "start";
		while(1){
			getline(cin, str);
			if(cin.eof()){
				break;
			}
			cout << str << endl;
		}
	}
	else{
		for(int i = 1; i < argc; ++i){
			path file(argv[i]);
			if(!exists(file)){
				dir_nexist("cat", argv[i]);
				return 0;
			}
			if(is_directory(file)){
				is_dir_error(argv[i]);
				return 0;
			}
			file_data * data= filepath2filedata(argv[i]);
			if(data->dir_path != nullptr){
				chdir(data->dir_path);
			}
			showfile(data->file_name);
		}
		chdir(origin);
	}
}