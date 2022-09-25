#include"runtimeFile.h"
#include<fcntl.h>
#include<unistd.h>
using namespace std;
RuntimeFile file;
void mainIntf();
int main(int argc, char** argv)
{
    cout << starStr << endl;
    cout << "请阅读以下注意事项：" << endl;
    cout << "   1.输入操作编号和数值时，不要在您输入的中间或者最后添加空格，否则视该输入为不合法输入" << endl;
    cout << "   2.如果您输入的字符串的长度超过了规定长度，系统将会截取规定长度的字符串作为您的最终输入，\n"
    "超出规定长度的部分将会被忽略，所以请控制您输入的字符串的长度" << endl;
    cout << "   3.任何包含 ',' 的输入都会被视为不合法输入" << endl;
    cout << starStr << endl;

    int fd;
    if(argc == 2)
    {
        close(0);
        fd = open(argv[argc-1], O_RDONLY);  
    }
   
    int seq;
    mainIntf();
    if(argc == 2)
        close(fd);
    return 0;
}



