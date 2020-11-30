#include<stdio.h>
#include<string.h>
#include"data_base.h"


char* Output_subject(Course temp)
{
	switch (temp)
	{
	case higher_math: return "higher_math";
	case english_1: return "english_1";
	case english_2: return "english_2";
	case english_3: return "english_3";
	case english_4: return "english_4";
	default: return "error: no this subject code\n";
	}
}

void Output_student(Student* stu_tem)
{
	Subject* sub_tem;

	printf("********************************************\n");
	printf("name: %s\n", stu_tem->name);
	printf("num : %s\n\n", stu_tem->num);
	if (stu_tem->score_LL != NULL)
	{
		sub_tem = stu_tem->score_LL;
		printf("Score:\n");
		while (sub_tem != NULL)
		{
			printf("\tsubject: %s\n", Output_subject(sub_tem->course));
			printf("\tscore  : %.1f\n", sub_tem->score);
			sub_tem = sub_tem->next;
		}
	}
	printf("********************************************\n\n");
}

void Output_class(Class* cla_tem)
{
	Student* stu_tem;

	if (cla_tem == NULL)
		return;
	stu_tem = cla_tem->student_LL;
	while (stu_tem != NULL)
	{
		Output_student(stu_tem);
		stu_tem = stu_tem->next;
	}
}


Class* Class_init(void)
{
	Class* temp = malloc(sizeof(Class));
	temp->student_LL = NULL;
	temp->stu_num = 0;
	temp->last = NULL;
	return temp;
}

Student* Student_input(void)
{
	Student* stu_tem = malloc(sizeof(Student));
	Subject* sub_tem1;
	Subject* sub_tem2;
	
	printf("please input name:\n");
	scanf("%s", stu_tem->name);
	if (!strcmp(stu_tem->name, END_NAME))
	{
		free(stu_tem);
		return NULL;
	}
	printf("please input number:\n");
	scanf("%s", stu_tem->num);

	printf("please input student score, input -1 as subject to stop\n");
	stu_tem->score_LL = sub_tem2 = Subject_input(stu_tem);
	if (sub_tem2 != NULL)
	{
		while (1)
		{
			sub_tem1 = Subject_input();
			if (sub_tem1 == NULL)
				break;
			sub_tem2->next = sub_tem1;
			sub_tem2 = sub_tem1;
		}
		sub_tem2->next = NULL;
		stu_tem->last = sub_tem2;
	}
	return stu_tem;
}

Subject* Subject_input(void)
{
	Subject* sub = malloc(sizeof(Subject));

	printf("please input sbuject code:\n");
	scanf("%d", &sub->course);
	if (sub->course == END_SUBJECT)
	{
		free(sub);
		return NULL;
	}
	printf("please input score:\n");
	scanf("%f", &sub->score);

	return sub;
}

void Class_input(Class* cla_tem)
{
	Student* stu_tem1;
	Student* stu_tem2;

	printf("please input student, input ### as name to stop\n");
	cla_tem->student_LL = stu_tem2 = Student_input();
	if (stu_tem2 != NULL)
	{
		cla_tem->stu_num++;
		while (1)
		{
			stu_tem1 = Student_input();
			if (stu_tem1 == NULL)
				break;
			stu_tem2->next = stu_tem1;
			stu_tem2 = stu_tem1;
			cla_tem->stu_num++;
		}
		stu_tem2->next = NULL;
		cla_tem->last = stu_tem2;
	}
}

FILE* File_head_process(file_process_mode mode)
{
	FILE* fp;

	if (mode == Write)
	{
		fp = fopen(FILE_NAME, "wb");

		return fp;
	}
	if (mode == Read)
	{
		fp = fopen(FILE_NAME, "rb");

		return fp;
	}
}

void Save(Class* cla_tem)
{
	FILE* fp;
	Student* stu_tem;
	Subject* sub_tem;

	fp = File_head_process(Write);
	fwrite(cla_tem, sizeof(Class), 1, fp);
	stu_tem = cla_tem->student_LL;
	while (stu_tem != NULL)
	{
		fwrite(stu_tem, sizeof(Student), 1, fp);
		sub_tem = stu_tem->score_LL;
		while (sub_tem != NULL)
		{
			fwrite(sub_tem, sizeof(Subject), 1, fp);
			sub_tem = sub_tem->next;
		}
		stu_tem = stu_tem->next;
	}
	fclose(fp);
}

void Subject_LL_load(Student* stu_tem, FILE* fp)
{
	Subject* sub_tem;

	if (stu_tem->score_LL != NULL)
	{
		stu_tem->score_LL = sub_tem = malloc(sizeof(Subject));
		fread(sub_tem, sizeof(Subject), 1, fp);

		while (sub_tem->next != NULL)
		{
			sub_tem->next = malloc(sizeof(Subject));
			sub_tem = sub_tem->next;
			fread(sub_tem, sizeof(Subject), 1, fp);
		}
	}

}

Class* Load(void)
{
	Class* cla_tem = Class_init();
	FILE* fp = File_head_process(Read);
	Student* stu_tem;
	Subject* sub_tem;

	fread(cla_tem, sizeof(Class), 1, fp);
	if (cla_tem->student_LL != NULL)
	{
		stu_tem = cla_tem->student_LL = malloc(sizeof(Student));
		fread(stu_tem, sizeof(Student), 1, fp);
		Subject_LL_load(stu_tem, fp);

		while (stu_tem->next != NULL)
		{
			
			stu_tem->next = malloc(sizeof(Student));
			stu_tem = stu_tem->next;
			fread(stu_tem, sizeof(Student), 1, fp);
			Subject_LL_load(stu_tem, fp);
		}
	}
	fclose(fp);

	return cla_tem;
}
