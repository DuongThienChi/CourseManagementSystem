
#include "student.h"
void load_Student(Student*& DS, string path,bool user) {
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
		int sl = count(path);
		while (i<sl) {
			getline(student, DS[i].No, ',');
			getline(student, DS[i].Id, ',');
			getline(student, DS[i].Firstname, ',');
			getline(student, DS[i].Lastname, ',');
			getline(student, DS[i].Gender, ',');
			getline(student, DS[i].DoB, ',');
			if (user == 1) {
				getline(student, DS[i].Social_Id, ',');
				getline(student, DS[i].password);
			}
			else {
				getline(student, DS[i].Social_Id);
			}
			i++;
		}
		student.close();
		return;
	}
}
void view_list_course_study(Student std) {
	string path = semester_path + "student/" + std.Id + "-scoreboard.csv";
	string path_course = semester_path + "staff/courses.csv";
	int number_courses = count(semester_path + "staff/courses.csv");
	int number_courses_study = count(path);
	if (number_courses_study > 0) {
		Course* DS_Courses = NULL;
		get_list_courses(path_course, DS_Courses);
		ifstream f_course;
		f_course.open(path);
		if (f_course.is_open()) {
			string temp;
			getline(f_course, temp);
			int i = 0;
			system("cls");
			cout << left << setw(3) << "No" << setw(9) << "ID" << setw(24) << "Name" << setw(12) << "Class" << setw(24) << "Teacher" << setw(9) << "Credits" << setw(17) << "Maximum students " << setw(10) << "Day" << setw(7) << "Session" << endl;
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
				for (int j = 0; j < number_courses; j++) {
					if (DS_Courses[j].course_id == course.course_id && DS_Courses[j].class_name == course.class_name) {
						cout << left << setw(3) << i + 1 << setw(9) << DS_Courses[j].course_id << setw(24) << DS_Courses[j].course_name << setw(12) << DS_Courses[j].class_name << setw(24) << DS_Courses[j].teacher_name << setw(9) << DS_Courses[j].credits << setw(17) << DS_Courses[j].max_students << setw(10) << DS_Courses[j].wDay << setw(7) << DS_Courses[j].session << endl;
						break;
					}
				}
				i++;
			}
			system("pause");
		}
	}
	else {
		notify_box("You have not registered for any courses yet");
		return;
	}
}
void view_scoreboard(Student std) {
	bool publish = 0;
	ifstream f_publish("./Data/Publish_Scoreboard.bin");
	if (f_publish.is_open()) {
		f_publish >> publish;
		f_publish.close();
	}
	if (publish) {
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
			cout << left << setw(3) << "No" << setw(10) << "Course ID" << setw(24) << "Course Name" << setw(12) << "Class" << setw(13) << "Midterm Mark" << setw(11) << "Final Mark" << setw(12) << "Other Mark" << setw(11) << "Final Mark" << "\n";
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
				for (int j = 0; j < number_courses; j++) {
					if (DS_Courses[j].course_id == course.course_id && DS_Courses[j].class_name == course.class_name) {
						cout << left << setw(3) << i + 1 << setw(10) << DS_Courses[j].course_id << setw(24) << DS_Courses[j].course_name << setw(12) << DS_Courses[j].class_name << setw(13) << course.MidtermMark << setw(11) << course.FinalMark << setw(12) << course.OtherMark << setw(11) << course.TotalMark << endl;
						break;
					}
				}
				i++;
			}
			system("pause");
		}
	}
	else {
		notify_box("The scoreboard has not been released yet");
		return;
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
	load_Student(DS, path, 1);
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
		char menu_student[5][40] = { "1.Your profile", "2.Change the password","3.View list of your courses", "4.View your scoreboard","5.Log out" };
		do {
			system("cls");
			print_Text("./Data/Title/student_title.txt", 9, 35, 3);
			int choice = menu(menu_student, 5, 40, 35, 8);
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
				view_scoreboard((*std_user));
			}
			else if (choice == 4) {
				break;
			}
		} while (1);
	}
}