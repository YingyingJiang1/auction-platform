#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H
#define ID_SIZE 4
typedef struct UserEntry
{
    double balance;
    int state;
    char id[5];  
    char passwd[21];
    char phone[21]; 
    char name[11]; 
    char address[41]; 
}UserEntry;

typedef struct CommodityEntry
{
	char description[201];  
    int number;
    int state;
    char id[5];
    char sellerID[5];
    char addedDate[11];
    char name[21];  
    double price;  
}CommodityEntry;

typedef struct OrderEntry
{
   char id[5];
    char commodityID[5];
    char sellerID[5];
    char buyerID[5];
    int number;
    double unitPrice;    
    char date[11]; 
}OrderEntry;

#define ON_AUCTION 1
#define REMOVED 0

#define MAX_COMM_NAME_SIZE 20
#define MAX_COMM_DESCRIPTION_SIZE 200
#define MAX_NAME_SIZE 10
#define MAX_PASSEWD_SIZE 20
#define MAX_PHONENUMBER_SIZE 20
#define MAX_ADDRESS_SIZE 40
#endif