#include"administrator.h"
void Administrator::viewUsers() const
{
    file.showUsers();
}
	
void Administrator::banUser() const
{
    file.modifyUserState();
}

void Administrator::pullCommodity() const
{

}

void Administrator::searchCommodities() const
{

}

void Administrator::viewCommodities() const
{
    file.showCommodities();
}

void Administrator::viewOrders() const
{
    file.showOrders();
}

