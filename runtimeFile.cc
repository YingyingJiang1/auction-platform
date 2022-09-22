#include"runtimeFile.h"
#include<fstream>
#include<cstdio>
#include<ctime>
#define ID_SIZE 4
#define PRINT_COMM_ATTRS_VALUE \
printf("%-6s    %-20s   %-10lf   %-10s     %-10d   %-10s     %-10d\n",\
            commoditiesFile[i].id, commoditiesFile[i].name, commoditiesFile[i].price, commoditiesFile[i].addedDate,\
            commoditiesFile[i].number, commoditiesFile[i].sellerID, commoditiesFile[i].state)
string starStr = "***************************************************************************************************************";

RuntimeFile::RuntimeFile(int defaultSize )
{
    size = defaultSize * 10;
    maxUserSize = defaultSize;
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

OrderEntry* RuntimeFile::addOrder(int index, int num, char* buyerID)
{
    if(orderSize == size)
        overflowProcess();
    assignID('T', ordersFile[orderSize].id, orderSize+1);
    assignment(buyerID,ordersFile[orderSize].buyerID ) ;
    assignment(commoditiesFile[index].sellerID,ordersFile[orderSize].sellerID) ;
    assignCurDate(ordersFile[orderSize].date);
    assignment(commoditiesFile[index].id, ordersFile[orderSize].id);
    ordersFile[orderSize].number = num;
    ordersFile[orderSize].unitPrice = commoditiesFile[index].price;
    ++orderSize;
    writeOrdersFile("a");
    return &ordersFile[orderSize-1];
}

void RuntimeFile::addUser(const string name, string passwd)
{
    if(usersSize == maxUserSize)
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

/*convert the numeric value "amount" to array of char*/
void RuntimeFile::assignID(char category, char* id, int amount)
{
    id[0] = category;
    char str[ID_SIZE];
    /*%03d means if "amount" is less than three digits then make up 0 in front */
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

int RuntimeFile::getIndex(string id) const
{
    int i = 0;
    /*查找商品ID*/
    if(id[0] == 'M')
    {
        for(; i < commSize; ++i)
        {
            if(equal(id, commoditiesFile[i].id))
                break;
        }
    }
    /*查找用户ID*/
    else if(id[0] == 'U')
    {
        for(; i < usersSize; ++i)
            if(equal(id, usersFile[i].id))
                break;
    }
    else
    {
        for(; i < orderSize; ++i)
            if(equal(id, ordersFile[i].id))
                break;
    }
    return i;
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

/*数据结构设计得很有问题！一旦用new重新分配空间，那么会影响到
用户对象中数据成员， 需要改动很大，懒得改了*/
void RuntimeFile::overflowProcess()
{
    if(usersSize == maxUserSize)
    {
        
    }
    else if(commSize == size)
    {

    }
    else if(orderSize == size)
    {

    }
}

/*用户文件结构：userID userName passewd phone address balance userState*/
/*商品文件结构：commID commName price number description sellerID addedDate state*/
/*订单文件结构：orderID commID unitPrice number date sellerID buyerID*/
void RuntimeFile::readToComms()
{
    FILE* input = fopen("commodities.txt", "r");
    int ret = 0;
    if(input)
    {    
        while(1)
        {
            ret = fscanf(input, "%[^,]%*c%[^,]%*c%lf%*c%d%*c%[^,]%*c%[^,]%*c%[^,]%*c%d\n",
                                commoditiesFile[commSize].id, commoditiesFile[commSize].name,&commoditiesFile[commSize].price,
                                &commoditiesFile[commSize].number, commoditiesFile[commSize].description,
                                commoditiesFile[commSize].sellerID,commoditiesFile[commSize].addedDate,&commoditiesFile[commSize].state);
            if(ret != 8)
                break;
            ++commSize;
        }
        fclose(input);
    }
}

void RuntimeFile::readToOrders()
{
   FILE* input = fopen("orders.txt", "r");
    int ret = 0;
    if(input)
    {    
        while(1)
        {
           ret = fscanf(input, "%[^,]%*c%[^,]%*c%lf%*c%d%*c%[^,]%*c%[^,]%*c%[^,]%*c\n",
                                ordersFile[orderSize].id, ordersFile[orderSize].commodityID,&ordersFile[orderSize].unitPrice,
                                &ordersFile[orderSize].number, ordersFile[orderSize].date,ordersFile[orderSize].sellerID,
                                ordersFile[orderSize].buyerID);
            if(ret != 7)
                break;
            ++orderSize;
        }
        fclose(input);
    }
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
    cout << starStr << endl;
    PRINT_COMM_ATTRS_NAME;
    for(int i = 0; i < commSize; ++i)
    {
        PRINT_COMM_ATTRS_VALUE;
    }
}

void RuntimeFile::showCommDetail(string id) const
{
    int i = getIndex(id);
    cout << starStr << endl;
    cout << "商品ID：" << commoditiesFile[i].id << endl;
    cout << "商品名称：" << commoditiesFile[i].name << endl;
    cout << "商品价格：" << commoditiesFile[i].price << endl;
    cout << "上架时间：" << commoditiesFile[i].addedDate << endl;
    cout << "商品描述：" << commoditiesFile[i].description << endl;
    cout << "商品买家：" << commoditiesFile[i].sellerID << endl;
    cout << starStr << endl;
}

void RuntimeFile::showSpecificComms(string name, int flag) const
{
    /*管理员的flag设置为1， 用户的flag设置为0*/
    cout << starStr << endl;
    bool noOutput = true;
    int i = 0;
    for(; i < commSize; ++i)
    {
        if(equal(name, commoditiesFile[i].name) && (flag || commoditiesFile[i].state))
        {
            noOutput = false;
            break;
        }
    }
    if(noOutput)
        cout << "没有找到您想要的商品！返回管理员主界面！" << endl ;
    else
    {
        PRINT_COMM_ATTRS_NAME;
        for(; i < commSize; ++i)
            if(equal(name, commoditiesFile[i].name) && (flag || commoditiesFile[i].state))
                PRINT_COMM_ATTRS_VALUE;
    }   
    cout << starStr << endl;
}

void RuntimeFile::showOrders() const
{
    cout << starStr << endl;
    PRINT_ORDER_ATTRS_NAME;
    for(int i = 0; i < orderSize; ++i)
        PRINT_ORDER_ATTRS_VALUE;
    cout << starStr << endl;
}

void RuntimeFile::showUsers() const
{
    std::cout << starStr << endl;
    PRINT_USER_ATTRS_NAME;
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