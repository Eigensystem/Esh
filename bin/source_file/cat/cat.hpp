#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

int showfile(char * filename){
    char tmp[0x110] = "./";
    filename = strcat(tmp, filename);
    ifstream file(filename);
    string str;
    while(file.good()){
        getline(file, str);
        cout << str << endl;
    }
    return 0;
}