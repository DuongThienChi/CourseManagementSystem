


#include "staff.h"
const int  month_begin_a_schoolyear = 9;
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
        string schoolyear_path = "./Data/" + to_string(currentdate.Year) + "-" + to_string(currentdate.Year + 1);
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
bool add_Student_to_Class() {
    system("cls");
    string schoolyear_path = "./Data/" + to_string(currentdate.Year) + "-" + to_string(currentdate.Year + 1);
   /* if (currentdate.Month != month_begin_a_schoolyear)
    {
        notify_box("Can't add new Student in this time");
        return 0;
    }
    else*/ {
        Student new_std;
        string name_Class;
        gotoxy(35, 4);
        cout << "Class:";
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
        gotoxy(35, 11);
        cout << "Password:";
        gotoxy(43, 4);
        getline(cin, name_Class);
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
        gotoxy(45, 11);
        getline(cin, new_std.password);
        string class_path = schoolyear_path + "/classes/firstyear/" + name_Class + ".csv";
        ifstream class_file;
        class_file.open(class_path);
        if (class_file.is_open()) {
            int sl = count(class_file);  class_file.close();
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
                getline(class_file, Social_Id, ',');
                DS[i].Social_Id = Social_Id;
                i++;
            }
            class_file.close();
            DS[sl] = new_std;
            sort_DS_Student(DS, sl + 1);
            ofstream class_file;
            class_file.open(class_path);
            if (class_file.is_open()) {
                class_file << temp;
                for (int i = 0; i < sl + 1; i++) {
                    class_file << i + 1 << "," << DS[i].Id << "," << DS[i].Firstname << "," << DS[i].Lastname << "," << DS[i].Gender << "," << DS[i].DoB << "," << DS[i].Social_Id;
                }
                class_file.close();
            }
            else return 0;
            delete[] DS;
        }
        else return 0;
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
        string schoolyear_path = "./Data/" + to_string(currentdate.Year) + "-" + to_string(currentdate.Year + 1);
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
void Staff_lg() {
    ifstream staff;
    string path = "./Data/Users/Staff.csv";
    staff.open(path);
    if (!staff.is_open()) {
        cout << "Can't open file";
        system("pause");
        return ;
    }
    int sl = count(staff);
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

        char menu_staff[6][40] = { "1.Your profile", "2.Change the password","3.Create new School Year", "4.Quick Input Class","5.Add a student into Class", "6.Log out" };
        do {
            system("cls");
            int choice = menu(menu_staff, 6, 40);
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
            else if (choice == 3)
            {   
                if(Quick_Input_Classes()) notify_box("Input Class successful!");
            }
            else if (choice == 4) {
                if (add_Student_to_Class()) notify_box("Input Student successful!");
            }
            else if (choice == 5) {
                break;
            }
        } while (1);
        system("pause");
    }
}