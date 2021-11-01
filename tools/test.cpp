#include <iostream>
#include <string.h>
#include <stdlib.h>
int main(){
    char * str = malloc(0x20);
    str = "hello  hello hello";
    char ch = ' ';
    int length = strlen(str);
	int count = 0;
	bool flag = 0;
	for(int i = 0; i < length; ++i){
		if(str[i] == ch && flag == 0){
			++count;
			flag = 1;
		}
		else if(str[i] != ch && flag == 1){
			flag = 0;
		}
	}
    printf("%d", count);
}