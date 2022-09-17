#ifndef INTERFACE_H
#define INTERFACE_H
#include "administrator.h"
#include "user.h"
#include "prompt.h"
#include"type.h"
#define HUGE_NUM 0X7FFFFFFF
Administrator *admLogin();
User *usrLogin();
void signIn();
void logout(Administrator *, User *);
#endif