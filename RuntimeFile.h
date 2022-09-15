#ifndef USER_H
#define USER_H
#include<string>
using namespace std;
#include"type.h"


typedef struct UserEntry
{
    
}UserEntry;

typedef struct CommodityEntry
{
    /* data */
}CommodityEntry;

typedef struct OrderEntry
{
    /* data */
}OrderEntry;

class RuntimeFile
{
private:
    UserEntry** usrsFile;
    CommodityEntry** commoditiesFile;
    OrderEntry** ordersFile;
	int usrIndex;
	int commIndex;
	int orderIndex;
    void ReadToUsrs();
	void ReadToComms();
	void ReadToOrders();
public:
    RuntimeFile();
    ~RuntimeFile();
	void AddUser(string name, string passwd);
    LogFlag matching(string name, string ) const;
	bool find(string name) const;
	void ShowUsrs()const;
	void ShowCommodities()const;
	void ShowOrders()const;
	bool modifyUsr();
	bool modifyComm();
	bool modifyOrder();
	void WriteUsrsFile()const;
	void WriteCommsFile()const;
	void WriteOrdersFile()const;
};


#endif