#include"user.h"
#define HUGE_NUM 0X7FFFFFFF
extern string starStr;
bool checkAlnum(string,int);
void User::auction()
{

}

void User::buy()
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
        balance += money;
        file.modifyUsrBal(name, balance);
        cout << "充值成功，当前余额：" << balance <<  endl << endl;
    }
}

void User::viewUsrInfo() const
{
    cout << starStr << endl;
    cout << "用户名：" << name << endl;
    cout << "联系方式：" << phone << endl;
    cout << "地址：" << address << endl;
    cout << "钱包余额：" << balance << endl;
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

void User::modifyCommInfo() const
{

}

/*检查字符串是否由数字组成且符合长度要求*/
bool checkNum(string str, int size)
{
    if(str.length() > size || str.length() == 0)
        return false;
    for(int i = 0; i < str.length(); ++i)
        if(!isdigit(str[i]))
            return false;
    return true;
}

/*检查字符串是否不包含“,”且符合长度要求*/
bool checkStr(string str, int size)
{
    if(str.length() > size || str.length() == 0)
        return false;
    for(int i = 0; i < str.length(); ++i)
        if(str[i] == ',')
            return false;
    return true;
}

void User::modifyUsrInfo()
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
            string newName;
            getline(cin, newName);
            if(checkAlnum(newName,MAX_NAME_SIZE))
            {
                if(file.find(newName))
                    std::cout << "用户名已存在，修改失败！" << endl << endl;
                else
                {
                    name = newName;
                    file.modifyUsrInfo(1, name, newName);
                    std::cout << "修改成功！" << endl << endl;
                }                   
            }
            else
                std::cout << "用户名不合法，修改失败！" << endl << endl;
        }
        else if(2 == seq)
        {            
            std::cout << "请输入修改后的联系方式：" ;
            string newPhone;
            getline(cin, newPhone);
            if(checkNum(newPhone,MAX_PHONENUMBER_SIZE))
            {
                phone = newPhone;
                file.modifyUsrInfo(2, name, newPhone);
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
            string newAddress;
            getline(cin, newAddress);
            if(checkStr(newAddress,MAX_ADDRESS_SIZE))
            {
                address = newAddress;
                file.modifyUsrInfo(3, name, newAddress);
                std::cout << "修改成功！" << endl << endl;                  
            }
            else
                std::cout << "地址不合法，修改失败！" << endl << endl;
        }
    }
}

void User::releaseCommodity() const
{

}