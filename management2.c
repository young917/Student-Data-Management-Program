#include "management.h"

void printing();

int main()
{
  int exit=0;
  int login_flag=0;
  char choice;
  initscr();
  Create_Struct();
  while(!exit)
  {
	  switch(Account_Manage()){
		  case MENU_LOGIN:{
							  clear();
							  if(login()){
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
															 break;
														 }
										//for st
										case '5':{
												   clear();
												   printing();
												   break;
											   }
										default: {
													 printw("Wrong enter\nPlease enter any key to choose again\n");
													 refresh();
													 getch();
													 clear();
												 }
									  }
							  	}
							  }
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
							  break;
							 }
		  //for test
		  case '6': {
					  clear();
					  printing();
					  break;
				  }
		  default:{
					  printw("Wrong enter\nPlease enter any key to choose again\n");
					  refresh();
					  getch();
					  clear();
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
		  while(cur_assign != NULL){
			  fprintf(fpoint,"%s/%s/%s/%d/%d\n",cur_assign->name,cur_assign->describe,cur_assign->professor,cur_assign->date[0],cur_assign->date[1]);
			  pre_assign=cur_assign;
			  cur_assign=cur_assign->link;
			  free(pre_assign);
		  }
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
  int i;
  int current_num;
  char temp[350]; // store temporarily student's year
  FILE* fpoint;
  YEAR* Cur_year; // entered student will put into Cur_year and it indicate the YEAR(structure) where previously entered student is stored.
  YEAR* New_year;
  YEAR* Pre_year;
  STUDENT* Pre_student;
  STUDENT* New_student;
  STUDENT* Cur_student;
  ASSIGN* Pre_assign;
  ASSIGN* New_assign;
  CGPA* New_CGPA;
  CGPA* Cur_CGPA;  
  CGPA* Pre_CGPA;
  fpoint=fopen("data.txt","r");

  //TOP initialization
  TOP=(TREE_HEAD*)malloc(sizeof(TREE_HEAD));
  TOP->Year_Size=0;
  TOP->ST_YEAR=NULL;
  Pre_year=NULL;

  while(1){
	  if(fscanf(fpoint,"%4s",temp)== EOF) // take year
		  break; 
	  if(TOP->Year_Size == 0){ // case : there is no YEAR(structure)
		  TOP->Year_Size=1;
		  New_year=(YEAR*)malloc(sizeof(YEAR));
		  TOP->ST_YEAR=New_year;
		  strncpy(New_year->year,temp,5);
		  New_year->Num_Size=0;
		  New_year->ST_NUM=NULL;
		  New_year->link=NULL;
		  Cur_year=New_year;
	  }
	  else{
           // [ case : previously stored student's year is bigger than currently entered student's year ] ->(then) search from the first(TOP->ST_YEAR)
		   // not the case ->(then) search from Cur_year;
		   if(strncmp(temp,Cur_year->year,4)<0){ 
			  Pre_year=NULL;
			  Cur_year=TOP->ST_YEAR;
		   }
	
		   while(Cur_year!= NULL && strncmp(temp,Cur_year->year,4)>0){
			  Pre_year=Cur_year;
			  Cur_year=Cur_year->link;
		   }
		   // case : all stored year is smaller than current year
		   if(Cur_year == NULL){ 
			  TOP->Year_Size+=1;
			  New_year=(YEAR*)malloc(sizeof(YEAR));
			  strncpy(New_year->year,temp,5);
			  New_year->Num_Size=0;
			  New_year->ST_NUM=NULL;
			  New_year->link=NULL;
			  Pre_year->link=New_year;
			  Cur_year=New_year;
		  }
		   // case : there is no year corrresponding to current year
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
	  New_student->link=NULL;

	  //find insert point starting from Cur_year->ST_NUM)
	  Pre_student=NULL;
	  Cur_student=Cur_year->ST_NUM;
	  while(Cur_student != NULL && strncmp(Cur_student->number,New_student->number,4)<0){
		  Pre_student=Cur_student;
		  Cur_student=Cur_student->link;
	  }
	  //case : insert at front
	  if(Pre_student == NULL){
		  New_student->link=Cur_year->ST_NUM;
		  Cur_year->ST_NUM=New_student;
		  Cur_student=New_student;
	  }
	  //case : already stored student is entered 
	  else if(Cur_student != NULL && strncmp(Cur_student->number,New_student->number,4)== 0){
		  Cur_year->Num_Size-=1;
	  }
	  else{
		  New_student->link=Pre_student->link;
		  Pre_student->link=New_student;
		  Cur_student=New_student;
	  }

	  // Put assign linked-list and CGPA linke_list into Cur_student
	  // put assignment like 'queue'
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

	  Cur_CGPA=Cur_student->Child_C; // Cur_CGPA is insert point and where previously entered CGPA is stored.
	  current_num=Cur_student->CGPA_Size;
	  for(i=0;i<current_num;i++){
		  New_CGPA=(CGPA*)malloc(sizeof(CGPA));
		  fscanf(fpoint,"%d%*c%f%*c",&New_CGPA->semester,&New_CGPA->score);
		  New_CGPA->link=NULL;
		  // case: there is no CGPA in the Cur_student's CGPA list
		  if(Cur_CGPA == NULL){
			  Pre_CGPA=NULL;
			  Cur_student->Child_C=New_CGPA;
			  Cur_CGPA=New_CGPA;
			  continue;
		  }
		  // [ case: previously stored CGPA is bigger than currently entered CGPA ] ->(then) search insert point from start(Cur_student->Child_C)
		  // no the case ->(then) search insert point from Cur_CGPA
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
		printw("Year : %s / Year number : %d\n\n",Cur_year->year,Cur_year->Num_Size);
		refresh();
	 	for(Cur_student=Cur_year->ST_NUM;Cur_student!=NULL;Cur_student=Cur_student->link){
		  printw("number: %s / password: %s\n",Cur_student->number,Cur_student->password);
		  refresh();
		  printw("assignment number : %d \n", Cur_student->Assign_Size);
		  for(Cur_assign=Cur_student->Child_A;Cur_assign!=NULL;Cur_assign=Cur_assign->link){
			  printw("name : %s / describe : %s / professor :  %s /  date : %d:%d\n",Cur_assign->name,Cur_assign->describe,Cur_assign->professor,Cur_assign->date[0],Cur_assign->date[1]);
			  refresh();
		  }
		  printw("CGPA number : %d \n",Cur_student->CGPA_Size);
		  for(Cur_CGPA=Cur_student->Child_C;Cur_CGPA!=NULL;Cur_CGPA=Cur_CGPA->link){	
			  printw("semester : %d score : %.2f\n",Cur_CGPA->semester,Cur_CGPA->score);
			  refresh();
		  }
		  printw("\n");
		  refresh();
	  	}
	}
	getch();
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
	if(Asize){ // case : assignment exist
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
		case '3': {
					  clear();
					  break;
				  }
	}
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
	if(thistime == -1){
		printw("Error!\n");
		refresh();
		getch();
		return;
	}	
	today_month=today->tm_mon;
	today_month+=1; 
	cur_assign=Login_Num->Child_A;
	k=1;
	printw("today : %d/ %d \n",today_month,today->tm_mday);
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
			printw("    D-day	: -%d\n",(D_day)-(today->tm_mday)+(cur_assign->date[1]));
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
			default: {
						 clear();
						 printw("Enter wrong\n");
						 refresh();
						 getch();
						 clear();
						 break;
					 }
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

	echo();
	printw("Input the semester of GPA : ");
	refresh();
	scanw("%c", &semester);
  	gpa_size = Login_Num->CGPA_Size;  
 	if(semester - '0' > (gpa_size + 1) || semester - '0' < 1) {
    	printw("You entered wrong number!\n");
    	getch();
		clear();
    	return ;
  	} 
  	printw("Input the GPA : ");
	refresh();
	echo();
  	scanw("%f", &gpa);
  	if(gpa < 0 || gpa > 4.31) {
    	printw("You entered wrong number!\n");
    	getch();
		clear();
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
		//cur store latest GPA
		cur->link=malloc(sizeof(CGPA));
		cur=cur->link;
		cur->semester=semester-'0';
		cur->score=gpa;
		cur->link=NULL;
	}
	printw("Successfully added or changed\n");
	refresh();
	getch();
	clear();
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
  clear();
  return ;
}
void Print_CGPA() //Additional
{
  int i=0;
  int tmpSemester;
  float tmpGPA;
  float sum = 0; // sum of gpa until corresponding semester
  CGPA *cur;

  printw("<CGPA Management for %s>\n", Curr_Num);
  printw("------------------------------\n");
  printw("  Semester  |  GPA  |  CGPA  |  \n");
  refresh();
  cur=Login_Num->Child_C;
  while(cur != NULL) // until arriving at the end of the gpa list
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
  clear();
  return;
}
void Print_CGPA_Graph() 
{
	CGPA *cgpa_list; // sort high CGPA -> low CGPA (if CGPA is same, early semester -> late semester) and 
	CGPA *cur_cgpa;
	int i,j,k,h;// i indicates gpa's integer portion / j indicates gpa's decimal portion's range / k indicates semester
	int index;
	int temp_semester;
	float temp_score;
	int insert_index; // cgpa_list[index] will be inserted in front of cgpa_list[insert_index]
	int cgpa_size;
	int integer_portion;
	int decimal_portion;
	float left;// right and left indicate gpa's decimal portion's range. These variables are decided by j
	float *score_list;// after printing '*', score_list is used to print corresponding score next line.
	                  // this list's index indicates semester
					  // -1 means 'not printing'	
	cgpa_size=Login_Num->CGPA_Size;
	cgpa_list=malloc(sizeof(CGPA)*cgpa_size);
	score_list=malloc(sizeof(float)*8);
	for(i=0;i<8;i++)
		score_list[i]=-1;
	//make cgpa_list : input CGPA in the cgpa_list
	index=0;
	cur_cgpa=Login_Num->Child_C;
	while(cur_cgpa != NULL){
		cgpa_list[index].semester=cur_cgpa->semester;
		integer_portion=(cur_cgpa->score)*100;
		decimal_portion=(integer_portion)%100;
		decimal_portion/=10;
		decimal_portion=(decimal_portion)/2*2;
		integer_portion/=100;
		cgpa_list[index++].score=integer_portion+(float)(decimal_portion)*(0.1);
		cur_cgpa=cur_cgpa->link;
	}
	//make cgpa_list :sorting like insertion sort
	for(index=1;index<cgpa_size;index++){
		//finding insertion point
		insert_index=0;
		while(insert_index<index &&  cgpa_list[insert_index].score>cgpa_list[index].score)
			insert_index++;
		if(cgpa_list[insert_index].score == cgpa_list[index].score){
			while(cgpa_list[insert_index].score == cgpa_list[index].score && cgpa_list[insert_index].semester<cgpa_list[index].semester)
				insert_index++;
		}
		if(insert_index == index)
			continue;
		//make insertion space
		temp_semester=cgpa_list[index].semester;
		temp_score=cgpa_list[index].score;
		for(;index>insert_index;index--){
			cgpa_list[index]=cgpa_list[index-1];
		}
		//insertion
		cgpa_list[insert_index].score=temp_score;
		cgpa_list[insert_index].semester=temp_semester;
	}
	//printing graph
	index=0;
	j=3;
	for(i=4;i>=0;i--){
		for(;j>0;j--){
			if(j ==1)
				printw(" %d.0 |",i);
			else
				printw("     |");
			refresh();
			for(k=1;k<=8;k++){ 
				if(index < cgpa_size && k == cgpa_list[index].semester){
					left=0.2*(j-1)+i;
					if(cgpa_list[index].score ==left){
						printw("  *   ");
						cur_cgpa=Login_Num->Child_C;
						for(h=0;h<(k-1);h++)
							cur_cgpa=cur_cgpa->link;
						score_list[cgpa_list[index].semester-1]=cur_cgpa->score;
						index++;
						continue;
					}				
				} 
				if(score_list[k-1]>=0){
					printw(" %.2f ",score_list[k-1]);
					score_list[k-1]=-1;
				}
				else{
					printw("      "); // not printing
					score_list[k-1]=-1;
				}
				refresh();
			}
			printw("\n");
			refresh();
		}
		j=5;
	}
	j=-1;
	for(i=0;i<8;i++)
		if(score_list[i]>=0 && score_list[i]< 0.2){
			if(j==-1)
				printw("      ");
			while(j!=i-1){
				printw("      ");
				j++;
				refresh();
			}
			printw(" %.2f ",score_list[i]);
			j++;
			refresh();
		}
	if(j!= -1){
		printw("\n");
		refresh();
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

	// using insertion-sort
	while(cur != NULL){
		//find insert_position from start
		insert_position=Login_Num->Child_A;
		if(insert_position->date[0] > cur->date[0]){ 
			//case :  insert in front of Login_Num->Child_A
			pre->link=cur->link;
			cur->link=Login_Num->Child_A;
			Login_Num->Child_A=cur;
			cur=pre->link;
			continue;
		}
		else if(insert_position->date[0] == cur->date[0] && insert_position->date[1] > cur->date[1]){
			//case: insert in front of Login_Num->Child_A
			pre->link=cur->link;
			cur->link=Login_Num->Child_A;
			Login_Num->Child_A=cur;
			cur=pre->link;
			continue;
		}
		//find insert position(not in front of Login_Num->Child_A)
		//insert_position which current assign(ASSIGN *cur) is linked to
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
	int wrong=0;
	printw("Add New Assignment\n");
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
	//decide whether or not date is entered correctly
	if(new->date[0]<=0 || new->date[0]>12)
		wrong=1;
	else if(new->date[1]<=0 || new->date[1]>31)
		wrong=1;
	else if(new->date[0]<= 7 && new->date[0]%2 ==0){
		if(new->date[1] == 31)
			wrong=1;
	}
	else if(new->date[0]>7 && new->date[0]%2==1){
		if(new->date[1] == 31)
			wrong=1;
	}
	if(wrong){
		printw("You entered wrong date\n");
		refresh();
		getch();
		clear();
		free(new);
		return;
	}
	// insert in front of (Login_Num->Child_A)
	new->link=Login_Num->Child_A;
	Login_Num->Child_A=new;
	Login_Num->Assign_Size+=1;
	printw("New assignment is successfully added!!\n");
	refresh();
	getch();
	clear();
}
void Delete_Assign()
{
	int flag=0;
	int wrong=0;
	char compare1[300]; // store entered assignment's name and describe, professor ina line
	char compare2[300]; // store already stored assignment's name and describe,professor in a line
	int date[2];
	ASSIGN* pre;
	ASSIGN* cur;

	if(Login_Num->Assign_Size == 0){
		printw("There is no assignment\n");
		refresh();
		getch();
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
	if(date[0]<=0 || date[0]>12)
		wrong=1;
	else if(date[1]<=0 || date[1]>31)
		wrong=1;
	else if(date[0]<= 7 && date[0]%2 ==0){
		if(date[1] == 31)
			wrong=1;
	}
	else if(date[0]>7 && date[0]%2==1){
		if(date[1] == 31)
			wrong=1;
	}
	if(wrong){
		printw("You entered wrong date\n");
		refresh();
		getch();
		clear();
		return;
	}
	
	pre=NULL;
	cur=Login_Num->Child_A;
	while(cur != NULL && cur->date[0]<date[0]){
		pre=cur;
		cur=cur->link;
	}
	//after above process: (if all of stored assignment's due date month is earlier than entered month, cur stores NULL)
	//					   (if not, all assignments following 'cur' in the list are same or later than entered month)

	while(cur != NULL && cur->date[1] < date[1]){ // search until already stored assignment's month is same as the entered month and date is earlier than entered date
		if(cur->date[0] != date[0])
			break;
		pre=cur;
		cur=cur->link;
	}
	// 
	while(cur != NULL && cur->date[1] == date[1] && cur->date[0] == date[0]){
		// only for date is same
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
	else{
		printw("Fail deletion\n");
		refresh();
	}
	getch();
	clear();
}
void New_Account()
{
	int i;
	int enter_flag;
	YEAR *pre_year;
	YEAR * cur_year;
	STUDENT * pre_student;
	STUDENT * cur_student;
	while(1){
		enter_flag=1;
		printw("Student Number: ");
		refresh();
		echo();
		scanw("%8[^\n]%*c",Curr_Num);
		if(strlen(Curr_Num)!=8)
			enter_flag=0;
		for(i=0;i<8;i++){
			if(Curr_Num[i]<'0' || Curr_Num[i]>'9'){
				enter_flag=0;
				break;
			}
		}
		printw("Password: ");
		refresh();
		noecho();
		scanw("%15[^\n]%*c",Curr_Pass);
		if(!enter_flag){
			printw("Incorrect\n");
			refresh();
			getch();
			clear();
			continue;// enter again
		}
		//find same year or insert-point of year list
		pre_year=NULL;
		cur_year=TOP->ST_YEAR;
		while(cur_year != NULL && strncmp(cur_year->year,Curr_Num,4)<0){
			pre_year=cur_year;
			cur_year=cur_year->link;
		}
		if(cur_year == NULL || strncmp(cur_year->year,Curr_Num,4)!=0){
			cur_year=malloc(sizeof(YEAR));
			for(i=0;i<4;i++)
				cur_year->year[i]=Curr_Num[i];
			cur_year->year[4]='\0';
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
		//find insert-point of student list
		cur_student=cur_year->ST_NUM;
		while(cur_student != NULL && strcmp(cur_student->number,Curr_Num+4)<0){
			pre_student=cur_student;
			cur_student=cur_student->link;
		}
		//Exception : entered student already exists
		if(cur_student != NULL && strcmp(cur_student->number,Curr_Num+4) ==0){
			printw("Entered student number exist\n");
			refresh();
			break;
		}
		else{
			// insert entered student
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
			printw("New account is successfully created\n");
			refresh();
			break;
		}
	}
	getch();
	clear();
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
	float score;

	printw("Enter student number you want to delete : ");
	refresh();
	echo();
	scanw("%8[^\n]%*c",Curr_Num);
	if(strlen(Curr_Num)!=8){
		printw("Incorrect\n");
		refresh();
		getch();
		clear();
		return;
	}
	for(i=0;i<8;i++){
		if(Curr_Num[i]<'0' || Curr_Num[i]>'9'){
			printw("Incorrect\n");
			refresh();
			getch();
			clear();
			return;
		}
	}
	//find corresponding YEAR structure
	pre_year=NULL;
	cur_year=TOP->ST_YEAR;
	while(cur_year != NULL && strncmp(cur_year->year,Curr_Num,4)!=0){
		pre_year=cur_year;
		cur_year=cur_year->link;
	}
	if(cur_year == NULL){
		printw("Entered student number is not found\n");
		refresh();
		getch();
		clear();
		return;
	}
	//find corresponding STUDENT structure
	pre_student=NULL;
	cur_student=cur_year->ST_NUM;
	while(cur_student != NULL && strcmp(cur_student->number,Curr_Num+4)!=0){
		pre_student=cur_student;
		cur_student=cur_student->link;
	}
	if(cur_student == NULL){
		printw("Entered student number is not found\n");
		refresh();
		getch();
		clear();
		return;
	}

	printw("Enter student password : ");
	refresh();
	noecho();
	scanw("%15[^\n]%*c",Curr_Pass);
	if(strlen(cur_student->password) != strlen(Curr_Pass) || strncmp(cur_student->password,Curr_Pass,strlen(Curr_Pass) != 0)){
			printw("Entered password doesn't match\n");
			refresh();
			getch();
			clear();
			return;
	}
	//delete corresponding account
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
	printw("Successfully deleted!\n");
	refresh();
	getch();
	clear();
}
void Change_Password()
{
	char new[16];
	char confirm[16];
	while(1){
		printw("Enter new password:");
		refresh();
		noecho();
		scanw("%15[^\n]%*c",new);
		printw("Confirm new password:");
		refresh();
		noecho();
		scanw("%15[^\n]%*c", confirm);
		if(strlen(new) == strlen(confirm) && strncmp(new,confirm,strlen(new)) == 0){
			strncpy(Login_Num->password, new, strlen(new)+1);
			printw("Password of Account <%s%s> is successfully changed.\n",Login_Year->year,Login_Num->number);
			refresh();
			break;
		}
		printw("Two passwords are not matched.\n");
		refresh();
		getch();
		clear();
	}
	getch();
	clear();
}

int login()
{
  int i,j;
  int enter_flag=1; // correctly enter : 1  , incorrectly enter : 0
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
  if(strlen(Curr_Num)!=8)
	  enter_flag=0;
  for(i=0;i<8;i++)
	  if(Curr_Num[i]< '0' || Curr_Num[i]>'9')
		  enter_flag=0;
  printw("Password:");
  refresh();
  noecho();
  scanw("%15[^/n]%*c",Curr_Pass);
  if(enter_flag == 1){
  	for(i=0;i<4;i++)
    	year[i]=Curr_Num[i];
  	for(i=4;i<8;i++)
    	num[i-4]=Curr_Num[i];
  	//find corresponding YEAR structure
 	cur_year=TOP->ST_YEAR;
  	while(cur_year != NULL){
	  	if(!strncmp(cur_year->year,year,4)){
		  	year_flag=1;
		  	break;
	  	}
	  	cur_year=cur_year->link;
  	}
  }
  if(year_flag==1)
  {
	  //find corresponding STUDENT structure
	  cur_student=cur_year->ST_NUM;
	  while(cur_student != NULL){
      	if(!strncmp(cur_student->number,num,4)){
        	num_flag=1;
       		break;
      	}
		cur_student=cur_student->link;
      }
  }
  if(num_flag==1){
	  // whether or not password is matching
	  if(!strncmp(cur_student->password,Curr_Pass,strlen(Curr_Pass))){
		  pass_flag=1;
      	  Login_Year=cur_year;//stores logged in user's year
      	  Login_Num=cur_student;//stores logged in user's number
   	  }
  }
  if(pass_flag==1){
	printw("Login success\n");
	refresh();
	getch();
	clear();
    return 1;
  }
  else{
	  printw("Login fail\n");
  	  refresh();
      getch();
	  clear();
	  return 0;
  }
}

void Temp_Password()
{
  int i,j;
  char num[5]={};
  char temppassword[8];
  float temp;
  YEAR * cur_year;
  STUDENT * cur_student;
  CGPA * cur_cgpa;
  
  echo();
  srand(time(NULL));
  printw("Student Number:");
  refresh();
  scanw("%8[^\n]%*c",Curr_Num);
  if(strlen(Curr_Num) != 8){
	  printw("Incorrect\n");
	  refresh();
	  getch();
	  clear();
	  return;
  }
  for(i=0;i<8;i++){
	  if(Curr_Num[i]<'0' || Curr_Num[i]>'9'){
		  printw("Incorrect\n");
		  refresh();
		  getch();
		  clear();
		  return;
	  }
  } 
  printw("Input latest semester's GPA:");
  refresh();
  echo();
  scanw("%f",&temp);
  if(temp<0 || temp>4.3){
	  printw("Incorrect\n");
	  refresh();
	  getch();
	  clear();
	  return;
  }

  cur_year=TOP->ST_YEAR;
  while(cur_year!=NULL && strncmp(cur_year->year,Curr_Num,4)!=0)
	  cur_year=cur_year->link;
  refresh();
  if(cur_year != NULL){ //cur_year is where the entered student is stored
	  for(i=4;i<8;i++)
		  num[i-4]=Curr_Num[i]; 
	  cur_student=cur_year->ST_NUM;
	  while(cur_student!=NULL && strncmp(cur_student->number,num,4)!=0)
		  cur_student=cur_student->link;
	  if(cur_student != NULL){
		  cur_cgpa=cur_student->Child_C;
		  while(cur_cgpa->link != NULL)
			  cur_cgpa=cur_cgpa->link;
		  // cur_cgpa is student's latest gpa
	  }
	  else{
		  printw("Can't find\n");
		  refresh();
		  getch();
		  clear();
		  return;
	  }
  }
  else{
	  printw("Can't find\n");
	  refresh();
	  getch();
	  clear();
	  return;
  }
  if(cur_cgpa != NULL && temp == cur_cgpa->score){
	  refresh();
	  for(i=0;i<8;i++){
		  j= rand()%127;
		  if(j<33){ // the process to set j again
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
	  strncpy(cur_student->password,temppassword,9);
  }
  else{
	  printw("It is not the latest GPA\n");
	  refresh();
  }
  getch();
  clear();
}
