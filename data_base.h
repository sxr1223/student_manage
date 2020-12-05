#ifndef DATA_BASE
#define DATA_BASE

#include <stdio.h>

#define MAX_NAME_SIZE 20
#define NUM_SIZE 10
#define END_NAME "###"
#define END_SUBJECT -1
#define FILE_NAME "sxr.bin"

typedef enum file_process_mode
{
	Write = 1,
	Read,
	Write_pwd,
	Read_pwd
}file_process_mode;

typedef enum course
{
	higher_math = 0,
	english_1,
	english_2,
	english_3,
	english_4
}Course;

typedef struct Subject
{
	Course course;
	float score;
	struct Subject* next;
}Subject;

typedef struct Average
{
	int num;
	float sum;
	Course course;
	struct Average* next;
}Average;

typedef struct Student
{
	char name[MAX_NAME_SIZE + 1];
	char num[NUM_SIZE + 1];
	struct Student* next;
	char pwd[32];
	Subject* score_LL;
	Subject* last;
}Student;

typedef struct Class
{
	Student* student_LL;
	int stu_num;
	char name[MAX_NAME_SIZE + 1];
	Average* aver_LL;
	struct Class* next;
}Class;



Class* Class_init(void);
FILE* File_head_process(file_process_mode mode);

Subject* Subject_input(void);
Student* Student_input(void);
Class* Class_input(void);
Class* All_class_input(Class* cla_LL);

char* Output_subject(Course temp);
void Output_student(Student* stu_tem);
void Output_aver(Average* aver_tem);
void Output_class(Class* cla_tem);
void Output_all_class(Class* cla);

Subject** Find_Subject(Subject** sub_LL, Course cour_tem);
Average* Find_Average(Average* sub_LL, Course cour_tem);
Class* Find_Class(Class* cla_LL, char name[MAX_NAME_SIZE + 1]);
Student* Find_Student_Name(Student* stu_LL, char name[MAX_NAME_SIZE + 1]);
void Find_data(Class* cla_LL);

void Average_add_Subject(Average** aver_LL, Subject* sub_tem);
void Average_add_Student(Average** aver_LL, Student* stu_tem);
void Average_update_Class(Class* cla_tem);

Subject* Subject_LL_load(FILE* fp);
void Save(Class* cla_tem);
Class* Load(void);
void Change_data(Class* cla_LL);

void Del_Class_LL(Class** cla_start);
void Del_Student(Student** stu_tem);
void Del_Subject_LL(Subject** sub_LL);
void Del_aver_LL(Average** aver_start);

void Student_Authority_Output(Student* stu_tem);

#endif
