#include"user.h"

extern std::string starStr;
bool checkAlnum(std::string,int);

User::User(const std::string name,int defaultSize )
{
    size = defaultSize;

    /*set "userInfo" point to the user's info in the runtime file*/
    for(int i = 0; i < file.usersSize; ++i)
        if(equal(name, file.usersFile[i].name))
        {
            userInfo = &file.usersFile[i];
            break;
        }

    /*set a pointer for each commodity the user released and
    assign the address of each released commodity to each pointer*/
    commSize = 0;
    releasedComms = new CommodityEntry*[size];
    for(int i = 0; i < file.commSize; ++i)
    {
        if(equal(userInfo->id, file.commoditiesFile[i].sellerID))
            releasedComms[commSize++] = &file.commoditiesFile[i];
    }

}

void User::auction()
{

}

void User::buy()
{

}

void User::modifyCommInfo() const
{

}

void User::pullCommodity()
{

}

/*检查字符串是否由数字组成且符合长度要求*/
bool checkNum(std::string str, int size)
{
    if(str.length() > size || str.length() == 0)
        return false;
    for(int i = 0; i < str.length(); ++i)
        if(!isdigit(str[i]))
            return false;
    return true;
}

/*检查字符串是否不包含“,”且符合长度要求*/
bool checkStr(std::string str, int size)
{
    if(str.length() > size || str.length() == 0)
        return false;
    for(int i = 0; i < str.length(); ++i)
        if(str[i] == ',')
            return false;
    return true;
}

void User::modifyUserInfo()
{
    int seq;
    std::cout << "请选择要修改的属性(1. 用户名  2. 联系方式  3.地址) :";
    cin >> seq;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore();
        std::cout << "输入不合法，修改失败！" << endl << endl;
    }
    else
    {
        cin.ignore(HUGE_NUM,'\n');
        if(1 == seq)
        {
            std::cout << starStr << endl;
            std::cout << "请注意用户名只能由英文字母和数字构成且不能超过10个字符" << endl;
            std::cout << starStr << endl;
            std::cout << "请输入修改后的用户名：" ;
            std::string newName;
            getline(cin, newName);
            if(checkAlnum(newName,MAX_NAME_SIZE))
            {
                if(file.find(newName))
                    std::cout << "用户名已存在，修改失败！" << endl << endl;
                else
                {
                    assignment(newName, userInfo->name);
                    file.writeUsersFile("w");
                    std::cout << "修改成功！" << endl << endl;
                }                   
            }
            else
                std::cout << "用户名不合法，修改失败！" << endl << endl;
        }
        else if(2 == seq)
        {            
            std::cout << "请输入修改后的联系方式：" ;
            std::string newPhone;
            getline(cin, newPhone);
            if(checkNum(newPhone,MAX_PHONENUMBER_SIZE))
            {
                assignment(newPhone, userInfo->phone);
                file.writeUsersFile("w");
                std::cout << "修改成功！" << endl << endl;                  
            }
            else
                std::cout << "联系方式不合法，修改失败！" << endl << endl;
        }
        else  if(3 == seq)
        {
            std::cout << starStr << endl;
            std::cout << "请不要在您的地址中包含“,” " << endl;
            std::cout << starStr << endl;
            std::cout << "请输入修改后的地址：" ;
            std::string newAddress;
            getline(cin, newAddress);
            if(checkStr(newAddress,MAX_ADDRESS_SIZE))
            {
                assignment(newAddress, userInfo->address);
                file.writeUsersFile("w");
                std::cout << "修改成功！" << endl << endl;                  
            }
            else
                std::cout << "地址不合法，修改失败！" << endl << endl;
        }
    }
}

void User::overflowProcess()
{

}

void User::releaseCommodity() 
{
    std::string commName, description;
    double price;
    int amount;

    cout << "请输入商品名称：";
    getline(cin, commName);
    if(!checkStr(commName,MAX_COMM_NAME_SIZE))
    {
        cout << "商品名称输入不合法，发布失败！" << endl << endl;
        return;
    }

    cout << "请输入商品价格：";
    cin >> price;
    char ch = getc(stdin);
    ungetc(ch, stdin);
    if(cin.fail() || ch != '\n')
    {
        cin.clear();
        cin.ignore(HUGE_NUM,'\n');
        cout << "商品价格输入不合法，发布失败！" << endl << endl;
        return;
    }

    cout << "请输入商品数量：";
    cin >> amount;
    ch = getc(stdin);
    //ungetc(ch,stdin);
    if(cin.fail() || ch != '\n')
    {
        cin.clear();
        cin.ignore(HUGE_NUM,'\n');
        cout << "商品数量输入不合法，发布失败！" << endl << endl;
        return;
    }

    cout << "请输入商品描述：";
    getline(cin, description);
    if(!checkStr(description,MAX_COMM_DESCRIPTION_SIZE))
    {
        cout << "商品描述输入不合法，发布失败！" << endl << endl;
        return;
    }

    cout << starStr << endl;
    cout << "请确认要发布的商品信息无误：" << endl;
    cout << "商品名称：" << commName << endl;
    cout << "商品价格：" << price << endl;
    cout << "商品数量：" << amount << endl;
    cout << "商品描述：" << description << endl;
    cout << starStr << endl;
    cout << "是否确认发布?(y/n)" << endl;

    char confirm;
    cout << "请输入：" ;
    cin >> confirm;
    cin.ignore(HUGE_NUM,'\n');
    if(tolower(confirm) == 'y')
    {
        if(commSize == size)
            overflowProcess();
        releasedComms[commSize] =  file.addCommodity(commName, price, amount, description, userInfo->id);
        ++commSize;
        cout << "商品发布成功！" << endl << endl;
    }
    else
        cout << "商品发布失败！" << endl << endl;


}

void User::searchCommodity() const
{

}

void User::topUp()
{
    cout << starStr << endl;
    cout << "请不要在您输入金额的中间或者结尾加入任何无关字符，包括空格！" << endl;
    cout << starStr << endl;

    double money;
    cout << "请输入要充值的金额：" ;
    cin >> money;
    /*在调用完getc取出回车符后要立即将字符放回，否则程序会等待输入回车符*/
    char ch = getc(stdin);
    ungetc(ch, stdin);
    if(cin.fail() || money <= 0 || ch != '\n')
    {
        cin.clear();
        cin.ignore(HUGE_NUM, '\n');
        cout << "输入不合法，充值失败！" << endl << endl;
    }
    else
    {
        cin.ignore(HUGE_NUM, '\n');
        userInfo->balance += money;
        file.writeUsersFile("w");
        cout << "充值成功，当前余额：" << userInfo->balance <<  endl << endl;
    }
}

void User::viewUserInfo() const
{
    cout << starStr << endl;
    cout << "用户名：" << userInfo->name << endl;
    cout << "联系方式：" <<userInfo-> phone << endl;
    cout << "地址：" <<userInfo-> address << endl;
    cout << "钱包余额：" << userInfo->balance << endl;
    cout << starStr << endl;
}
	
void User::viewCommodities() const 
{

}	

void User::viewCommDetail() const
{

}

void User::viewBuyerOrders() const
{

}

void User::viewSellerOrders() const 
{

}

void User::viewReleasedComm() const
{

}

