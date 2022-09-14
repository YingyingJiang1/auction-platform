#ifndef USER
#define USER
#include"BaseUser.h"

class User: public BaseUser
{
private:
	double balance;
	string phone;
	string address;
public:
    User(string n, string p): BaseUser(n, p)
    {
        balance = 0.0;
    }
	void ReleaseCommodity()const;
	void modifyCommInfo()const;
	void auction();
	void ShowUsrInfo()const;
    virtual void ShowCommodities() const ;	
	virtual void ShowOrders() const ;
	void modifyUsrInfo();
};
#endif

