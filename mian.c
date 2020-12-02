#include<stdio.h>
#include<stdlib.h>
#include"sha256.h"
#include"data_base.h"

int menu_select(void)
{
	char s[80];
	int c;

	printf("----------欢迎使用学生管理系统系统-------\n");
	printf("-----------------------------------------\n");
	printf("-------------- 1.输入信息 ---------------\n");
	printf("-------------- 2.修改数据 ---------------\n");
	printf("-------------- 3.显示信息 ---------------\n");
	printf("-------------- 4.查找     ---------------\n");
	printf("-------------- 5.存档     ---------------\n");
	printf("-------------- 6.读档     ---------------\n");
	printf("-------------- 7.退出     ---------------\n");
	printf("-----------------------------------------\n");
	do
	{
		printf("\nPlease enter your choice:\n");
		gets(s);
		c = atoi(s);
	} while (c < 0 || c>7);

	return c;
}

int main(void)
{
	Class* cla_LL = NULL;

	while (1)
	{
		switch (menu_select())
		{
		case 1:
			cla_LL->next = All_class_input(cla_LL);
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
			break;
		case 7:
			exit(0);
		}
		system("pause");
		system("CLS");
	}


	return 0;
}