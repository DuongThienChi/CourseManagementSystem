
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

		char menu_student[5][40] = { "1.Your profile", "2.Change the password","3.View list of your courses", "4.View your scoreboard","5.Log out" };
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
				cout << 3;
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