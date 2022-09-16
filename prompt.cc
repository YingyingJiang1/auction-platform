#include<string>
#include<iostream>
using namespace std;
static string str = "======================================================================="
"=============";
 
void prompt()
{
    cout << str << endl;
    cout << "                  1.管理员登陆    2.用户注册  3.用户登陆  4.退出程序"<< endl;
    cout << str << endl;
    cout <<  "请输入要进行的操作的编号:  ";
}

void promptAdm()
{
    cout << str << endl;
    cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销";
    cout << endl;
    cout << str << endl;
    cout << "请输入要进行的操作的编号：";
}

void promptUser()
{
    cout << str << endl;
    cout << "       1.我是买家     2. 我是卖家     3.个人信息管理      4.注销登陆" << endl;
    cout << str << endl;

}

void promptSeller()
{
    cout << str <<endl;
    cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面";
    cout << endl;
    cout << str << endl;
    cout << "请输入要进行的操作的编号：";
}

void promptBuyer()
{
    cout << str <<endl;
    cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面";
    cout << endl;
    cout << str <<endl;
    cout << "请输入要进行的操作的编号：";
}

void promptPersonalInfo()
{
    cout << str << endl;
    cout << "       1.查看信息      2.修改信息      3.充值      4.返回用户主界面" << endl;
    cout << str << endl;
    cout << "请输入要进行的操作的编号：";
}