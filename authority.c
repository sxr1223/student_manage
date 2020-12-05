#include "authority.h"

#define PWD_FILE_NAME "pwd.bin"

User user_now = guest;
Student* user_pt;

char admin_pwd[32] = { 0x8c,0x69,0x76,0xe5,0xb5,0x41,0x04,0x15,0xbd,0xe9,0x08,
					   0xbd,0x4d,0xee,0x15,0xdf,0xb1,0x67,0xa9,0xc8,0x73,0xfc,
					   0x4b,0xb8,0xa8,0x1f,0x6f,0x2a,0xb4,0x48,0xa9,0x18 };

void login(Class* cla_LL)
{
	char char_tem[MAX_NAME_SIZE + 1];
	Student* stu_tem = NULL;

	printf("please input your name(number).\n");
	scanf("%s", char_tem);
	if (!strcmp(char_tem, "admin"))
	{
		printf("please input your password.(default id number)\n");
		scanf("%s", char_tem);
		if (!sha256_confirm(char_tem, strlen(char_tem), admin_pwd))
		{
			user_now = admin;
			printf("login successful.\n");
		}
		else
		{
			printf("wrong password.\n");
			user_now = guest;
		}
		return;
	}
	while (cla_LL != NULL && stu_tem == NULL)
	{
		stu_tem = Find_Student_Name(cla_LL->student_LL, char_tem);
		cla_LL = cla_LL->next;
	}
	if (stu_tem == NULL)
	{
		printf("no such account.\n");
		return;
	}
	printf("please input your password.(default id number)\n");
	scanf("%s", char_tem);
	if (!sha256_confirm(char_tem, strlen(char_tem), stu_tem->pwd))
	{
		user_now = student;
		user_pt = stu_tem;
		printf("login successful.\n");
	}
	else
	{
		printf("wrong password.\n");
		user_now = guest;
	}
}

void Student_pwd_reset_All(Class* cla)
{
	Student* stu_tem;

	while (cla != NULL)
	{
		stu_tem = cla->student_LL;
		while (stu_tem != NULL)
		{
			sha256_calc(stu_tem->num, strlen(stu_tem->num), stu_tem->pwd);
			stu_tem = stu_tem->next;
		}
		cla = cla->next;
	}
}

void Change_pwd(Class* cla_LL)
{
	char name[MAX_NAME_SIZE + 1];
	char pwd[NUM_SIZE + 1];
	Student* stu_tem;
	FILE* fp;

	printf("please verify your authority.\n");
	user_now = guest;
	login(NULL);
	if (user_now != admin)
	{
		printf("wrong password or account.\n");
		return;
	}

	printf("please input the account you want to change password.\n");
	scanf("%s", name);
	if (!strcmp(name, "admin"))
	{
		printf("please input new password.\n");
		scanf("%s", pwd);
		sha256_calc(pwd, strlen(pwd), admin_pwd);

		fp = File_head_process(Write_pwd);
		fwrite(admin_pwd, 32 * sizeof(char), 1, fp);


		printf("change successful.\n");
		printf("please login again.\n");
		user_now = guest;
		while (user_now == guest)
		{
			login(NULL);
			system("pause");
			system("CLS");
		}
	}
	else
	{
		stu_tem = Find_Student_Name(cla_LL, name);
		if (stu_tem == NULL)
		{
			printf("no such account.\n");
			return 0;
		}
		printf("please input new password.\n");
		scanf("%s", pwd);
		sha256_calc(pwd, strlen(pwd), stu_tem->pwd);
		printf("change successful.\n");
	}
}

void Admin_pwd_Load(FILE* fp)
{
	fread(admin_pwd, 32 * sizeof(char), 1, fp);
}
