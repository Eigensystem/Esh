#include <iostream>

void SH_INThandler(int signum){
    char * buf = (char *)malloc(0x100);
    char * work_dir = getcwd(buf, 0x100);
    strcat(work_dir, " > ");
    printf("\n\n%s", work_dir);
    return;
}