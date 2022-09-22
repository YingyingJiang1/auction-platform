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
    for(int i = 0; i < file.commSize; ++i)
    {
        if(equal(userInfo->id, file.commoditiesFile[i].sellerID))
            releasedComms[commSize++] = &file.commoditiesFile[i];
    }

    buySize = 0;
    sellSize = 0;
    buyOrder = new OrderEntry*[size];
    sellOrder = new OrderEntry*[size];
    for(int i =0; i < file.orderSize; ++i)
    {
        if(equal(userInfo->id, file.ordersFile[i].buyerID))
            buyOrder[buySize++] = &file.ordersFile[i];
        else if(equal(userInfo->id, file.ordersFile[i].sellerID))
            sellOrder[sellSize++] = &file.ordersFile[i];
    }
}

void User::auction()
{

}

void User::buy()
{
    string id;
    std::cout << "请输入商品ID：";
    getline(cin, id);
    if(checkID('M', id))
    {
        int num;
        std::cin >> num;
        if(checkNum())
        {
            int i = file.getIndex(id);
            if(i == file.commSize || file.commoditiesFile[i].state == REMOVED)
                std::cout << "没有找到该ID的商品！" << std::endl << std::endl;
            else
            {
                int left = file.commoditiesFile[i].number;
                if(num <= left)
                {
                    if(userInfo->balance >= file.commoditiesFile[i].price * left)
                    {
                        int sum = file.commoditiesFile[i].price * left;
                        int j = file.getIndex(file.commoditiesFile[i].sellerID);
                        userInfo->balance -= sum;                        
                        file.commoditiesFile[i].number -= num;                        
                        file.usersFile[j].balance += sum;
                        buyOrder[buySize++] = file.addOrder(i, num, userInfo->id);
                        file.writeCommsFile("w");
                        file.writeUsersFile("w");
                        cout << starStr << endl;
                        cout << "交易提醒！" << endl;
                        cout << "交易时间：" << buyOrder[buySize-1]->date << endl;
                        cout << "交易单价：" << buyOrder[buySize-1]->unitPrice << endl;
                        cout << "交易数量：" << num << endl;
                        cout << "交易状态：交易成功" << endl; 
                        cout << "您的余额：" << userInfo->balance << endl;
                        cout << starStr << endl;
                    }
                    else
                        cout << "余额不足，请充值！" << endl << endl;
                }
                else
                    std::cout << "该商品剩余数量为 " << file.commoditiesFile[i].number << " ，购买失败！" << std::endl << std::endl;
            }                            
        }      
        else
            std::cout << "商品数量输入不合法！" << std::endl << std::endl; 
    }
    else
        std::cout << "商品ID输入不合法！" << std::endl << std::endl;
}

int User::getCommIndex(string &id) const
	{
		int i = 0;
		for(; i < commSize; ++i)
        {
            if(equal(id, releasedComms[i]->id))
                break;
        }
		return i;
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
                std::cout << "请输入新的价格：";
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
                std::cout << "请输入新的描述：";
                std::getline(std::cin ,description);
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
    std::cout << "请输入要下架的商品的ID：";
    std::getline(std::cin ,id);
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
    std::cin >> seq;
    if(!checkNum())
        PROMPT_OPERATION_NUMBER_ERROR;
    else
    {
        std::cin.ignore(HUGE_NUM,'\n');
        switch (seq)
        {
            case 1:
            {
                std::cout << starStr << std::endl;
                std::cout << "请注意用户名只能由英文字母和数字构成且不能超过10个字符" << std::endl;
                std::cout << starStr << std::endl;
                std::cout << "请输入修改后的用户名：" ;
                std::string newName;
                std::getline(std::cin, newName);
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
                std::getline(std::cin, newPhone);
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
                std::cout << starStr << std::endl;
                std::cout << "请不要在您的地址中包含“,” " << std::endl;
                std::cout << starStr << std::endl;
                std::cout << "请输入修改后的地址：" ;
                std::string newAddress;
                std::getline(std::cin, newAddress);
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

    std::cout << "请输入商品名称：";
    std::getline(std::cin, commName);
    if(!checkStr(commName,MAX_COMM_NAME_SIZE))
    {
        PROMPT_MODIFICATION_FAILURE("用户名已存在");
        return;
    }

    std::cout << "请输入商品价格：";
    std::cin >> price;
    char ch = getc(stdin);
    ungetc(ch, stdin);
    if(std::cin.fail() || ch != '\n')
    {
        std::cin.clear();
        std::cin.ignore(HUGE_NUM,'\n');
        std::cout << "商品价格输入不合法，发布失败！" << std::endl << std::endl;
        return;
    }

    std::cout << "请输入商品数量：";
    std::cin >> amount;
    ch = getc(stdin);
    //ungetc(ch,stdin);
    if(std::cin.fail() || ch != '\n')
    {
        std::cin.clear();
        std::cin.ignore(HUGE_NUM,'\n');
        std::cout << "商品数量输入不合法，发布失败！" << std::endl << std::endl;
        return;
    }

    std::cout << "请输入商品描述：";
    std::getline(std::cin, description);
    if(!checkStr(description,MAX_COMM_DESCRIPTION_SIZE))
    {
        std::cout << "商品描述输入不合法，发布失败！" << std::endl << std::endl;
        return;
    }

    std::cout << starStr << std::endl;
    std::cout << "请确认要发布的商品信息无误：" << std::endl;
    std::cout << "商品名称：" << commName << std::endl;
    std::cout << "商品价格：" << price << std::endl;
    std::cout << "商品数量：" << amount << std::endl;
    std::cout << "商品描述：" << description << std::endl;
    std::cout << starStr << std::endl;
    std::cout << "是否确认发布?(y/n)" << std::endl;

    char confirm;
    std::cout << "请输入：" ;
    std::cin >> confirm;
    std::cin.ignore(HUGE_NUM,'\n');
    if(tolower(confirm) == 'y')
    {
        if(commSize == size)
            overflowProcess();
        releasedComms[commSize] =  file.addCommodity(commName, price, amount, description, userInfo->id);
        ++commSize;
        std::cout << "商品发布成功！" << std::endl << std::endl;
    }
    else
        std::cout << "商品发布失败！" << std::endl << std::endl;


}

void User::searchCommodity() const
{
    string name;
    std::getline(std::cin , name);
    std::cout << "请输入商品名称：" ;
    file.showSpecificComms(name, 0);    
}

void User::topUp()
{
    std::cout << starStr << std::endl;
    std::cout << "请不要在您输入金额的中间或者结尾加入任何无关字符，包括空格！" << std::endl;
    std::cout << starStr << std::endl;

    double money;
    std::cout << "请输入要充值的金额：" ;
    std::cin >> money;
    /*在调用完getc取出回车符后要立即将字符放回，否则程序会等待输入回车符*/
    char ch = getc(stdin);
    ungetc(ch, stdin);
    if(std::cin.fail() || money <= 0 || ch != '\n')
    {
        std::cin.clear();
        std::cin.ignore(HUGE_NUM, '\n');
        std::cout << "输入不合法，充值失败！" << std::endl << std::endl;
    }
    else
    {
        std::cin.ignore(HUGE_NUM, '\n');
        userInfo->balance += money;
        file.writeUsersFile("w");
        std::cout << "充值成功，当前余额：" << userInfo->balance <<  std::endl << std::endl;
    }
}

void User::viewUserInfo() const
{
    std::cout << starStr << std::endl;
    std::cout << "用户名：" << userInfo->name << std::endl;
    std::cout << "联系方式：" <<userInfo-> phone << std::endl;
    std::cout << "地址：" <<userInfo-> address << std::endl;
    std::cout << "钱包余额：" << userInfo->balance << std::endl;
    std::cout << starStr << std::endl;
}	

void User::viewCommDetail() const
{
    string id;
    std::cout << "请输入您想要查看的商品的ID：";
    std::getline(std::cin, id);
    if(checkID('M', id))
        file.showCommDetail(id);
    else
        std::cout << "商品ID输入不合法！" << std::endl << std::endl;
}

void User::viewBuyerOrders() const
{
    cout << starStr << endl;
    PRINT_BUYER_ORDER_ATTRS_NAME;
    for(int i = 0; i < buySize; ++i)
        PRINT_BUYER_ORDER_ATTRS_VALUE;
    cout << starStr << endl;
}

void User::viewSellerOrders() const 
{
    cout << starStr << endl;
    PRINT_SELLER_ORDER_ATTRS_NAME;
    for(int i = 0; i < sellSize; ++i)
        PRINT_SELLER_ORDER_ATTRS_VALUE;
    cout << starStr << endl;
}

void User::viewReleasedComm() const
{
    std::cout << starStr << std::endl;
    PRINT_COMM_ATTRS_NAME;    
    for(int i = 0; i < commSize; ++i)
        PRINT_COMM_ATTRS_VALUE;
    std::cout << starStr << std::endl;
}

