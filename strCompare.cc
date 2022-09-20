#include<string>
using namespace std;

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