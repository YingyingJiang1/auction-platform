#include"administrator.h"
#define PRINT_COMM_ATTRS_VALUE \
printf("%-6s    %-20s   %-10lf   %-10s     %-10d   %-10s     %-10d\n",\
            file.commoditiesFile[i].id, file.commoditiesFile[i].name, file.commoditiesFile[i].price, file.commoditiesFile[i].addedDate,\
            file.commoditiesFile[i].number, file.commoditiesFile[i].sellerID, file.commoditiesFile[i].state)

#define PRINT_USER_ATTRS_VALUE \
                       printf("%-6s    %-10s   %-20s   %-40s   %-10lf  %-10d\n", \
                            file.usersFile[i].id, file.usersFile[i].name, file.usersFile[i].phone, \
                            file.usersFile[i].address,file.usersFile[i].balance,file.usersFile[i].state)

void Administrator::viewUsers() const
{
    file.showAllUsers();
}
	
void Administrator::banUser() const
{
    char userID[MAX_ID_SIZE+1];
    std::cout << "请输入要封禁的用户的ID：" ;
    fgets(userID, MAX_ID_SIZE+1, stdin);
    if(checkID('U', userID))
   {
       bool found = file.findUser(userID);
       if(found)
       {
           std::cout << "是否确认封禁该用户?" << endl;
           file.showUserInfo(userID);

           std::cout << "请输入(y/n): ";
            char confirm;
            cin >> confirm;
            if(tolower(confirm) == 'y')
            {
                file.modifyUserState(userID, INACTIVE);
                std::cout << "封禁成功！" << endl << endl;
            }
            else
                std::cout << "封禁失败！" << endl << endl;
       }                                        
        else
            std::cout << "用户ID不存在，封禁失败！" << endl <<endl;
   }
    else
        std::cout << "用户ID输入不合法，封禁失败！" << endl << endl;
}

void Administrator::pullCommodity() const
{
    char id[MAX_ID_SIZE+1], seller[MAX_ID_SIZE+1];
    cout << "请输入要下架的商品的ID：";
    fgets(id, MAX_ID_SIZE+1, stdin);
    if(checkID('M', id))
    {
        bool found = file.findComm(seller, id, file.onAuctionCommList());
        if(!found)
            found = file.findComm(seller, id, file.removedCommList());
        if(!found)
        {
            PROMPT_MODIFICATION_FAILURE("未找到该ID的商品");
            return;
        }
        if(file.beAuctioned(id))
        {
            PROMPT_PULL_FAILURE("该商品已有用户拍下");
            return;
        }            
        std::cout << "确认要下架该商品吗？" << std::endl;
        file.showCommDetail(id);

        std::cout << "请选择(y/n):";
        char confirm;
        std::cin >> confirm;
        if(tolower(confirm) == 'y')
        {
            file.modifyCommState(id, REMOVED);
            std::cout << "下架成功！" << std::endl << std::endl;
        }
        else
            std::cout << "下架失败！" << std::endl << std::endl;
    }
    /*商品ID不是"M+三位数字"的形式*/
    else
        PROMPT_MODIFICATION_FAILURE("商品ID输入不合法");
}

void Administrator::searchCommodities() const
{
    char commName[MAX_COMM_NAME_SIZE+1];
    std::cout << "请输入商品名称：" ;
    fgets(commName, MAX_COMM_NAME_SIZE+1, stdin);
    /*因为商品名都不包含‘,'，所以当输入商品名包含','时无需查找*/
    if(!checkStr(commName, MAX_COMM_NAME_SIZE))
        std::cout << "没有找到您想要的商品，返回管理员主界面！" << std::endl << std::endl;
    file.showSpecificComms(commName, ADMIN);    
}

void Administrator::unbanUser() const
{
    char userID[MAX_ID_SIZE+1];
    std::cout << "请输入您要解除封禁的用户的ID：";
    fgets(userID, MAX_ID_SIZE+1, stdin);
    if(checkID('U', userID))
    {
        if(file.modifyUserState(userID, ACTIVE))
            std::cout << "成功解封用户 " << userID << " ！" << std::endl << std::endl;
        else
            std::cout << "该用户不存在或该用户未被封禁！" << std::endl << std::endl;
    }
    else
        std::cout << "用户ID输入不合法，解封用户失败！" << std::endl << std::endl;
}

void Administrator::viewAllBannedUsers() const
{
    file.showInactiveUsers();
}

void Administrator::viewCommodities() const
{
    file.showAllComms(ADMIN);
}

void Administrator::viewOrders() const
{
    file.showAllOrders();
}
