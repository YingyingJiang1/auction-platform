#include"runtimeFile.h"
#include<fstream>
#include<cstdio>
#include<ctime>
#define ID_SIZE 4
#define ON_AUCTION 1
#define REMOVED 0
string starStr = "***************************************************************************************************************";

RuntimeFile::RuntimeFile(int defaultSize )
{
    size = defaultSize;
    usersFile = new UserEntry[defaultSize]; 
    commoditiesFile = new CommodityEntry[defaultSize*10];
    ordersFile = new OrderEntry[defaultSize*10];
    usersSize = 0;
    commSize = 0;
    orderSize =  0;
    readToUsers();
    readToComms();
    readToOrders();
}

RuntimeFile::~RuntimeFile()
{
    delete [] usersFile;
    delete [] commoditiesFile;
    delete [] ordersFile;
}

RuntimeFile RuntimeFile::operator=(RuntimeFile fFile)
{

}

RuntimeFile::RuntimeFile(const RuntimeFile& rFile)
{

}

CommodityEntry* RuntimeFile::addCommodity(string& name, double price, int amount, string& description, char*sellerID)
{
    if(commSize == size)
        overflowProcess();
    
    assignID('M',commoditiesFile[commSize].id,  commSize+1);
    assignment(name, commoditiesFile[commSize].name);
    assignment(description, commoditiesFile[commSize].description);
    assignment(sellerID, commoditiesFile[commSize].sellerID);
    assignCurDate(commoditiesFile[commSize].addedDate);
    commoditiesFile[commSize].price = price;
    commoditiesFile[commSize].number = amount;
    commoditiesFile[commSize].state = ON_AUCTION;
    ++commSize;

    writeCommsFile("a");
    return &commoditiesFile[commSize-1];
}

void RuntimeFile::addUser(const string name, string passwd)
{
    if(usersSize == size)
        overflowProcess();
    assignment(name, usersFile[usersSize].name);
    assignment(passwd, usersFile[usersSize].passwd);
    assignment("modify your address", usersFile[usersSize].address);
    assignment("phoneNumber",usersFile[usersSize].phone);
    usersFile[usersSize].balance = 0.0;
    usersFile[usersSize].state = ACTIVE;
    ++usersSize;
    /*从0开始存放数据，用户id号从1开始*/
    assignID('U',usersFile[usersSize-1].id, usersSize);
   
}

void RuntimeFile::assignID(char category, char* id, int amount)
{
    id[0] = category;
    char str[ID_SIZE];
    /*convert the numeric value "amount" to array of char
    %03d means if "amount" is less than three digits then make up 0 in front */
    sprintf(str, "%03d", amount);

    for(int i = 1; i < ID_SIZE; ++i)
        id[i] = str[i-1];
    id[ID_SIZE] = 0;
}

void RuntimeFile::assignCurDate(char* date)
{
    time_t rawtime;
    struct tm *ptminfo;
 
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    sprintf(date, "%02d-%02d-%02d", 
                        ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday);
}


bool RuntimeFile::find(const string name) const
{
    for(int i = 0; i < usersSize; ++i)
    {
        if(equal(name, usersFile[i].name))
            return true;
    }
    return false;
}




LogFlag RuntimeFile::matching(const string name, string passwd) const
{
    int i = 0;
    for(; i < usersSize; ++i)
    {
        if(equal(name, usersFile[i].name))
        {
            if(equal(passwd, usersFile[i].passwd))
                return LOGIN_SUCCEED;
            else
                return WRONG_PASSWD;
        }
    }
    if(i == usersSize)
        return NO_USER;
}

bool RuntimeFile::modifyComm()
{

}

bool RuntimeFile::modifyOrder()
{

}

void RuntimeFile::modifyUserBal(string name, double newBalance)
{
    for(int i = 0; i < usersSize; ++i)
    {
        if(equal(name, usersFile[i].name))
        {
            usersFile[i].balance = newBalance;
            writeUsersFile("w");
            break;
        }
    }
}

void RuntimeFile::modifyUserInfo(int flag, string userName, string newInfo)
{
    int i = 0;
     for(; i < usersSize; ++i)
    {
        if(equal(userName,usersFile[i].name))
            break;
    }
    /*修改用户名*/
    if(1 == flag)
        assignment(newInfo,usersFile[i].name);                
    /*修改联系方式*/
    else if(2 == flag)
        assignment(newInfo,usersFile[i].phone);       
    /*修改地址*/
    else if(3 == flag)
        assignment(newInfo,usersFile[i].address);       

    writeUsersFile("w");
}
bool checkID(string userID)
{
    if(userID.length() != ID_SIZE || userID[0] != 'U')
        return false;
    for(int i = 1; i < ID_SIZE; ++i)
        if(!isdigit(userID[i]))
            return false;
    return true;
}
void RuntimeFile::modifyUserState()
{
    string userID;
    std::cout << "请输入要封禁的用户的ID：" ;
    getline(cin,userID);
   if(checkID(userID))
   {
        for(int i = 0; i < usersSize; ++i)
        {
            if(equal(userID, usersFile[i].id))
            {
                std::cout << "是否确认封禁该用户?" << endl;
                std::cout << starStr << endl;
                printf("%-6s    %-10s   %-20s   %-40s   %-10s\n",
                            "UserID","UserName","PhoneNumber","Address","Balance");
                printf("%-6s    %-10s   %-20s   %-40s   %-10lf\n",
                            usersFile[i].id, usersFile[i].name, usersFile[i].phone, usersFile[i].address,usersFile[i].balance);
                std::cout << starStr << endl;
                std::cout << "请输入(y/n): ";
                char ch;
                cin >> ch;
                if(tolower(ch) == 'y')
                {
                    usersFile[i].state = INACTIVE;
                    writeUsersFile("w");
                    std::cout << "封禁成功！" << endl << endl;
                }
                else
                    std::cout << "封禁失败！" << endl << endl;
                return;
            }
        }
        std::cout << "用户ID不存在，封禁失败！" << endl <<endl;
   }
    else
        std::cout << "非法ID，封禁失败！" << endl << endl;
}



void RuntimeFile::overflowProcess()
{
    
}

void RuntimeFile::readToComms()
{

}
/*用户文件结构：userID userName passewd phone address balance userState*/
/*商品文件结构：commID commName price number description sellerID addedDate state*/
/*订单文件结构：orderID commID unitPrice number date sellerID buyerID*/
void RuntimeFile::readToOrders()
{
   
}

void RuntimeFile::readToUsers()
{
    FILE* input = fopen("users.txt", "r");
    int ret = 0;
    if(input)
    {    
        while(1)
        {
            ret = fscanf(input, "%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%lf%*c%d\n",
                                usersFile[usersSize].id, usersFile[usersSize].name,usersFile[usersSize].passwd,
                                usersFile[usersSize].phone, usersFile[usersSize].address,&usersFile[usersSize].balance,
                                &usersFile[usersSize].state);
            if(ret != 7)
                break;
            ++usersSize;
        }
        fclose(input);
    }
}

void RuntimeFile::showCommodities() const
{

}

void RuntimeFile::showOrders() const
{

}

void RuntimeFile::showUsers() const
{
    std::cout << starStr << endl;
    printf("%-6s    %-10s   %-20s   %-40s   %-10s   %-10s\n",
                "UserID","UserName","PhoneNumber","Address","Balance","UserState");
    for(int i = 0; i < usersSize; ++i)
    {
        printf("%-6s    %-10s   %-20s   %-40s   %-10lf   ",
                    usersFile[i].id, usersFile[i].name, usersFile[i].phone, usersFile[i].address,
                    usersFile[i].balance);
        if(usersFile[i].state)
            printf("%-10s\n","ACTIVE");
        else
            printf("%-10s\n","INACTIVE");
    }
    std::cout << starStr << endl;
}

void RuntimeFile::writeCommsFile(const char* mode) const
{
    FILE* output = fopen("commodities.txt",mode);
    /*append to file*/
    if(mode[0] == 'a')
    {
        fprintf(output, "%s,%s,%lf,%d,%s,%s,%s,%d\n",commoditiesFile[commSize-1].id, commoditiesFile[commSize-1].name,
                                commoditiesFile[commSize-1].price, commoditiesFile[commSize-1].number, commoditiesFile[commSize-1].description,
                                commoditiesFile[commSize-1].sellerID, commoditiesFile[commSize-1].addedDate,commoditiesFile[commSize-1].state);
    }
    /*clean contents of file before writing*/
    else
    {
        for(int i = 0; i < commSize; ++i)    
            fprintf(output, "%s,%s,%lf,%d,%s,%s,%s,%d\n",commoditiesFile[i].id, commoditiesFile[i].name,
                                    commoditiesFile[i].price, commoditiesFile[i].number, commoditiesFile[i].description,
                                    commoditiesFile[i].sellerID, commoditiesFile[i].addedDate,commoditiesFile[i].state);
    }
    fclose(output);
}

void RuntimeFile::writeOrdersFile(const char* mode) const
{
    FILE* output = fopen("orders.txt",mode);
    /*append to file*/
    if(mode[0] == 'a')
    {
        fprintf(output, "%s,%s,%lf,%d,%s,%s,%s\n",ordersFile[orderSize-1].id, ordersFile[orderSize-1].commodityID,
                                ordersFile[orderSize-1].unitPrice, ordersFile[orderSize-1].number, ordersFile[orderSize-1].date,
                                ordersFile[orderSize-1].sellerID, ordersFile[orderSize-1].buyerID);
    }
    /*clean contents of file before writing*/
    else
    {
        for(int i = 0; i < orderSize; ++i)    
            fprintf(output, "%s,%s,%lf,%d,%s,%s,%s\n",ordersFile[i].id, ordersFile[i].commodityID,
                                ordersFile[i].unitPrice, ordersFile[i].number, ordersFile[i].date,
                                ordersFile[i].sellerID, ordersFile[i].buyerID);
    }
    fclose(output);
}

void RuntimeFile::writeUsersFile(const char* mode) const
{
    FILE* output = fopen("users.txt",mode);
    /*append to file*/
    if(mode[0] == 'a')
    {
        fprintf(output, "%s,%s,%s,%s,%s,%lf,%d\n",usersFile[usersSize-1].id, usersFile[usersSize-1].name,
                    usersFile[usersSize-1].passwd, usersFile[usersSize-1].phone, usersFile[usersSize-1].address,
                    usersFile[usersSize-1].balance, usersFile[usersSize-1].state);
    }
    /*clean contents of file before writing*/
    else
    {
        for(int i = 0; i < usersSize; ++i)    
        fprintf(output, "%s,%s,%s,%s,%s,%lf,%d\n",usersFile[i].id, usersFile[i].name, usersFile[i].passwd, 
                    usersFile[i].phone, usersFile[i].address, usersFile[i].balance, usersFile[i].state);
    }
    fclose(output);
}