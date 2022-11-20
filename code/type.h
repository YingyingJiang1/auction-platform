#ifndef TYPE_H
#define TYPE_H
/* 商品的拍卖时长，以秒为单位 */
#define AUCTION_DURATION 24*60*60
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
#define COMM_PRICE 1
#define COMM_DESCRIPTION 2
#define COMM_AMOUNT 3

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
    char bidderID[MAX_ID_SIZE+1];   /* 竞拍者ID */
    double unitPrice;   /* 竞拍单价 */
    int amount; /* 竞拍数量 */
    char date[MAX_DATE_SIZE+1]; /* 该条竞拍信息创建时间 */
    AuctionInfo* next;  /* 用于指向下一条竞拍信息 */
}AuctionInfo;

typedef struct AuctionList
{
    char commID[MAX_ID_SIZE+1]; /* 被竞拍的商品ID */
    char startDate[MAX_DATE_SIZE+1];    /* 该商品的发布时间，用于检查商品竞拍到期 */
    int bidderNum;  /* 竞拍者的数量 */
    AuctionInfo* head;  /* 用于指向本商品的竞拍信息链表 */
    AuctionList* next;  /* 用于指向竞拍列表的下一个节点 */
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