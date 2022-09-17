#include"runtimeFile.h"
#include<fstream>

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
    usrsFile[usrsSize].address[0] = 0;
    usrsFile[usrsSize].phone[0] = 0;
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

bool RuntimeFile::equal(string str1, const char* str2) const
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

LogFlag RuntimeFile::matching(const string name, string passwd) const
{

}

bool RuntimeFile::modifyComm()
{

}

bool RuntimeFile::modifyOrder()
{

}

bool RuntimeFile::modifyUsr()
{

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
            ret = fscanf(input, "%s,%s,%s,%s,%s,%lf,%d\n",usrsFile[usrsSize].id, usrsFile[usrsSize].name, 
                                usrsFile[usrsSize].passwd,  usrsFile[usrsSize].phone, usrsFile[usrsSize].address,
                                &usrsFile[usrsSize].balance, &usrsFile[usrsSize].state);
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