// main.cpp
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Portal.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Portal sys;
    sys.loadAll();

    while (true) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << string(80, '*') << endl;
        cout << "\t\t\t   BAHRIA UNIVERSITY\n";
        cout << "\t\t\t    ISLAMABAD CAMPUS\n\n";
        cout << "\t\t     MANAGEMENT SYSTEM (PORTAL)\n";
        cout << string(80, '*') << endl << endl;

        cout << "\t\t[1] . Admin Login\n";
        cout << "\t\t[2] . Faculty Login\n";
        cout << "\t\t[3] . Student Login\n";
        cout << "\t\t[4] . Exit\n\n";
        cout << string(80, '*') << endl;
        cout << "\t\t>> Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        if (choice == 4) {
            sys.saveAll();
            cout << "\t\tExiting...\n\n";
            break;
        }
        if (choice < 1 || choice > 4) continue;

        string uID, passKey;
        cout << "\n\t\tUser ID: ";
        getline(cin, uID);
        if (uID == "exit" || uID == "Exit") {
            sys.saveAll();
            break;
        }
        cout << "\t\tPassword: ";
        getline(cin, passKey);

        int idx = -1;
        string role;
        Person* user = nullptr;

        if (choice == 1) {
            if (sys.admin.verifyAuth(uID, passKey)) {
                user = &sys.admin;
                idx = 0;
                role = "Admin";
            }
        }
        else if (choice == 2) {
            idx = sys.findFacultyUser(uID);
            if (idx != -1 && sys.facList[idx].verifyAuth(uID, passKey)) {
                user = &sys.facList[idx];
                role = "Faculty";
            }
        }
        else if (choice == 3) {
            idx = sys.findStudentUser(uID);
            if (idx != -1 && sys.students[idx].verifyAuth(uID, passKey)) {
                user = &sys.students[idx];
                role = "Student";
            }
        }

        if (user != nullptr) {
            cout << "\n\n" << string(20, ' ') << "Login Success!\n";
            cout << string(18, ' ') << "Welcome, " << role << "!\n\n";
            cout << "\t\tPress Enter...";
            cin.get();
            user->showMenu(sys, idx);
        }
        else {
            cout << "\n\n" << string(15, ' ') << "Invalid Credentials!\n";
            cout << "\t\tPress Enter...";
            cin.get();
        }
    }
    return 0;
}