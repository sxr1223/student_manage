#include<stdio.h>
#include<stdlib.h>
#include"sha256.h"
#include"data_base.h"
#include"authority.h"

int menu_select_admin(void)
{
	char s[80];
	int c;

	printf("----------��ӭʹ��ѧ������ϵͳϵͳ-------\n");
	printf("-----------------------------------------\n");
	printf("-------------- 1.������Ϣ ---------------\n");
	printf("-------------- 2.�޸����� ---------------\n");
	printf("-------------- 3.��ʾ��Ϣ ---------------\n");
	printf("-------------- 4.����     ---------------\n");
	printf("-------------- 5.�浵     ---------------\n");
	printf("-------------- 6.����     ---------------\n");
	printf("-------------- 7.�˳�     ---------------\n");
	printf("-----------------------------------------\n");
	do
	{
		printf("\nPlease enter your choice:\n");
		gets(s);
		c = atoi(s);
	} while (c < 0 || c>7);

	return c;
}

int menu_select_student(void)
{
	char s[80];
	int c;

	printf("----------��ӭʹ��ѧ������ϵͳϵͳ-------\n");
	printf("-----------------------------------------\n");
	printf("-------------- 1.��ʾ��Ϣ ---------------\n");
	printf("-------------- 2.�浵     ---------------\n");
	printf("-------------- 3.����     ---------------\n");
	printf("-------------- 4.�˳�     ---------------\n");
	printf("-----------------------------------------\n");
	do
	{
		printf("\nPlease enter your choice:\n");
		gets(s);
		c = atoi(s);
	} while (c < 0 || c>7);

	return c;
}

void admin_surface(Class* cla_LL)
{
	while (1)
	{
		switch (menu_select_admin())
		{
		case 1:
			Del_Class_LL(&cla_LL);
			cla_LL = All_class_input(cla_LL);
			break;
		case 2:
			Change_data(cla_LL);
			break;
		case 3:
			Output_all_class(cla_LL);
			break;
		case 4:
			Find_data(cla_LL);
			getchar();
			break;
		case 5:
			Save(cla_LL);
			break;
		case 6:
			cla_LL = Load();
			printf("Load data from file success\n");
			break;
		case 7:
			exit(0);
		}
		system("pause");
		system("CLS");
	}
}

void student_surface(Class* cla_LL)
{
	while (1)
	{
		switch (menu_select_student())
		{
		case 1:
			Output_student(user_pt);
			break;
		case 2:
			Save(cla_LL);
			break;
		case 3:
			cla_LL = Load();
			printf("Load data from file success\n");
			break;
		case 4:
			exit(0);
		}
		system("pause");
		system("CLS");
	}
}

void pwd(Class* cla)
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

int main(void)
{
	Class* cla_LL = NULL;

	cla_LL = Load();
	//pwd(cla_LL);
	printf("welcome to use students manage system.\n");
	while (user_now == guest)
	{
		login(cla_LL);
		system("pause");
		system("CLS");
	}
	getchar();
	if (user_now == admin)
		admin_surface(cla_LL);
	if (user_now == student)
		student_surface(cla_LL);

	return 0;
}
