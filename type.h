#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H
/*商品状态*/
#define ON_AUCTION 1
#define REMOVED 0
/*用户状态*/
#define ACTIVE 1
#define INACTIVE 0
/*身份*/
#define BUYER 1
#define SELLER 2
#define ADMIN 1
#define USER 0
/*属性*/
#define USER_NAME 1
#define PHONE_NUMBER 2
#define ADDRESS 3
#define PASSWD 4

/*各属性所占空间大小*/
#define MAX_ID_SIZE 4
#define MAX_DATE_SIZE 20
#define MAX_COMM_NAME_SIZE 20
#define MAX_COMM_DESCRIPTION_SIZE 200
#define MAX_NAME_SIZE 10
#define MAX_PASSEWD_SIZE 20
#define MAX_PHONENUMBER_SIZE 20
#define MAX_ADDRESS_SIZE 40


typedef struct AuctionInfo
{
    char bidderID[MAX_ID_SIZE+1];
    double unitPrice;
    int amount;
    char date[MAX_DATE_SIZE+1];
    AuctionInfo* next;
}AuctionInfo;

typedef struct AuctionList
{
    char commID[MAX_ID_SIZE+1];
    char startDate[MAX_DATE_SIZE+1];
    int bidderNum;
    AuctionInfo* head;
    AuctionList* next;
}AuctionList;

typedef struct UserEntry
{
    double balance;
    int state;
    char id[MAX_ID_SIZE+1];  
    char passwd[MAX_PASSEWD_SIZE+1];
    char phone[MAX_PHONENUMBER_SIZE+1]; 
    char name[MAX_NAME_SIZE+1]; 
    char address[MAX_ADDRESS_SIZE+1]; 
}UserEntry;

typedef struct CommodityEntry
{
	char description[MAX_COMM_DESCRIPTION_SIZE+1];  
    int amount;
    int state;
    char id[MAX_ID_SIZE+1];
    char sellerID[MAX_ID_SIZE+1];
    char addedDate[MAX_DATE_SIZE+1];
    char name[MAX_COMM_NAME_SIZE+1];  
    double price;      
    CommodityEntry* next;
}CommodityEntry;

typedef struct OrderEntry
{
   char id[MAX_ID_SIZE+1];
    char commodityID[MAX_ID_SIZE+1];
    char sellerID[MAX_ID_SIZE+1];
    char buyerID[MAX_ID_SIZE+1];
    int amount;
    double unitPrice;    
    char date[MAX_DATE_SIZE+1]; 
}OrderEntry;


#endif