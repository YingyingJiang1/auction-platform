#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include"runtimeFile.h"

extern RuntimeFile file;
extern  char starStr[];
class Administrator
{
public:
	Administrator(){}
	Administrator(string n, string p){}
	void banUser()const;
	void unbanUser()const;
	void pullCommodity() const;
	void searchCommodities() const;
	void viewAllBannedUsers()const;
	void viewUsers()const;
	void viewCommodities() const;	
	void viewOrders() const;
};
#endif

