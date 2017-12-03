#ifndef MANAGEMENT_H
#define MANAGEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#define MENU_ASSIGN '1'
#define MENU_CGPA '2'
#define MENU_CHANGE '3'
#define MENU_LOGOUT '4'
#define MENU_LOGIN '1'
#define MENU_NEW '2'
#define MENU_DEL '3'
#define MENU_TEMP '4'
#define MENU_QUIT '5'
#define CGPA_ADD '1'
#define CGPA_VIEW '2'
#define CGPA_QUIT '3'

char Curr_Num[9];
char Curr_Pass[16];
char New_Num[9];
char New_Pass[16];
int Curr_year_index;
int Curr_num_index;
typedef struct CHILD1
{
  char name[100];
  char describe[100];
  char professor[100];
  int date[2];
}ASSIGN;

typedef struct CHILD2
{
  int semester;
  float score;
}CGPA;
typedef struct SUB_SUB_HEAD
{
  char number[5];
  char password[16];
  ASSIGN* Child_A;
  int Assign_Size;
  int CGPA_Size;
  CGPA* Child_C;
}STUDENT;
typedef struct SUB_HEAD
{
  char year[5];
  int Num_Size;
  STUDENT* ST_NUM;
}YEAR;

typedef struct HEAD
{
  int Year_Size;
  YEAR* ST_YEAR;
}TREE_HEAD;
int Login_Year;
int Login_Num;
int Year_Count=8;
int Student_Count;
int Assign_Count;
int CGPA_Count;
TREE_HEAD* TOP;
void Load_Data();
void Save_Data();
char menu();
char cgpa_menu();
void Add_GPA();
void Del_GPA();
void Cor_GPA(char semester,float gpa);
void Create_Struct();
void Search_Assign();
void Search_CGPA();
void Print_Assign(int);
void Print_CGPA();
void Print_CGPA_Graph();
void New_Account();
void Delete_Account();
void Change_Password();
void rank();
void Sort_Assign();
void Add_Assign();
void Delete_Assign();
void Temp_Password();
int login();
void Temp_Password();
char Account_Manage();
#endif
