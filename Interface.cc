#include"Administrator.h"
#include"User.h"
#include"Prompt.h"
#define HUGE_NUM 0X7FFFFFFF
Administrator* AdmLogin(RuntimeFile*);
User* UsrLogin(RuntimeFile*);
void SignIn(RuntimeFile*);
void EnterAdmInterface();
void EnterUserInterface();
void MainInterface(RuntimeFile* file)
{
    int seq;
    Administrator* adm;
    User* user;
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
                adm = AdmLogin(file);
                if(adm)
                    EnterAdmInterface();
                break;
            case 2:
                SignIn(file);
                break;
            case 3:
                user = UsrLogin(file);
                if(user)
                    EnterUserInterface();
                break;
            default:
                cout << "输入不合法，请输入正确的操作编号！"<<endl;
        }        
    }
}

void EnterAdmInterface()
{   
    while(1)
    {
        PromptAdm();
    }
}

void EnterUserInterface()
{
    while(1)
    {
        PromptUser();
    }
}

Administrator* AdmLogin(RuntimeFile* file)
{
    string name, passwd;
    cout << "请输入用户名： " ;
    cin >> name;
    cout << "请输入密码： " ;
    cin >> passwd;
    if(name == "admin" && passwd == "123456")
    {
        cout << "登陆成功！" << endl << endl;
        Administrator* adm = new Administrator(name, passwd);
        return adm;
    }
    else
    {
        cout << "用户名或密码错误，登录失败，返回主菜单！" << endl<<endl;
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
    LogFlag flag = file->matching(name, passwd);
    switch(flag)
    {
        case LOGIN_SUCCEED:   
        {
            User* usr = new User(name, passwd);
            cout << "登陆成功！" << endl<<endl;
            return usr;   
        }                  
        case NO_USER:
            cout << "用户不存在，请先注册！" << endl<<endl;
        case WRONG_PASSWD:
            cout << "密码错误，登录失败，返回主菜单！" << endl<<endl;
        default:;
    }  
    return nullptr;
}

void SignIn(RuntimeFile* file)
{
    /*
    用户输入用户名和密码;
    if(该用户名存在)
        提示用户输入用户名存在,注册失败；
    else
        在运行时用户文件创建一条新的用户记录；
        将该文件写入磁盘用户文件；
        提示注册成功；
    */
   string name, passwd;
   if(file->find(name))
        cout << "该用户名已存在，注册失败！" << endl << endl;
    else
    {
        file->AddUser(name, passwd);
        file->WriteUsrsFile();
        cout << "注册成功！" << endl << endl;
    }

}