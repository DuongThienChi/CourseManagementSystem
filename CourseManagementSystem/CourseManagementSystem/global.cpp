#include "mylib.h"
#include "student.cpp"
Date currentdate;
string  schoolyear_path;
string semester_path;
void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void disp(int n, char menu[][40], int rows, int cols)
{
	int i = 0;
	for (i = 0; i < rows; i++)
	{
		if (i == n)
		{
			color(12);
			gotoxy(35, 5 + i);
			cout << menu[i];
			color(7);

		}
		else
		{
			gotoxy(35, 5 + i);
			color(7);
			cout << menu[i];
		}
	}
}
void notify_box(string messg) {
	system("cls");
	gotoxy(35, 6);
	cout << messg << endl;
	system("pause");
}
int menu(char menu[][40], int rows, int cols)
{
	int  i = 0;
	int x;
	disp(i, menu, rows, cols);
	while (1)
	{
		x = _getch();
		if (x == 80)
		{
			if (i < rows - 1)
			{

				i = i + 1;
				disp(i, menu, rows, cols);
			}
			else if (i == rows - 1)
			{
				i = 0;
				disp(i, menu, rows, cols);
			}
		}
		else if (x == 72)
		{
			if (i > 0)
			{
				i = i - 1;
				disp(i, menu, rows, cols);
			}
			else if (i == 0)
			{
				i = rows - 1;
				disp(i, menu, rows, cols);
			}
		}
		else if (x == '\r')
		{
			return i;
		}
		else
		{
			disp(i, menu, rows, cols);
		}
	}
	return -1;
}
void thoatctrinh() {
	char c;
	do {
		color(7);
		cout << "\nBan co thoat chuong trinh? (y/n):";
		cin >> c;
	} while (c != 'y' && c != 'n');
	if (c == 'y')
		exit(1);
	if (c == 'n') {
		system("cls");

	}
}
void get_list_courses(string path, Course*& DS) {
	ifstream list_courses;
	list_courses.open(path);
	if (list_courses.is_open()) {
		string temp;
		getline(list_courses, temp);
		int sl = count(path);
		DS = new Course[sl];
		int i = 0;
		while (!list_courses.eof()) {
			getline(list_courses, DS[i].course_id, ',');
			getline(list_courses, DS[i].course_name, ',');
			getline(list_courses, DS[i].class_name, ',');
			getline(list_courses, DS[i].teacher_name, ',');
			string credits;
			getline(list_courses, credits, ',');
			DS[i].credits = stoi(credits);
			string maximum_students;
			getline(list_courses, maximum_students, ',');
			DS[i].max_students = stoi(maximum_students);
			getline(list_courses, DS[i].wDay, ',');
			getline(list_courses, DS[i].session);
			i++;
		}
	}
	else {
		notify_box("Can't open file!");
		return;
	}
}
void calculate_GPA(Student& a) {
	string scoreboard_path = semester_path + "student/" + a.Id + "-scoreboard.csv";
	float GPA = 0;
	Course* DS_course = NULL;
	string path_course = semester_path + "staff/courses.csv";
	int number_courses = count(path_course);
	int number_courses_study = count(scoreboard_path);
	Course* DS_Courses_study = new Course[number_courses_study];
	get_list_courses(path_course, DS_course);
	ifstream f_course;
	f_course.open(scoreboard_path);
	if (f_course.is_open()) {
		string temp;
		getline(f_course, temp);
		int i = 0;
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
				if (DS_course[j].course_id == course.course_id && DS_course[j].class_name == course.class_name) {
					DS_Courses_study[i].course_id = course.course_id;
					DS_Courses_study[i].credits = DS_course[j].credits;
					DS_Courses_study[i].TotalMark = course.TotalMark;
					break;
				}
			}
			i++;
		}
		float Sum_TotalMark = 0;
		int Sum_creadits = 0;
		for (int i = 0; i < number_courses_study; i++) {
			Sum_TotalMark += DS_Courses_study[i].TotalMark * DS_Courses_study[i].credits;
			Sum_creadits+= DS_Courses_study[i].credits;
		}
		GPA = Sum_TotalMark / Sum_creadits;
		a.GPA = GPA;
	}
	else {
		notify_box("Can't open file scoreboard!");
		return;
	}

}
void calculate_OverallGPA(Student& a) {
	string overallGPA_path = "./Data/OverallGPA/" + a.Id + "-overallGPA.bin";
	calculate_GPA(a);
	ifstream fin(overallGPA_path);
	float overall_GPA = 0;
	if (fin.is_open()) {
		fin >> overall_GPA;
		if (overall_GPA == 0) {
			overall_GPA = a.GPA;
		}
		else {
			overall_GPA = (overall_GPA + a.GPA) / 2.0;
		}
		a.overallGPA = overall_GPA;
		fin.close();
		ofstream fout(overallGPA_path);
		fout << a.overallGPA;
		fout.close();
	}
	else {
		notify_box("Can't open file overall GPA!");
		return;
	}
}
int count(string path) {
	ifstream file;
	file.open(path);
	int count = 0;
	if (file.is_open()) {
		string line;
		getline(file, line);
		while (file) {
			getline(file, line);
			count++;
		}
		count--;
		file.close();
	}
	else notify_box("Can't open file");
	return count;
}
void changepass(Staff* staff_user, Student* std_user) {
	string newpass1;
	string newpass2;
	do {
		system("cls");
		gotoxy(35, 4);
		cout << "New password: ";
		getline(cin, newpass1);
		gotoxy(35, 5);
		cout << "Re-enter new password: ";
		getline(cin, newpass2);
		if (newpass1.length() != 9 || newpass2.length() != 9) {
			gotoxy(35, 6);
			cout << "Mat khau phai du 9 ki tu!" << endl;
			system("pause");
		}
		else if (newpass1 != newpass2)
		{
			gotoxy(35, 6);
			cout << "Hai mat khau khong trung khop nhau!" << endl;
			system("pause");
		}
		else break;
	} while (1);
	if (staff_user != NULL) {
		(*staff_user).password = newpass1;
	}
	else
		(*std_user).password = newpass1;
	{
		gotoxy(35, 6);
		color(14);
		cout << "Cap nhat thanh cong mat khau moi" << endl; }
	system("pause");
}
void Menu_Login() {
	char menu1[3][40] = { "Login as Student" ,"Login as Staff","Exit" };
	while (1) {
		system("cls");
		cout << currentdate.Day << "/" << currentdate.Month << "/" << currentdate.Year << endl;
		gotoxy(35, 4);
		color(9);
		cout << "COURSE MANAGEMENT SYSTEM";
		int choice = menu(menu1, 3, 40);
		if (choice == 0)
		{
			Student_lg();
		}
		else if (choice == 1)
		{
			Staff_lg();
		}
		else if (choice == 2)
		{
			thoatctrinh();
		}
	}
}
void getcurrentDate() {
	time_t now = time(0);
	tm _tm;
	localtime_s(&_tm, &now);
	currentdate.Year = 1900 + _tm.tm_year;
	currentdate.Month = 1 + _tm.tm_mon;
	currentdate.Day = _tm.tm_mday;
}
void getschoolyear_path() {
	if (currentdate.Month >= month_begin_a_schoolyear)
		schoolyear_path = "./Data/" + to_string(currentdate.Year) + "-" + to_string(currentdate.Year + 1);
	else
		schoolyear_path = "./Data/" + to_string(currentdate.Year - 1) + "-" + to_string(currentdate.Year);
}
void getsemester_path() {
	int i = 0;
	for (i; i < 3; i++) {
		if (currentdate.Month == month_begin_semester[i])
		{
			i += 1;
			break;
		}
	}
	semester_path = schoolyear_path + "/semester " + to_string(i) + "/";
}
bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}
void copyFolder(string from, string to) {
	const auto copyOptions = filesystem::copy_options::update_existing
		| filesystem::copy_options::recursive
		;
	filesystem::copy(from, to, copyOptions);
}
