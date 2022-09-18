#include"runtimeFile.h"
#include<fstream>
#define ID_SIZE 4
string starStr = "***************************************************************************************************************";

RuntimeFile::RuntimeFile(int defaultSize )
{
    size = defaultSize;
    usrsFile = new UserEntry[defaultSize]; 
    commoditiesFile = new CommodityEntry[defaultSize*10];
    ordersFile = new OrderEntry[defaultSize*10];
    usrsSize = 0;
    commSize = 0;
    orderSize =  0;
    readToUsrs();
    readToComms();
    readToOrders();
}

RuntimeFile::~RuntimeFile()
{
    delete [] usrsFile;
    delete [] commoditiesFile;
    delete [] ordersFile;
}

RuntimeFile RuntimeFile::operator=(RuntimeFile fFile)
{

}

RuntimeFile::RuntimeFile(const RuntimeFile& rFile)
{

}

void RuntimeFile::addUser(const string name, string passwd)
{
    if(usrsSize == size)
        overflowProcess();
    assignment(name, usrsFile[usrsSize].name);
    assignment(passwd, usrsFile[usrsSize].passwd);
    assignment("modify your address", usrsFile[usrsSize].address);
    assignment("phoneNumber",usrsFile[usrsSize].phone);
    usrsFile[usrsSize].balance = 0.0;
    usrsFile[usrsSize].state = ACTIVE;
    ++usrsSize;
    /*从0开始存放数据，用户id号从1开始*/
    assignID(usrsFile[usrsSize-1].id);
   
}

void RuntimeFile::assignID(char* id)
{
    id[0] = 'U';
    char str[4];
    int ret = sprintf(str, "%d", usrsSize);
    /*先把由usrsSize转换得到的字符串写入id，再在需要的地方补‘0’*/
    for(int i = 0, j = 4-ret; i < ret; ++i,++j)
        id[j] = str[i];
    for(int i = 1; i < 4-ret; ++i)
        id[i] = '0';
}

bool RuntimeFile::equal(const string str1, const char* str2) const
{
    int i = 0;
    for(; str1[i] != 0 && str2[i] != 0; ++i)
        if(str1[i] != str2[i])
            return false;
    if(str1[i] == 0 && str2[i] == 0)
        return true;
    return false;
}

bool RuntimeFile::find(const string name) const
{
    for(int i = 0; i < usrsSize; ++i)
    {
        if(equal(name, usrsFile[i].name))
            return true;
    }
    return false;
}

void RuntimeFile::getUsrInfo(const string name, UsrInfo* usrInfo) const
{
    for(int i = 0; i < usrsSize; ++i)
    {
        if(equal(name,usrsFile[i].name))
        {
            usrInfo->balance = usrsFile[i].balance;
            usrInfo->phone = usrsFile[i].phone;
            usrInfo->address = usrsFile[i].address;
            break;
        }
    }
}

LogFlag RuntimeFile::matching(const string name, string passwd) const
{
    int i = 0;
    for(; i < usrsSize; ++i)
    {
        if(equal(name, usrsFile[i].name))
        {
            if(equal(passwd, usrsFile[i].passwd))
                return LOGIN_SUCCEED;
            else
                return WRONG_PASSWD;
        }
    }
    if(i == usrsSize)
        return NO_USER;
}

bool RuntimeFile::modifyComm()
{

}

bool RuntimeFile::modifyOrder()
{

}

void RuntimeFile::modifyUsrBal(string name, double newBalance)
{
    for(int i = 0; i < usrsSize; ++i)
    {
        if(equal(name, usrsFile[i].name))
        {
            usrsFile[i].balance = newBalance;
            writeUsrsFile("w");
            break;
        }
    }
}

void RuntimeFile::modifyUsrInfo(int flag, string usrName, string newInfo)
{
    int i = 0;
     for(; i < usrsSize; ++i)
    {
        if(equal(usrName,usrsFile[i].name))
            break;
    }
    /*修改用户名*/
    if(1 == flag)
        assignment(newInfo,usrsFile[i].name);                
    /*修改联系方式*/
    else if(2 == flag)
        assignment(newInfo,usrsFile[i].phone);       
    /*修改地址*/
    else if(3 == flag)
        assignment(newInfo,usrsFile[i].address);       

    writeUsrsFile("w");
}
bool checkID(string usrID)
{
    if(usrID.length() != 4 || usrID[0] != 'U')
        return false;
    for(int i = 1; i < ID_SIZE; ++i)
        if(!isdigit(usrID[i]))
            return false;
    return true;
}
void RuntimeFile::modifyUsrState()
{
    string usrID;
    std::cout << "请输入要封禁的用户的ID：" ;
    getline(cin,usrID);
   if(checkID(usrID))
   {
        for(int i = 0; i < usrsSize; ++i)
        {
            if(equal(usrID, usrsFile[i].id))
            {
                std::cout << "是否确认封禁该用户?" << endl;
                std::cout << starStr << endl;
                printf("%-6s    %-10s   %-20s   %-40s   %-10s\n",
                            "UserID","UserName","PhoneNumber","Address","Balance");
                printf("%-6s    %-10s   %-20s   %-40s   %-10lf\n",
                            usrsFile[i].id, usrsFile[i].name, usrsFile[i].phone, usrsFile[i].address,usrsFile[i].balance);
                std::cout << starStr << endl;
                std::cout << "请输入(y/n): ";
                char ch;
                cin >> ch;
                if(tolower(ch) == 'y')
                {
                    usrsFile[i].state = INACTIVE;
                    writeUsrsFile("w");
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

void RuntimeFile::readToUsrs()
{
    FILE* input = fopen("usrs.txt", "r");
    int ret = 0;
    if(input)
    {    
        while(1)
        {
            ret = fscanf(input, "%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%lf%*c%d\n",
                                usrsFile[usrsSize].id, usrsFile[usrsSize].name,usrsFile[usrsSize].passwd,
                                usrsFile[usrsSize].phone, usrsFile[usrsSize].address,&usrsFile[usrsSize].balance,
                                &usrsFile[usrsSize].state);
            //std::cout << usrsFile[0].id << ' ' << usrsFile[0].name << ' ' << usrsFile[0].passwd << " " << usrsFile[0].balance<<endl;
            //std::cout << usrsFile[0].state<<endl;
            //std::cout << ret <<endl;
            if(ret != 7)
                break;
            ++usrsSize;
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

void RuntimeFile::showUsrs() const
{
    std::cout << starStr << endl;
    printf("%-6s    %-10s   %-20s   %-40s   %-10s   %-10s\n",
                "UserID","UserName","PhoneNumber","Address","Balance","UserState");
    for(int i = 0; i < usrsSize; ++i)
    {
        printf("%-6s    %-10s   %-20s   %-40s   %-10lf   ",
                    usrsFile[i].id, usrsFile[i].name, usrsFile[i].phone, usrsFile[i].address,
                    usrsFile[i].balance);
        if(usrsFile[i].state)
            printf("%-10s\n","ACTIVE");
        else
            printf("%-10s\n","INACTIVE");
    }
    std::cout << starStr << endl;
}

void RuntimeFile::writeCommsFile(const char* mode) const
{

}

void RuntimeFile::writeOrdersFile(const char* mode) const
{

}

void RuntimeFile::writeUsrsFile(const char* mode) const
{
    FILE* output = fopen("usrs.txt",mode);
    /*append to file*/
    if(mode[0] == 'a')
    {
        fprintf(output, "%s,%s,%s,%s,%s,%lf,%d\n",usrsFile[usrsSize-1].id, usrsFile[usrsSize-1].name,
                    usrsFile[usrsSize-1].passwd, usrsFile[usrsSize-1].phone, usrsFile[usrsSize-1].address,
                    usrsFile[usrsSize-1].balance, usrsFile[usrsSize-1].state);
    }
    /*clean contents of file before writing*/
    else
    {
        for(int i = 0; i < usrsSize; ++i)    
        fprintf(output, "%s,%s,%s,%s,%s,%lf,%d\n",usrsFile[i].id, usrsFile[i].name, usrsFile[i].passwd, 
                    usrsFile[i].phone, usrsFile[i].address, usrsFile[i].balance, usrsFile[i].state);
    }
    fclose(output);
}