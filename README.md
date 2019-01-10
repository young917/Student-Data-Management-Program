# **_student-data-management-program_**

## Term

2017.11.23 ~ 2017.12.15

---

## Flow Chart 
---

<img src="https://github.com/young917/student-data-management-program/blob/master/%EC%88%9C%EC%84%9C%EB%8F%84.png?raw=true" width="80%" height="80%">


## Program Implementation

# 0. Program Start

<img src="https://user-images.githubusercontent.com/30820487/50948686-b39daf00-14e6-11e9-877a-c521ad52508c.png" width="40%" height="40%">

# 1. Select Login

<img src="https://user-images.githubusercontent.com/30820487/50948723-dcbe3f80-14e6-11e9-9a70-efa2f364ca3a.png" width="40%" height="40%">

<img src="https://user-images.githubusercontent.com/30820487/50948754-f9f30e00-14e6-11e9-84ac-19f16f0414df.png" width="40%" height="40%">

# 1.1. Assignment Management

<img src="https://user-images.githubusercontent.com/30820487/50948877-800f5480-14e7-11e9-8594-ec97b6056638.png" width="40%" height="40%">

# 1.1.1. New Assignment

<img src="https://user-images.githubusercontent.com/30820487/50948928-ae8d2f80-14e7-11e9-972d-84ed8ec190ee.png" width="40%" height="40%">

# 1.2. CGPA Management

<img src="https://user-images.githubusercontent.com/30820487/50948982-de3c3780-14e7-11e9-84e4-2e5b674b444e.png" width="40%" height="40%">

# 1.2.2. View all

<img src="https://user-images.githubusercontent.com/30820487/50949053-0deb3f80-14e8-11e9-875a-1836d262fe7d.png" width="40%" height="40%">

# 1.3. Change Password

<img src="https://user-images.githubusercontent.com/30820487/50948852-62da8600-14e7-11e9-8990-a649abaa3dcf.png" width="40%" height="40%">

# 4. Select Temporary Password

<img src="https://user-images.githubusercontent.com/30820487/50948798-358dd800-14e7-11e9-9502-079449ac4030.png" width="40%" height="40%">


---

## global variable 

**YEAR*Login_Year**

variable saves the YEAR address that includes student who login currently 

**STUDENT*Login_num** 

variable saves the STUDENT address that includes the information of the student who login currently 


---

## structure

<img src="https://user-images.githubusercontent.com/30820487/50948465-ea26fa00-14e5-11e9-8d8d-4b5022ef485b.png" width="40%" height="40%">

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
