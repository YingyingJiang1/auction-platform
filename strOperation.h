#ifndef STR_COMPARE_H
#define STR_COMPARE_H
#include<string>
using namespace std;
void assignment(const char* src, char* dest);
bool equal(const char*, const char*);
bool checkAlnum(char* str, int size);
bool checkNum();
bool myGreater(const char* str1, const char* str2);
bool checkID(char category ,char* userID);
bool checkDigits(char* str, int size);
bool checkStr(char* str, int size);


#endif