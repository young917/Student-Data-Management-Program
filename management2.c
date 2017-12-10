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
									  clear();
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
  YEAR *pre_year;
  YEAR *cur_year;
  STUDENT *pre_num;
  STUDENT *cur_num;
  ASSIGN *pre_assign;
  ASSIGN *cur_assign;
  CGPA *pre_cgpa;
  CGPA *cur_cgpa;
  FILE* fpoint;
  fpoint=fopen("data.txt","w");
  cur_year=TOP->ST_YEAR;
  while(cur_year != NULL){
	  cur_num=cur_year->ST_NUM;
	  while(cur_num != NULL){
		  fprintf(fpoint,"%s%s\n",cur_year->year,cur_num->number);
	 	  fprintf(fpoint,"%s\n",cur_num->password);
	  	  fprintf(fpoint,"%d/%d\n",cur_num->Assign_Size,cur_num->CGPA_Size);
		  cur_assign=cur_num->Child_A;
		  pre_assign=NULL;
		  while(cur_assign != NULL){
			  fprintf(fpoint,"%s/%s/%s/%d/%d\n",cur_assign->name,cur_assign->describe,cur_assign->professor,cur_assign->date[0],cur_assign->date[1]);
			  pre_assign=cur_assign;
			  cur_assign=cur_assign->link;
			  free(pre_assign);
		  }
		  pre_cgpa=NULL;
		  cur_cgpa=cur_num->Child_C;
		  while(cur_cgpa != NULL){
			  fprintf(fpoint,"%d-%.2f\n",cur_cgpa->semester,cur_cgpa->score);
			  pre_cgpa=cur_cgpa;
			  cur_cgpa=cur_cgpa->link;
			  free(pre_cgpa);
		  }
		  pre_num=cur_num;
		  cur_num=cur_num->link;
		  free(pre_num);
	  }
	  pre_year=cur_year;
	  cur_year=cur_year->link;
	  free(pre_year);
  }
  free(TOP);
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
	refresh();
	Asize = Login_Num->Assign_Size;
	if(Asize){
		Sort_Assign();
		Print_Assign(Asize);
	}
	printw("1. New Assignment\n2. Delete Assignment\n3. Return to main menu\n\n");
	refresh();
	noecho();
	input=wgetch(stdscr);
	switch(input)
	{
		case '1': Add_Assign();break;
		case '2': Delete_Assign();break;
		case '3': return; break;
	}
	clear();
}

void Print_Assign(int Asize)
{
	ASSIGN * cur_assign;
	int month,today_month,k,D_day,thistime,thattime;
	time_t t;
	struct tm *today;
	
	t = time(NULL);
	today = localtime(&t);
	thistime = mktime(today);
	today_month=today->tm_mon;
	today_month+=1;
	cur_assign=Login_Num->Child_A;
	k=1;
	printw("%d mon, %d date\n",today_month,today->tm_mday);
	refresh();
	while(cur_assign != NULL){
		printw("<%d> Name	: %s\n",k++,cur_assign->name);
		printw("    Describe	: %s\n",cur_assign->describe);
		printw("    Professor	: %s\n",cur_assign->professor);
		printw("    Due	: %d/%d\n",cur_assign->date[0],cur_assign->date[1]);
		refresh();
		if(today_month < cur_assign->date[0]){
			month=cur_assign->date[0];
			D_day=0;
			while(month != today_month){
				if(month == 2)
					D_day+=28;
				else if(month<=7 && month%2 == 1)
					D_day+=31;
				else if(month>7 && month%2 == 0)
					D_day+=31;
				else
					D_day+=30;
				month++;
			}
			printw("    D-day	: -%d\n",(D_day)+(today->tm_mday)-(cur_assign->date[1]));
		}
		else if(today_month == cur_assign->date[0]){
			if(today->tm_mday == cur_assign->date[1])
				printw("    TODAY!\n");
			else if(today->tm_mday<cur_assign->date[1])
				printw("    D-day	: -%d\n",(cur_assign->date[1]-(today->tm_mday)));
			else
				printw("    D-day over!!\n");
		}
		else
			printw("    D-day over!!\n");
		printw("\n");
		refresh();
		cur_assign=cur_assign->link;
	}
}
char cgpa_menu()
{
	printw("1. Add new GPA or Change existing GPA\n");
	printw("2. View all\n");
	printw("3. Exit\n");
	refresh();
	noecho();
	return wgetch(stdscr);
}
void Search_CGPA() 
{
	int exit=0;
	while(!exit)
	{
		clear();
		switch(cgpa_menu())
		{
			case CGPA_ADD:{
							  clear();
							  Add_GPA();
							  break;
						  }
			case CGPA_VIEW: {
								clear();
								Print_CGPA();
								break;
							}
			case CGPA_QUIT: {
								clear();
								exit = 1;
								break;
							}
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
	CGPA *cur;
	clear();
	echo();
	printw("Input the semester of GPA : ");
	refresh();
	scanw("%c", &semester);
  	gpa_size = Login_Num->CGPA_Size;  
 	if(semester - '0' > (gpa_size + 1) || semester - '0' < 1) {
    	printw("You entered wrong number!\n");
    	getch();
    	return ;
  	} 
  	printw("Input the GPA : ");
	refresh();
	echo();
  	scanw("%f", &gpa);
  	if(gpa < 0 || gpa > 4.31) {
    	printw("You entered wrong number!\n");
    	getch();
    	return ;
  	}
  	if(semester - '0' <= gpa_size) { // change existing gpa
    	Cor_GPA(semester, gpa);
    	return ;
  	}
	// add new gpa
  	Login_Num->CGPA_Size++;
  	gpa_size++;
	if(gpa_size == 1){
		cur=malloc(sizeof(CGPA));
		cur->semester=semester-'0';
		cur->score=gpa;
		cur->link=NULL;
		Login_Num->Child_C=cur;
	}
	else{
		cur=Login_Num->Child_C;
		while(cur->link != NULL)
			cur=cur->link;
		cur->link=malloc(sizeof(CGPA));
		cur=cur->link;
		cur->semester=semester-'0';
		cur->score=gpa;
		cur->link=NULL;
	}
	return ;
}
void Cor_GPA(char semester, float gpa) 
{
  int i;
  CGPA *cur;
  cur=Login_Num->Child_C;
  while(cur!= NULL && cur->semester<(semester-'0'))
	  cur=cur->link;
  if(cur != NULL && cur->semester == semester-'0'){
	  cur->score=gpa;
	  printw("GPA is changed successfully!\n");
  }
  else
	  printw("GPA is not changed\n");
  refresh();
  getch();
  return ;
}
void Print_CGPA() //Additional
{
  int i=0;
  int tmpSemester;
  float tmpGPA;
  float sum = 0;
  CGPA *cur;
  clear();
  printw("<CGPA Management for %s>\n", Curr_Num);
  printw("------------------------------\n");
  printw("  Semester  |  GPA  |  CGPA  |  \n");
  refresh();
  cur=Login_Num->Child_C;
  while(cur != NULL)
  {
	  tmpSemester=cur->semester;
	  tmpGPA=cur->score;
	  sum+=tmpGPA;
	  printw("------------------------------\n");
      printw("     %d      |  %.2f |  %.2f  |\n", tmpSemester, tmpGPA, sum/(++i));
	  refresh();
	  cur=cur->link;
  }
  printw("------------------------------\n\n");
  printw("<CGPA Management by Graph for %s>\n", Curr_Num);
  printw("(x-axis : semester,  y-axis : score)\n");
  refresh();
  Print_CGPA_Graph();
  getch();
}
void Print_CGPA_Graph() 
{
	CGPA *cgpa_list;
	CGPA *cur_cgpa;
	int i,j,k;
	int index;
	int temp_semester;
	float temp_score;
	int insert_index; // cgpa_list[index] will be inserted in front of cgpa_list[insert_index]
	int cgpa_size;
	float left;
	float right;
	float *score_list;
	
	cgpa_size=Login_Num->CGPA_Size;
	cgpa_list=malloc(sizeof(CGPA)*cgpa_size);
	score_list=malloc(sizeof(float)*8);
	for(i=0;i<8;i++)
		score_list[i]=-1;
	index=0;
	cur_cgpa=Login_Num->Child_C;
	while(cur_cgpa != NULL){
		cgpa_list[index++]=*(cur_cgpa);
		cur_cgpa=cur_cgpa->link;
	}
	for(index=1;index<cgpa_size;index++){
		insert_index=0;
		while(insert_index<index &&  cgpa_list[insert_index].score>cgpa_list[index].score)
			insert_index++;
		if(cgpa_list[insert_index].score == cgpa_list[index].score){
			while(cgpa_list[insert_index].score == cgpa_list[index].score && cgpa_list[insert_index].semester<cgpa_list[index].semester)
				insert_index++;
		}
		if(insert_index == index)
			continue;
		temp_semester=cgpa_list[index].semester;
		temp_score=cgpa_list[index].score;
		for(;index>insert_index;index--){
			cgpa_list[index]=cgpa_list[index-1];
		}
		cgpa_list[insert_index].score=temp_score;
		cgpa_list[insert_index].semester=temp_semester;
	}
	index=0;
	j=4;
	for(i=4;i>=0;i--){
		for(;j>0;j--){
			if(j ==1)
				printw(" %d.0 |",i);
			else
				printw("     |");
			for(k=1;k<=8;k++){
				if(index < cgpa_size && k == cgpa_list[index].semester){
					right=0.2*j+i;
					left=0.2*(j-1)+i;
					if(cgpa_list[index].score < right && cgpa_list[index].score >= left){
						printw("  *   ");
						score_list[cgpa_list[index].semester-1]=cgpa_list[index].score;
						index++;
						continue;
					}				
				}
				if(score_list[k-1]>=0){
					printw(" %.2f ",score_list[k-1]);
					score_list[k-1]=-1;
				}
				else{
					printw("      ");
					score_list[k-1]=-1;
				}
				refresh();
			}
			printw("\n");
			refresh();
		}
		j=5;
	}
	for(i=0;i<9;i++)
		printw("------");
	printw("\n");
	refresh();
	printw("     |");
	for(i=1;i<=8;i++)
		printw("  %d  |",i);
	printw("\n");
	refresh();
	free(score_list);
	free(cgpa_list);
	/*
	checking
	for(index=0;index<cgpa_size;index++){
		printw("score :%f, semester: %d\n",cgpa_list[index].score,cgpa_list[index].semester);
	}
	refresh();
	getch();*/
}
void Sort_Assign()
{
	ASSIGN* cur;
	ASSIGN* pre;
	ASSIGN* insert_position;

	pre=Login_Num->Child_A;
	cur=Login_Num->Child_A->link;

	while(cur != NULL){
		insert_position=Login_Num->Child_A;
		if(insert_position->date[0] > cur->date[0]){
			pre->link=cur->link;
			cur->link=Login_Num->Child_A;
			Login_Num->Child_A=cur;
			pre=cur;
			cur=cur->link;
			continue;
		}
		else if(insert_position->date[0] == cur->date[0] && insert_position->date[1] > cur->date[1]){
			pre->link=cur->link;
			cur->link=Login_Num->Child_A;
			Login_Num->Child_A=cur;
			pre=cur;
			cur=cur->link;
			continue;
		}
		while(insert_position != pre){
			if(insert_position->link->date[0]>cur->date[0])
				break;
			else if(insert_position->link->date[0] == cur->date[0] && insert_position->link->date[1] > cur->date[1])
				break;
			insert_position=insert_position->link;
		}
		if(insert_position != pre){
			pre->link=cur->link;
			cur->link=insert_position->link;
			insert_position->link=cur;
		}
		pre=cur;
		cur=cur->link;
	}
}

void Add_Assign()
{
	ASSIGN* new=malloc(sizeof(ASSIGN));
	printw("Enter the name of new assignment:\n");
	refresh();
	echo();
	scanw("%99[^\n]%*c",new->name);
	printw("Enter the description of new assignment:\n");
	refresh();
	echo();
	scanw("%99[^\n]%*c",new->describe);
	printw("Enter the professor of new assignment:\n");
	refresh();
	echo();
	scanw("%99[^\n]%*c",new->professor);
	printw("Enter the due month of new assignment: ");
	refresh();
	echo();
	scanw("%d",&new->date[0]);
	printw("Enter the due day of new assignment: ");
	refresh();
	echo();
	scanw("%d",&new->date[1]);
	new->link=Login_Num->Child_A;
	Login_Num->Child_A=new;
	Login_Num->Assign_Size+=1;
	printw("New assignment is successfully added!!\n");
	refresh();
	noecho();
	wgetch(stdscr);
	clear();
}
void Delete_Assign()
{
	int flag=0;
	char compare1[300];
	char compare2[300];
	int date[2];
	ASSIGN* pre;
	ASSIGN* cur;

	if(Login_Num->Assign_Size == 0){
		printw("There is no assignment\n");
		refresh();
		noecho();
		wgetch(stdscr);
		clear();
		return;
	}
	printw("Enter the name of assignment you want to delete:\n");
	refresh();
	echo();
	scanw("%99[^\n]%*c",compare1);
	printw("Enter the description of assignment you want to delete:\n");
	refresh();
	echo();
	scanw("%99[^\n]%*c",compare2);
	strncat(compare1,compare2,strlen(compare2));
	printw("Enter the professor of assignment you want to delete:\n");
	refresh();
	echo();
	scanw("%99[^\n]%*c",compare2);
	strncat(compare1,compare2,strlen(compare2));
	printw("Enter the due month of assignment you want to delete: ");
	refresh();
	echo();
	scanw("%d",&date[0]);
	printw("Enter the due day of assignment you want to delete: ");
	refresh();
	echo();
	scanw("%d",&date[1]);
	pre=NULL;
	cur=Login_Num->Child_A;
	while(cur != NULL && cur->date[0]<date[0]){
		pre=cur;
		cur=cur->link;
	}
	while(cur != NULL && cur->date[1] < date[1]){
		if(cur->date[0] != date[0])
			break;
		pre=cur;
		cur=cur->link;
	}
	while(cur != NULL && cur->date[1] == date[1] && cur->date[0] == date[0]){
		strncpy(compare2,cur->name,strlen(cur->name)+1);
		strncat(compare2,cur->describe,strlen(cur->describe));
		strncat(compare2,cur->professor,strlen(cur->professor));
		if(strlen(compare1) == strlen(compare2) && strncmp(compare1,compare2,strlen(compare2)) == 0){
			flag=1;
			break;
		}
		pre=cur;
		cur=cur->link;
	}
	if(flag){
		printw("Successfully Deleted\n");
		refresh();
    	Login_Num->Assign_Size-=1;
		if(pre == NULL)
			Login_Num->Child_A=cur->link;
		else
			pre->link=cur->link;
		free(cur);
	}
	noecho();
	wgetch(stdscr);
	clear();
}
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
  if(num_flag==1){
	  if(!strncmp(cur_student->password,Curr_Pass,strlen(Curr_Pass))){
		  pass_flag=1;
      	  Login_Year=cur_year;//stores logged in user's year
      	  Login_Num=cur_student;//stores logged in user's number
   	  }
  }
  if(pass_flag==1)
    return 1;
  printw("Login fail\n");
  refresh();
  noecho();
  wgetch(stdscr);
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
