#ifndef USER_H
#define USER_H
#include"baseUser.h"

class User: public BaseUser
{
private:
	double balance;
	string phone;
	string address;
public:
	User(){}
    User(string n, string p): BaseUser(n, p)
    {
        balance = 0.0;
    }
	void auction();
	void buy();
	void releaseCommodity()const;
	void modifyCommInfo()const;	
	void  topUp();
	void viewUsrInfo()const;
    virtual void viewCommodities() const ;	
	void viewCommDetail() const;
	void viewBuyerOrders() const;
	void viewSellerOrders() const ;
	void viewReleasedComm() const;
	void modifyUsrInfo();
};
#endif

