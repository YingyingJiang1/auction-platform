#ifndef RUNTIME_FILE
#define RUNTIME_FILE
#include<string>
using namespace std;
#include"type.h"
#include"fileEntry.h"
#include"strCompare.h"
#include<iostream>



class RuntimeFile
{
	friend class Administrator;
	friend class User;
private:
    UserEntry* usersFile;
    CommodityEntry* commoditiesFile;
    OrderEntry* ordersFile;
	int usersSize;
	int commSize;
	int orderSize;
	/*动态数组的大小*/
	int size;
    void readToUsers();
	void readToComms();
	void readToOrders();	
	void overflowProcess();
	void assignCurDate(char*);
	void assignID(char, char*, int);
public:
    RuntimeFile(int defaultSize = 100);
    ~RuntimeFile();		
	RuntimeFile operator = (RuntimeFile rFile);
	RuntimeFile(const RuntimeFile&);
	CommodityEntry* addCommodity( string &, double, int, string &, char*);
	void addUser(const string name, const string passwd);
    LogFlag matching(const string name, const string ) const;
	bool find(const string ) const;
	void showUsers()const;
	void showCommodities()const;
	void showOrders()const;
	void modifyUserInfo(int, string,string);
	void modifyUserBal(string, double);
	bool modifyComm();
	bool modifyOrder();
	void modifyUserState();
	void writeUsersFile(const char*)const;
	void writeCommsFile(const char*)const;
	void writeOrdersFile(const char*)const;
};


#endif