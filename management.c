#include "management.h"

int main()
{
  int exit=0;
  int login_flag=0;
  Create_Struct();
  /*while(!exit)
  {
	  
  }
  endwin();
  Save_Data();
  system("clear");*/
  return 0;
}
void Save_Data()
{
  int i,j,k;
  int current_year;
  int current_num;
  int current_assign;
  int current_cgpa;
  FILE* fpoint;
  fpoint=fopen("data.txt","w");

	/*
	
		To do...
	
	*/
	


}
void Create_Struct()
{
  int i,j,k,h; 
  int current_year;
  int current_num;
  int current_assign;
  int current_cgpa;
  char* token;
  char temp[350];
  FILE* fpoint;
  int left,medi,right; //variable for 2진탐색
  YEAR* Cur_year;
  STUDENT* Cur_student;
  ASSIGN* Cur_assign;
  CGPA* Cur_cgpa;
  CGPA Temp_cgpa;

  fpoint=fopen("data.txt","r");
  TOP=NULL;
  while(fscanf(fpoint,"%4s",temp) != EOF){
	  if(TOP == NULL){
		  TOP=(TREE_HEAD*)malloc(sizeof(TREE_HEAD));
		  TOP->Year_Size=1;
		  Cur_year=(YEAR*)malloc(sizeof(YEAR));
		  TOP->ST_YEAR=Cur_year;
		  strncpy(Cur_year->year,temp,5);
		  Cur_year->Num_Size=0;
		  Cur_year->ST_NUM=NULL;
		  k=0;
	  }
	  else{
		  left=0,right=(TOP->Year_Size)-1;
		  medi=k;
		  Cur_year=(TOP->ST_YEAR)+medi;
		  while(1){ 
			  if(strncmp(Cur_year->year,temp,4)<0)
				  left=medi+1;
			  else if(strncmp(Cur_year->year,temp,4)==0){
				  k=medi;
				  break;
			  }
			  else
				  right=medi-1;
			  if(left>right)
				  break;
			  medi=(left+right)/2;
              Cur_year=(TOP->ST_YEAR)+medi;
		  }
		  if(left>right){
			  TOP->Year_Size+=1;
			  current_year=TOP->Year_Size;
			  TOP->ST_YEAR=realloc(TOP->ST_YEAR,sizeof(YEAR)*current_year);
			  for(j=current_year-1;j>left;j--)
				  TOP->ST_YEAR[j]=TOP->ST_YEAR[j-1];
			  k=left;
			  Cur_year=TOP->ST_YEAR+k;
			  strncpy(Cur_year->year,temp,5);
			  Cur_year->Num_Size=0;
			  Cur_year->ST_NUM=NULL;
		  }
		  //current student information will be stored in TOP->ST_YEAR[k];
	  }
	  printf("\nfind year!\n\n");
	  //current_num is linked to (Cur_year->ST_NUM)
	  fscanf(fpoint,"%4[^/]%*c",temp);
	  current_num=Cur_year->Num_Size;
	  if(Cur_year->ST_NUM == NULL){
		  Cur_student=(STUDENT*)malloc(sizeof(STUDENT));
		  Cur_year->ST_NUM=Cur_student;
	  }
	  else{
		  Cur_year->ST_NUM=realloc(Cur_year->ST_NUM,sizeof(STUDENT)*(current_num+1));
		  left=0,right=current_num-1;
	      while(left<=right){
			  medi=(left+right)/2;
			  Cur_student=(Cur_year->ST_NUM)+medi;
			  if(strncmp(Cur_student->number,temp,4)<0)
				  left=medi+1;
			  else
				  right=medi-1;
		  }
		  for(j=current_num;j>left;j--)
			  Cur_year->ST_NUM[j]=Cur_year->ST_NUM[j-1];
		  Cur_student=(Cur_year->ST_NUM)+left;
	  }	
	  printf("\nfind student position\n\n");
	  fscanf(fpoint,"%*c%15[^>]%*c%*c%d%*c%d%*c",Cur_student->password,&current_assign,&current_cgpa);
	  Cur_year->Num_Size+=1;
	  strncpy(Cur_student->number,temp,5);
	  Cur_student->Assign_Size=current_assign;
	  Cur_student->CGPA_Size=current_cgpa;
	  Cur_student->Child_A=malloc(sizeof(ASSIGN)*current_assign);
	  Cur_student->Child_C=malloc(sizeof(CGPA)*current_cgpa);

	  for(i=0;i<current_assign;i++){
		  Cur_assign=(Cur_student->Child_A)+i;
		  fscanf(fpoint,"%99[^/]%*c %99[^/]%*c %99[^/]%*c %d%*c%d%*c",Cur_assign->name,Cur_assign->describe,Cur_assign->professor,&Cur_assign->date[0],&Cur_assign->date[1]);
	  }
	  printf("\nend student's assignment list\n\n");
	  for(i=0;i<current_cgpa;i++){
		  Cur_cgpa=(Cur_student->Child_C)+i;
		  fscanf(fpoint,"%d%*c%f%*c",&Cur_cgpa->semester,&Cur_cgpa->score);
		  for(j=0;j<i;j++){
			  if(Cur_student->Child_C[j].semester > Cur_cgpa->semester)
				  break;
		  }
		  if(j == i)
			  continue;
		  else{
			  Temp_cgpa.semester=Cur_cgpa->semester;
			  Temp_cgpa.score=Cur_cgpa->score;
			  for(h=i;h>j;h--){
				  Cur_student->Child_C[h]=Cur_student->Child_C[h-1];
			  }
			  Cur_student->Child_C[j]=Temp_cgpa;
		  }
	  }
	  printf("\nend student's CGPA list\n\n");
  }
  current_year=TOP->Year_Size;
  for(i=0;i<current_year;i++){
	  Cur_year=TOP->ST_YEAR+i;
	  printf("year : %s\n",Cur_year->year);
	  current_num=Cur_year->Num_Size;
	  for(j=0;j<current_num;j++){
		  Cur_student=Cur_year->ST_NUM+j;
		  printf("student num : %s and password : %s\n",Cur_student->number,Cur_student->password);
		  current_assign=Cur_student->Assign_Size;
		  current_cgpa=Cur_student->CGPA_Size;
		  for(k=0;k<current_assign;k++){
			  Cur_assign=Cur_student->Child_A+k;
			  printf("%d ASSIGNMENT\n%s\n%s\n%s\n%d-%d\n",k+1,Cur_assign->name,Cur_assign->describe,Cur_assign->professor,Cur_assign->date[0],Cur_assign->date[1]);
		  }
		  for(k=0;k<current_cgpa;k++){
			  Cur_cgpa=Cur_student->Child_C+k;
			  printf("%d semester\n%.2f score\n",Cur_cgpa->semester,Cur_cgpa->score);
		  }
	  }
  }
  fclose(fpoint);
}
char Account_Manage()
{
	printw("1. Login\n");
	printw("2. Create new Account\n");
	printw("3. Delete Account\n");
	printw("4. Get Temporary Password\n");
	printw("5. Exit\n");
	return wgetch(stdscr);
}
char menu()
{
	printw("1. Assignment Management\n");
	printw("2. CGPA Management\n");
	printw("3. Change Password\n");
	printw("4. Logout\n");
	return wgetch(stdscr);
}
void Search_Assign()
{
	int Asize;
	char input;
	clear();
	printw("<Assignment Management for %s>\n",Curr_Num);
	Asize = TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Assign_Size;
	Sort_Assign();
	Print_Assign(Asize);
	printw("1. New Assignment\n2. Delete Assignment\n3. Return to main menu\n");
	noecho();
	input=wgetch(stdscr);
	switch(input)
	{
		case '1': Add_Assign(); break;
		case '2': Delete_Assign(); break;
		case '3': return; break;
	}
	clear();
}

void Print_Assign(int Asize)
{
	int k,D_day,thistime,thattime;
	time_t t;
	struct tm *today;
	int i;
	int j;
	i=Login_Year;
	j=Login_Num;
	t = time(NULL);
	today = localtime(&t);
	thistime = mktime(today);
	/*
	   To do...
	   */


}

char cgpa_menu()
{
	printw("1. Add new GPA or Change existing GPA\n");
	printw("2. View all\n");
	printw("3. Exit\n");
	return wgetch(stdscr);
}
void Search_CGPA() 
{
	int exit;
	Curr_year_index=Login_Year;
	Curr_num_index=Login_Num;
	while(!exit)
	{
		clear();
		switch(cgpa_menu())
		{
			case CGPA_ADD: Add_GPA(); break;
			case CGPA_VIEW: Print_CGPA(); break;
			case CGPA_QUIT: exit = 1; break;
			default: break;
		}
	}
	exit = 0;
}
void Add_GPA()
{
	char semester;
	float gpa;
	int gpa_size;
	clear();
	echo();
	printw("Input the semester of GPA : ");
	scanw("%c", &semester);

  gpa_size = TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].CGPA_Size;  

  if(semester - '0' > (gpa_size + 1) || semester - '0' < 1) {
    printw("You entered wrong number!\n");
    getch();
    return ;
  } 
  printw("Input the GPA : ");
  scanw("%f", &gpa);

  if(gpa < 0 || gpa > 4.31) {
    printw("You entered wrong number!\n");
    getch();
    return ;
  }

  if(semester - '0' <= gpa_size) {
    Cor_GPA(semester, gpa);
    return ;
  }

  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].CGPA_Size++;
  gpa_size++;

  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C = (CGPA*)realloc(TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C,gpa_size * sizeof(CGPA));

  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[gpa_size - 1].semester = semester - '0';
  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[gpa_size - 1].score = gpa; 

  return ;

}
void Cor_GPA(char semester, float gpa) 
{
  int i;
  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[semester - '0' - 1].score = gpa;
  printw("GPA is changed successfully!\n");
  getch();
  return ;

}
void Print_CGPA() //Additional
{
  int i;
  int tmpSemester;
  float tmpGPA;
  float sum = 0;
  clear();
  printw("<CGPA Management for %s>\n", Curr_Num);
  printw("------------------------------\n");
  printw("  Semester  |  GPA  |  CGPA  |  \n");
  for(i = 0 ; i < TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].CGPA_Size ; i++) 
  {
    /*
		To do...
    */
    printw("------------------------------\n");
    printw("     %d      |  %.2f |  %.2f  |\n", tmpSemester, tmpGPA, sum/(i + 1));
  }
  printw("------------------------------\n\n");
  printw("<CGPA Management by Graph for %s>\n", Curr_Num);
  printw("(x-axis : semester,  y-axis : score)\n");
  Print_CGPA_Graph();
  getch();
}
void Print_CGPA_Graph() 
{
 	/*
		To do...(Additional)
	*/
}
void Sort_Assign()
{
  
  /*
  
  	To do...
  
  */
}
void Add_Assign()
{
  //Login_Num,Login_Year
  /*
  	To do...
  
  */
  }
void Delete_Assign()
{
  /*
  	To do...
   
  */
}
void Add_CGPA()
{
  //Login_Num,Login_Year
  
  /*
  	To do...
  */  
  
}
void New_Account()
{
	/*
		To do...
	*/

}
void Delete_Account()
{
    /*
		To do...
    */

}
void Change_Password()
{

	/*
		To do...
	*/

}

int login()
{
  int i,j;
  int year_flag=0;
  int num_flag=0;
  int pass_flag=0;
  char year[5]={};
  char num[5]={};
  for(i=0;i<4;i++)
    year[i]=Curr_Num[i];
  for(i=4;i<8;i++)
    num[i-4]=Curr_Num[i];
  for(i=0;i<TOP->Year_Size;i++)
  {
    if(!strcmp(TOP->ST_YEAR[i].year,year))
    {
      year_flag=1;
      break;
    }
  }
  if(year_flag==1)
  {
    for(j=0;j<TOP->ST_YEAR[i].Num_Size;j++)
    {
      if(!strcmp(TOP->ST_YEAR[i].ST_NUM[j].number,num))
      {
        num_flag=1;
        break;
      }
    }
  }
  if(num_flag==1)
  {
    if(!strcmp(TOP->ST_YEAR[i].ST_NUM[j].password,Curr_Pass))
    {
      pass_flag=1;
      Login_Year=i;//stores logged in user's year
      Login_Num=j;//stores logged in user's number
    }
  }
  if(pass_flag==1)
    return 1;
  return 0;
}

void Temp_Password()
{
  int flag1=0;
  int i, j, k;
  char num[5]={};
  char temppassword[8];
  float temp;
  clear();
  echo();
  srand(time(NULL));
  printw("Student Number:");
  scanw("%s",Curr_Num);
	/*
		To do...
	*/
}
