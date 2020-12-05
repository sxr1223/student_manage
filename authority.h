#ifndef __AUTHORITY
#define __AUTHORITY

#include <string.h>
#include<stdio.h>
#include"sha256.h"
#include"data_base.h"

typedef enum User
{
	guest,
	admin,
	teacher,
	student
}User;

extern Student* user_pt;
extern User user_now;
void login(Class* cla_LL);
void Student_pwd_reset_All(Class* cla);
void Change_pwd(Class* cla_LL);

#endif
