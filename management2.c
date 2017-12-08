#include "management.h"

void printing();

int main()
{
  int exit=0;
  int login_flag=0;
  char choice;
  initscr();
  Create_Struct();
  printing();
  while(!exit)
  {
	  switch(Account_Manage()){
		  case MENU_LOGIN:{
							  clear();
							  if(login()){
								  clear();
								  login_flag=0;
								  while(!login_flag){
									  switch(menu()){
									  	case MENU_ASSIGN: {
															  clear();
															  Search_Assign();
															  break;
														  }
										case MENU_CGPA:{
														   clear();
														   Search_CGPA();
														   break;
													   }
										case MENU_CHANGE:{
															 clear();
															 Change_Password();
															 break;
														 }
										case MENU_LOGOUT:{
															 clear();
															 login_flag=1;
														 }
									  }
							  }
							  clear();
							  break;
						  }
		  case MENU_NEW: {
							 clear();
							 New_Account();
							 break;
						 }
		  case MENU_DEL: {
							 clear();
							 Delete_Account();
							 break;
						 }
		  case MENU_TEMP: {
							  clear();
							  Temp_Password();
							  break;
						  }
		  case MENU_QUIT: {
							  clear();
							  exit=1;
							  
						  }
	  }		   
  }
  endwin();
  Save_Data();
  system("clear");
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
  int i,j,k;
  int current_year;
  int current_num;
  int current_assign;
  int current_cgpa;
  char* token;
  char temp[350];
  FILE* fpoint;
  YEAR* Cur_year;
  YEAR* Pre_year;
  YEAR* New_year;
  STUDENT* Pre_student;
  STUDENT* New_student;
  STUDENT* Cur_student;
  ASSIGN* Pre_assign;
  ASSIGN* New_assign;
  ASSIGN* Cur_assign;
  CGPA* New_CGPA;
  CGPA* Cur_CGPA;
  CGPA* Pre_CGPA;
  
  fpoint=fopen("data.txt","r");
  TOP=(TREE_HEAD*)malloc(sizeof(TREE_HEAD));
  TOP->Year_Size=0;
  TOP->ST_YEAR=NULL;
  Pre_year=NULL;
  while(1){
	  if(fscanf(fpoint,"%4s",temp)== EOF)
		  break;
	  if(TOP->Year_Size == 0){
		  TOP->Year_Size=1;
		  Cur_year=(YEAR*)malloc(sizeof(YEAR));
		  TOP->ST_YEAR=Cur_year;
		  strncpy(Cur_year->year,temp,5);
		  Cur_year->Num_Size=0;
		  Cur_year->ST_NUM=NULL;
		  Cur_year->link=NULL;
	  }
	  else{
		  if(strncmp(temp,Cur_year->year,4)<0){
			  Pre_year=NULL;
			  Cur_year=TOP->ST_YEAR;
		  }
		  while(Cur_year!= NULL && strncmp(temp,Cur_year->year,4)>0){
			  Pre_year=Cur_year;
			  Cur_year=Cur_year->link;
		  }
		  if(Cur_year == NULL){
			  TOP->Year_Size+=1;
			  Cur_year=(YEAR*)malloc(sizeof(YEAR));
			  strncpy(Cur_year->year,temp,5);
			  Cur_year->Num_Size=0;
			  Cur_year->ST_NUM=NULL;
			  Cur_year->link=NULL;
			  Pre_year->link=Cur_year;
		  }
		  else if(strncmp(temp,Cur_year->year,4) != 0){
			  TOP->Year_Size+=1;
			  New_year=(YEAR*)malloc(sizeof(YEAR));
			  strncpy(New_year->year,temp,5);
			  New_year->Num_Size=0;
			  New_year->ST_NUM=NULL;
			  if(Pre_year == NULL){
				  New_year->link=TOP->ST_YEAR;
				  TOP->ST_YEAR=New_year;
			  }
			  else{
				  New_year->link=Pre_year->link;
				  Pre_year->link=New_year;
			  }
			  Cur_year=New_year;
		  }
	  }
	  //current student is linked to (Cur_year->ST_NUM)
	  New_student=(STUDENT*)malloc(sizeof(STUDENT));
	  fscanf(fpoint,"%4[^\n]%*c",New_student->number);
	  fscanf(fpoint,"%15[^\n]%*c",New_student->password);
	  fscanf(fpoint,"%d%*c%d%*c",&New_student->Assign_Size,&New_student->CGPA_Size);
	  Cur_year->Num_Size+=1;
	  New_student->Child_A=NULL;
	  New_student->Child_C=NULL;
	  Pre_student=NULL;
	  Cur_student=Cur_year->ST_NUM;
	  while(Cur_student != NULL && strncmp(Cur_student->number,New_student->number,4)<0){
		  Pre_student=Cur_student;
		  Cur_student=Cur_student->link;
	  }
	  if(Pre_student == NULL){
		  New_student->link=Cur_year->ST_NUM;
		  Cur_year->ST_NUM=New_student;
		  Cur_student=New_student;
	  }
	  else if(Cur_student != NULL && strncmp(Cur_student->number,New_student->number,4)== 0){
		  Cur_year->Num_Size-=1;
	  }
	  else{
		  New_student->link=Pre_student->link;
		  Pre_student->link=New_student;
		  Cur_student=New_student;
	  }
	  // Cur_student에 assign linked-list만들고 head 넣고 CGPA linke_list만들고 head넣기
	  Pre_assign=NULL;
	  current_num = Cur_student->Assign_Size;
	  for(i=0;i<current_num;i++){
		  New_assign=(ASSIGN*)malloc(sizeof(ASSIGN));
		  fscanf(fpoint,"%99[^/]%*c %99[^/]%*c %99[^/]%*c %d%*c%d%*c",New_assign->name,New_assign->describe,New_assign->professor,&New_assign->date[0],&New_assign->date[1]);
		  New_assign->link=NULL;
		  if(Pre_assign == NULL)
			  Cur_student->Child_A=New_assign;
		  else
			  Pre_assign->link=New_assign;
		  Pre_assign=New_assign;
	  }
	  Cur_CGPA=Cur_student->Child_C;
	  current_num=Cur_student->CGPA_Size;
	  for(i=0;i<current_num;i++){
		  New_CGPA=(CGPA*)malloc(sizeof(CGPA));
		  fscanf(fpoint,"%d%*c%f%*c",&New_CGPA->semester,&New_CGPA->score);
		  New_CGPA->link=NULL;
		  if(Cur_CGPA == NULL){
			  Pre_CGPA=NULL;
			  Cur_student->Child_C=New_CGPA;
			  Cur_CGPA=New_CGPA;
			  continue;
		  }
		  else if(Cur_CGPA->semester>New_CGPA->semester){
			  Pre_CGPA=NULL;
			  Cur_CGPA=Cur_student->Child_C;
		  }
		  while(Cur_CGPA != NULL && Cur_CGPA->semester<New_CGPA->semester){
			  Pre_CGPA=Cur_CGPA;
			  Cur_CGPA=Cur_CGPA->link;
		  }
		  if(Pre_CGPA == NULL){
			  New_CGPA->link=Cur_student->Child_C;
			  Cur_student->Child_C=New_CGPA;
		  }
		  else{
			  New_CGPA->link=Pre_CGPA->link;
			  Pre_CGPA->link=New_CGPA;
		  }
		  Cur_CGPA=New_CGPA;
	  }
  }
  fclose(fpoint);
}
void printing(){
	YEAR* Cur_year;
	STUDENT* Cur_student;
	ASSIGN* Cur_assign;
	CGPA* Cur_CGPA;
  	printw("Year_Size : %d\n",TOP->Year_Size);
	refresh();
  	for(Cur_year=TOP->ST_YEAR;Cur_year!= NULL;Cur_year=Cur_year->link){
		printw("Year : %s / Year number : %d\n",Cur_year->year,Cur_year->Num_Size);
		refresh();
	 	for(Cur_student=Cur_year->ST_NUM;Cur_student!=NULL;Cur_student=Cur_student->link){
		  printw("student) number: %s / password: %s / Assign number :  %d / CGPA number : %d\n",Cur_student->number,Cur_student->password,Cur_student->Assign_Size,Cur_student->CGPA_Size);
		  refresh();
		  for(Cur_assign=Cur_student->Child_A;Cur_assign!=NULL;Cur_assign=Cur_assign->link){
			  printw("name : %s / describe : %s / professor :  %s /  date : %d:%d\n",Cur_assign->name,Cur_assign->describe,Cur_assign->professor,Cur_assign->date[0],Cur_assign->date[1]);
			  refresh();
		  }
		  for(Cur_CGPA=Cur_student->Child_C;Cur_CGPA!=NULL;Cur_CGPA=Cur_CGPA->link){	
			  printw("semester : %d score : %.2f\n",Cur_CGPA->semester,Cur_CGPA->score);
			  refresh();
		  }
	  	}
	}
	wgetch(stdscr);
	clear();
}

char Account_Manage()
{
	printw("1. Login\n");
	printw("2. Create new Account\n");
	printw("3. Delete Account\n");
	printw("4. Get Temporary Password\n");
	printw("5. Exit\n");
	refresh();
	noecho();
	return wgetch(stdscr);
}
char menu()
{
	printw("1. Assignment Management\n");
	printw("2. CGPA Management\n");
	printw("3. Change Password\n");
	printw("4. Logout\n");
	refresh();
	noecho();
	return wgetch(stdscr);
}
void Search_Assign()
{
	int Asize;
	char input;
	clear();
	printw("<Assignment Management for %s>\n",Curr_Num);
	Asize = Login_num->Assign_Size;
	if(Asize){
		Sort_Assign();
		Print_Assign(Asize);
	}
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
	
	t = time(NULL);
	today = localtime(&t);
	thistime = mktime(today);
	
	   To do...
	   


}
/*
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
    
		To do...
    
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
	
}*/
void Sort_Assign()
{
	ASSIGN* cur;
	ASSIGN* pre;
	ASSIGN* insert_position;

	pre=Login_num->Child_C;
	cur=Login_num->Child_C->link;

	while(cur != NULL){
		insert_position=Login_num->Child_C;
		if(insert_position->date[0] > cur_date[0]){
			pre->link=cur->link;
			cur->link=Login_num->Child_C;
			Login_num->Child_C=cur;
			pre=cur;
			cur=cur->link;
			continue;
		}
		else if(insert_position->date[0] == cur_date[0] && insert_position->date[1] > cur_date[1]){
			pre->link=cur->link;
			cur->link=Login_num->Child_C;
			Login_num->Child_C=cur;
			pre=cur;
			cur=cur->link;
			continue;
		}
		while(insert_position != pre){
			if(insert_position->link->date[0]>cur_date[0])
				break;
			else if(insert_position->link->date[0] == cur_date[0] && insert_position->link->date[1] > cur_date[1])
				break;
			insert_position=insert_position->link;
		}
		if(insert != pre){
			pre->link=cur->link;
			cur->link=insert_position->link;
			insert_position->link=cur;
		}
		pre=cur;
		cur=cur->link;
	}
	printing();
	noecho();
	wgetch(strscr);
	clear();
}
/*
void Add_Assign()
{
  //Login_Num,Login_Year
  /*
  	To do...
  
  
  }
void Delete_Assign()
{
  /*
  	To do...
   
  
}
void Add_CGPA()
{
  //Login_Num,Login_Year
   
  
}*/
void New_Account()
{
	int i;
	YEAR *pre_year=NULL;
	YEAR * cur_year;
	STUDENT * pre_student=NULL;
	STUDENT * cur_student;
	printw("Student Number: ");
	refresh();
	echo();
	scanw("%8s",Curr_Num);
	printw("Password: ");
	refresh();
	noecho();
	scanw("%15s",Curr_Pass);
	cur_year=TOP->ST_YEAR;
	while(cur_year != NULL && strncmp(cur_year->year,Curr_Num,4)<0){
		pre_year=cur_year;
		cur_year=cur_year->link;
	}
	if(cur_year == NULL || strncmp(cur_year->year,Curr_Num,4)!=0){
		cur_year=malloc(sizeof(YEAR));
		strncpy(cur_year->year,Curr_Num,4);
		cur_year->Num_Size =0;
		cur_year ->ST_NUM = NULL;
		TOP->Year_Size +=1;
		if(pre_year== NULL){
			cur_year->link=TOP->ST_YEAR;
			TOP->ST_YEAR=cur_year;
		}
		else{
			cur_year->link=pre_year->link;
			pre_year->link=cur_year;
		}
	}
	cur_student=cur_year->ST_NUM;
	while(cur_student != NULL && strcmp(cur_student->number,Curr_Num+4)<0){
		pre_student=cur_student;
		cur_student=cur_student->link;
	}
	//Exception 
	if(cur_student != NULL && strcmp(cur_student->number,Curr_Num+4) ==0){
		printw("Entered student number exist\n");
		refresh();
	}
	else{
		cur_student=malloc(sizeof(STUDENT));
		strcpy(cur_student->number,Curr_Num+4);
		strcpy(cur_student->password,Curr_Pass);
		cur_student->Child_A=NULL;
		cur_student->Child_C=NULL;
		cur_student->Assign_Size=0;
		cur_student->CGPA_Size=0;
		cur_year->Num_Size+=1;
		if(pre_student == NULL){
			cur_student->link=cur_year->ST_NUM;
			cur_year->ST_NUM=cur_student;
		}
		else{
			cur_student->link=pre_student->link;
			pre_student->link=cur_student;
		}
	}
	clear();
	printing();
}
void Delete_Account()
{
	int i;
	YEAR* pre_year;
	YEAR* cur_year;
	STUDENT* pre_student;
	STUDENT* cur_student;
	ASSIGN* pre_assign=NULL;
	ASSIGN* cur_assign;
	CGPA* pre_cgpa=NULL;
	CGPA* cur_cgpa;
	printw("Enter student number you want to delete : ");
	refresh();
	echo();
	scanw("%8s",Curr_Num);
	pre_year=NULL;
	cur_year=TOP->ST_YEAR;
	while(cur_year != NULL && strncmp(cur_year->year,Curr_Num,4)!=0){
		pre_year=cur_year;
		cur_year=cur_year->link;
	}
	if(cur_year == NULL)
		return;
	pre_student=NULL;
	cur_student=cur_year->ST_NUM;
	while(cur_student != NULL && strcmp(cur_student->number,Curr_Num+4)!=0){
		pre_student=cur_student;
		cur_student=cur_student->link;
	}
	if(cur_student == NULL)
		return;
	cur_assign=cur_student->Child_A;
	while(cur_assign != NULL){
		free(pre_assign);
		pre_assign=cur_assign;
		cur_assign=cur_assign->link;
	}
	cur_cgpa=cur_student->Child_C;
	while(cur_cgpa != NULL){
		free(pre_cgpa);
		pre_cgpa=cur_cgpa;
		cur_cgpa=cur_cgpa->link;
	}
	if(pre_student == NULL)
		cur_year->ST_NUM=cur_student->link;
	else
		pre_student->link=cur_student->link;
	cur_year->Num_Size-=1;
	free(cur_student);
	if(cur_year->Num_Size ==0){
		if(pre_year == NULL)
			TOP->ST_YEAR=cur_year->link;
		else
			pre_year->link=cur_year->link;
		free(cur_year);
		TOP->Year_Size-=1;
	}
	clear();
	printing();
}
void Change_Password()
{
	char new[16];
	char confirm[16];
	while(1){
		printw("Enter new password:");
		refresh();
		noecho();
		scanw("%15s",new);
		printw("Confirm new password:");
		refresh();
		noecho();
		scanw("%15s", confirm);
		if(strncmp(new,confirm,strlen(new)) == 0){
			strncpy(Login_Num->password, new, strlen(new)+1);
			printw("Password of Account <%s%s> is successfully changed.\n",Login_Year->year,Login_Num->number);
			refresh();
			break;
		}
		printw("Two passwords are not matched.\n");
		clear();
	}
	noecho();
	wgetch(stdscr);
	printing();
	noecho();
	wgetch(stdscr);
	clear();
}

int login()
{
  int i,j;
  int year_flag=0;
  int num_flag=0;
  int pass_flag=0;
  char year[5]={};
  char num[5]={};
  YEAR * cur_year;
  STUDENT * cur_student;
  printw("Student Number:");
  refresh();
  echo();
  scanw("%8[^\n]%*c",Curr_Num);
  printw("Password:");
  refresh();
  noecho();
  scanw("%15[^/n]%*c",Curr_Pass);
  for(i=0;i<4;i++)
    year[i]=Curr_Num[i];
  for(i=4;i<8;i++)
    num[i-4]=Curr_Num[i];
  cur_year=TOP->ST_YEAR;
  while(cur_year != NULL){
	  if(!strncmp(cur_year->year,year,4)){
		  year_flag=1;
		  break;
	  }
	  cur_year=cur_year->link;
  }
  if(year_flag==1)
  {
	  cur_student=cur_year->ST_NUM;
	  while(cur_student != NULL){
      	if(!strncmp(cur_student->number,num,4))
      	{
        	num_flag=1;
       		break;
      	}
		cur_student=cur_student->link;
      }
  }
  if(num_flag==1)
  {
    if(strncmp(cur_student->password,Curr_Pass,sizeof(Curr_Pass)))
    {
      pass_flag=1;
      Login_Year=cur_year;//stores logged in user's year
      Login_Num=cur_student;//stores logged in user's number
    }
  }
  if(pass_flag==1)
    return 1;
  printw("Login fail\n");
  refresh();
  return 0;
}

void Temp_Password()
{
  int flag1=0;
  int i, j, k;
  char num[5]={};
  char temppassword[8];
  float temp;
  YEAR * cur_year;
  STUDENT * cur_student;
  CGPA * cur_cgpa;
  clear();
  echo();
  srand(time(NULL));
  printw("Student Number:");
  refresh();
  scanw("%8s",Curr_Num);
  refresh();
  printw("Input latest semester's GPA:");
  refresh();
  echo();
  scanw("%f",&temp);
  cur_year=TOP->ST_YEAR;
  while(cur_year!=NULL && strncmp(cur_year->year,Curr_Num,4)!=0)
	  cur_year=cur_year->link;
  refresh();
  if(cur_year != NULL){
	  for(i=4;i<8;i++)
		  num[i-4]=Curr_Num[i];
	  cur_student=cur_year->ST_NUM;
	  while(cur_student!=NULL && strncmp(cur_student->number,num,4)!=0)
		  cur_student=cur_student->link;
	  if(cur_student != NULL){
		  cur_cgpa=cur_student->Child_C;
		  while(cur_cgpa->link != NULL)
			  cur_cgpa=cur_cgpa->link;
	  }
  }
  if(temp == cur_cgpa->score){
	  refresh();
	  for(i=0;i<8;i++){
		  j= rand()%127;
		  if(j<33){
			  i--;
			  continue;
		  }
		  temppassword[i]=j;
	  }
	  printw("Temporary Password is <");
	  refresh();
	  for(i=0;i<8;i++)
		  printw("%c",temppassword[i]);
	  printw(">\n");
	  refresh();
	  printw("%s",cur_student->password);
	  refresh();
	  strncpy(cur_student->password,temppassword,9);
  }
  noecho();
  wgetch(stdscr);
  printing();
  clear();
}
