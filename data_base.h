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
	Read
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

typedef struct Student
{
	char name[MAX_NAME_SIZE + 1];
	char num[NUM_SIZE + 1];
	struct Student* next;
	Subject* score_LL;
	Subject* last;
}Student;

typedef struct Class
{
	Student* student_LL;
	int stu_num;
	Student* last;
}Class;

Class* Class_init(void);
void Class_input(Class* cla_tem);
Student* Student_input(void);
Subject* Subject_input(void);
void Save(Class* cla_tem);
Class* Load(void);
FILE* File_head_process(file_process_mode mode);
char* Output_subject(Course temp);
void Subject_LL_load(Student* stu_tem, FILE* fp);


#endif
