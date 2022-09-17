#include"administrator.h"
extern string starStr;
void Administrator::viewUsrs() const
{
    file.showUsrs();
}
	
void Administrator::viewCommodities() const
{
    file.showCommodities();
}

void Administrator::viewOrders() const
{
    file.showOrders();
}

void Administrator::banUsr() const
{
    file.modifyUsrState();
}