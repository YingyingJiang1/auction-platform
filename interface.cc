#include "administrator.h"
#include "user.h"
#include "prompt.h"
#define HUGE_NUM 0X7FFFFFFF
Administrator *admLogin(RuntimeFile *);
User *usrLogin(RuntimeFile *);
void signIn(RuntimeFile *);
void enterAdmIntf(Administrator *);
void enterUserIntf(User *);
void logout(Administrator *, User *);

/*操作编号：1a 输入合法，代解决！*/
/*记得要限定输入的字符个数！*/

void mainIntf(RuntimeFile *file)
{
    int seq;
    Administrator *adm;
    User *user;
    while (1)
    {
        prompt();
        cin >> seq;
        if (cin.fail())
        {
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
            cin.clear();
            cin.ignore(HUGE_NUM, '\n');
            continue;
        }
        cin.ignore(HUGE_NUM, '\n');
        switch (seq)
        {
        case ADM_LOG_IN:
            adm = admLogin(file);
            if (adm)
                enterAdmIntf(adm);
            break;
        case USER_SIGN_IN:
            signIn(file);
            break;
        case USER_LOG_IN:
            user = usrLogin(file);
            if (user)
                enterUserIntf(user);
            break;
        case EXIT:
            return;
        default:
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
        }
    }
}

void enterAdmIntf(Administrator *adm)
{
    int seq;
    while (1)
    {
        promptAdm();
        cin >> seq;
        if (cin.fail())
        {
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
            cin.clear();
            cin.ignore(HUGE_NUM, '\n');
            continue;
        }
        cin.ignore(HUGE_NUM, '\n');
        switch (seq)
        {
        case ADM_VIEW_ALL_COMMS:
            adm->viewCommodities();
            break;
        case ADM_SEARCH_COMM:
            adm->searchCommodities();
            break;
        case ADM_PULL_COMM:
            adm->pullCommodity();
            break;
        case ADM_VIEW_ALL_ORDERS:
            adm->viewOrders();
            break;
        case ADM_VIEW_ALL_USERS:
            adm->viewUsrs();
            break;
        case ADM_BAN_USER:
            adm->banUsr();
            break;
        case ADM_LOG_OUT:
            return;
        default:
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
        }
    }
}

void enterBuyerIntf(User *user)
{
    int seq;
    while (1)
    {
        promptBuyer();
        cin >> seq;
        if (cin.fail())
        {
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
            cin.clear();
            cin.ignore(HUGE_NUM, '\n');
            continue;
        }
        cin.ignore(HUGE_NUM, '\n');
        switch (seq)
        {
        case BUYER_VIEW_COMM_LIST:
            user->viewCommodities();
            break;
        case BUYER_BUY_COMM:
            user->buy();
            break;
        case BUYER_SEARCH_COMM:
            user->searchCommodities();
            break;
        case BUYER_VIEW_ORDERS:
            user->viewBuyerOrders();
            break;
        case BUYER_VIEW_COMM_DETAIL:
            user->viewCommDetail();
            break;
        case BUYER_BACK_TO_USER_INTF:
            return;
        default:
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
        }
    }
}

void enterSellerIntf(User *user)
{
    int seq;
    while (1)
    {
        promptSeller();
        cin >> seq;
        if (cin.fail())
        {
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
            cin.clear();
            cin.ignore(HUGE_NUM, '\n');
            continue;
        }
        cin.ignore(HUGE_NUM, '\n');
        switch (seq)
        {
        case SELLER_RELEASE_COMM:
            user->releaseCommodity();
            break;
        case SELLER_VIEW_RELEASED_COMM:
            user->viewReleasedComm();
            break;
        case SELLER_MODIFY_COMM_INFO:
            user->modifyCommInfo();
            break;
        case SELLER_PULL_COMM:
            user->pullCommodity();
            break;
        case SELLER_VIEW_ORDERS:
            user->viewSellerOrders();
            break;
        case SELLER_BACK_TO_USER_INTF:
            return;
        default:
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
        }
    }
}

void enterInfoManageIntf(User *user)
{
    int seq;
    while (1)
    {
        promptPersonalInfo();
        cin >> seq;
        if (cin.fail())
        {
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
            cin.clear();
            cin.ignore(HUGE_NUM, '\n');
            continue;
            ;
        }
        cin.ignore(HUGE_NUM, '\n');
        switch (seq)
        {
        case VIEW_INFO:
            user->viewUsrInfo();
            break;
        case MODIFY_INFO:
            user->modifyUsrInfo();
            break;
        case TOP_UP:
            user->topUp();
            break;
        case BACK_TO_USER_INTF:
            return;
        default:
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
        }
    }
}

void enterUserIntf(User *user)
{
    int seq;
    while (1)
    {
        promptUser();
        cin >> seq;
        if (cin.fail())
        {
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
            cin.clear();
            cin.ignore(HUGE_NUM, '\n');
            continue;
            ;
        }
        cin.ignore(HUGE_NUM, '\n');
        switch (seq)
        {
        case BUYER_ROLE:
            enterBuyerIntf(user);
            break;
        case SELLER_ROLE:
            enterSellerIntf(user);
            break;
        case PERSONAL_INFO_MANAGEMENT:
            enterInfoManageIntf(user);
            break;
        case USER_LOG_OUT:
            logout(nullptr, user);
            return;
        default:
            cout << "输入不合法，请输入正确的操作编号！" << endl
                 << endl;
        }
    }
}

void logout(Administrator *adm, User *user)
{
    if (adm)
        delete adm;
    if (user)
        delete user;
}

Administrator *admLogin(RuntimeFile *file)
{
    string name, passwd;
    cout << "请输入用户名： ";
    cin >> name;
    cout << "请输入密码： ";
    cin >> passwd;
    if (name == "admin" && passwd == "123456")
    {
        cout << "登陆成功！" << endl
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

User *usrLogin(RuntimeFile *file)
{
    string name, passwd;
    cout << "请输入用户名： ";
    cin >> name;
    cout << "请输入密码： ";
    cin >> passwd;
    LogFlag flag = file->matching(name, passwd);
    switch (flag)
    {
    case LOGIN_SUCCEED:
    {
        User *usr = new User(name, passwd);
        cout << "登陆成功！" << endl
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

void signIn(RuntimeFile *file)
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
    cout << "请输入用户名：";
    cin >> name;
    cout << "请输入密码：";
    cin >> passwd;
    if (file->find(name))
        cout << "该用户名已存在，注册失败！" << endl  << endl;
    else
    {
        file->addUser(name, passwd);
        file->writeUsrsFile();
        cout << "注册成功！" << endl << endl;
    }
}