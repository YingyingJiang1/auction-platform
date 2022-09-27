#include"user.h"

#define PRINT_COMM_ATTRS_VALUE \
printf("%-6s    %-20s   %-10lf   %-20s     %-10d   %-10s     %-10d\n",\
            releasedComms[i]->id, releasedComms[i]->name, releasedComms[i]->price, releasedComms[i]->addedDate,\
            releasedComms[i]->number, releasedComms[i]->sellerID, releasedComms[i]->state)

User::User(const char* nameInputed)
{
    char ret[MAX_ID_SIZE+1];
    file.getID(nameInputed, ret);
    assignment(nameInputed,name);
    assignment(ret, userID);
}

void User::auction()
{
   char commID[MAX_ID_SIZE+1], seller[MAX_ID_SIZE+1];
   std::cout << "请输入你要竞拍的商品的ID：" ;
   fgets(commID, MAX_ID_SIZE+1, stdin);
   if(checkID('M', commID))
   {
       bool found = file.findComm(seller, commID, file.onAuctionCommList());
       if(found)
       {
           if(equal(seller, userID))
           {
               std::cout << "您不能参与自己发布的商品的竞拍！" << std::endl << std::endl;
               return;
           }
           if(file.findUserInAucList(userID, commID))
           {
               std::cout << "您已参与了该商品的竞拍，请不要重复参与！" << std::endl << std::endl;
               return;
           }
           double unitPrice;
           int amount;
           std::cout << "请输入竞拍单价：";
           std::cin >> unitPrice;
           if(!checkNum())
           {
               PROMPT_AUCTION_FAILURE("竞拍单价输入不合法");
               return;
           }
           std::cout << "请输入竞拍数量：";
           std::cin >> amount;
           if(!checkNum())
           {
               PROMPT_AUCTION_FAILURE("商品数量不合法");
               return;
           }
           /*输入全部合法，可以参与竞拍的情况*/
           char  buyer[MAX_ID_SIZE+1];
           assignment(userID, buyer);
            std::cout << starStr << std::endl;
           if(file.addAuctionInfo(commID, buyer, unitPrice, amount))
           {
                std::cout << "成功参与竞拍，该商品竞拍结束后才能知道竞拍结果，"
            "在此期间您可以随时修改您的竞拍单价和数量或取消竞拍，\n"
            "但相应的您的竞拍时间也会被修改！" << std::endl << std::endl;
           }           
           std::cout << starStr << std::endl;
       }
       else
            std::cout << "未找到ID为 " << commID << " 的在售商品，参与竞拍失败！" 
            << std::endl << std::endl;
   }
   else
        std::cout << "商品ID输入不合法，参与竞拍失败！" << std::endl << std::endl;
}

void User::modifyAuction()
{
    char commID[MAX_COMM_NAME_SIZE+1];
    std::cout << "请输入您要修改的竞拍信息的商品ID：";
    fgets(commID, MAX_COMM_NAME_SIZE+1, stdin);
    if(checkID('M', commID))
    {
        int seq;
        std::cout << "请输入要进行的操作(1.修改竞拍单价 2.修改竞拍数量 3.取消竞拍）";
        std::cin >> seq;
        if(checkNum())
            /*此处仅能确保seq是整数*/
            file.modifyAuctionInfo(userID, commID, seq);
        else
            PROMPT_OPERATION_NUMBER_ERROR;
    }
    else
        PROMPT_MODIFICATION_FAILURE("商品输入不合法");
}

void User::modifyCommInfo() const
{
    int seq;
    char id[MAX_ID_SIZE+1], seller[MAX_ID_SIZE+1];
    std::cout << "请输入要修改的商品的ID：";
    fgets(id, MAX_ID_SIZE+1, stdin);
    if(checkID('M', id))
    {
        bool found = file.findComm(seller, id, file.onAuctionCommList());        
        if(!found || !equal(seller, userID))
        {
            PROMPT_MODIFICATION_FAILURE("未在您发布的商品中找到该ID的商品");
            return;
        }
        std::cout << "请输入要修改的商品的属性(1.价格 2.描述）：";
        std::cin >> seq;
        if(!checkNum())
            PROMPT_OPERATION_NUMBER_ERROR;
        else
        {
            /*修改商品价格*/
            if(seq == 1)
            {
                double price;
                std::cout << "请输入新的价格：";
                std::cin >> price;
                if(checkNum())
                {
                    file.modifyCommPrice(id, price);
                    PROMPT_MODIFICATION_SUCCEEED;
                }
                else
                    PROMPT_MODIFICATION_FAILURE("商品价格输入不合法");
            }
            /*修改商品描述*/
            else if(seq == 2)
            {
                char description[MAX_COMM_DESCRIPTION_SIZE+1];
                std::cout << "请输入新的描述：";
                fgets(description, MAX_COMM_DESCRIPTION_SIZE+1, stdin);
                if(checkStr(description, MAX_COMM_DESCRIPTION_SIZE))
                {
                    file.modifyCommDesc( id, description);
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
    char commID[MAX_ID_SIZE+1], seller[MAX_ID_SIZE+1];
    assignment(userID, seller);
    std::cout << "请输入要下架的商品的ID：";
    fgets(commID, MAX_ID_SIZE+1, stdin);
    if(checkID('M', commID))
    {
        bool found = file.findComm(seller, commID, file.onAuctionCommList());
        if(!found || !equal(seller, userID))
        {
            PROMPT_PULL_FAILURE("未在您发布的商品中找到该ID的商品");
            return;
        }
        if(file.beAuctioned(commID))
        {
            PROMPT_PULL_FAILURE("该商品已有用户拍下");
            return;
        }
        std::cout << "确认要下架该商品吗？" << std::endl;
        file.showCommDetail(commID);        

        std::cout << "请选择(y/n):";
        char confirm;
        std::cin >> confirm;
        cin.ignore(HUGE_NUM, '\n');
        if(tolower(confirm) == 'y')
        {
            file.modifyCommState(commID, REMOVED);
            std::cout << "下架成功！" << std::endl << std::endl;
        }
        else
            std::cout << "下架失败！" << std::endl << std::endl;
    }
    /*商品ID不是"M+三位数字"的形式*/
    else
        PROMPT_PULL_FAILURE("商品ID输入不合法");
}

void User::putawayComm() const
{
    PRINT_STAR_STRING;
    std::cout << "请输入您要重新上架的商品的ID：" ;
    char commID[MAX_ID_SIZE+1], seller[MAX_ID_SIZE+1];
    fgets(commID, MAX_COMM_NAME_SIZE+1, stdin);
    if(checkID('M',commID))
    {
        file.findComm(seller, commID, file.removedCommList());
        if(equal(userID, seller))
        {
            if(file.modifyCommState(commID, ON_AUCTION))
                std::cout << "重新上架成功！" << std::endl;
            else
                std::cout << "该商品无余货，无法重新上架！" << std::endl;               
        }
        else  
            std::cout << "未在您的下架商品中找到该ID的商品" << std::endl;
    }
    else    
        std::cout << "商品ID输入不合法，重新上架失败！" << std::endl;
    PRINT_STAR_STRING;
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
        char id[MAX_ID_SIZE+1];
        assignment(userID, id);      
        switch (seq)
        {
            case 1:
            {
                std::cout << starStr << std::endl;
                std::cout << "请注意用户名只能由英文字母和数字构成且不能超过10个字符" << std::endl;
                std::cout << starStr << std::endl;
                std::cout << "请输入修改后的用户名：" ;
                char newName[MAX_NAME_SIZE+1];
                fgets(newName, MAX_NAME_SIZE+1, stdin);
                if(checkAlnum(newName,MAX_NAME_SIZE))
                {
                    if(file.find(newName))
                        PROMPT_MODIFICATION_FAILURE("用户名已存在");
                    else
                    {                                          
                        file.modifyUserAttr(id, newName, 1);
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
                char newPhone[MAX_PHONENUMBER_SIZE+1];
                fgets(newPhone, MAX_PHONENUMBER_SIZE+1, stdin);
                if(checkDigits(newPhone,MAX_PHONENUMBER_SIZE))
                {
                    file.modifyUserAttr(id, newPhone, 2);
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
                char newAddress[MAX_ADDRESS_SIZE+1];
                fgets(newAddress, MAX_ADDRESS_SIZE+1, stdin);
                if(checkStr(newAddress,MAX_ADDRESS_SIZE))
                {
                    file.modifyUserAttr(id, newAddress, 3);
                    PROMPT_MODIFICATION_SUCCEEED;                          
                }
                else
                    PROMPT_MODIFICATION_FAILURE("地址不合法");
                break;;
            }
            default:
                PROMPT_OPERATION_NUMBER_ERROR;          
        }            
    }
}

void User::releaseCommodity() 
{
    char commName[MAX_COMM_NAME_SIZE+1], description[MAX_COMM_DESCRIPTION_SIZE+1];
    double price;
    int amount;

    std::cout << "请输入商品名称(不要超过20个字符）：";
    fgets(commName, MAX_COMM_NAME_SIZE+1, stdin);
    if(!checkStr(commName,MAX_COMM_NAME_SIZE))
    {
        PROMPT_RELEASE_FAILURE("商品名称不合法，可能包含 ‘,' 号");
        return;
    }

    std::cout << "请输入商品价格：";
    std::cin >> price;
    if(!checkNum())
    {
        PROMPT_RELEASE_FAILURE("商品价格输入不合法");
        return;
    }
    
    std::cout << "请输入商品数量：";
    std::cin >> amount;
    if(!checkNum())
    {
        PROMPT_RELEASE_FAILURE("商品数量输入不合法");
        return;
    }

    std::cout << "请输入商品描述：";
    fgets(description, MAX_COMM_DESCRIPTION_SIZE+1, stdin);
    if(!checkStr(description,MAX_COMM_DESCRIPTION_SIZE))
    {
        PROMPT_RELEASE_FAILURE("商品描述输入不合法");
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
        char seller[MAX_ID_SIZE+1];
        assignment(userID, seller);
        file.addCommodity(seller, commName, price, amount, description);
        std::cout << "商品发布成功！" << std::endl << std::endl;
    }
    else
        std::cout << "商品发布失败！" << std::endl << std::endl;


}

void User::searchCommodity() const
{
    char commName[MAX_COMM_NAME_SIZE+1];
    std::cout << "请输入商品名称：" ;
    fgets(commName, MAX_COMM_NAME_SIZE+1, stdin);
    /*因为商品名都不包含‘,'，所以当输入商品名包含','时无需查找*/
    if(!checkStr(commName, MAX_COMM_NAME_SIZE))
        std::cout << "没有找到您想要的商品，返回用户主界面！" << std::endl << std::endl;
    else
        file.showSpecificComms(commName, USER);    
}

void User::topUp()
{
    double money;
    std::cout << "请输入要充值的金额(请不要在金额的中间或者结尾加入空格)：" ;
    std::cin >> money;
    if(!checkNum() || money <= 0)
        std::cout << "输入不合法，充值失败！" << std::endl << std::endl;
    else
    {
        char id[MAX_ID_SIZE+1];
        assignment(userID, id);
        int curBalance = file.modifyUserBal(id, money);
        std::cout << "充值成功，当前余额：" <<curBalance <<  std::endl << std::endl;
    }
}

void User::viewAllAuctions() 
{
    file.showAuctions(userID);
}

/*买家查看在拍商品列表*/
void User::viewAllComms() const
{
    file.showAllComms(USER);
}

void User::viewUserInfo() const
{
    char id[MAX_ID_SIZE+1];
    assignment(userID, id);
    file.showUserInfo(id);    
}	

/*买家查看在拍商品的详细信息*/
void User::viewCommDetail() const
{
    char id[MAX_ID_SIZE+1], seller[MAX_ID_SIZE+1];
    std::cout << "请输入您想要查看的商品的ID：";
    fgets(id, MAX_ID_SIZE+1, stdin);
    if(checkID('M', id))
    {
        bool found = file.findComm(seller, id, file.onAuctionCommList());
        if(found)
            file.showCommDetail(id);    
        else
            std::cout << "未在正在拍卖的商品中找到ID为 " << id << " 的商品!" << std:: endl << std::endl;
    }
    else
        std::cout << "商品ID输入不合法！" << std::endl << std::endl;
}

void User::viewBuyerOrders() const
{
    char id[MAX_ID_SIZE+1];
    assignment(userID, id);
    file.showOrders(id, BUYER);

}

void User::viewSellerOrders() const 
{
    char id[MAX_ID_SIZE+1];
    assignment(userID, id);
    file.showOrders(id, SELLER);
}

/*卖家查看已发布商品*/
void User::viewReleasedComm() const
{
    char id[MAX_ID_SIZE+1];
    assignment(userID, id);
    file.showSellerComms(userID);
}

