#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include"runtimeFile.h"

extern RuntimeFile file;
extern string starStr;
class Administrator
{
public:
	Administrator(){}
	Administrator(string n, string p){}
	void banUser()const;
	void pullCommodity() const;
	void searchCommodities() const;
	void viewUsers()const;
	virtual void viewCommodities() const;	
	virtual void viewOrders() const;
};
#endif

