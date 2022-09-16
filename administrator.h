#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include"baseUser.h"

class Administrator: public BaseUser
{
public:
	Administrator(){}
	Administrator(string n, string p):BaseUser(n, p){}
	void viewUsrs()const;
	virtual void viewCommodities() const;	
	virtual void viewOrders() const;
	void banUsr()const;
};
#endif

