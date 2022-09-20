#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H

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

#endif