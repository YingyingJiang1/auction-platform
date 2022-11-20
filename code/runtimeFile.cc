#include "runtimeFile.h"
#include <fstream>
#include <cstdio>
#include <ctime>
#include <assert.h>
#include "promptMacro.h"
#include "strOperation.h"
#include <iostream>
using namespace std;

#define PRINT_COMM_ATTRS_VALUE                                             \
    printf("%-6s    %-20s   %-10lf   %-20s     %-10d   %-10s     %-10s\n", \
           cur->id, cur->name, cur->price, cur->addedDate,                 \
           cur->amount, cur->sellerID, cur->state ? "ON_AUCTION" : "REMOVED")
#define PRINT_USER_ATTRS_VALUE                                                           \
    printf("%-6s    %-10s   %-20s   %-40s   %-10lf   %-10s\n",                           \
           usersFile[i].id, usersFile[i].name, usersFile[i].phone, usersFile[i].address, \
           usersFile[i].balance, usersFile[i].state == ACTIVE ? "ACTIVE" : "INACTIVE");
char starStr[120] = "*****************************************************************************************************************";
inline int min(int a, int b)
{
    return a < b ? a : b;
}

RuntimeFile::RuntimeFile(int defaultSize)
{
    size = defaultSize * 10;
    maxUserSize = defaultSize;
    usersFile = new UserEntry[maxUserSize];
    ordersFile = new OrderEntry[size];
    usersSize = 0;
    orderSize = 0;
    commAmount = 0;
    auctionList = NULL;
    listTail = NULL;
    onAuctionComms = NULL;
    removedComms = NULL;
    previous = NULL;
   readToAucList();
   readToUsers();
   readToComms();
    readToOrders();
}

RuntimeFile::~RuntimeFile()
{
    delete[] usersFile;
    delete[] ordersFile;
    if (onAuctionComms)
        freeList(onAuctionComms);
    if (removedComms)
        freeList(removedComms);
    AuctionList *cur = auctionList;
    while (cur)
    {
        AuctionList *tmp = cur;
        freeList(cur->head);
        cur = cur->next;
        delete tmp;
    }
}

RuntimeFile RuntimeFile::operator=(RuntimeFile fFile)
{
}

RuntimeFile::RuntimeFile(const RuntimeFile &rFile)
{
}

/*新增商品，将商品写入商品文件*/
void RuntimeFile::addCommodity(const char *seller, const char *name, double price, int amount, const char *description)
{
    ++commAmount;
    CommodityEntry *ptr = new CommodityEntry;
    assignID('M', ptr->id, commAmount);
    assignment(name, ptr->name);
    assignment(description, ptr->description);
    assignment(seller, ptr->sellerID);
    assignCurDate(ptr->addedDate);
    ptr->price = price;
    ptr->amount = amount;
    ptr->state = ON_AUCTION;
    ptr->next = onAuctionComms;
    onAuctionComms = ptr;

    writeCommsFile("a");
}

/*新增订单，将订单写入订单文件*/
OrderEntry *RuntimeFile::addOrder(const char *commID, const char *buyerID, const char *sellerID,
                                  int amount, double unitPrice)
{
    /*为订单的各属性赋值*/
    if (orderSize == size)
        overflowProcess();
    assignment(commID, ordersFile[orderSize].commodityID);
    assignment(buyerID, ordersFile[orderSize].buyerID);
    assignment(sellerID, ordersFile[orderSize].sellerID);
    assignID('T', ordersFile[orderSize].id, orderSize + 1);
    assignCurDate(ordersFile[orderSize].date);
    ordersFile[orderSize].amount = amount;
    ordersFile[orderSize].unitPrice = unitPrice;
    ++orderSize;

    writeOrdersFile("a");
}

/*有新用户参与竞拍，在竞拍列表中新增一条竞拍信息,新增成功返回true*/
bool RuntimeFile::addAuctionInfo(const char *commID, const char *buyer, double unitPrice, int amount)
{
    /*对用户的竞拍数量和余额进行检查*/
    findCommID(commID, onAuctionComms);
    if (amount > previous->amount)
    {
        std::cout << "您要求的竞拍数量超过了商品现存数量，参与竞拍失败！" << std::endl;
        return false;
    }
    int i = getIndex(buyer);
    if (unitPrice * amount > usersFile[i].balance)
    {
        std::cout << "参与竞拍失败！余额不足，请先充值！" << std::endl;
        return false;
    }

    /*新增竞拍信息*/
    AuctionInfo *ptrInfo = new AuctionInfo;
    assignment(buyer, ptrInfo->bidderID);
    assignCurDate(ptrInfo->date);
    ptrInfo->amount = amount;
    ptrInfo->unitPrice = unitPrice;

    /*先在竞拍列表中查找该商品ID的节点是否存在*/
    AuctionList *cur = auctionList;
    while (cur)
    {
        if (equal(commID, cur->commID))
            break;
        cur = cur->next;
    }
    /*竞拍列表没有该商品ID的竞拍信息，需要
    先创建, 要保证竞拍列表中的节点按照商品的发布时间升序排列*/
    if (NULL == cur)
    {
        AuctionList *ptr = new AuctionList;
        ptr->next = NULL;
        assignment(commID, ptr->commID);
        findCommID(commID, onAuctionComms);
        assignment(previous->addedDate, ptr->startDate);
        ptr->bidderNum = 1;
        ptr->head = NULL;
        /*对竞拍列表根据商品的发布时间进行排序*/
        if (NULL == auctionList)
            auctionList = ptr;
        else
        {
            AuctionList *listCur = auctionList, *listPre = listCur;
            while (listCur)
            {
                if (!myGreater(ptr->startDate, listCur->startDate))
                    break;
                listPre = listCur;
                listCur = listCur->next;
            }
            ptr->next = listCur;
            if (auctionList == listCur)
                auctionList = ptr;
            else
                listPre->next = ptr;
        }
        /*为该商品加入竞拍信息并写入竞拍文件*/
        ptrInfo->next = ptr->head;
        ptr->head = ptrInfo;
        writeAuctionFile("w");
        return true;
    }
    /*竞拍列表有该商品的竞拍信息，寻找合适位置插入新的信息，
    要求所有竞拍信息首先按照unitPrice降序排列，unitPrice相等时
    按date升序排列*/
    else
    {
        ++cur->bidderNum;
        AuctionInfo *head = sortList(cur->head, ptrInfo);
        cur->head = head;
        writeAuctionFile("w");
        return true;
    }
}

/*新增用户写入用户文件*/
void RuntimeFile::addUser(const char *name, const char *passwd)
{
    /*为用户各属性赋值*/
    assignment(name, usersFile[usersSize].name);
    assignment(passwd, usersFile[usersSize].passwd);
    assignment("modify your address", usersFile[usersSize].address);
    assignment("phoneNumber", usersFile[usersSize].phone);
    usersFile[usersSize].balance = 0.0;
    usersFile[usersSize].state = ACTIVE;
    ++usersSize;
    /*从0开始存放数据，用户id号从1开始*/
    assignID('U', usersFile[usersSize - 1].id, usersSize);

    writeUsersFile("a");
}

/*将数值amount转换为三位字符串（不足三位在前面补0），然后将转换得到的字符串赋值给id*/
void RuntimeFile::assignID(char category, char *id, int amount)
{
    id[0] = category;
    char str[MAX_ID_SIZE + 1];
    /*%03d means if "amount" is less than three digits then make up 0 in front */
    sprintf(str, "%03d", amount);

    for (int i = 1; i < MAX_ID_SIZE; ++i)
        id[i] = str[i - 1];
    id[MAX_ID_SIZE] = 0;
}

/*日期格式为：年-月-日 时:分:秒*/
void RuntimeFile::assignCurDate(char *date)
{
    time_t rawtime;
    struct tm *ptminfo;

    time(&rawtime);
    ptminfo = localtime(&rawtime);
    sprintf(date, "%02d-%02d-%02d %02d:%02d:%02d",
            ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
            ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
}

/*检查ID为commID的商品是否有用户参与竞拍，有则返回true*/
bool RuntimeFile::beAuctioned(const char *commID)
{
    AuctionList *ptrList = auctionList;
    while (ptrList)
    {
        if (equal(commID, ptrList->commID))
            return true;
        ptrList = ptrList->next;
    }
    return false;
}

inline int toSeconds(int year, int month, int day, int hour, int minute, int second)
{
    int dayToSeconds = 24 * 60 * 60;
    int sum = 0;
    bool leap = false;
    if (year % 4 == 0)
    {
        sum += 366 * dayToSeconds;
        leap = true;
    }
    else
        sum += 365 * dayToSeconds;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        sum += 30 * dayToSeconds;
    else if (month == 2)
    {
        if (leap)
            sum += 29 * dayToSeconds;
        else
            sum += 28 * dayToSeconds;
    }
    else
        sum += 31 * dayToSeconds;
    sum = sum + hour * 60 * 60 + minute * 60 + second;
    return sum;
}

bool RuntimeFile::checkDateExpired(const char* startDate, int auctionDuration)
{
    struct tm timeInfo;
    strptime(startDate, "%Y-%m-%d %H:%M:%S",  &timeInfo);
    time_t timeStamp = mktime(&timeInfo);
    if(time(nullptr) - timeStamp >= auctionDuration)
        return true;
    return false;
}
/*
这里写的有点问题，还没改 
bool RuntimeFile::checkDateExpired(const char *startDate, int auctionDuration)
{
    int now = 0, before = 0;
    char nowDate[MAX_DATE_SIZE + 1];
    time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    int year = ptminfo->tm_year + 1900, month = ptminfo->tm_mon + 1, day = ptminfo->tm_mday;
    int sYear, sMonth, sDay, sHour, sMinute, sSecond;
    sscanf(startDate, "%d-%d-%d %d:%d:%d", &sYear, &sMonth, &sDay, &sHour, &sMinute, &sSecond);
    now = toSeconds(year, month, day, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
    before = toSeconds(sYear, sMonth, sDay, sHour, sMinute, sSecond);
    if (now - before >= auctionDuration)
        return true;
    return false;
}
*/

/*检查竞拍列表中的商品是否到期，如果到期就进行结算，为成功竞拍的用户创建相应订单，
并把已经完成结算的商品节点从竞拍列表中删去*/
void RuntimeFile::checkAuctionList()
{
    AuctionList *cur = auctionList, *pre = cur;
    /*对于头节点需要单独处理*/
    while (cur)
    {
        if (checkDateExpired(cur->startDate, AUCTION_DURATION))
        {
            endAuction(cur);
            /*在竞拍列表中删除当前结点*/
            if (cur == auctionList)
            {
                auctionList = cur->next;
                delete cur;
                cur = auctionList;
                pre = cur;
            }
            else
            {
                pre->next = cur->next;
                delete cur;
                cur = pre->next;
            }
            writeAuctionFile("w");
        }
        else
        {
            pre = cur;
            cur = cur->next;
        }
    }
}

/*检查所有在拍商品是否到期，到期就下架*/
void RuntimeFile::checkCommExpired()
{
    checkAuctionList();
    CommodityEntry *cur = onAuctionComms;
    while (cur)
    {
        if (checkDateExpired(cur->addedDate, AUCTION_DURATION))
            modifyCommState(cur->id, REMOVED);
        cur = cur->next;
    }
}

bool RuntimeFile::checkUnitPrice(const char *commID, double unitPrice)
{
    findCommID(commID, onAuctionComms);
    if (unitPrice < previous->price)
        return false;
    return true;
}

void RuntimeFile::endAuction(const AuctionList *ptr)
{
    findCommID(ptr->commID, onAuctionComms);
    int left = previous->amount, sumPrice = 0, tradeAmount = 0;
    AuctionInfo *curPtr = ptr->head;
    /*将当前商品的所有竞拍进行结算*/
    while (curPtr && left > 0)
    {
        int i = getIndex(curPtr->bidderID);
        int j = getIndex(previous->sellerID);
        tradeAmount = min(left, curPtr->amount);
        sumPrice = curPtr->unitPrice * tradeAmount;
        if (usersFile[i].balance >= sumPrice)
        {
            usersFile[i].balance -= sumPrice;
            usersFile[j].balance += sumPrice;
            writeUsersFile("w");
            addOrder(ptr->commID, curPtr->bidderID, previous->sellerID, tradeAmount, curPtr->unitPrice);
            left -= tradeAmount;
        }
        curPtr = curPtr->next;
    }
    previous->amount = left;
    /*释放为该商品存储的竞拍信息*/
    if (ptr->head)
        freeList(ptr->head);

    modifyCommState(ptr->commID, REMOVED);
    writeCommsFile("w");
}

/*查找是否有用户名为name的用户，有就返回true*/
bool RuntimeFile::find(const char *name) const
{
    for (int i = 0; i < usersSize; ++i)
    {
        if (equal(name, usersFile[i].name))
            return true;
    }
    return false;
}

/*在commList中寻找ID为commID的商品，如果找到把该商品的卖家ID赋给seller,然后返回true*/
bool RuntimeFile::findComm(char *seller, const char *commID, CommodityEntry *commList)
{
    int state = (commList == onAuctionComms) ? ON_AUCTION : REMOVED;
    findCommID(commID, commList);
    if (previous)
    {
        assignment(previous->sellerID, seller);
        return true;
    }
    return false;
}

/*在commList中查找商品ID为commID的商品，previous指向该商品节点*/
inline void RuntimeFile::findCommID(const char *commID, CommodityEntry *commList)
{
    /*previous为空或者previous指向的节点不是要查找的商品，需要遍历整个链表*/

    if (!previous || !equal(commID, previous->id))
    {
        previous = commList;
        while (previous)
        {
            if (equal(commID, previous->id))
                break;
            previous = previous->next;
        }
    }
    else
    {
        /*防止出现此类情况：previous保留的历史值所指向的节点恰好是目标商品，因此不用进行链表遍历，
        但可能出现该商品是下架状态，而本次调用要求在在拍商品链表中进行搜索（不确定会不会出现这种情况，但还是
        加上这个判断比较好）*/
        int state = commList == onAuctionComms ? ON_AUCTION : REMOVED;
        if (previous->state != state)
            previous = NULL;
    }
}

/*如果用户ID为bidder的用户参与了商品ID为commID的竞拍，返回true*/
AuctionInfo *RuntimeFile::findUserInAucList(const char *bidder, const char *commID)
{
    AuctionList *ptrList = auctionList;
    AuctionInfo *ptrInfo = NULL;
    while (ptrList)
    {
        if (equal(commID, ptrList->commID))
        {
            ptrInfo = ptrList->head;
            while (ptrInfo)
            {
                if (equal(bidder, ptrInfo->bidderID))
                    return ptrInfo;
                ptrInfo = ptrInfo->next;
            }
        }
        ptrList = ptrList->next;
    }
    return NULL;
}

/*释放头节点为head的链表的内存空间*/
template <typename T>
void RuntimeFile::freeList(T *head)
{
    T *cur = head;
    while (cur)
    {
        T *tmp = cur;
        cur = cur->next;
        delete tmp;
    }
}

/*查找ID为id的用户或订单文件条目的索引*/
int RuntimeFile::getIndex(const char *id) const
{
    int i = 0;
    /*查找用户ID*/
    if (id[0] == 'U')
    {
        for (; i < usersSize; ++i)
            if (equal(id, usersFile[i].id))
                break;
    }
    else if (id[0] == 'T')
    {
        for (; i < orderSize; ++i)
            if (equal(id, ordersFile[i].id))
                break;
    }
    return i;
}

/*检查用户名和密码是否匹配*/
LogFlag RuntimeFile::matching(const char *name, const char *passwd) const
{
    int i = 0;
    for (; i < usersSize; ++i)
    {
        if (equal(name, usersFile[i].name))
        {
            if (equal(passwd, usersFile[i].passwd))
            {
                if (usersFile[i].state == ACTIVE)
                    return LOGIN_SUCCEED;
                else
                    return BANNED;
            }
            else
                return WRONG_PASSWD;
        }
    }
    if (i == usersSize)
        return NO_USER;
}

/*修改竞拍者bidder对商品ID为commID的竞拍信息，修改后仍要保证链表有序，option为1，修改竞拍单价
option为2修改竞拍数量，option为3取消竞拍(但传入的参数option并不能确保只有1、2、3这三种可能*/
void RuntimeFile::modifyAuctionInfo(const char *bidder, const char *commID, int option)
{
    AuctionList *ptrList = auctionList, *preList = ptrList;
    AuctionInfo *preInfo, *curInfo;
    /*寻找竞拍者为bidder，商品ID为commID的竞拍信息*/
    while (ptrList)
    {
        if (equal(commID, ptrList->commID))
        {
            curInfo = ptrList->head, preInfo = curInfo;
            while (curInfo)
            {
                if (equal(bidder, curInfo->bidderID))
                    break;
                preInfo = curInfo;
                curInfo = curInfo->next;
            }
            break;
        }
        preList = ptrList;
        ptrList = ptrList->next;
    }
    if (!curInfo)
    {
        PROMPT_MODIFICATION_FAILURE("您没有参与该商品的竞拍");
        return;
    }

    /*修改竞拍价格*/
    if (1 == option)
    {
        std::cout << "请输入新的竞拍单价：";
        double unitPrice;
        std::cin >> unitPrice;
        if (checkNum() && unitPrice > 0)
        {
            findCommID(commID, onAuctionComms);
            if (unitPrice < previous->price)
            {
                PROMPT_MODIFICATION_FAILURE("竞拍单价低于低价");
                return;
            }
            assignCurDate(curInfo->date);
            if (curInfo->unitPrice > unitPrice)
            {
                curInfo->unitPrice = unitPrice;
                /*将当前节点和该结点后面的节点进行排序，排序完成后
                将该节点前面的部分的尾部和后面的部分的头部连接起来*/
                if (curInfo->next)
                {
                    AuctionInfo *head = sortList(curInfo->next, curInfo);
                    if (curInfo == ptrList->head)
                        ptrList->head = head;
                    else
                        preInfo->next = head;
                }
            }
            else if (curInfo->unitPrice < unitPrice)
            {
                curInfo->unitPrice = unitPrice;
                if (curInfo == ptrList->head)
                    ptrList->head = curInfo->next;
                else
                    preInfo->next = curInfo->next;
                AuctionInfo *head = sortList(ptrList->head, curInfo);
                ptrList->head = head;
            }
            else
                curInfo->unitPrice = unitPrice;
            PROMPT_MODIFICATION_SUCCEEED;
        }
        else
        {
            PROMPT_MODIFICATION_FAILURE("竞拍价格输入不合法");
            return;
        }
    }
    /*修改竞拍数量*/
    else if (2 == option)
    {
        std::cout << "请输入新的竞拍数量：";
        int amount;
        std::cin >> amount;
        if (checkNum() && amount > 0)
        {
            findCommID(commID, onAuctionComms);
            if (previous->amount < amount)
            {
                PROMPT_MODIFICATION_FAILURE("竞拍数量超过商品现存数量");
                return;
            }               
            assignCurDate(curInfo->date);
            curInfo->amount = amount;
            if (curInfo->next)
            {
                AuctionInfo *head = sortList(curInfo->next, curInfo);
                if (curInfo == ptrList->head)
                    ptrList->head = head;
                else
                    preInfo->next = head;
            }
            PROMPT_MODIFICATION_SUCCEEED;
        }
        else
        {
            PROMPT_MODIFICATION_FAILURE("竞拍数量输入不合法");
            return;
        }   
    }
    /*删除对该商品的竞拍，当该商品所有竞拍信息都被删除时，从auctionList中删除为该商品维护的竞拍节点*/
    else if (3 == option)
    {
        --ptrList->bidderNum;
        if (curInfo == ptrList->head)
            ptrList->head = curInfo->next;
        else
            preInfo->next = curInfo->next;
        delete curInfo;
        if (NULL == ptrList->head)
        {
            if (ptrList == auctionList)
                auctionList = ptrList->next;
            else
                preList->next = ptrList->next;
            delete ptrList;
        }
        cout << "成功取消对该商品的竞拍！" << endl << endl;
    }
    else
    {
        PROMPT_MODIFICATION_FAILURE("输入操作编号不合法");
        return;
    }
    writeAuctionFile("w");
}

void RuntimeFile::modifyCommAmount(const char *commID, int amount)
{
    findCommID(commID, onAuctionComms);
    if (!previous)
        findCommID(commID, removedComms);
    previous->amount = amount;
    writeCommsFile("w");
}

/*修改在拍商品的描述*/
void RuntimeFile::modifyCommDesc(const char *commID, const char *newDescription)
{
    findCommID(commID, onAuctionComms);
    assignment(newDescription, previous->description);
    writeCommsFile("w");
}

/*修改在拍商品的价格*/
void RuntimeFile::modifyCommPrice(const char *commID, double newPrice)
{
    findCommID(commID, onAuctionComms);
    if (previous)
        previous->price = newPrice;
    writeCommsFile("w");
}

/*修改商品状态为newState,成功修改返回true*/
bool RuntimeFile::modifyCommState(const char *commID, int newState)
{
    CommodityEntry *pre, *cur;
    /*将在拍商品下架*/
    if (newState == REMOVED)
    {
        cur = onAuctionComms, pre = cur;
        while (cur)
        {
            if (equal(commID, cur->id))
            {
                cur->state = newState;
                /*从在拍列表中删除*/
                if (cur == onAuctionComms)
                    onAuctionComms = cur->next;
                else
                    pre->next = cur->next;
                /*加入下架列表*/
                cur->next = removedComms;
                removedComms = cur;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
    }
    /*将已下架商品重新上架*/
    else
    {
        cur = removedComms, pre = cur;
        while (cur)
        {
            if (equal(commID, cur->id))
            {
                /*商品数量为0时不可以重新上架*/
                if (cur->amount == 0)
                    return false;
                cur->state = newState;
                assignCurDate(cur->addedDate);
                /*从下架列表中删除*/
                if (cur == removedComms)
                    removedComms = cur->next;
                else
                    pre->next = cur->next;
                /*加入在拍列表*/
                cur->next = onAuctionComms;
                onAuctionComms = cur;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
    }
    writeCommsFile("w");
    return true;
}

/*根据option修改用户相对应的属性(1.用户名 2.联系方式 3.地址）*/
void RuntimeFile::modifyUserAttr(const char *userID, const char *newInfo, int option)
{
    int i = getIndex(userID);
    /*修改用户名*/
    if (USER_NAME == option)
        assignment(newInfo, usersFile[i].name);
    /*修改联系方式*/
    else if (PHONE_NUMBER == option)
        assignment(newInfo, usersFile[i].phone);
    /*修改地址*/
    else if (ADDRESS == option)
        assignment(newInfo, usersFile[i].address);
    /*修改密码*/
    else if (PASSWD == option)
        assignment(newInfo, usersFile[i].passwd);

    writeUsersFile("w");
}

/*将用户余额加上money并返回新的余额*/
int RuntimeFile::modifyUserBal(const char *userID, double money)
{
    int i = getIndex(userID);
    usersFile[i].balance += money;
    writeUsersFile("w");
    return usersFile[i].balance;
}

bool RuntimeFile::modifyUserState(const char *userID, int newState)
{
    int i = getIndex(userID);
    if (i == usersSize || usersFile[i].state == newState)
        return false;
    usersFile[i].state = newState;
    writeUsersFile("w");
    return true;
}

void RuntimeFile::overflowProcess()
{
    if (usersSize == maxUserSize)
    {
    }
    else if (orderSize == size)
    {
    }
}

void RuntimeFile::readToAucList()
{
    FILE *input = fopen("auction.txt", "r");
    int ret = 0;
    AuctionList *ptrList;
    AuctionInfo *ptrInfo, *tail;
    if (input)
    {
        while (1)
        {
            ptrList = new AuctionList;
            ptrList->next = NULL;
            ret = fscanf(input, "%[^,]%*c%[^,]%*c%d\n",
                         ptrList->commID, ptrList->startDate, &ptrList->bidderNum);
            if (ret != 3)
                break;
            ptrList->head = NULL;
            if (NULL == auctionList)
                auctionList = ptrList;
            else
                listTail->next = ptrList;
            listTail = ptrList;

            for (int i = 0; i < ptrList->bidderNum; ++i)
            {
                ptrInfo = new AuctionInfo;
                ret = fscanf(input, "%[^,]%*c%[^,]%*c%lf%*c%d\n", ptrInfo->bidderID,
                             ptrInfo->date, &ptrInfo->unitPrice, &ptrInfo->amount);
                assert(ret == 4);
                ptrInfo->next = NULL;
                if (NULL == ptrList->head)
                    ptrList->head = ptrInfo;
                else
                    tail->next = ptrInfo;
                tail = ptrInfo;
            }
        }
    }
}

/*用户文件结构：userID userName passewd phone address balance userState*/
/*商品文件结构：commID commName price amount description sellerID addedDate state*/
/*订单文件结构：orderID commID unitPrice amount date sellerID buyerID*/
void RuntimeFile::readToComms()
{
    FILE *input = fopen("commodities.txt", "r");
    int ret = 0;
    if (input)
    {
        while (1)
        {
            CommodityEntry *ptr = new CommodityEntry;
            ret = fscanf(input, "%[^,]%*c%[^,]%*c%lf%*c%d%*c%[^,]%*c%[^,]%*c%[^,]%*c%d\n",
                         ptr->id, ptr->name, &ptr->price,
                         &ptr->amount, ptr->description,
                         ptr->sellerID, ptr->addedDate, &ptr->state);
            if (ret != 8)
                break;
            if (ON_AUCTION == ptr->state)
            {
                ptr->next = onAuctionComms;
                onAuctionComms = ptr;
            }
            else
            {
                ptr->next = removedComms;
                removedComms = ptr;
            }
            ++commAmount;
        }
        fclose(input);
    }
}

void RuntimeFile::readToOrders()
{
    FILE *input = fopen("orders.txt", "r");
    int ret = 0;
    if (input)
    {
        while (1)
        {
            ret = fscanf(input, "%[^,]%*c%[^,]%*c%lf%*c%d%*c%[^,]%*c%[^,]%*c%s\n",
                         ordersFile[orderSize].id, ordersFile[orderSize].commodityID, &ordersFile[orderSize].unitPrice,
                         &ordersFile[orderSize].amount, ordersFile[orderSize].date, ordersFile[orderSize].sellerID,
                         ordersFile[orderSize].buyerID);
            if (ret != 7)
                break;
            ++orderSize;
        }
        fclose(input);
    }
}

void RuntimeFile::readToUsers()
{
    FILE *input = fopen("users.txt", "r");
    int ret = 0;
    if (input)
    {
        while (1)
        {
            ret = fscanf(input, "%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%lf%*c%d\n",
                         usersFile[usersSize].id, usersFile[usersSize].name, usersFile[usersSize].passwd,
                         usersFile[usersSize].phone, usersFile[usersSize].address, &usersFile[usersSize].balance,
                         &usersFile[usersSize].state);
            if (ret != 7)
                break;
            ++usersSize;
        }
        fclose(input);
    }
}

/*查找用户名为userName的用户的ID并赋值给userID*/
void RuntimeFile::getUserID(const char *userName, char *userID) const
{
    for (int i = 0; i < usersSize; ++i)
        if (equal(userName, usersFile[i].name))
            assignment(usersFile[i].id, userID);
}

/*查找用户ID为userID的用户，如果找到返回true，否则返回false*/
bool RuntimeFile::findUser(const char *userID) const
{
    for (int i = 0; i < usersSize; ++i)
    {
        if (equal(userID, usersFile[i].id))
            return true;
    }
    return false;
}

inline void RuntimeFile::printComms(CommodityEntry *commList, bool &printed) const
{
    CommodityEntry *cur = commList;
    while (cur)
    {
        if (!printed)
        {
            PRINT_COMM_ATTRS_NAME;
            printed = true;
        }
        PRINT_COMM_ATTRS_VALUE;
        cur = cur->next;
    }
}

/*在commList查找并打印卖家ID为sellerID的商品，printed保证最多只打印一边用户属性名*/
inline void RuntimeFile::printSellerComms(CommodityEntry *commList, const char *sellerID, bool &printed) const
{
    CommodityEntry *cur = commList;
    while (cur)
    {
        if (equal(sellerID, cur->sellerID))
        {
            if (!printed)
            {
                PRINT_COMM_ATTRS_NAME;
                printed = true;
            }
            PRINT_COMM_ATTRS_VALUE;
        }
        cur = cur->next;
    }
}

/*打印所有商品列表，identity为管理员打印在拍和下架商品，
identity为用户只打印在拍商品*/
void RuntimeFile::showAllComms(int identity) const
{
    bool printed = false;
    PRINT_STAR_STRING;
    printComms(onAuctionComms, printed);
    if (identity == ADMIN)
        printComms(removedComms, printed);
    if (!printed)
        PROMPT_NO_INFO("商品");
    PRINT_STAR_STRING;
}

/*打印竞拍者ID为bidder的竞拍信息*/
void RuntimeFile::showAuctions(char *bidder) const
{
    AuctionList *ptrList = auctionList;
    AuctionInfo *ptrInfo;
    bool printed = false;
    PRINT_STAR_STRING;
    while (ptrList)
    {
        ptrInfo = ptrList->head;
        while (ptrInfo)
        {
            if (equal(bidder, ptrInfo->bidderID))
            {
                if (!printed)
                {
                    PRINT_AUCTION_INFO_NAME;
                    printed = true;
                }
                PRINT_AUCTION_INFO_VALUE;
            }
            ptrInfo = ptrInfo->next;
        }
        ptrList = ptrList->next;
    }
    if (!printed)
        PROMPT_NO_INFO("竞拍");
    PRINT_STAR_STRING;
}

/*打印商品ID为commID的商品的详细信息*/
void RuntimeFile::showCommDetail(const char *commID)
{
    findCommID(commID, onAuctionComms);
    PRINT_STAR_STRING;
    std::cout << "商品ID：" << previous->id << std::endl;
    std::cout << "商品名称：" << previous->name << std::endl;
    std::cout << "商品价格：" << previous->price << std::endl;
    std::cout << "上架时间：" << previous->addedDate << std::endl;
    std::cout << "商品描述：" << previous->description << std::endl;
    std::cout << "商品卖家：" << previous->sellerID << std::endl;
    if (previous->state == ON_AUCTION)
        std::cout << "商品状态："
                  << "ON_AUCTION" << std::endl;
    else
        std::cout << "商品状态"
                  << "REMOVED" << std::endl;
    PRINT_STAR_STRING;
}

/*打印被封禁的用户信息*/
void RuntimeFile::showInactiveUsers() const
{
    PRINT_STAR_STRING;
    bool printed = false;
    for (int i = 0; i < usersSize; ++i)
    {
        if (usersFile[i].state == INACTIVE)
        {
            if (!printed)
            {
                PRINT_USER_ATTRS_NAME;
                printed = true;
            }
            PRINT_USER_ATTRS_VALUE;
        }
    }
    if (!printed)
        PROMPT_NO_INFO("封禁用户");
    PRINT_STAR_STRING;
}

/*identity分为卖家和买家，打印买家或卖家的ID为userID的订单信息*/
void RuntimeFile::showOrders(const char *userID, int identity) const
{
    bool printed = false;
    PRINT_STAR_STRING;
    if (BUYER == identity)
    {
        for (int i = 0; i < orderSize; ++i)
            if (equal(userID, ordersFile[i].buyerID))
            {
                if (!printed)
                {
                    PRINT_BUYER_ORDER_ATTRS_NAME;
                    printed = true;
                }
                PRINT_BUYER_ORDER_ATTRS_VALUE;
            }
        if (!printed)
            PROMPT_NO_INFO("订单");
    }
    else if (SELLER == identity)
    {
        for (int i = 0; i < orderSize; ++i)
            if (equal(userID, ordersFile[i].sellerID))
            {
                if (!printed)
                {
                    PRINT_BUYER_ORDER_ATTRS_NAME;
                    printed = true;
                }
                PRINT_BUYER_ORDER_ATTRS_VALUE;
            }
        if (!printed)
            PROMPT_NO_INFO("订单");
    }
    PRINT_STAR_STRING;
}

/*打印卖家ID为sellerID的商品，包括在拍的和下架的,printed保证最多只打印一遍属性名*/
void RuntimeFile::showSellerComms(const char *sellerID)
{
    PRINT_STAR_STRING;
    bool printed = false;
    printSellerComms(onAuctionComms, sellerID, printed);
    printSellerComms(removedComms, sellerID, printed);
    if (!printed)
        PROMPT_NO_INFO("商品");
    PRINT_STAR_STRING;
}

/*打印商品名为name的商品的信息，identity为管理员则包括在拍和下架商品，
identity为用户只包括在拍商品,管理员的identity设置为1， 用户的identity设置为0*/
void RuntimeFile::showSpecificComms(char *name, int identity) const
{
    cout << starStr << endl;
    /*noOutput主要是为了防止在没有找到商品的时候输出属性名以及
    找到商品时输出多行属性名*/
    bool noOutput = true;
    /*在正在拍卖的商品中查找*/
    CommodityEntry *cur = onAuctionComms;
    while (cur)
    {
        if (equal(name, cur->name))
        {
            noOutput = false;
            break;
        }
        cur = cur->next;
    }
    /*是用户,不用再查找已下架商品*/
    if (noOutput && !identity)
        cout << "没有找到您想要的商品！返回用户主界面！" << endl;
    else
    {
        /*打印正在拍卖的商品中符合要求的商品信息*/
        if (!noOutput)
        {
            PRINT_COMM_ATTRS_NAME;
            while (cur)
            {
                if (equal(name, cur->name))
                    PRINT_COMM_ATTRS_VALUE;
                cur = cur->next;
            }
        }
        /*管理员还需要在下架商品中查找*/
        if (identity)
        {
            cur = removedComms;
            if (noOutput)
            {
                while (cur)
                {
                    if (equal(name, cur->name))
                    {
                        noOutput = false;
                        break;
                    }
                    cur = cur->next;
                }
                if (!noOutput)
                    PRINT_COMM_ATTRS_NAME;
                else
                    std::cout << "没有找到您想要的商品，返回管理员主界面！" << std::endl
                              << std::endl;
            }
            while (cur)
            {
                if (equal(name, cur->name))
                    PRINT_COMM_ATTRS_VALUE;
                cur = cur->next;
            }
        }
    }
    cout << starStr << endl;
}

/*打印所有订单信息*/
void RuntimeFile::showAllOrders() const
{

    cout << starStr << endl;
    if (orderSize == 0)
        PROMPT_NO_INFO("订单");
    else
    {
        PRINT_ORDER_ATTRS_NAME;
        for (int i = 0; i < orderSize; ++i)
            PRINT_ORDER_ATTRS_VALUE;
    }
    cout << starStr << endl;
}

/*打印所有用户信息*/
void RuntimeFile::showAllUsers() const
{
    std::cout << starStr << endl;
    PRINT_USER_ATTRS_NAME;
    for (int i = 0; i < usersSize; ++i)
    {
        printf("%-6s    %-10s   %-20s   %-40s   %-10lf   ",
               usersFile[i].id, usersFile[i].name, usersFile[i].phone, usersFile[i].address,
               usersFile[i].balance);
        if (usersFile[i].state)
            printf("%-10s\n", "ACTIVE");
        else
            printf("%-10s\n", "INACTIVE");
    }
    std::cout << starStr << endl;
}

/*打印用户ID为userID的用户的详细信息*/
void RuntimeFile::showUserInfo(const char *userID) const
{
    int i = getIndex(userID);
    PRINT_STAR_STRING;
    std::cout << "用户ID：" << usersFile[i].id << std::endl;
    std::cout << "用户名：" << usersFile[i].name << std::endl;
    std::cout << "联系方式：" << usersFile[i].phone << std::endl;
    std::cout << "地址：" << usersFile[i].address << std::endl;
    std::cout << "钱包余额：" << usersFile[i].balance << std::endl;
    PRINT_STAR_STRING;
}

void RuntimeFile::writeAuctionFile(const char *mode)
{
    FILE *output = fopen("auction.txt", mode);
    AuctionList *ptrList = auctionList;
    AuctionInfo *ptrInfo;
    while (ptrList)
    {
        fprintf(output, "%s,%s,%d\n",
                ptrList->commID, ptrList->startDate, ptrList->bidderNum);
        ptrInfo = ptrList->head;
        while (ptrInfo)
        {
            fprintf(output, "%s,%s,%lf,%d\n",
                    ptrInfo->bidderID, ptrInfo->date, ptrInfo->unitPrice, ptrInfo->amount);
            ptrInfo = ptrInfo->next;
        }
        ptrList = ptrList->next;
    }
    fclose(output);
}

AuctionInfo *RuntimeFile::sortList(AuctionInfo *head, AuctionInfo *ptrInfo)
{
    AuctionInfo *curInfo = head, *preInfo = head;
    /*头节点为空*/
    if (NULL == head)
    {
        ptrInfo->next = NULL;
        head = ptrInfo;
    }
    /*单独处理插入在头节点前面的情况*/
    else if (ptrInfo->unitPrice > head->unitPrice || (ptrInfo->unitPrice == head->unitPrice && !myGreater(ptrInfo->date, head->date)))
    {
        ptrInfo->next = head;
        head = ptrInfo;
    }
    else
    {
        /*寻找合适的位置插入*/
        curInfo = curInfo->next;
        while (curInfo)
        {
            if (ptrInfo->unitPrice > curInfo->unitPrice || (ptrInfo->unitPrice == curInfo->unitPrice && !myGreater(ptrInfo->date, curInfo->date)))
                break;
            preInfo = curInfo;
            curInfo = curInfo->next;
        }
        ptrInfo->next = curInfo;
        preInfo->next = ptrInfo;
    }
    return head;
}

/*将所有商品信息写入商品磁盘文件，mode指出写入模式，
"w"表示先清空再全部写入，"a"表示在已有文件内容后追加新的内容*/
void RuntimeFile::writeCommsFile(const char *mode)
{
    FILE *output = fopen("commodities.txt", mode);
    /*append to file*/
    if (mode[0] == 'a')
    {
        fprintf(output, "%s,%s,%lf,%d,%s,%s,%s,%d\n", onAuctionComms->id, onAuctionComms->name,
                onAuctionComms->price, onAuctionComms->amount, onAuctionComms->description,
                onAuctionComms->sellerID, onAuctionComms->addedDate, onAuctionComms->state);
    }
    /*clean contents of file before writing*/
    else
    {
        CommodityEntry *cur = onAuctionComms;
        while (cur)
        {
            fprintf(output, "%s,%s,%lf,%d,%s,%s,%s,%d\n", cur->id, cur->name,
                    cur->price, cur->amount, cur->description,
                    cur->sellerID, cur->addedDate, cur->state);
            cur = cur->next;
        }
        cur = removedComms;
        while (cur)
        {
            fprintf(output, "%s,%s,%lf,%d,%s,%s,%s,%d\n", cur->id, cur->name,
                    cur->price, cur->amount, cur->description,
                    cur->sellerID, cur->addedDate, cur->state);
            cur = cur->next;
        }
    }
    fclose(output);
}

/*将所有订单信息写入商品磁盘文件，mode指出写入模式，
"w"表示先清空再全部写入，"a"表示在已有文件内容后追加新的内容*/
void RuntimeFile::writeOrdersFile(const char *mode)
{
    FILE *output = fopen("orders.txt", mode);
    /*append to file*/
    if (mode[0] == 'a')
    {
        fprintf(output, "%s,%s,%lf,%d,%s,%s,%s\n", ordersFile[orderSize - 1].id, ordersFile[orderSize - 1].commodityID,
                ordersFile[orderSize - 1].unitPrice, ordersFile[orderSize - 1].amount, ordersFile[orderSize - 1].date,
                ordersFile[orderSize - 1].sellerID, ordersFile[orderSize - 1].buyerID);
    }
    /*clean contents of file before writing*/
    else
    {
        for (int i = 0; i < orderSize; ++i)
            fprintf(output, "%s,%s,%lf,%d,%s,%s,%s\n", ordersFile[i].id, ordersFile[i].commodityID,
                    ordersFile[i].unitPrice, ordersFile[i].amount, ordersFile[i].date,
                    ordersFile[i].sellerID, ordersFile[i].buyerID);
    }
    fclose(output);
}

/*将所有用户信息写入商品磁盘文件，mode指出写入模式，
"w"表示先清空再全部写入，"a"表示在已有文件内容后追加新的内容*/
void RuntimeFile::writeUsersFile(const char *mode)
{
    FILE *output = fopen("users.txt", mode);
    /*append to file*/
    if (mode[0] == 'a')
    {
        fprintf(output, "%s,%s,%s,%s,%s,%lf,%d\n", usersFile[usersSize - 1].id, usersFile[usersSize - 1].name,
                usersFile[usersSize - 1].passwd, usersFile[usersSize - 1].phone, usersFile[usersSize - 1].address,
                usersFile[usersSize - 1].balance, usersFile[usersSize - 1].state);
    }
    /*clean contents of file before writing*/
    else
    {
        for (int i = 0; i < usersSize; ++i)
            fprintf(output, "%s,%s,%s,%s,%s,%lf,%d\n", usersFile[i].id, usersFile[i].name, usersFile[i].passwd,
                    usersFile[i].phone, usersFile[i].address, usersFile[i].balance, usersFile[i].state);
    }
    fclose(output);
}