
#include "student.h"
void load_Student(Student*& DS, string path) {
	ifstream student;
	student.open(path);
	if (!student.is_open()) {
		cout << "Can't open file";
		system("pause");
		return;
	}
	else {
		int i = 0;
		string temp;
		getline(student, temp);
		while (!student.eof()) {
			getline(student, DS[i].No, ',');
			getline(student, DS[i].Id, ',');
			getline(student, DS[i].Firstname, ',');
			getline(student, DS[i].Lastname, ',');
			getline(student, DS[i].Gender, ',');
			getline(student, DS[i].DoB, ',');
			getline(student, DS[i].Social_Id, ',');
			getline(student, DS[i].password);
			i++;
		}
		student.close();
	}
}
void view_list_course_study(Student std) {
	string path = semester_path + "student/" + std.Id + "-scoreboard.csv";
	string path_course = semester_path + "staff/courses.csv";
	int number_courses = count(semester_path + "staff/courses.csv");
	int number_courses_study = count(path);
	Course* DS_Courses = NULL;
	get_list_courses(path_course, DS_Courses);
	ifstream f_course;
	f_course.open(path);
	if (f_course.is_open()) {
		string temp;
		getline(f_course, temp);
		int i = 0;
		system("cls");
		cout << left << setw(9) << "ID" << setw(24) << "Name" << setw(12) << "Class" << setw(24) << "Teacher" << setw(9) << "Credits" << setw(17) << "Maximum students " << setw(10) << "Day" << setw(7) << "Session" << endl;
		while (i < number_courses_study) {
			Course course;
			string No;
			getline(f_course, No, ',');
			getline(f_course, course.course_id, ',');
			getline(f_course, course.class_name, ',');
			string MidtermMark;
			getline(f_course, MidtermMark, ',');
			course.MidtermMark = stof(MidtermMark);
			string FinalMark;
			getline(f_course, FinalMark, ',');
			course.FinalMark = stof(FinalMark);
			string OtherMark;
			getline(f_course, OtherMark, ',');
			course.OtherMark = stof(OtherMark);
			string TotalMark;
			getline(f_course, TotalMark);
			course.TotalMark = stof(TotalMark);
			for (int i = 0; i < number_courses; i++) {
				if (DS_Courses[i].course_id == course.course_id && DS_Courses[i].class_name == course.class_name) {
					cout << left << setw(9) << DS_Courses[i].course_id << setw(24) << DS_Courses[i].course_name << setw(12) << DS_Courses[i].class_name << setw(24) << DS_Courses[i].teacher_name << setw(9) << DS_Courses[i].credits << setw(17) << DS_Courses[i].max_students << setw(10) << DS_Courses[i].wDay << setw(7) << DS_Courses[i].session << endl;
					break;
				}
			}
			i++;
		}
	}

}
void Student_lg() {
	string path = "./Data/Users/Student.csv";
	int sl;
	ifstream student;
	student.open(path);
	if (!student.is_open()) {
		cout << "Can't open file";
		system("pause");
		return;
	}
	else {
		sl = count(path);
		student.close();
	}
	Student* DS = new Student[sl + 1];
	load_Student(DS, path);
	string username;
	string pass;
	cout << "Login as Student";
	bool flag = false;
	Student* std_user;
	std_user = new Student;
	Staff* staff_user = NULL;
	do {
		system("cls");
		gotoxy(35, 5);
		cout << "Username: ";
		getline(cin, username);
		gotoxy(35, 6);
		cout << "Password: ";
		getline(cin, pass);
		for (int i = 0; i < sl; i++) {
			if (username.compare(DS[i].Id) == 0 && pass.compare(DS[i].password) == 0) {
				flag = true;
				std_user = &DS[i];
				break;
			}
		}
		if (flag == false) {
			notify_box("Wrong user name or password");
			break;
		}
		else break;
		system("pause");
	} while (1);
	if (flag) {

		char menu_student[5][40] = { "1.Your profile", "2.Change the password","3.View list of your courses", "4.View your scoreboard","5.Log out"};
		do {
			system("cls");
			int choice = menu(menu_student, 5, 40);
			if (choice == 0)
			{
				system("cls");
				gotoxy(35, 4);
				cout << "ID: " << (*std_user).Id;
				gotoxy(35, 5);
				cout << "First name: " << (*std_user).Firstname;
				gotoxy(35, 6);
				cout << "Last name: " << (*std_user).Lastname;
				gotoxy(35, 7);
				cout << "Gender: " << (*std_user).Gender;
				gotoxy(35, 8);
				cout << "DayofBirth: " << (*std_user).DoB;
				gotoxy(35, 9);
				cout << "Social ID: " << (*std_user).Social_Id << endl;
				system("pause");

			}
			else if (choice == 1)
			{
				system("cls");
				changepass(staff_user, std_user);

			}
			else if (choice == 2) {
				view_list_course_study((*std_user));
			}
			else if (choice == 3)
			{
				cout << 4;
			}
			else if (choice == 4) {
				break;
			}
		} while (1);
		system("pause");
	}
}