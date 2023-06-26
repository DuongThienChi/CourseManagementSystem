
#include "staff.h"
const int  month_begin_a_schoolyear = 9;
const int month_begin_semester[] = { 9,3,7 };
Semester semester;;
void add_to_User(Student a) {
	fstream user;
	user.open("./Data/Users/Student.csv");
	if (!user.is_open()) {
		notify_box("Can't open file");
		system("pause");
		return;
	}
	else {
		int sl = count("./Data/Users/Student.csv");
		Student* DS = new Student[sl + 1];
		load_Student(DS, "./Data/Users/Student.csv");
		DS[sl] = a;
		user << "No, Student ID, First name, Last name, Gender, Day of birth, Social ID, Password" << "\n";
		for (int i = 0; i < sl + 1; i++) {
			user << i + 1 << "," << DS[i].Id << "," << DS[i].Firstname << "," << DS[i].Lastname << "," << DS[i].Gender << "," << DS[i].DoB << "," << DS[i].Social_Id << "," << DS[i].password << "\n";
		}
		user.close();
	}

}
bool Quick_Input_Student_to_class() {
	system("cls");
	gotoxy(35, 7);
	cout << "Linked to file classes:";
	gotoxy(35, 8);
	cout << "Name of class:";
	gotoxy(58, 7);
	string link;
	getline(cin, link);
	gotoxy(49, 8);
	string name_class;
	getline(cin, name_class);
	ifstream classe_in;
	classe_in.open(link);
	if (!classe_in.is_open()) {
		notify_box("Can't open file");
		system("pause");
		return 0;
	}
	else {
		string source_file = link;
		if (dirExists(schoolyear_path) || currentdate.Month != month_begin_a_schoolyear)
		{
			notify_box("Can't create new Class in this time");
			return 0;
		}
		string destination_file = schoolyear_path + "/classes/firstyear/";
		//for (int i = source_file.length(); i >= 0; i--) {
		//    if (source_file[i] == '/') {
		//        name_class = source_file.substr(i + 1, source_file.length() - i - 1); // /data/classes/22ctt2.csv
		//        break;
		//    }
		//}
		destination_file = destination_file + name_class + ".csv";
		/*Xu li sao chep du lieu */
		ifstream sfile;
		sfile.open(source_file, ios::binary | ios::in);
		ofstream dfile;
		dfile.open(destination_file, ios::binary | ios::out);
		if (sfile.is_open() && dfile.is_open()) {
			char c;
			while (sfile.get(c) && sfile.good()) {
				dfile.put(c);/*Chep tung byte*/
			}
			sfile.close();
			dfile.close();
			notify_box("Class " + name_class + " is created");
		}
		else {
			notify_box("Can't open file");
			return 0;
		}
		return 1;
	}

}
void sort_DS_Student(Student*& DS, int sl) {
	for (int i = 0; i < sl - 1; i++) {
		for (int j = 0; j < sl - i - 1; j++) {
			if (stoi(DS[j].Id) >= stoi(DS[j + 1].Id))
			{
				Student temp;
				temp = DS[j];
				DS[j] = DS[j + 1];
				DS[j + 1] = temp;
			}
		}
	}
}
bool check_repeat_student(Student a, Student* DS, int sl) {
	for (int i = 0; i < sl; i++) {
		if (stoi(a.Id) == stoi(DS[i].Id))
			return 1;
	}
	return 0;
}
bool add_Student_to_Class() {
	system("cls");
	/* if (currentdate.Month != month_begin_a_schoolyear)
	 {
		 notify_box("Can't add new Student in this time");
		 return 0;
	 }
	 else*/ {
		string name_Class;
		gotoxy(35, 4);
		cout << "Class:";
		gotoxy(43, 4);
		getline(cin, name_Class);
		string class_path = schoolyear_path + "/classes/firstyear/" + name_Class + ".csv";
		ifstream class_file;
		class_file.open(class_path);
		if (class_file.is_open()) {
			int sl = count(class_path);  class_file.close();
			class_file.open(class_path);
			Student* DS = new Student[sl + 1];
			int i = 0;
			string temp;
			getline(class_file, temp);
			while (i < sl) {
				getline(class_file, DS[i].No, ',');
				getline(class_file, DS[i].Id, ',');
				getline(class_file, DS[i].Firstname, ',');
				getline(class_file, DS[i].Lastname, ',');
				getline(class_file, DS[i].Gender, ',');
				getline(class_file, DS[i].DoB, ',');
				getline(class_file, DS[i].Social_Id);
				i++;
			}
			class_file.close();
			Student new_std;
			do {
				system("cls");
				gotoxy(35, 5);
				cout << "ID:";
				gotoxy(35, 6);
				cout << "First name :";
				gotoxy(35, 7);
				cout << "Last name:";
				gotoxy(35, 8);
				cout << "Gender:";
				gotoxy(35, 9);
				cout << "Day of birth:";
				gotoxy(35, 10);
				cout << "Scocial ID:";
				gotoxy(39, 5);
				getline(cin, new_std.Id);
				gotoxy(48, 6);
				getline(cin, new_std.Firstname);
				gotoxy(46, 7);
				getline(cin, new_std.Lastname);
				gotoxy(44, 8);
				getline(cin, new_std.Gender);
				gotoxy(48, 9);
				getline(cin, new_std.DoB);
				gotoxy(47, 10);
				getline(cin, new_std.Social_Id);
				if (check_repeat_student(new_std, DS, sl)) {
					notify_box("This ID Student already exists");
					system("pause");
				}
				else break;
			} while (1);
			DS[sl] = new_std;
			sort_DS_Student(DS, sl + 1);
			ofstream class_file;
			class_file.open(class_path);
			if (class_file.is_open()) {
				class_file << temp << "\n";
				for (int i = 0; i < sl; i++) {
					class_file << i + 1 << "," << DS[i].Id << "," << DS[i].Firstname << "," << DS[i].Lastname << "," << DS[i].Gender << "," << DS[i].DoB << "," << DS[i].Social_Id << "\n";
				}
				class_file << sl + 1 << "," << DS[sl].Id << "," << DS[sl].Firstname << "," << DS[sl].Lastname << "," << DS[sl].Gender << "," << DS[sl].DoB << "," << DS[sl].Social_Id;
				class_file.close();
				new_std.password = "12345678";
				add_to_User(new_std);
			}
			else {
				notify_box("Can not open file!");
				return 0;
			}
			delete[] DS;
		}
		else {
			notify_box("Can not open file!");
			return 0;
		}
		return 1;
	}
}
int count_number_classes() {
	string path = schoolyear_path + "/classes/";
	string extension(".csv");
	int k = 0;
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == extension) {
			k++;
		}
	}
	return k;
}
bool load_list_classes(Class*& ds) {
	string path = schoolyear_path + "/classes/";
	string extension(".csv");
	int k = 0;
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == extension) {
			Class c;
			c.className = p.path().stem().string();
			c.path = p.path();
			ds[k] = c;
			k++;
		}
	}
	return 1;
}
void view_list_of_classes() {
	int x = 35, y = 5;
	Class* ds = new Class[count_number_classes()];
	load_list_classes(ds);
	system("cls");
	gotoxy(x, y);
	cout << left << setw(4) << "STT" << setw(6) << "Class" << endl;
	for (int i = 0; i < count_number_classes(); i++) {
		gotoxy(35, 5 + i + 1);
		cout << left << setw(4) << i + 1 << setw(6) << ds[i].className << endl;
	}
	system("pause");
}
void view_list_of_student_in_class() {
	system("cls");
	gotoxy(35, 5);
	cout << "Class name:";
	string class_name;
	getline(cin, class_name);
	transform(class_name.begin(), class_name.end(), class_name.begin(), ::toupper);
	Class* ds = new Class[count_number_classes()];
	load_list_classes(ds);
	for (int i = 0; i < count_number_classes(); i++) {
		if (ds[i].className == class_name) {
			string path_string = { ds[i].path.u8string() };
			int sl = count(path_string);
			Student* DS_hocsinh = new Student[sl];
			ifstream student;
			student.open(path_string);
			if (!student.is_open()) {
				cout << "Can't open file";
				system("pause");
				return;
			}
			else {
				int i = 0;
				string temp;
				getline(student, temp);
				while (i < sl) {
					getline(student, DS_hocsinh[i].No, ',');
					getline(student, DS_hocsinh[i].Id, ',');
					getline(student, DS_hocsinh[i].Firstname, ',');
					getline(student, DS_hocsinh[i].Lastname, ',');
					getline(student, DS_hocsinh[i].Gender, ',');
					getline(student, DS_hocsinh[i].DoB, ',');
					getline(student, DS_hocsinh[i].Social_Id);
					i++;
				}
				student.close();
			}
			system("cls");
			cout << left << setw(3) << "No" << setw(11) << "Student ID" << setw(17) << "First name" << setw(10) << "Last name" << setw(7) << "Gender" << setw(9) << "DoB" << setw(10) << "Social ID" << "\n";
			for (int i = 0; i < sl; i++) {
				cout << left << setw(3) << i + 1 << setw(11) << DS_hocsinh->Id << setw(17) << DS_hocsinh->Firstname << setw(10) << DS_hocsinh->Lastname << setw(7) << DS_hocsinh->Gender << setw(9) << DS_hocsinh->DoB << setw(10) << DS_hocsinh->Social_Id << "\n";
			}
			system("pause");
			break;
		}

	}
	notify_box("Class does not exits!");


}
bool create_School_Year() {
	if (currentdate.Month != month_begin_a_schoolyear) {
		string mess = { "The new school year hasn't started yet!" };
		notify_box(mess);
		return 0;
	}
	else {
		string prevSchoolyear_path = "./Data/" + to_string(currentdate.Year - 1) + "-" + to_string(currentdate.Year);
		string classes_path = schoolyear_path + "/classes/firstyear/";
		/*ofstream fout("./data/schoolyear.dat");
		fout << currentSchoolYear << endl;
		fout << dateToStr(currentDate) << endl;
		fout << "9/" + to_string(lastYear + 1);
		fout.close();*/
		if (dirExists(prevSchoolyear_path)) {
			fs::create_directories(classes_path);
			/* ofstream(schoolYearPath + "/semester.dat");*/
			prevSchoolyear_path += "/classes";
			copyFolder(prevSchoolyear_path, classes_path);
			fs::remove_all(classes_path + "/finalyear");
			fs::rename(classes_path + "/thirdyear", classes_path + "/finalyear");
			fs::rename(classes_path + "/secondyear", classes_path + "/thirdyear");
			fs::rename(classes_path + "/firstyear", classes_path + "/secondyear");
			fs::create_directories(classes_path + "/firstyear");
			return 1;
		}
		else {
			//   ofstream(schoolYearPath + "/semester.dat");
			fs::create_directories(classes_path + "/firstyear");
			fs::create_directories(classes_path + "/secondyear");
			fs::create_directories(classes_path + "/thirdyear");
			fs::create_directories(classes_path + "/finalyear");
			return 1;
		}

	}
}
bool createSemester() {
	/* if (currentdate.Month != month_begin_semester[0] || currentdate.Month != month_begin_semester[1] || currentdate.Month != month_begin_semester[2]) {
		 string mess = { "Can not create a new semester in this time!" };
		 notify_box(mess);
		 return 0;
	 }
	 else {*/
	if (!dirExists(semester_path)) {
		fs::create_directories(semester_path);
		fs::create_directories(semester_path + "staff/");
		fs::create_directories(semester_path + "student/");
		system("cls");
		gotoxy(35, 5);
		cout << "Start date(dd/mm/yyyy): ";
		gotoxy(35, 6);
		cout << "End date(dd/mm/yyyy): ";
		gotoxy(59, 5);
		getline(cin, semester.start_date);
		gotoxy(57, 6);
		getline(cin, semester.end_date);
		ofstream f_semester(semester_path + "semester.bin");
		if (f_semester.is_open()) {
			f_semester << "Start date: " << semester.start_date << endl;
			f_semester << "End date: " << semester.end_date << endl;
			f_semester.close();
		}
		else return 0;
		ofstream f_course(semester_path + "staff/" + "courses.csv");
		if (f_course.is_open()) {
			f_course << "ID,Course name,Class name,Teacher name,Number of credits,Maximum number of students,Day of week,Session" << endl;
			f_course.close();
			return 1;
		}
		else return 0;
	}
	else return 1;
	// }
}
bool check_course(Course a) {
	if (a.course_id.length() != 8 || a.class_name == "" || a.teacher_name == "")
		return 1;
	return 0;
}
bool input_course(Course& new_course) {
	string session[4] = { "S1-7:30","S2-9:30","S3-13:30","S4-15:30" };
	do {
		system("cls");
		gotoxy(35, 5);
		cout << "ID:";
		gotoxy(35, 6);
		cout << "Course name :";
		gotoxy(35, 7);
		cout << "Class name:";
		gotoxy(35, 8);
		cout << "Teacher name:";
		gotoxy(35, 9);
		cout << "Credits:";
		gotoxy(35, 10);
		cout << "Day of week:";
		gotoxy(35, 11);
		cout << "Session:";
		gotoxy(39, 5);
		getline(cin, new_course.course_id);
		gotoxy(48, 6);
		getline(cin, new_course.course_name);
		gotoxy(47, 7);
		getline(cin, new_course.class_name);
		gotoxy(49, 8);
		getline(cin, new_course.teacher_name);
		gotoxy(43, 9);
		cin >> new_course.credits;
		cin.ignore();
		gotoxy(47, 10);
		getline(cin, new_course.wDay);
		int temp = 0;
		gotoxy(43, 11);
		cin >> temp;
		cin.ignore();
		if (check_course(new_course) && temp < 5 && temp>0) {
			gotoxy(35, 11);
			cout << "Nhap sai! Ban co muon nhap lai(y/n): ";
			string tmp;
			getline(cin, tmp);
			if (tmp == "n")
				return 0;
			break;
		}
		new_course.session = session[temp - 1];

	} while (1);
	return 1;
}

bool add_Course_to_Semester() {
	/* if (currentdate.Month != month_begin_semester[0] || currentdate.Month != month_begin_semester[1] || currentdate.Month != month_begin_semester[2]) {
		 string mess = { "Can not add a new course in this time!" };
		 notify_box(mess);
		 return 0;
	 }
	 else {*/
	fstream f_course;
	f_course.open(semester_path + "staff/courses.csv");
	if (f_course.is_open()) {
		Course new_course;
		if (input_course(new_course)) {
			f_course.seekp(0, ios::end);
			f_course << "\n" << new_course.course_id << "," << new_course.course_name << "," << new_course.class_name << "," << new_course.teacher_name << "," << new_course.credits << "," << new_course.max_students << "," << new_course.wDay << "," << new_course.session;
			f_course.close();
			ofstream f_new_course;
			f_new_course.open(semester_path + "staff/" + new_course.course_id + "-" + new_course.class_name + ".csv");
			if (f_new_course.is_open()) {
				f_new_course << "No, Student ID, First name, Last name, Gender, Day of birth, Social ID" << endl;
			}
			else {
				notify_box("Can not create file!");
				return 0;
			}
			return 1;
		}
		else {
			notify_box("Can not open file!");
			return 0;
		}
	}
	else {
		notify_box("Course not created");
		return 0;
	}
	// }
}
bool Quick_Input_student_to_course() {
	system("cls");
	gotoxy(35, 7);
	cout << "Linked to file list student:";
	gotoxy(35, 8);
	cout << "Course ID:";
	gotoxy(35, 9);
	cout << "Class name:";
	gotoxy(63, 7);
	string link;
	getline(cin, link);
	gotoxy(45, 8);
	string id;
	getline(cin, id);
	gotoxy(46, 9);
	string classname;
	getline(cin, classname);
	ifstream list_student;
	list_student.open(link);
	if (!list_student.is_open()) {
		notify_box("Can't open file");
		return 0;
	}
	else {
		string source_file = link;
		/* if (currentdate.Month != month_begin_semester[0] || currentdate.Month != month_begin_semester[1] || currentdate.Month != month_begin_semester[2]) {
		string mess = { "Can not add a new course in this time!" };
		notify_box(mess);
		return 0;
		 }
		else {*/
		string destination_file = semester_path + "staff/" + id + "-" + classname + ".csv";
		/*Xu li sao chep du lieu */
		ifstream sfile;
		sfile.open(source_file, ios::binary | ios::in);
		ofstream dfile;
		dfile.open(destination_file, ios::binary | ios::out);
		if (sfile.is_open() && dfile.is_open()) {
			char c;
			while (sfile.get(c) && sfile.good()) {
				dfile.put(c);/*Chep tung byte*/
			}
			sfile.close();
			dfile.close();
		}
		else {
			notify_box("Can't open file");
			return 0;
		}
		list_student.close();
		return 1;
		// }
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
void view_list_courses() {
	string path = semester_path + "staff/courses.csv";
	int sl = count(path);
	Course* DS;
	get_list_courses(path, DS);
	system("cls");
	cout << left << setw(9) << "ID" << setw(24) << "Name" << setw(12) << "Class" << setw(24) << "Teacher" << setw(9) << "Credits" << setw(17) << "Maximum students " << setw(10) << "Day" << setw(7) << "Session" << endl;
	for (int i = 0; i < sl; i++) {
		cout << left << setw(9) << DS[i].course_id << setw(24) << DS[i].course_name << setw(12) << DS[i].class_name << setw(24) << DS[i].teacher_name << setw(9) << DS[i].credits << setw(17) << DS[i].max_students << setw(10) << DS[i].wDay << setw(7) << DS[i].session << endl;
	}
	system("pause");
	return;
	}
bool update_course_information() {
	ifstream list_courses;
	list_courses.open(semester_path + "staff/courses.csv");
	if (list_courses.is_open()) {
		string temp;
		getline(list_courses, temp);
		int sl = count(semester_path + "staff/courses.csv");
		Course* DS = new Course[sl];
		int i = 0;
		while (i < sl) {
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
		system("cls");
		Course new_course;
		input_course(new_course);
		for (int i = 0; i < sl; i++) {
			if (DS[i].course_id == new_course.course_id && DS[i].class_name == new_course.class_name) {
				DS[i] = new_course;
				list_courses.close();
				ofstream list_courses;
				list_courses.open(semester_path + "staff/courses.csv");
				if (list_courses.is_open()) {
					list_courses << temp << endl;
					for (int i = 0; i < sl - 1; i++) {
						list_courses << DS[i].course_id << "," << DS[i].course_name << "," << DS[i].class_name << "," << DS[i].teacher_name << "," << DS[i].credits << "," << DS[i].max_students << "," << DS[i].wDay << "," << DS[i].session << "\n";
					}
					list_courses << DS[sl - 1].course_id << "," << DS[sl - 1].course_name << "," << DS[sl - 1].class_name << "," << DS[sl - 1].teacher_name << "," << DS[sl - 1].credits << "," << DS[sl - 1].max_students << "," << DS[sl - 1].wDay << "," << DS[sl - 1].session;
				}
				else {
					notify_box("Can not open file!");
					return 0;
				}
				return 1;
				list_courses.close();
			}
		}
		notify_box("This course is not exits!");
		return 0;
	}
	else {
		notify_box("Can not open file!");
		return 0;
	}
}
bool Remove_student_frome_course() {
	system("cls");
	gotoxy(35, 5);
	cout << "Course ID:";
	gotoxy(35, 6);
	cout << "Class name:";
	gotoxy(35, 7);
	cout << "Student ID:";
	string id;
	gotoxy(45, 5);
	getline(cin, id);
	gotoxy(46, 6);
	string classname;
	getline(cin, classname);
	gotoxy(46, 7);
	string student_id;
	getline(cin, student_id);
	string path = semester_path + "staff/" + id + "-" + classname + ".csv";
	int sl = count(path);
	Student* DS = new Student[sl + 1];
	ifstream student;
	student.open(path);
	if (!student.is_open()) {
		cout << "Can't open file";
		system("pause");
		return 0;
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
			getline(student, DS[i].Social_Id);
			i++;
		}
		student.close();
	}
	for (int i = 0; i < sl; i++) {
		if (DS[i].Id == student_id) {
			for (int j = i; j < sl - 1; j++) {
				DS[j] = DS[j + 1];
			}
			sl--;
			break;
		}
	}
	ofstream f_course;
	f_course.open(path);
	if (f_course.is_open()) {
		f_course << "No, Student ID, First name, Last name, Gender, Day of birth, Social ID" << "\n";
		for (int i = 0; i < sl - 1; i++) {
			f_course << i + 1 << "," << DS[i].Id << "," << DS[i].Firstname << "," << DS[i].Lastname << "," << DS[i].Gender << "," << DS[i].DoB << "," << DS[i].Social_Id << "\n";
		}
		f_course << sl << "," << DS[sl - 1].Id << "," << DS[sl - 1].Firstname << "," << DS[sl - 1].Lastname << "," << DS[sl - 1].Gender << "," << DS[sl - 1].DoB << "," << DS[sl - 1].Social_Id;
		f_course.close();
		return 1;
	}
	else {
		notify_box("Can not open file!");
		return 0;
	}

}
void view_list_of_student_in_course() {
	system("cls");
	gotoxy(35, 5);
	cout << "Course ID:";
	gotoxy(35, 6);
	cout << "Class name:";
	gotoxy(45, 5);
	string course_id;
	getline(cin, course_id);
	gotoxy(46, 6);
	string class_name;
	getline(cin, class_name);
	transform(course_id.begin(), course_id.end(), course_id.begin(), ::toupper);
	transform(class_name.begin(), class_name.end(), class_name.begin(), ::toupper);
	string path_course = semester_path + "staff/" + course_id + "-" + class_name + ".csv";
	int sl = count(path_course);
	Student* DS_hocsinh = new Student[sl];
	ifstream student;
	student.open(path_course);
	if (!student.is_open()) {
		cout << "Can't open file";
		system("pause");
		return;
	}
	else {
		int i = 0;
		string temp;
		getline(student, temp);
		while (i < sl) {
			getline(student, DS_hocsinh[i].No, ',');
			getline(student, DS_hocsinh[i].Id, ',');
			getline(student, DS_hocsinh[i].Firstname, ',');
			getline(student, DS_hocsinh[i].Lastname, ',');
			getline(student, DS_hocsinh[i].Gender, ',');
			getline(student, DS_hocsinh[i].DoB, ',');
			getline(student, DS_hocsinh[i].Social_Id);
			i++;
		}
		student.close();
	}
	system("cls");
	cout << left << setw(3) << "No" << setw(11) << "Student ID" << setw(17) << "First name" << setw(10) << "Last name" << setw(7) << "Gender" << setw(9) << "DoB" << setw(10) << "Social ID" << "\n";
	for (int i = 0; i < sl; i++) {
		cout << left << setw(3) << i + 1 << setw(11) << DS_hocsinh->Id << setw(17) << DS_hocsinh->Firstname << setw(10) << DS_hocsinh->Lastname << setw(7) << DS_hocsinh->Gender << setw(9) << DS_hocsinh->DoB << setw(10) << DS_hocsinh->Social_Id << "\n";
	}
	system("pause");

}
bool export_list_of_student_in_course() {
	system("cls");
	gotoxy(35, 5);
	cout << "Course ID:";
	gotoxy(35, 6);
	cout << "Class name:";
	gotoxy(45, 5);
	string course_id;
	getline(cin, course_id);
	gotoxy(46, 6);
	string class_name;
	getline(cin, class_name);
	transform(course_id.begin(), course_id.end(), course_id.begin(), ::toupper);
	transform(class_name.begin(), class_name.end(), class_name.begin(), ::toupper);
	string path_course = semester_path + "staff/" + course_id + "-" + class_name + ".csv";
	ifstream student;
	student.open(path_course);
	if (!student.is_open()) {
		cout << "Can't open file";
		system("pause");
		return 0;
	}
	else {
		string source_file = path_course;
		/*if (dirExists(schoolyear_path) || currentdate.Month != month_begin_a_schoolyear)
		{
			notify_box("Can't create new Class in this time");
			return 0;
		}*/
		string destination_file = "./Data/Export/";
		destination_file = destination_file + course_id + "-" + class_name + ".csv";
		/*Xu li sao chep du lieu */
		ifstream sfile;
		sfile.open(source_file, ios::binary | ios::in);
		ofstream dfile;
		dfile.open(destination_file, ios::binary | ios::out);
		if (sfile.is_open() && dfile.is_open()) {
			char c;
			while (sfile.get(c) && sfile.good()) {
				dfile.put(c);/*Chep tung byte*/
			}
			sfile.close();
			dfile.close();
			notify_box(course_id + "-" + class_name + " is created");
		}
		else {
			notify_box("Can't open file");
			return 0;
		}
		return 1;
	}
}

void save_scoreboard_student(Student student, Course course) {
	fstream student_scoreboard;
	student_scoreboard.open(semester_path + "student/" + student.Id + "-scoreboard.csv");
	if (student_scoreboard.is_open()) {
			int i = 0;
			int sl = count(semester_path + "student/" + student.Id + "-scoreboard.csv");
			if (sl > 0) {
				Course* ds = new Course[sl];
				string temp;
				bool flag = false;
				getline(student_scoreboard, temp);
				while (i < sl) {
					string no;
					getline(student_scoreboard, no, ',');
					getline(student_scoreboard, ds[i].course_id, ',');
					getline(student_scoreboard, ds[i].class_name, ',');
					string MidtermMark;
					getline(student_scoreboard, MidtermMark, ',');
					ds[i].MidtermMark = stof(MidtermMark);
					string FinalMark;
					getline(student_scoreboard, FinalMark, ',');
					ds[i].FinalMark = stof(FinalMark);
					string OtherMark;
					getline(student_scoreboard, OtherMark, ',');
					ds[i].OtherMark = stof(OtherMark);
					string TotalMark;
					getline(student_scoreboard, TotalMark);
					ds[i].TotalMark = stof(TotalMark);
					i++;
				}
				for (int i = 0; i < sl; i++) {
					if (course.course_id == ds[i].course_id)
					{
						ds[i] = course;
						flag = true;
						break;
					}
				}
				if (flag) {
					student_scoreboard.close();
					ofstream new_scoreboard;
					new_scoreboard.open(semester_path + "student/" + student.Id + "-scoreboard.csv");
					if (new_scoreboard.is_open()) {
						new_scoreboard << temp << endl;
						for (int i = 0; i < sl - 1; i++) {
							new_scoreboard <<i+1 <<","<< ds[i].course_id << "," << ds[i].class_name << "," << ds[i].MidtermMark << "," << ds[i].FinalMark << "," << ds[i].OtherMark << "," << ds[i].TotalMark << "\n";
						}
						sl = (sl == 1) ? 1 : sl - 1;
					    new_scoreboard << sl << "," << ds[sl-1].course_id << "," << ds[sl-1].class_name << "," << ds[sl-1].MidtermMark << "," << ds[sl-1].FinalMark << "," << ds[sl-1].OtherMark << "," << ds[sl-1].TotalMark;
						new_scoreboard.close();
					}
					else {
						notify_box("Can't open file!");
						return;
					}
					
				}
				else {
					student_scoreboard.seekp(0, ios::end);
					student_scoreboard << i + 1 << "," << course.course_id << "," << course.class_name << "," << course.MidtermMark << "," << course.FinalMark<< "," <<course.OtherMark << "," << course.TotalMark;
					student_scoreboard.close();
					return;
				}
			}
			else {
				string temp;
				getline(student_scoreboard, temp);
				student_scoreboard << 1 << "," << course.course_id << "," << course.class_name << "," << course.MidtermMark << "," << course.FinalMark << "," << course.OtherMark << "," << course.TotalMark;
				student_scoreboard.close();
				return;
			}
	}
	else {
		notify_box("Can't open file!");
		return;
	}
}
bool import_scoreboard_of_course() {
	system("cls");
	string link;
	Course course;
	gotoxy(35, 5);
	cout << "Linked to scoreboard of course:";
	getline(cin, link);
	gotoxy(35, 6);
	cout << "Course ID:";
	gotoxy(35, 7);
	cout << "Class:";
	gotoxy(45, 6);
	getline(cin, course.course_id);
	gotoxy(41, 7);
	getline(cin, course.class_name);
	transform(course.course_id.begin(), course.course_id.end(), course.course_id.begin(), ::toupper);
	transform(course.class_name.begin(), course.class_name.end(), course.class_name.begin(), ::toupper);
	string source_file = link;
	string destination_file = semester_path + "staff/" + course.course_id + "-" + course.class_name + "-scoreboard.csv";
	/*Xu li sao chep du lieu */
	ifstream sfile;
	sfile.open(source_file, ios::binary | ios::in);
	ofstream dfile;
	dfile.open(destination_file, ios::binary | ios::out);
	if (sfile.is_open() && dfile.is_open()) {
		char c;
		while (sfile.get(c) && sfile.good()) {
			dfile.put(c);/*Chep tung byte*/
		}
		sfile.close();
		dfile.close();
		notify_box(course.course_id + "-" + course.class_name + "-scoreboard is created");
	}
	else {
		notify_box("Can't open file");
		return 0;
	}
	ifstream course_scoreboard;
	course_scoreboard.open(link);
	if (course_scoreboard.is_open()) {
		string temp;
		getline(course_scoreboard, temp);
		Student student;
		int sl = count(link);
		int i = 0;
		while (i < sl) {
			string No;
			getline(course_scoreboard, No, ',');
			getline(course_scoreboard, student.Id, ',');
			string full_name;
			getline(course_scoreboard, full_name, ',');
			string MidtermMark;
			getline(course_scoreboard, MidtermMark, ',');
			course.MidtermMark = stof(MidtermMark);
			string FinalMark;
			getline(course_scoreboard, FinalMark, ',');
			course.FinalMark = stof(FinalMark);
			string OtherMark;
			getline(course_scoreboard, OtherMark, ',');
			course.OtherMark = stof(OtherMark);
			string TotalMark;
			getline(course_scoreboard, TotalMark);
			course.TotalMark = stof(TotalMark);
			save_scoreboard_student(student, course);
			i++;
		}
		course_scoreboard.close();
	}
	else {
		notify_box("Can't open file!");
		return 0;
	}
	return 1;
}
void view_scoreboard_of_course() {
	system("cls");
	gotoxy(35, 5);
	cout << "Course ID:";
	gotoxy(35, 6);
	cout << "Class name:";
	gotoxy(45, 5);
	string course_id;
	getline(cin, course_id);
	gotoxy(46, 6);
	string class_name;
	getline(cin, class_name);
	transform(course_id.begin(), course_id.end(), course_id.begin(), ::toupper);
	transform(class_name.begin(), class_name.end(), class_name.begin(), ::toupper);
	string path_course = semester_path + "staff/" + course_id + "-" + class_name + "-scoreboard.csv";
	int sl = count(path_course);
	ifstream course_scoreboard;
	course_scoreboard.open(path_course);
	if (!course_scoreboard.is_open()) {
		cout << "Can't open file";
		system("pause");
		return;
	}
	else {
		int i = 0;
		string temp;
		getline(course_scoreboard, temp);
		system("cls");
		cout << left << setw(3) << "No" << setw(11) << "Student ID" << setw(24) << "Full name" << setw(13) << "Midterm Mark" << setw(11) << "Final Mark" << setw(12) << "Other Mark" << setw(11) << "Final Mark" << "\n";
		while (i < sl) {
			string No;
			getline(course_scoreboard, No, ',');
			string student_id;
			getline(course_scoreboard, student_id, ',');
			string full_name;
			getline(course_scoreboard, full_name, ',');
			string MidtermMark;
			getline(course_scoreboard, MidtermMark, ',');
			string FinalMark;
			getline(course_scoreboard, FinalMark, ',');
			string OtherMark;
			getline(course_scoreboard, OtherMark, ',');
			string TotalMark;
			getline(course_scoreboard, TotalMark);
			cout << left << setw(3) << No << setw(11) << student_id << setw(24) << full_name << setw(13) << MidtermMark << setw(11) << FinalMark << setw(12) << OtherMark << setw(11) << TotalMark << "\n";
			i++;
		}
		course_scoreboard.close();
		system("pause");
	}

}
bool update_student_result() {
	system("cls");
	gotoxy(35, 5);
	cout << "UPDATE STUDENT RESULT";
	gotoxy(35, 6);
	cout << "Student ID:";
	gotoxy(35, 7);
	cout << "Course ID:";
	gotoxy(35, 8);
	cout << "Class:";
	gotoxy(35, 9);
	cout << "Midterm Mark:";
	gotoxy(35, 10);
	cout << "Final Mark:";
	gotoxy(35, 11);
	cout << "Other Mark:";
	gotoxy(35, 12);
	cout << "Total Mark:";
	Course course;
	string student_id;
	string MidtermMark;
	string FinalMark;
	string OtherMark;
	string TotalMark;
	gotoxy(46, 6);
	getline(cin, student_id);
	gotoxy(45, 7);
	getline(cin, course.course_id);
	gotoxy(41, 8);
	getline(cin, course.class_name);
	gotoxy(48, 9);
	getline(cin, MidtermMark);
	gotoxy(46, 10);
	getline(cin, FinalMark);
	gotoxy(46, 11);
	getline(cin, OtherMark);
	gotoxy(46, 12);
	getline(cin, TotalMark);
	course.MidtermMark = stof(MidtermMark);
	course.FinalMark = stof(FinalMark);
	course.OtherMark = stof(OtherMark);
	course.TotalMark = stof(TotalMark);
	transform(course.course_id.begin(), course.course_id.end(), course.course_id.begin(), ::toupper);
	transform(course.class_name.begin(), course.class_name.end(), course.class_name.begin(), ::toupper);
	string path_course = semester_path + "staff/" + course.course_id + "-" + course.class_name + "-scoreboard.csv";
	int sl = count(path_course);
	Course* DS_Course = new Course[sl];
	Student* DS_Student = new Student[sl];
    ifstream course_scoreboard;
	course_scoreboard.open(path_course);
	if (!course_scoreboard.is_open()) {
		cout << "Can't open file";
		system("pause");
		return 0;
	}
	else {
		int i = 0;
		bool flag = false;
		string temp;
		getline(course_scoreboard, temp);
		while (i < sl) {
			getline(course_scoreboard, DS_Student[i].No, ',');
			getline(course_scoreboard, DS_Student[i].Id, ',');
			getline(course_scoreboard, DS_Student[i].Firstname, ',');
			string MidtermMark;
			getline(course_scoreboard, MidtermMark, ',');
			string FinalMark;
			getline(course_scoreboard, FinalMark, ',');
			string OtherMark;
			getline(course_scoreboard, OtherMark, ',');
			string TotalMark;
			getline(course_scoreboard, TotalMark);
			DS_Course[i].MidtermMark = stof(MidtermMark);
			DS_Course[i].FinalMark = stof(FinalMark);
			DS_Course[i].OtherMark = stof(OtherMark);
			DS_Course[i].TotalMark = stof(TotalMark);
			i++;
		}
		course_scoreboard.close();
		for (int i = 0; i < sl; i++) {
			if (DS_Student[i].Id == student_id) {
				DS_Course[i] = course;
				save_scoreboard_student(DS_Student[i], DS_Course[i]);
				flag = true;
			}
		}
		if(flag){
			ofstream course_scoreboard;
			course_scoreboard.open(path_course);
			if (course_scoreboard.is_open()) {
				course_scoreboard << "No,Student ID,Full name,Midterm Mark,Final Mark,Other Mark,Final Mark" << "\n";
				for (int i = 0; i < sl - 1; i++) {
					course_scoreboard << DS_Student[i].No << "," << DS_Student[i].Id << "," << DS_Student[i].Firstname << "," << DS_Course[i].MidtermMark << "," << DS_Course[i].FinalMark << "," << DS_Course[i].OtherMark << "," << DS_Course[i].TotalMark << "\n";
				}
				course_scoreboard << DS_Student[sl - 1].No << "," << DS_Student[sl - 1].Id << "," << DS_Student[sl - 1].Firstname << "," << DS_Course[sl - 1].MidtermMark << "," << DS_Course[sl - 1].FinalMark << "," << DS_Course[sl - 1].OtherMark << "," << DS_Course[sl - 1].TotalMark << "\n";
			}
			course_scoreboard.close();
			
			return 1;
		}
		else {
			notify_box("Student does not exits!");
			return 0;
		}
	}
}
void Staff_lg() {
	ifstream staff;
	string path = "./Data/Users/Staff.csv";
	staff.open(path);
	if (!staff.is_open()) {
		cout << "Can't open file";
		system("pause");
		return;
	}
	int sl = count("./Data/Users/Staff.csv");
	staff.close();
	staff.open(path);
	Staff* DS = new Staff[sl];
	int i = 0;
	string temp;
	getline(staff, temp);
	while (!staff.eof()) {
		getline(staff, DS[i].No, ',');
		getline(staff, DS[i].Id, ',');
		getline(staff, DS[i].Firstname, ',');
		getline(staff, DS[i].Lastname, ',');
		getline(staff, DS[i].Facultry, ',');
		getline(staff, DS[i].Social_Id, ',');
		getline(staff, DS[i].password);
		i++;
	}
	string username;
	string pass;
	cout << "Login as Staff";
	bool flag = false;
	Student* std_user = NULL;
	Staff* staff_user = new Staff;
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
				staff_user = &DS[i];
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
	staff.close();
	if (flag) {
		char menu_staff[19][40] = { "1.Your profile", "2.Change the password","3.Create new School Year","4.Create new semester", "5.Quick input student to class","6.Quick input student to a course","7.Add a student to a class", "8.Add a course to a semester","9.View the list of courses ","10.Update course information","11.Remove student form a course","12.View list of classes","13.View list of student in class","14.View list of student in course","15.Export list of student in course","16.Import course scoreboard","17.View scoreboard of a course","18.Update a student result","19.Log out" };
		do {
			system("cls");
			int choice = menu(menu_staff, 19, 40);
			if (choice == 0)
			{
				system("cls");
				gotoxy(35, 4);
				cout << "ID: " << (*staff_user).Id;
				gotoxy(35, 5);
				cout << "First name: " << (*staff_user).Firstname;
				gotoxy(35, 6);
				cout << "Last name: " << (*staff_user).Lastname;
				gotoxy(35, 7);
				cout << "Social ID: " << (*staff_user).Social_Id << endl;
				system("pause");

			}
			else if (choice == 1)
			{
				system("cls");
				changepass(staff_user, std_user);

			}
			else if (choice == 2) {
				if (create_School_Year()) notify_box("New School Year is created!");

			}
			else if (choice == 3) {
				if (createSemester()) notify_box("New Semester is created!");
			}
			else if (choice == 4)
			{
				if (Quick_Input_Student_to_class()) notify_box("Input Class successful!");
			}
			else if (choice == 5) {
				if (Quick_Input_student_to_course()) notify_box("Input Courses successful!");
			}
			else if (choice == 6) {
				if (add_Student_to_Class()) notify_box("Input Student successful!");
			}
			else if (choice == 7) {
				if (add_Course_to_Semester()) notify_box("Input Course successful!");
			}
			else if (choice == 8) {
				view_list_courses();
			}
			else if (choice == 9) {
				if (update_course_information()) notify_box("Update successfull!");
			}
			else if (choice == 10) {
				if (Remove_student_frome_course()) notify_box("Remove successful!");
			}
			else if (choice == 11) {
				view_list_of_classes();
			}
			else if (choice == 12) {
				view_list_of_student_in_class();
			}
			else if (choice == 13) {
				view_list_of_student_in_course();
			}
			else if (choice == 14) {
				if (export_list_of_student_in_course()) notify_box("Export successfull!");
			}
			else if (choice == 15) {
				if (import_scoreboard_of_course()) notify_box("Import successfull!");
			}
			else if (choice == 16) {
				view_scoreboard_of_course();
			}
			else if (choice == 17)
			{
				if(update_student_result()) notify_box("Update successfull!");
			}
			else if (choice == 18) {
				break;
			}
		} while (1);
		system("pause");
	}
}