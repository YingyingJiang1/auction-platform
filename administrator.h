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
	void banUser()const; /* 封禁用户*/
	void unbanUser()const; /* 解封用户 */
	void pullCommodity() const; /* 下架商品 */
	void searchCommodities() const;/* 搜索商品 */ 
	void viewAllBannedUsers()const; /* 查看所有被封禁用户 */
	void viewUsers()const; /* 查看所有用户（包括封禁和未被封禁）*/
	void viewCommodities() const;	/* 查看所有商品 */
	void viewOrders() const;			/* 查看所有订单 */
};
#endif

