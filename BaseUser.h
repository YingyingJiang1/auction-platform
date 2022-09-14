#ifndef BASEUSER_H
#define BASEUSER_H
#include"RuntimeFile.h"
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
	void Logout();
	virtual void ShowCommodities() const = 0;
	void SearchCommodities()const;
	void PullCommodity()const;
	virtual void ShowOrders() const = 0;
};


#endif