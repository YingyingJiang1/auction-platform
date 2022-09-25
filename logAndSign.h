#ifndef LOG_AND_SIGN_H
#define LOG_AND_SIGN_H
#include "administrator.h"
#include "user.h"
extern char starStr[];
Administrator *admLogin();
User *userLogin();
void signIn();
void logout(Administrator *, User *);
#endif