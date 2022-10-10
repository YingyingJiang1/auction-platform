#ifndef RUNTIME_FILE
#define RUNTIME_FILE
using namespace std;
#include"type.h"
#include"strOperation.h"
#include"promptMacro.h"
#include<iostream>
#define HUGE_NUM 0X7FFFFFFF

enum LogFlag{NO_USER= 1, WRONG_PASSWD,LOGIN_SUCCEED, BANNED};
extern char starStr[];

class RuntimeFile
{
private:
    UserEntry* usersFile;    
    OrderEntry* ordersFile;
	/*商品列表用链表表示*/
	CommodityEntry* onAuctionComms;
	CommodityEntry* removedComms;
	AuctionList* auctionList;
	AuctionList* listTail;
	/*存储上一次搜索到的位置,对于连续搜索同一个商品ID的情况
	只需要遍历链表一次就可以实现*/
	CommodityEntry* previous;
	int usersSize;
	int orderSize;
	int commAmount;
	/*动态数组的大小*/
	int size;
	int maxUserSize;	
	void assignCurDate(char* date);
	void assignID(char, char*, int);
	void checkAuctionList();
	bool checkDateExpired(const char* startDate);
	void endAuction(const AuctionList* ptr);
	void findCommID(const char* commID, CommodityEntry* commList);
	template<typename T>
	void freeList(T* head);
	int getIndex(const char* id) const;		
	void overflowProcess();	
	void printSellerComms(CommodityEntry* commList, const char* sellerID, bool& printed) const;
	void printComms(CommodityEntry* commList, bool& printed) const;
	void readToAucList();
    void readToUsers();
	void readToComms();
	void readToOrders();	
	AuctionInfo* sortList(AuctionInfo* head,AuctionInfo* ptrInfo);
	void writeUsersFile(const char*);
	void writeCommsFile(const char*);
	void writeOrdersFile(const char*);
	void writeAuctionFile(const char* mode);
public:
    RuntimeFile(int defaultSize = 200000);
    ~RuntimeFile();		
	RuntimeFile operator = (RuntimeFile rFile);
	RuntimeFile(const RuntimeFile&);
	void addCommodity( const char* seller , const char* name, double price, int amount, const char*description);/* 新增一个商品 */
	OrderEntry* addOrder(const char* commID, const char* buyerID, const char* sellerID,int amount, double unitPrice);	/* 新增一条订单 */
	void addUser(const char* name, const char* passwd); 	/* 新增一个用户 */
	bool addAuctionInfo(const char* commID, const char* buyer, double unitPrice, int amount); /* 新增一条竞拍信息 */
	bool beAuctioned(const char* commID);	/* 判度商品ID为commID的商品是否有用户参与竞拍 */
	void checkCommExpired();	/* 检查商品拍卖到期情况 */
    LogFlag matching(const char* name, const char* passwd) const;	/* 判断用户名和密码是否匹配 */
	bool find(const char* name ) const;		/* 判断用户名为name的用户是否存在 */
	/*在commList中寻找ID为commID的商品，如果找到把该商品的卖家ID赋给seller,然后返回true*/
	bool findComm(char* seller, const char* commID, CommodityEntry* commList) ;
	bool findUser(const char* userID) const;	/* 判断是否存在用户ID为userID的用户 */
	AuctionInfo* findUserInAucList(const char* bidder, const char* commID);
	void getUserID(const char*userName, char*userID)const;
	void modifyAuctionInfo(const char* bidder, const char* commID,int option);
	void modifyCommAmount(const char* commID, int amount);
	void modifyCommPrice(const char* commID , double newPrice);
	void modifyCommDesc(const char* commID, const char* newDescription);
	bool modifyCommState(const char*commID, int newState);
	void modifyUserAttr(const char* userID, const char* newInfo, int option);
	int modifyUserBal(const char* userID, double money);
	bool modifyUserState(const char* userID, int newState);
	CommodityEntry* onAuctionCommList(){
		return onAuctionComms;
	}
	CommodityEntry* removedCommList()
	{
		return removedComms;
	}
	void showAllUsers()const;
	void showAllComms(int identity)const;
	void showAuctions(char* bidder) const;
	void showInactiveUsers()const;
	void showSellerComms(const char* sellerID);
	void showCommDetail(const char* commID);
	void showSpecificComms(char* name, int identity)const ;
	void showAllOrders()const;
	void showOrders(const char* userID, int identity)const;
	void showUserInfo(const char* userID) const;	
};

#endif