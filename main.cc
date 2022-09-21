#include"runtimeFile.h"
#include<fcntl.h>
#include<unistd.h>
RuntimeFile file;
void mainIntf(RuntimeFile*);
int main(int argc, char** argv)
{
    int fd;
    if(argc == 2)
    {
        close(0);
        fd = open(argv[argc-1], O_RDONLY);  
    }
   
    int seq;
    mainIntf(&file);
    if(argc == 2)
        close(fd);
    return 0;
}



