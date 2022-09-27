#ifndef MACRO_H
#define MACRO_H
#define PROMPT_OPERATION_NUMBER_ERROR \
std::cout << "输入不合法，请输入正确的操作编号！" << std::endl << std::endl
#define PROMPT_MODIFICATION_SUCCEEED std::cout << "修改成功！" << std::endl << std::endl

#define PROMPT_MODIFICATION_FAILURE(reason) \
std::cout << reason << "，修改失败！" << std::endl << std::endl

#define PROMPT_RELEASE_FAILURE(reason) \
std::cout << reason << "，发布失败！" << std::endl << std::endl

#define PROMPT_AUCTION_FAILURE(reason) \
std::cout << reason << "， 参与竞拍失败！" << std::endl << std::endl

#define PROMPT_PULL_FAILURE(reson) \
std::cout << reson << "，下架失败！" << std::endl << std::endl;

#define PROMPT_NO_INFO(type) \
std::cout << "无" << type << "信息" << std::endl

#define PRINT_STAR_STRING \
std::cout << starStr << std::endl

#define PRINT_AUCTION_INFO_NAME \
printf("%-10s   %-10s   %-10s   %-20s\n", "commID", "unitPrice", "amount", "date")

#define PRINT_AUCTION_INFO_VALUE \
printf("%-10s   %-10lf   %-10d   %-20s\n", ptrList->commID, ptrInfo->unitPrice, ptrInfo->amount, ptrInfo->date)

#define PRINT_COMM_ATTRS_NAME \
printf("%-6s    %-20s   %-10s   %-20s     %-10s   %-10s     %-10s\n",\
            "CommID","CommName","Price","AddedDate", "Amount","SellerID", "State")
    
#define PRINT_USER_ATTRS_NAME \
printf("%-6s    %-10s   %-20s   %-40s   %-10s   %-10s\n", \
                "UserID","UserName","PhoneNumber","Address","Balance","UserState")
            
#define PRINT_BUYER_ORDER_ATTRS_NAME \
printf("%-10s    %-10s   %-10s   %-10s   %-20s   %-10s\n", \
            "OrderID", "CommID", "UnitPrice", "Amount", "Date", "SellerID")

#define PRINT_BUYER_ORDER_ATTRS_VALUE \
printf("%-10s    %-10s   %-10lf   %-10d   %-20s   %-10s\n", \
                    ordersFile[i].buyerID, ordersFile[i].commodityID, ordersFile[i].unitPrice, \
                    ordersFile[i].amount, ordersFile[i].date, ordersFile[i].sellerID)

#define PRINT_SELLER_ORDER_ATTRS_NAME \
printf("%-6s    %-6s   %-10s   %-10s   %-20s   %-10s\n", \
            "OrderID", "CommID", "UnitPrice", "Amount", "Date", "BuyerID")

#define PRINT_SELLER_ORDER_ATTRS_VALUE \
printf("%-6s    %-6s   %-10lf   %-10d   %-20s   %-10s\n", \
                    ordersFile[i].id, ordersFile[i].commodityID, ordersFile[i].unitPrice, \
                    ordersFile[i].amount, ordersFile[i].date, ordersFile[i].buyerID)

#define PRINT_ORDER_ATTRS_NAME \
printf("%-6s    %-6s   %-10s   %-10s   %-20s   %-10s    %-10s\n", \
            "OrderID", "CommID", "UnitPrice", "Amount", "Date", "SellerID","BuyerID")

#define PRINT_ORDER_ATTRS_VALUE \
printf("%-6s    %-6s   %-10lf   %-10d   %-20s   %-10s   %-10s\n", \
            ordersFile[i].id, ordersFile[i].commodityID, ordersFile[i].unitPrice, \
            ordersFile[i].amount, ordersFile[i].date, ordersFile[i].sellerID, ordersFile[i].buyerID)


#endif