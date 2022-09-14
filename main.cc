#include "include.h"
#define HUGE_NUM 0X7FFFFFFF
using namespace std;

void Prompt();
Administrator* AdmLogin(RuntimeFile*);
User* UsrLogin(RuntimeFile*);
void SignIn(RuntimeFile*);
int main()
{
    int seq;
    RuntimeFile file;
    while(1)
    {
        Prompt();
        cin >> seq;
        cin.clear();
        cin.ignore(HUGE_NUM, '\n');
       if(seq == 4)
            break;
        switch(seq)
        {
            case 1:
                AdmLogin(&file);
                break;
            case 2:
                SignIn(&file);
                break;
            case 3:
                UsrLogin(&file);
                break;
            default:
                cout << "输入不合法，请输入正确的操作编号！"<<endl;
        }        
    }
    return 0;
}

void Prompt()
{
    string str = "====================================================";
    cout << str << endl;
    cout << "1.管理员登陆    2.用户注册  3.用户登陆  4.退出程序"<< endl;
    cout << str << endl;
    cout <<  "请输入要进行的操作的编号:  ";
}

Administrator* AdmLogin(RuntimeFile* file)
{
    /*
    打印输入提示信息,用户输入用户名和密码；
    if(用户名和密码匹配)
        创建管理员/用户对象并返回
    else
        打印出错提示信息；返回空指针；
    */
    string name, passwd;
    cout << "请输入用户名： " ;
    cin >> name;
    cout << "请输入密码： " ;
    cin >> passwd;
    if(name == "admin" && passwd == "123456")
    {
        cout << "登陆成功！" << endl;
        Administrator adm(name, passwd);
        return &adm;
    }
    else
    {
        cout << "用户名或密码错误！" << endl;
        return nullptr;
    }
}

User* UsrLogin(RuntimeFile* file)
{
     string name, passwd;
    cout << "请输入用户名： " ;
    cin >> name;
    cout << "请输入密码： " ;
    cin >> passwd;
    LogFlag flag = file->find(name, passwd);
    switch(flag)
    {
        case LOGIN_SUCCEED:   
        {
            User usr(name, passwd);
            cout << "登陆成功！" << endl;
            return &usr;   
        }                  
        case NO_USER:
            cout << "用户不存在，请先注册！" << endl;
        case WRONG_PASSWD:
            cout << "密码错误！" << endl;
        default:;
    }  
    return nullptr;
}

void SignIn(RuntimeFile* file)
{
    
}