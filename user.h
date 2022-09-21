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
	int size;
	int commSize;
	void overflowProcess();
	int getCommIndex(string &id) const
	{
		int i = 0;
		for(; i < commSize; ++i)
        {
            if(equal(id, releasedComms[i]->id))
                break;
        }
		return i;
	}
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
	void viewCommDetail() const;
	void viewBuyerOrders() const;
	void viewSellerOrders() const ;
	void viewReleasedComm() const;
};
#endif

