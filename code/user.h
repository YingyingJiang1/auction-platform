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
	void auction();	/* 竞拍商品 */
	void modifyAuction(); /* 修改竞拍信息(可取消竞拍) */
	void modifyCommInfo()const;	 /* 修改发布的商品的信息 */
	void modifyPasswd() const; /* 修改密码 */ 
	void modifyUserInfo();	/* 修改用户信息 */
	void pullCommodity();	/* 下架发布的商品 */
	void putawayComm()const;	/* 重新发布已下架的商品*/
	void releaseCommodity();	/* 发布商品 */
	void searchCommodity()const;	/* 搜索商品 */
	void  topUp();	/* 充值 */
	void viewUserInfo()const;	/* 查看用户信息 */
	void viewAllComms( ) const;	/* 查看所有在拍的商品*/
	void viewAllAuctions();	/* 查看所有竞拍信息 */
	void viewCommDetail() const; /* 查看商品详细信息 */
	void viewBuyerOrders() const;	/* 查看买家订单 */
	void viewSellerOrders() const ;	/* 查看卖家订单 */
	void viewReleasedComm() const;	/* 查看本用户发布的商品*/
};
#endif

