#include<stdio.h>
#include"sha256.h"
#include"data_base.h"

int menu_select(void)
{
	char s[80];
	int c;

	printf("----------��ӭʹ��ѧ������ϵͳϵͳ-------\n");
	printf("-----------------------------------------\n");
	printf("-------------- 1.������Ϣ ---------------\n");
	printf("-------------- 2.ɾ����Ϣ ---------------\n");
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