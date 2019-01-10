# **_student-data-management-program_**

## flow chart 

![flow chart](https://github.com/young917/student-data-management-program/blob/master/%EC%88%9C%EC%84%9C%EB%8F%84.png?raw=true)

---

## global variable 

**YEAR*Login_Year**

variable saves the YEAR address that includes student who login currently 

**STUDENT*Login_num** 

variable saves the STUDENT address that includes the information of the student who login currently 


---

## structure

![image](https://user-images.githubusercontent.com/30820487/50948465-ea26fa00-14e5-11e9-8d8d-4b5022ef485b.png)

---

## Function description


**Create_Struct()**

create data structures from the file "data.txt". Funcion reads data and allocates the information to corresponding structure. In this process, insert currently made structure in the right order in the linked-list.(except: assignment). Function can read data that is not sorted. But if data that is sorted comes, function read it differently to create data structure fast.

**Account_Manage(), menu(), cgpa_menu()**

get character that indicates user's choice from the user and return it

**New_Account()**

make new student account. Function make new STUDENT structure using input data and insert it in the right order.

**Delete_Account()**

delete student account. Function finds STUDENT structure that includes information which match input data, then delete it.

**Temp_Password()**

Function finds corresponding STUDENT structure that match input data. Then, Function makes temporary password that is made up of ramdomly choosed ASCII code in the range from 34 to 126.

**login()**

If function can find STUDENT structure that match input data, return 1. In other cases, return 0

**Change_Password()** 

function change password that global variable Login_num indicates.

**Search_Assign()** 
If the number of student's assignment is one or more, call Sort_Assign() and Print_Assign(int Asize). Then at user's choice, call add_Assign() or Delete_Assign() or menu()

**Sort_Assign()**

Using insertion sort, linked-list of assignment is sorted in the order of due-date

**Print_Assign()**

print assignment's information in the order of due-date. In this process, function find today's date and get D-Day then print it

**Add_Assign()** 

make new ASSIGN structure that contatins input data and insert it at the beginning of the linked-list

**Delete_Assign()** 

If function finds ASSIGN structure that contains information matched with input data, delete it.

**Search_CGPA()** 

call function according to the character returned by cgpa_menu() function

**Add_GPA()** 

If input semester is next semester of latest stored semester, make new CGPA structure and insert at the end of the linked-list of CGPA.If input semester already exist in the linked-list, then call Cor_GA(int semester, float gpa)

**Cor_GPA(int semester, float gpa)**

Function finds CGPA structure that matched semester gotten from parameter of the function. Then change gpa

**Print_CGPA()** 

print CGPA depending on the order of the linked-list

**Print_CGPA_Graph()** 

Function make graph whose x axis is semester and whose y axis is gpa.
