#include "staff.h"

void create_School_Year() {
    const int  Allow_month = 9;
    if (currentdate.Month != 9) {
        string mess = { "Nam hoc moi chua bat dau!" };
        notify_box(mess);
    }
    else {
        string schoolyear_path = "./Data/" + to_string(currentdate.Year) + "-" + to_string(currentdate.Year + 1);
        string prevSchoolyear_path = "./Data/" + to_string(currentdate.Year - 1) + "-" + to_string(currentdate.Year);
        string classes_path = schoolyear_path + "/classes";
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
        }
        else {
            //   ofstream(schoolYearPath + "/semester.dat");
            fs::create_directories(classes_path + "/firstyear");
            fs::create_directories(classes_path + "/secondyear");
            fs::create_directories(classes_path + "/thirdyear");
            fs::create_directories(classes_path + "/finalyear");
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
            cout << "Sai tai khoan hoac mat khau vui long nhap lai" << endl;
            thoatctrinh();
            cin.ignore();
        }
        else break;
        system("pause");
    } while (1);
    staff.close();
    if (flag) {

        char menu_staff[5][40] = { "1.Your profile", "2.Change the password","3.Create new School Year", "4.View your scoreboard","5.Log out" };
        do {
            system("cls");
            int choice = menu(menu_staff, 5, 40);
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
                create_School_Year();
                string mssg = { "Da tao thanh cong nam hoc moi" };
                notify_box(mssg);
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