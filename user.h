#ifndef USER_H
#define USER_H
#include"fileEntry.h"
#include"runtimeFile.h"
#include"strCompare.h"
#define HUGE_NUM 0X7FFFFFFF
#define MAX_COMM_NAME_SIZE 20
#define MAX_COMM_DESCRIPTION_SIZE 200
#define MAX_NAME_SIZE 10
#define MAX_PASSEWD_SIZE 20
#define MAX_PHONENUMBER_SIZE 20
#define MAX_ADDRESS_SIZE 40

extern RuntimeFile file;
class User
{
private:
	UserEntry* userInfo;
	CommodityEntry** releasedComms;
	int size;
	int commSize;
	void overflowProcess();
public:
	User(){}
    User(const std::string,int defaultSize = 200);
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
    void viewCommodities() const ;	
	void viewCommDetail() const;
	void viewBuyerOrders() const;
	void viewSellerOrders() const ;
	void viewReleasedComm() const;
};
#endif

