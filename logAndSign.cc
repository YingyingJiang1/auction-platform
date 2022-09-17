
#include"administrator.h"
#include"user.h"
extern string starStr;
void logout(Administrator *adm, User *user)
{
    if (adm)
        delete adm;
    if (user)
        delete user;
}
/*判断字符串是否只包含数字和英文字母，且符合长度*/
bool checkAlnum(string str, int size)
{
    if(str.length() > size)
        return false;
    for(int i = 0; i < str.length(); ++i)
    {
        if(!isalnum(str[i]))
            return false;
    }
    return true;
}

Administrator *admLogin()
{
    string name, passwd;
    cout << "请输入用户名： ";
    getline(cin, name);
    cout << "请输入密码： ";
    getline(cin, passwd);
    if (name == "admin" && passwd == "123456")
    {
        cout << "登录成功！" << endl
             << endl;
        Administrator *adm = new Administrator(name, passwd);
        return adm;
    }
    else
    {
        cout << "用户名或密码错误，登录失败，返回主菜单！" << endl
             << endl;
        return nullptr;
    }
}

User *usrLogin()
{
    string name, passwd;
    cout << "请输入用户名： ";
    getline(cin, name);
    cout << "请输入密码： ";
    getline(cin, passwd);
    if(!checkAlnum(name,MAX_NAME_SIZE) ||!checkAlnum(passwd, MAX_PASSEWD_SIZE) )
    {
        cout << "用户名或密码不合法，登录失败！" <<endl <<endl;
        return nullptr;
    }
    LogFlag flag = file.matching(name, passwd);
    switch (flag)
    {
    case LOGIN_SUCCEED:
    {
        User *usr = new User(name, passwd);
        cout << "登录成功！" << endl
             << endl;
        return usr;
    }
    case NO_USER:
        cout << "用户不存在，请先注册！" << endl
             << endl;
    case WRONG_PASSWD:
        cout << "密码错误，登录失败，返回主菜单！" << endl
             << endl;
    default:;
    }
    return nullptr;
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
    string name, passwd;
    cout << endl;
    cout << starStr <<endl;
    cout << "请注意:" << endl;
    cout << "用户名和密码都只能包含数字和英文字母" << endl;
    cout << "用户名不能超过10个字符，密码不能超过20个字符" << endl;
    cout << starStr <<endl;
    cout << "请输入用户名：";
    getline(cin, name);
    cout << "请输入密码：";
    getline(cin, passwd);
    if(!checkAlnum(name,MAX_NAME_SIZE) ||!checkAlnum(passwd, MAX_PASSEWD_SIZE) )
        cout << "用户名或密码不合法，注册失败！" <<endl <<endl;
    else if (file.find(name))
        cout << "该用户名已存在，注册失败！" << endl  << endl;
    else
    {
        file.addUser(name, passwd);
        file.writeUsrsFile("a");
        cout << "注册成功！" << endl << endl;
    }
}