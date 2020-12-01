#include<stdio.h>
#include"sha256.h"
#include"data_base.h"

int menu_select(void)
{
	char s[80];
	int c;

	printf("----------欢迎使用学生管理系统系统-------\n");
	printf("-----------------------------------------\n");
	printf("-------------- 1.输入信息 ---------------\n");
	printf("-------------- 2.删除信息 ---------------\n");
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
	Class* test;
	Class* temp;

	//test = All_class_input();
	//Output_all_class(test);
	//Save(test);
	temp = Load();
	Output_all_class(temp);

	while (1)
	{
		switch (menu_select())
		{
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		case 6:
			
			break;
		case 7:
			exit(0);
		}
		system("pause");
		system("CLS");
	}


	return 0;
}