#ifndef USER_H
#define USER_H
#include"runtimeFile.h"

extern RuntimeFile file;
class User
{
private:
	char name[MAX_NAME_SIZE+1];
	char userID[MAX_ID_SIZE+1];
public:
	User(){}
    User(const char* nameInputed);
	void auction();	
	void modifyAuction();
	void modifyCommInfo()const;	
	void modifyUserInfo();
	void pullCommodity();
	void releaseCommodity();
	void searchCommodity()const;
	void  topUp();
	void viewUserInfo()const;
	void viewAllComms( ) const;
	void viewAllAuctions();
	void viewCommDetail() const;
	void viewBuyerOrders() const;
	void viewSellerOrders() const ;
	void viewReleasedComm() const;
};
#endif

