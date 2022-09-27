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
	friend bool myGreater(const char* str1, const char* str2);
private:
    UserEntry* usersFile;    
    OrderEntry* ordersFile;
	/*商品列表用链表表示*/
	CommodityEntry* onAuctionComms;
	CommodityEntry* removedComms;
	AuctionList* auctionList;
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
	void addCommodity( const char* seller , const char* name, 
	double price, int amount, const char*description);
	OrderEntry* addOrder(const char* commID, const char* buyerID, const char* sellerID,
	int amount, double unitPrice);
	void addUser(const char* name, const char* passwd);
	bool addAuctionInfo(const char* commID, const char* buyer, double unitPrice, int amount);
	bool beAuctioned(const char* commID);	
	void checkCommExpired();
    LogFlag matching(const char* name, const char* passwd) const;
	bool find(const char* name ) const;
	bool findComm(char* seller, const char* commID, CommodityEntry* commList) ;
	bool findUser(const char* userID) const;
	AuctionInfo* findUserInAucList(const char* bidder, const char* commID);
	void getID(const char*userName, char*userID)const;
	void modifyAuctionInfo(const char* bidder, const char* commID,int option);
	void modifyCommPrice(const char* commID , double newPrice);
	void modifyCommDesc(const char* commID, const char* newDescription);
	bool modifyCommState(const char*commID, int newState);
	void modifyUserAttr(const char* userID, const char* newInfo, int option);
	int modifyUserBal(const char* userID, double money);
	void modifyUserState(const char* userID);
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
	void showSellerComms(const char* sellerID);
	void showCommDetail(const char* commID);
	void showSpecificComms(char* name, int identity)const ;
	void showAllOrders()const;
	void showOrders(const char* userID, int identity)const;
	void showUserInfo(const char* userID) const;	
};

#endif