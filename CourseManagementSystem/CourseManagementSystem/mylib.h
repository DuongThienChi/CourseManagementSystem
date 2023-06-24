#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <direct.h>
#include <io.h>
#include <filesystem>

#include "student.h"
#include "staff.h"

using namespace std;
namespace fs = filesystem;
struct Date {
    int Day;
    int Month;
    int Year;
};
struct Student {
    string No;
    string Id;
    string Firstname;
    string Lastname;
    string Gender;
    string DoB;
    string Social_Id;
    string password;
};
struct Staff {
    string No;
    string Id;
    string Firstname;
    string Lastname;
    string Facultry;
    string Social_Id;
    string password;
};
struct Semester {
    int School_year;
    Date start_date;
    Date end_date;
};
struct Course {
    string course_id;
    string course_name;
    string teacher_name;
    string class_name;
    int credits;
    int max_students = 50;
    string wDay;
    string session;
    
};
void color(int color);
void gotoxy(int x, int y);
void disp(int n, char menu[][40], int rows, int cols);
int count(string path);
void changepass(Staff* staff_user, Student* std_user);
int menu(char menu[][40], int rows, int cols);
void Menu_Login();
void thoatctrinh();
void getcurrentDate();
void notify_box(string messg);
bool dirExists(const std::string& dirName_in);
void copyFolder(string from, string to);
void load_Student(Student* &DS, string path);
void getschoolyear_path();
void getsemester_path();

extern Date currentdate;
extern const int  month_begin_a_schoolyear = 9;
extern const int month_begin_semester[3] = { 9,3,7 };
extern string  schoolyear_path;
extern string semester_path;