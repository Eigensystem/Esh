#include <iostream>
#include <stdlib.h>

void echo(char ** argv, int count){
	for(int i = 1; i < count; ++i){
		printf("%s ", argv[i]);
	}
	printf("\n");
}

void sh_exit(char ** argv, int count){
	free(argv[0]);
	free(argv);
	exit(0);
}