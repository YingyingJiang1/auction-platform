#ifndef TYPE_H
#define TYPE_H
enum LogFlag{NO_USER= 1, WRONG_PASSWD,LOGIN_SUCCEED};
/*主菜单操作编号*/
#define ADM_LOG_IN  1
#define USER_SIGN_IN 2
#define USER_LOG_IN 3
#define EXIT 4

/*用户主菜单操作编号*/
#define BUYER_ROLE 1
#define SELLER_ROLE 2
#define PERSONAL_INFO_MANAGEMENT 3
#define USER_LOG_OUT 4

/*管理员菜单操作编号*/
#define ADM_VIEW_ALL_COMMS 1
#define ADM_SEARCH_COMM 2
#define ADM_PULL_COMM 3
#define ADM_VIEW_ALL_ORDERS 4
#define ADM_VIEW_ALL_USERS 5
#define ADM_BAN_USER 6
#define ADM_LOG_OUT 7

/*卖家操作菜单编号*/
#define SELLER_RELEASE_COMM 1
#define SELLER_VIEW_RELEASED_COMM 2
#define SELLER_MODIFY_COMM_INFO 3
#define SELLER_PULL_COMM 4
#define SELLER_VIEW_ORDERS 5
#define SELLER_BACK_TO_USER_INTF 6

/*买家操作菜单编号*/
#define BUYER_VIEW_COMM_LIST 1
#define BUYER_BUY_COMM 2
#define BUYER_SEARCH_COMM 3
#define BUYER_VIEW_ORDERS 4
#define BUYER_VIEW_COMM_DETAIL 5
#define BUYER_BACK_TO_USER_INTF 6

/*个人信息管理菜单操作编号*/
#define VIEW_INFO 1
#define MODIFY_INFO 2
#define TOP_UP 3
#define BACK_TO_USER_INTF 4

#define ACTIVE 1
#define INACTIVE 0
#endif