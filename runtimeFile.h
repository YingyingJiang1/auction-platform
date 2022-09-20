#ifndef RUNTIME_FILE
#define RUNTIME_FILE
#include<string>
using namespace std;
#include"type.h"
#include<iostream>



class RuntimeFile
{
private:
    UserEntry* usrsFile;
    CommodityEntry* commoditiesFile;
    OrderEntry* ordersFile;
	int usrsSize;
	int commSize;
	int orderSize;
	/*动态数组的大小*/
	int size;
    void readToUsrs();
	void readToComms();
	void readToOrders();	
	bool equal(const string, const char* )const ;
	void overflowProcess();
	/*将src赋值给dest*/
	void assignment(const string src, char* dest){
		int i = 0;
		for(; src[i] != 0; ++i)
			dest[i] = src[i];
		dest[i] = 0;
	}
	void assignID(char*);
public:
    RuntimeFile(int defaultSize = 100);
    ~RuntimeFile();
	RuntimeFile operator = (RuntimeFile rFile);
	RuntimeFile(const RuntimeFile&);
	void addUser(const string name, const string passwd);
    LogFlag matching(const string name, const string ) const;
	bool find(const string ) const;
	void getUsrInfo(const string, UsrInfo*) const;
	void showUsrs()const;
	void showCommodities()const;
	void showOrders()const;
	void modifyUsrInfo(int, string,string);
	void modifyUsrBal(string, double);
	bool modifyComm();
	bool modifyOrder();
	void modifyUsrState();
	void writeUsrsFile(const char*)const;
	void writeCommsFile(const char*)const;
	void writeOrdersFile(const char*)const;
};


#endif