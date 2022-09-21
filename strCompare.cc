#include<string>
#include<iostream>
using namespace std;
#define ID_SIZE 4
#define HUGE_NUM 0X7FFFFFFF
/*将src赋值给dest*/
void assignment(const string src, char* dest){
    int i = 0;
    for(; src[i] != 0; ++i)
        dest[i] = src[i];
    dest[i] = 0;
}

bool equal(const string str1, const char* str2)
{
    int i = 0;
    for(; str1[i] != 0 && str2[i] != 0; ++i)
        if(str1[i] != str2[i])
            return false;
    if(str1[i] == 0 && str2[i] == 0)
        return true;
    return false;
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

bool checkID(char category ,string userID)
{
    if(userID.length() != ID_SIZE || userID[0] != category)
        return false;
    for(int i = 1; i < ID_SIZE; ++i)
        if(!isdigit(userID[i]))
            return false;
    return true;
}

/*检查字符串是否由数字组成且符合长度要求*/
bool checkDigits(std::string str, int size)
{
    if(str.length() > size || str.length() == 0)
        return false;
    for(int i = 0; i < str.length(); ++i)
        if(!isdigit(str[i]))
            return false;
    return true;
}

/*检查字符串是否不包含“,”且符合长度要求*/
bool checkStr(std::string str, int size)
{
    if(str.length() > size || str.length() == 0)
        return false;
    for(int i = 0; i < str.length(); ++i)
        if(str[i] == ',')
            return false;
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
    return true;
}