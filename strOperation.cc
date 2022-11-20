#include<iostream>
using namespace std;
#define ID_SIZE 4
#define HUGE_NUM 0X7FFFFFFF

/*将src赋值给dest*/
void assignment(const char* src, char* dest){
    int i = 0;
    for(; src[i] != 0; ++i)
        dest[i] = src[i];
    dest[i] = 0;
}

bool equal(const char* str1, const char* str2)
{
    int i = 0;
    for(; str1[i] != 0 && str2[i] != 0; ++i)
        if(str1[i] != str2[i])
            return false;
    if(str1[i] == 0 && str2[i] == 0)
        return true;
    return false;
}

/*由于字符串输入采用fgets, 该函数会读取换行符，所以需要手动将换行符去掉；
如果输入的字符数量超过fgets可以读取的最大数量，那么需要将缓冲区中剩余的字符清空*/
inline void cleanBuffer(char* str)
{
    bool needClean = true;
    for(int i = 0; str[i] != 0; ++i)
    {
        if(str[i] == '\n')
        {
            needClean = false;
            str[i] = 0;
            break;
        }        
    }
    if(needClean)
        cin.ignore(HUGE_NUM, '\n');
}

/*判断字符串是否只包含数字和英文字母，且符合长度*/
bool checkAlnum(char* str, int size)
{
    
    cleanBuffer(str);
    if(str[0] == 0)
        return false;
    for(int i = 0; str[i] != 0; ++i)
    {                  
        if(!isalnum(str[i]))
            return false;
    }
    return true;
}

bool checkID(char category ,char* userID)
{    
    cleanBuffer(userID);

    if(0 == userID[0] || userID[0] != category)
        return false;
    for(int i = 1; i < ID_SIZE; ++i)
        if(!isdigit(userID[i]))
             return false;
    return true;
}

/*检查字符串是否由数字组成且符合长度要求*/
bool checkDigits(char* str, int size)
{    
    cleanBuffer(str);

    if(0 == str[0])
        return false;
    for(int i = 0; str[i] != 0; ++i)
    {
        
        if(!isdigit(str[i]))
            return false;
    }     
    return true;
}

/*检查字符串是否不包含“,”且符合长度要求*/
bool checkStr(char* str, int size)
{
    cleanBuffer(str);

    if(0 == str[0] )
        return false;
    for(int i = 0; str[i] != 0; ++i)
    {
       if(str[i] == ',')
            return false;
    }   
    return true;
}

/*检查操作编号和数值型数据输入，只有输入后面紧跟回车符是
合法输入*/
bool checkNum()
{
    char ch = getc(stdin);
    ungetc(ch, stdin);
    if(cin.fail() || ch != '\n')
    {
        cin.clear();
        cin.ignore(HUGE_NUM, '\n');
        return false;
    }
    cin.ignore(HUGE_NUM, '\n');
    return true;
}

ostream& operator <<(ostream& os, const char* str)
{
    for(int  i = 0; str[i] != 0; ++i)
        os << str[i];
    return os;
}

bool myGreater(const char* str1, const char* str2)
{
    int i = 0;
    for(; str1[i] != 0 && str2[i] != 0; ++i)
    {
        if(str1[i] > str2[i])
            return true;
        else if(str1[i] < str2[i])
            return false;
    }
    if(str1[i] != 0)
        return true;
    return false;
}