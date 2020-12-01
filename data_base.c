#include<stdio.h>
#include<string.h>
#include"data_base.h"


Class* Class_init(void)
{
	Class* temp = malloc(sizeof(Class));
	temp->student_LL = NULL;
	temp->stu_num = 0;
	temp->aver_LL = NULL;
	temp->next = NULL;
	return temp;
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

void Output_aver(Average* aver_tem)
{
	if (aver_tem != NULL)
	{
		printf("***************Average***********************\n");
		while (aver_tem != NULL)
		{
			printf("Subject: %s\n", Output_subject(aver_tem->course));
			printf("Average: %.2f\n\n", aver_tem->sum / aver_tem->num);
			aver_tem = aver_tem->next;
		}
		printf("********************************************\n\n");
	}
}

void Output_class(Class* cla_tem)
{
	Student* stu_tem;

	if (cla_tem == NULL)
		return;
	printf("\n\n         %s         \n", cla_tem->name);
	Output_aver(cla_tem->aver_LL);
	stu_tem = cla_tem->student_LL;
	while (stu_tem != NULL)
	{
		Output_student(stu_tem);
		stu_tem = stu_tem->next;
	}
}

void Output_all_class(Class* cla)
{
	Class* cla_tem = cla;

	while (cla_tem != NULL)
	{
		Output_class(cla_tem);
		cla_tem = cla_tem->next;
	}
}



Subject* Find_Subject(Subject* sub_LL, Course cour_tem)
{
	if (sub_LL == NULL)
		return NULL;
	while (sub_LL != NULL)
	{
		if (sub_LL->course == cour_tem)
			return sub_LL;
		sub_LL = sub_LL->next;
	}
	return NULL;
}

Average* Find_Average(Average* sub_LL, Course cour_tem)
{
	if (sub_LL == NULL)
		return NULL;
	while (sub_LL != NULL)
	{
		if (sub_LL->course == cour_tem)
			return sub_LL;
		sub_LL = sub_LL->next;
	}
	return NULL;
}

Average* Average_add_subject(Average* aver_LL, Subject* sub_tem)
{
	Average* aver_start = aver_LL;

	if (aver_LL != NULL)
	{
		while (aver_LL->next != NULL)
			aver_LL = aver_LL->next;
		aver_LL->next = malloc(sizeof(Average));
		aver_LL = aver_LL->next;
		aver_LL->next = NULL;
		aver_LL->num = 1;
		aver_LL->course = sub_tem->course;
		aver_LL->sum = sub_tem->score;

		return aver_start;
	}
	else
	{
		aver_LL = malloc(sizeof(Average));
		aver_LL->next = NULL;
		aver_LL->num = 1;
		aver_LL->course = sub_tem->course;
		aver_LL->sum = sub_tem->score;

		return aver_LL;
	}
}

void Average_updata(Class* cla_tem, Student* stu_tem)
{
	Average* aver_position;
	Subject* sub_tem = stu_tem->score_LL;

	while (sub_tem != NULL)
	{
		aver_position = Find_Average(cla_tem->aver_LL, sub_tem->course);
		if (aver_position == NULL)
			cla_tem->aver_LL = Average_add_subject(cla_tem->aver_LL, sub_tem);
		else
		{
			aver_position->num++;
			aver_position->sum += sub_tem->score;
		}
		sub_tem = sub_tem->next;
	}
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

Class* Class_input(void)
{
	Student* stu_tem1;
	Student* stu_tem2;
	Class* cla_tem = Class_init();

	printf("please input class, input ### as class name to stop\n");
	scanf("%s", cla_tem->name);
	if (!strcmp(cla_tem->name, END_NAME))
	{
		free(cla_tem);
		return NULL;
	}

	printf("please input student, input ### as student name to stop\n");
	cla_tem->student_LL = stu_tem2 = Student_input();
	if (stu_tem2 != NULL)
	{
		Average_updata(cla_tem, stu_tem2);
		cla_tem->stu_num++;
		while (1)
		{
			stu_tem1 = Student_input();
			if (stu_tem1 == NULL)
				break;
			Average_updata(cla_tem, stu_tem1);
			stu_tem2->next = stu_tem1;
			stu_tem2 = stu_tem1;
			cla_tem->stu_num++;
		}
		stu_tem2->next = NULL;
	}
	return cla_tem;
}

Class* All_class_input(void)
{
	Class* cla_start;
	Class* cla_tem;

	cla_start = cla_tem = Class_input();
	while (cla_tem != NULL)
	{
		cla_tem->next = Class_input();
		cla_tem = cla_tem->next;
	}

	return cla_start;
}





void Save(Class* cla_tem)
{
	FILE* fp;
	Average* aver_tem;
	Student* stu_tem;
	Subject* sub_tem;

	fp = File_head_process(Write);

	while (cla_tem != NULL)
	{
		fwrite(cla_tem, sizeof(Class), 1, fp);
		aver_tem = cla_tem->aver_LL;
		while (aver_tem != NULL)
		{
			fwrite(aver_tem, sizeof(Average), 1, fp);
			aver_tem = aver_tem->next;
		}
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
		cla_tem = cla_tem->next;
	}
	fclose(fp);
}

Subject* Subject_LL_load(FILE* fp)
{
	Subject* sub_tem;
	Subject* sub_start;

	sub_start = sub_tem = malloc(sizeof(Subject));
	fread(sub_tem, sizeof(Subject), 1, fp);
	while (sub_tem->next != NULL)
	{
		sub_tem->next = malloc(sizeof(Subject));
		sub_tem = sub_tem->next;
		fread(sub_tem, sizeof(Subject), 1, fp);
	}
	return sub_start;
}

Student* Student_LL_load(FILE* fp)
{
	Student* stu_tem;
	Student* stu_start;

	stu_start = stu_tem = malloc(sizeof(Student));
	fread(stu_tem, sizeof(Student), 1, fp);
	if(stu_tem->score_LL !=NULL)
		stu_tem->score_LL = Subject_LL_load(fp);

	while (stu_tem->next != NULL)
	{
		stu_tem->next = malloc(sizeof(Student));
		stu_tem = stu_tem->next;
		fread(stu_tem, sizeof(Student), 1, fp);
		if (stu_tem->score_LL != NULL)
			stu_tem->score_LL = Subject_LL_load(fp);
	}
	return stu_start;
}

Average* Aver_LL_load(FILE* fp)
{
	Average* aver_tem;
	Average* aver_start;

	aver_start = aver_tem = malloc(sizeof(Average));
	fread(aver_tem, sizeof(Average), 1, fp);
	while (aver_tem->next != NULL)
	{
		aver_tem->next = malloc(sizeof(Average));
		aver_tem = aver_tem->next;
		fread(aver_tem, sizeof(Average), 1, fp);
	}
	return aver_start;
}

Class* Class_LL_load(FILE* fp)
{
	Class* cla_tem;
	Class* cla_start;

	cla_start = cla_tem = malloc(sizeof(Class));
	fread(cla_tem, sizeof(Class), 1, fp);
	if (cla_tem->aver_LL != NULL)
		cla_tem->aver_LL = Aver_LL_load(fp);
	if (cla_tem->student_LL != NULL)
		cla_tem->student_LL = Student_LL_load(fp);

	while (cla_tem->next != NULL)
	{
		cla_tem->next = malloc(sizeof(Class));
		cla_tem = cla_tem->next;

		fread(cla_tem, sizeof(Class), 1, fp);
		if (cla_tem->aver_LL != NULL)
			cla_tem->aver_LL = Aver_LL_load(fp);
		if (cla_tem->student_LL != NULL)
			cla_tem->student_LL = Student_LL_load(fp);
	}

	return cla_start;
}

Class* Load(void)
{
	FILE* fp = File_head_process(Read);
	if (fp == NULL)
	{
		printf("error: cann't find data file.\n");
		exit(-1);
	}
	Class* cla_LL = Class_LL_load(fp);

	fclose(fp);

	return cla_LL;
}
