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
    file.showUsers();
}
	
void Administrator::banUser() const
{
    string userID;
    std::cout << "请输入要封禁的用户的ID：" ;
    getline(cin,userID);
   if(checkID('U', userID))
   {
        for(int i = 0; i < file.usersSize; ++i)
        {
            if(equal(userID, file.usersFile[i].id))
            {
                std::cout << "是否确认封禁该用户?" << endl;
                std::cout << starStr << endl;
                PRINT_USER_ATTRS_NAME;
                PRINT_USER_ATTRS_VALUE;                                
                std::cout << starStr << endl;

                std::cout << "请输入(y/n): ";
                char ch;
                cin >> ch;
                if(tolower(ch) == 'y')
                {
                    file.usersFile[i].state = INACTIVE;
                    file.writeUsersFile("w");
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
        std::cout << "用户ID输入不合法，封禁失败！" << endl << endl;
}

void Administrator::pullCommodity() const
{
    string id;
    cout << "请输入要下架的商品的ID：";
    std::getline(cin ,id);
    if(checkID('M', id))
    {
        int i = file.getIndex(id);         
        if(i == file.commSize)
        {
            PROMPT_MODIFICATION_FAILURE("未找到该ID的商品");
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
            file.commoditiesFile[i].state = REMOVED;
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

void Administrator::searchCommodities() const
{
    string name;
    getline(cin , name);
    std::cout << "请输入商品名称：" ;
    file.showSpecificComms(name, 1);    
}

void Administrator::viewCommodities() const
{
    file.showCommodities();
}

void Administrator::viewOrders() const
{
    file.showOrders();
}

