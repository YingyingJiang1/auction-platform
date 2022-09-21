#include"user.h"
extern std::string starStr;
bool checkAlnum(std::string,int);
#define PRINT_COMM_ATTRS_VALUE \
printf("%-6s    %-20s   %-10lf   %-10s     %-10d   %-10s     %-10d\n",\
            releasedComms[i]->id, releasedComms[i]->name, releasedComms[i]->price, releasedComms[i]->addedDate,\
            releasedComms[i]->number, releasedComms[i]->sellerID, releasedComms[i]->state)

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
    cout << file.commSize << endl;

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
    int seq;
    string id;    
    std::cout << "请输入要修改的商品的ID：";
    std::getline(std::cin, id);
    if(checkID('M', id))
    {
        int i = getCommIndex(id);
        
        if(i == commSize)
        {
            PROMPT_MODIFICATION_FAILURE("未在您发布的商品中找到该ID的商品");
            return;
        }
        std::cout << "请输入要修改的商品的属性(1.价格 2.描述）：";
        std::cin >> seq;
        if(!checkNum)
            PROMPT_OPERATION_NUMBER_ERROR;
        else
        {
            std::cin.ignore(HUGE_NUM, '\n');
            /*修改商品价格*/
            if(seq == 1)
            {
                double price;
                cout << "请输入新的价格：";
                std::cin >> price;
                if(checkNum())
                {
                    releasedComms[i]->price = price;
                    file.writeCommsFile("w");
                    PROMPT_MODIFICATION_SUCCEEED;
                }
                else
                    PROMPT_MODIFICATION_FAILURE("商品价格输入不合法");
            }
            /*修改商品描述*/
            else if(seq == 2)
            {
                string description;
                cout << "请输入新的描述：";
                std::getline(cin ,description);
                if(checkAlnum(description, MAX_COMM_DESCRIPTION_SIZE))
                {
                    assignment(description, releasedComms[i]->description);
                    file.writeCommsFile("w");
                    PROMPT_MODIFICATION_SUCCEEED;
                }
                else
                    PROMPT_MODIFICATION_FAILURE("商品描述输入不合法");
            }
            else
                PROMPT_MODIFICATION_FAILURE("该属性不存在");
        }
    }
    /*商品ID不是"M+三位数字"的形式*/
    else
        PROMPT_MODIFICATION_FAILURE("商品ID输入不合法");
}

void User::pullCommodity()
{
    string id;
    cout << "请输入要下架的商品的ID：";
    std::getline(cin ,id);
    if(checkID('M', id))
    {
        int i = 0; 
        for(; i < commSize; ++i)
            if(equal(id, releasedComms[i]->id))
                break;
        if(i == commSize)
        {
            PROMPT_MODIFICATION_FAILURE("未在您发布的商品中找到该ID的商品");
            return;
        }

        std::cout << "确认要下架该商品吗？" << std::endl;
        std::cout << starStr << std::endl;
        PRINT_COMM_ATTRS_NAME;
        PRINT_COMM_ATTRS_VALUE;        
        std::cout << starStr << std::endl;  

        std::cout << "请选择(y/n):";
        char confirm;
        std::cin >> confirm;
        if(tolower(confirm) == 'y')
        {
            releasedComms[i]->state = REMOVED;
            file.writeCommsFile("w");
            std::cout << "下架成功！" << std::endl << std::endl;
        }
        else
            std::cout << "下架失败！" << std::endl << std::endl;
    }
    /*商品ID不是"M+三位数字"的形式*/
    else
        PROMPT_MODIFICATION_FAILURE("商品ID输入不合法");
}



void User::modifyUserInfo()
{
    int seq;
    std::cout << "请选择要修改的属性(1. 用户名  2. 联系方式  3.地址) :";
    cin >> seq;
    if(!checkNum())
        PROMPT_OPERATION_NUMBER_ERROR;
    else
    {
        cin.ignore(HUGE_NUM,'\n');
        switch (seq)
        {
            case 1:
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
                        PROMPT_MODIFICATION_FAILURE("用户名已存在");
                    else
                    {
                        assignment(newName, userInfo->name);
                        file.writeUsersFile("w");
                        PROMPT_MODIFICATION_SUCCEEED;
                    }                   
                }
                else
                    PROMPT_MODIFICATION_FAILURE("用户名不合法");
                break;
            }
            case 2:
            {
                std::cout << "请输入修改后的联系方式：" ;
                std::string newPhone;
                getline(cin, newPhone);
                if(checkDigits(newPhone,MAX_PHONENUMBER_SIZE))
                {
                    assignment(newPhone, userInfo->phone);
                    file.writeUsersFile("w");
                    PROMPT_MODIFICATION_SUCCEEED;            
                }
                else
                    PROMPT_MODIFICATION_FAILURE("联系方式不合法");
                break;
            } 
            case 3:
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
                    PROMPT_MODIFICATION_SUCCEEED;                          
                }
                else
                    PROMPT_MODIFICATION_FAILURE("地址不合法");
            }
            default:
                PROMPT_OPERATION_NUMBER_ERROR;          
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
        PROMPT_MODIFICATION_FAILURE("用户名已存在");
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
    string name;
    getline(cin , name);
    std::cout << "请输入商品名称：" ;
    file.showSpecificComms(name, 0);    
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

void User::viewCommDetail() const
{
    string id;
    cout << "请输入您想要查看的商品的ID：";
    getline(cin, id);
    if(checkID('M', id))
        file.showCommDetail(id);
    else
        cout << "商品ID输入不合法！" << endl << endl;
}

void User::viewBuyerOrders() const
{

}

void User::viewSellerOrders() const 
{

}

void User::viewReleasedComm() const
{
    cout << starStr << endl;
    PRINT_COMM_ATTRS_NAME;    
    for(int i = 0; i < commSize; ++i)
        PRINT_COMM_ATTRS_VALUE;
    cout << starStr << endl;
}

