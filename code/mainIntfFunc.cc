
#include"administrator.h"
#include"user.h"
#include"strOperation.h"
#include<stdio.h>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
bool inputName(char* name);
bool inputPasswd(char* passwd);

void logout(Administrator *adm, User *user)
{
    if (adm)
        delete adm;
    if (user)
        delete user;
}

Administrator *admLogin()
{
    char name[MAX_NAME_SIZE+1], passwd[MAX_PASSEWD_SIZE+1];
    if(!inputName(name))
    {
        cout << "不是合法的用户名，登陆失败!" << endl;
        return NULL;
    }
    if(!inputPasswd(passwd))
    {
        cout << "密码不合法，登陆失败！" << endl << endl;
        return NULL;
    }
    if (equal(name, "admin") && equal(passwd, "123456"))
    {
        cout << "登录成功！" << endl << endl;
        Administrator *adm = new Administrator;
        return adm;
    }
    else
    {
        cout << "用户名或密码错误，登录失败，返回主菜单！" << endl<< endl;
        return nullptr;
    }
}

User *userLogin()
{
    char name[MAX_NAME_SIZE+1], passwd[MAX_PASSEWD_SIZE+1];
    if(!inputName(name))
    {
        cout << "不是合法的用户名，登陆失败!" << endl;
        return NULL;
    }
    if(!inputPasswd(passwd))
    {
        cout << "密码不合法，登陆失败！" << endl << endl;
        return NULL;
    }

    LogFlag flag = file.matching(name, passwd);
    switch (flag)
    {
    case LOGIN_SUCCEED:
    {
        User *user = new User(name);
        cout << "登录成功！" << endl << endl;
        return user;
    }
    case NO_USER:
        cout << "用户不存在，请先注册！" << endl << endl;
        return NULL;
    case WRONG_PASSWD:
        cout << "密码错误，登录失败，返回主菜单！" << endl << endl;
        return NULL;
    case BANNED:
        cout << "您已被管理员封禁，无法登陆！" << endl << endl;
        return NULL;
    }
}

void signIn()
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
    char name[MAX_NAME_SIZE+1], passwd[MAX_PASSEWD_SIZE+1];    
    cout << endl;
    cout << starStr <<endl;
    cout << "请注意:" << endl;
    cout << "用户名和密码都只能包含数字和英文字母" << endl;
    cout << "用户名不能超过10个字符，密码不能超过20个字符" << endl;
    cout << starStr <<endl;

    if(!inputName(name))
    {
        cout << "用户名不合法，注册失败！" << endl << endl;
        return;
    }
    if(!inputPasswd(passwd))
    {
        cout << "密码不合法，注册失败！" << endl << endl;
    }
    
    else if (file.find(name))
        cout << "该用户名已存在，注册失败！" << endl  << endl;
    else
    {
        file.addUser(name, passwd);
        cout << "注册成功！" << endl << endl;
    }
}

inline bool  inputName(char* name)
{
    cout << "请输入用户名： ";
    fgets(name, MAX_NAME_SIZE+1, stdin);
    if(!checkAlnum(name,MAX_NAME_SIZE))
        return false;
    return true;
}

inline bool inputPasswd(char* passwd)
{
    cout << "请输入密码： ";
    fgets(passwd, MAX_PASSEWD_SIZE+1, stdin);
    if(!checkAlnum(passwd, MAX_PASSEWD_SIZE) )
        return false;
    return true;
}

/*
void applyForUnban()
{
    char userID[MAX_ID_SIZE+1];
    std::cout << "请输入您的用户ID：" ;
    fgets(userID, MAX_ID_SIZE+1, stdin);
    if(checkID('U', userID))
    {

    }
    else
        std::cout << "用户ID输入不合法！" << std::endl;
}
*/