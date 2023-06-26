#pragma once
#include "mylib.h"
using namespace std;
void Staff_lg();
bool create_School_Year();
bool createSemester();

bool Quick_Input_Student_to_class();
bool add_Student_to_Class();
int count_number_classes();
bool load_list_classes(Class*& ds);
bool add_Course_to_Semester();
bool Quick_Input_student_to_course();
void get_list_courses(string path, Course*& DS);
void view_list_courses (string path);