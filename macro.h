#ifndef MACRO_H
#define MACRO_H
#define PROMPT_OPERATION_NUMBER_ERROR \
std::cout << "输入不合法，请输入正确的操作编号！" << std::endl << std::endl
#define PROMPT_MODIFICATION_SUCCEEED std::cout << "修改成功！" << std::endl << std::endl
#define PROMPT_MODIFICATION_FAILURE(reason) \
std::cout << reason << "，修改失败！" << std::endl << std::endl

#define PRINT_COMM_ATTRS_NAME \
printf("%-6s    %-20s   %-10s   %-10s     %-10s   %-10s     %-10s\n",\
            "CommID","CommName","Price","AddedDate", "Amount","SellerID", "State")
    
#define PRINT_USER_ATTRS_NAME \
printf("%-6s    %-10s   %-20s   %-40s   %-10s   %-10s\n", \
                "UserID","UserName","PhoneNumber","Address","Balance","UserState")
            
#endif