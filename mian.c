#include<stdio.h>
#include<stdlib.h>
#include"sha256.h"
#include"data_base.h"

int menu_select(void)
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