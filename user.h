#ifndef USER_H
#define USER_H
#include"fileEntry.h"
#include"runtimeFile.h"
#include"strCompare.h"
#include"macro.h"

#define HUGE_NUM 0X7FFFFFFF

extern RuntimeFile file;
class User
{
private:
	UserEntry* userInfo;
	CommodityEntry** releasedComms;
	OrderEntry** buyOrder;
	OrderEntry** sellOrder;
	int size;
	int commSize;
	int buySize;
	int sellSize;
	void overflowProcess();
	int getCommIndex(string &id) const;
public:
	User(){}
    User(const std::string,int defaultSize = 20000);
	~User(){
		delete [] releasedComms;
	}
	void auction();
	void buy();
	void modifyCommInfo()const;	
	void modifyUserInfo();
	void pullCommodity();
	void releaseCommodity();
	void searchCommodity()const;
	void  topUp();
	void viewUserInfo()const;
	void viewCommDetail() const;
	void viewBuyerOrders() const;
	void viewSellerOrders() const ;
	void viewReleasedComm() const;
};
#endif

