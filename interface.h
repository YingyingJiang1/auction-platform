#ifndef INTERFACE_H
#define INTERFACE_H
#include "administrator.h"
#include "user.h"
#include "prompt.h"
#include"type.h"
Administrator *admLogin();
User *userLogin();
void signIn();
void logout(Administrator *, User *);
#endif