#ifndef STR_COMPARE_H
#define STR_COMPARE_H
#include<string>
using namespace std;
void assignment(const string, char* dest);
bool equal(const string , const char*);
bool equal(const char*, const char*);
bool checkID(char  ,string );
bool checkDigits(std::string str, int size);
bool checkStr(std::string str, int size);
bool checkNum();

#endif