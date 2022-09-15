#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include"BaseUser.h"

class Administrator: public BaseUser
{
public:
	Administrator(){}
	Administrator(string n, string p):BaseUser(n, p){}
	void ShowUsrs()const;
	virtual void ShowCommodities() const;	
	virtual void ShowOrders() const;
	void BanUsr()const;
};
#endif

