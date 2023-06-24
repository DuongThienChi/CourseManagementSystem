
#include "staff.h"
void add_to_User(Student a) {
    fstream user;
    user.open("./Data/Users/Student.csv");
    if (!user.is_open()) {
        notify_box("Can't open file");
        system("pause");
        return ;
    }
    else {
        int sl = count("./Data/Users/Student.csv");
        Student * DS = new Student[sl + 1];
        load_Student(DS, "./Data/Users/Student.csv");
        DS[sl] = a;
        user << "No, Student ID, First name, Last name, Gender, Day of birth, Social ID, Password" << "\n";
        for (int i = 0; i < sl + 1; i++) {
            user << i + 1 << "," << DS[i].Id << "," << DS[i].Firstname << "," << DS[i].Lastname << "," << DS[i].Gender << "," << DS[i].DoB << "," << DS[i].Social_Id << ","<< DS[i].password<< "\n";
        }
        user.close();
    }

}
bool Quick_Input_Classes() {
    system("cls");
    gotoxy(35, 7);
    cout << "Linked to file classes: ";
    string link;
    getline(cin, link);
    gotoxy(35, 8);
    cout << "Name of class: ";
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
void sort_DS_Student(Student*&DS, int sl) {
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
                string No;
                string Id;
                string Firstname;
                string Lastname;
                string Gender;
                string DoB;
                string Social_Id;
                getline(class_file, temp);
                while (!class_file.eof()) {
                    getline(class_file, No, ',');
                    DS[i].No = No;
                    getline(class_file, Id, ',');
                    DS[i].Id = Id;
                    getline(class_file, Firstname, ',');
                    DS[i].Firstname = Firstname;
                    getline(class_file, Lastname, ',');
                    DS[i].Lastname = Lastname;
                    getline(class_file, Gender, ',');
                    DS[i].Gender = Gender;
                    getline(class_file, DoB, ',');
                    DS[i].DoB = DoB;
                    getline(class_file, Social_Id);
                    DS[i].Social_Id = Social_Id;
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
                for (int i = 0; i < sl + 1; i++) {
                    class_file << i + 1 << "," << DS[i].Id << "," << DS[i].Firstname << "," << DS[i].Lastname << "," << DS[i].Gender << "," << DS[i].DoB << "," << DS[i].Social_Id << "\n";
                }
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
        fs::create_directories(semester_path);
        ofstream f_course(semester_path + "courses.csv");
        if (f_course.is_open()) {
            f_course << "ID,Course name,Class name,Teacher name,Number of credits,Maximum number of students,Day of week,Session" << endl;
            f_course.close();
            return 1;
        }
        else return 0;
   // }
}
bool add_Course_to_Semester() {
   /* if (currentdate.Month != month_begin_semester[0] || currentdate.Month != month_begin_semester[1] || currentdate.Month != month_begin_semester[2]) {
        string mess = { "Can not add a new course in this time!" };
        notify_box(mess);
        return 0;
    }
    else {*/
        fstream f_course;
        f_course.open(semester_path + +"courses.csv");
        if (f_course.is_open()) {
            Course new_course;
            string session[4] = { "S1-7:30","S2-9:30","S3-13:30","S4-15:30" };
            system("cls");
            gotoxy(35, 5);
            cout << "ID:";
            gotoxy(35, 6);
            cout << "Course name :";
            gotoxy(35, 7);
            cout << "Teacher name:";
            gotoxy(35, 8);
            cout << "Class name:";
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
            gotoxy(49, 7);
            getline(cin, new_course.teacher_name);
            gotoxy(47, 8);
            getline(cin, new_course.class_name);
            gotoxy(43, 9);
            cin >> new_course.credits;
            cin.ignore();
            gotoxy(47, 10);
            getline(cin, new_course.wDay);
            int temp;
            gotoxy(43, 11);
            cin >> temp;
            new_course.session = session[temp - 1];
            cin.ignore();
            f_course.seekp(0, ios::end);
            f_course << new_course.course_id << "," << new_course.course_name << "," << new_course.class_name << "," << new_course.teacher_name << "," << new_course.credits << "," << new_course.max_students << "," << new_course.wDay << "," << new_course.session << "\n";
            f_course.close();
        }
        else {
            notify_box("Can not open file!");
            return 0;
        }
   // }
}
void Staff_lg() {
    ifstream staff;
    string path = "./Data/Users/Staff.csv";
    staff.open(path);
    if (!staff.is_open()) {
        cout << "Can't open file";
        system("pause");
        return ;
    }
    int sl = count("./Data/Users/Staff.csv");
    staff.close();
    staff.open(path);
    Staff* DS = new Staff[sl];
    int i = 0;
    string temp;
    string No;
    string Id;
    string Firstname;
    string Lastname;
    string Facultry;
    string Social_ID;
    string password;
    getline(staff, temp);
    while (!staff.eof()) {
        getline(staff, No, ',');
        DS[i].No = No;
        getline(staff, Id, ',');
        DS[i].Id = Id;
        getline(staff, Firstname, ',');
        DS[i].Firstname = Firstname;
        getline(staff, Lastname, ',');
        DS[i].Lastname = Lastname;
        getline(staff, Facultry, ',');
        DS[i].Facultry = Facultry;
        getline(staff, Social_ID, ',');
        DS[i].Social_Id = Social_ID;
        getline(staff, password);
        DS[i].password = password;

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
            gotoxy(35, 8);
            cout << "Wrong user name or password" << endl;
            thoatctrinh();
            cin.ignore();
        }
        else break;
        system("pause");
    } while (1);
    staff.close();
    if (flag) {

        char menu_staff[8][40] = { "1.Your profile", "2.Change the password","3.Create new School Year","4.Create new semester", "5.Quick Input Class","6.Add a student to a class", "7.Add a course to a semester","8.Log out"};
        do {
            system("cls");
            int choice = menu(menu_staff, 8, 40);
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
                if(create_School_Year()) notify_box("New School Year is created!");
                
            }
            else if (choice == 3) {
                if (createSemester()) notify_box("New Semester is created!");
            }
            else if (choice == 4)
            {   
                if(Quick_Input_Classes()) notify_box("Input Class successful!");
            }
            else if (choice == 5) {
                if (add_Student_to_Class()) notify_box("Input Student successful!");
            }
            else if (choice == 6) {
                if (add_Course_to_Semester()) notify_box("Input Course successful!");
            }
            else if (choice == 7) {
                break;
            }
        } while (1);
        system("pause");
    }
}