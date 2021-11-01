#include <stdlib.h>
#include "../tools/stringhandler.hpp"
void outer_exec(char * command, char * argv, int com_len){
    string2arr(argv, command, com_len);
}