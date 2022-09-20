#ifndef USER_H
#define USER_H
#include"baseUser.h"
#define MAX_NAME_SIZE 10
#define MAX_PASSEWD_SIZE 20
#define MAX_PHONENUMBER_SIZE 20
#define MAX_ADDRESS_SIZE 40
class User: public BaseUser
{
private:
	double balance;
	string id;
	std::string phone;
	std::string address;
	CommodityEntry* releasedComm;
	int commSize;
public:
	User(){}
    User(std::string n, std::string p, int size);
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

