#ifndef MAIN_INTF_H
#define MAIN_INTF_H
#include "administrator.h"
#include "user.h"
extern char starStr[];
Administrator *admLogin();
User *userLogin();
void signIn();
void logout(Administrator *, User *);
#endif