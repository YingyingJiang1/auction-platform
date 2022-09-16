#ifndef BASEUSER_H
#define BASEUSER_H
#include"runtimeFile.h"
#include<iostream>
using namespace std;

class BaseUser
{
protected:
	string name;
    string passwd;	
public:
    BaseUser(){}
    BaseUser(string n, string p) : name(n), passwd(p){}
    ~BaseUser(){}
	virtual void viewCommodities() const = 0;
	void searchCommodities()const;
	void pullCommodity()const;
};


#endif