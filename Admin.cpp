// Admin.cpp
#include "Admin.h"
#include "Portal.h"
#include "Subject.h"

Admin::Admin() { fullName = "System Admin"; }

void Admin::setup(const string& n, const string& u, const string& p) {
    fullName = n; setAuth(u, p);
}

string Admin::getType() const { return "admin"; }

void Admin::save(ofstream& out) const {
    saveAuth(out);
    out << fullName << "\n";
}

void Admin::load(ifstream& in) {
    loadAuth(in);
    if (!getline(in, fullName)) return;
}

// Menu Implementation
void Admin::showMenu(Portal& sys, int idx) {
    while (1) {
        cout << "\n********************************************************\n";
        cout << "           Admin Menu (" << fullName << ")\n";
        cout << "********************************************************\n";
        cout << "   1. Students List\n   2. Faculty List\n   3. Subjects List\n   4. Add Student\n   5. Remove Student\n   6. Add Faculty\n   7. Remove Faculty\n   8. Add Subject\n   9. Remove Subject\n   10. Assign Subject\n   11. Enroll Student\n   12. Attendance Logs\n   13. Score Logs\n   14. Logout\n   >> Choose: ";
        int ch;
        if (!(cin >> ch)) { cin.clear(); cin.ignore(10000, '\n'); continue; }
        cin.ignore(100, '\n');
        if (ch == 14) break;

        if (ch == 1) sys.listStudents();
        else if (ch == 2) sys.listFaculty();
        else if (ch == 3) sys.listSubjects();
        else if (ch == 4) {
            cout << "   Student ID: "; string id; getline(cin, id);
            cout << "   Name: "; string n; getline(cin, n);
            cout << "   Username: "; string u_n; getline(cin, u_n);
            cout << "   Password: "; string pass; getline(cin, pass);
            if (sys.addStudent(id, n, u_n, pass)) cout << "   [ Added ]\n";
            else cout << "   [ Failed ]\n";
        }
        else if (ch == 5) {
            cout << "   ID to remove: "; string id; getline(cin, id);
            if (sys.removeStudent(id)) cout << "   [ Removed ]\n";
            else cout << "   [ Not found ]\n";
        }
        else if (ch == 6) {
            cout << "   Faculty ID: "; string id; getline(cin, id);
            cout << "   Name: "; string n; getline(cin, n);
            cout << "   Username: "; string u_n; getline(cin, u_n);
            cout << "   Password: "; string pass; getline(cin, pass);
            if (sys.addFaculty(id, n, u_n, pass)) cout << "   [ Added ]\n";
            else cout << "   [ Failed ]\n";
        }
        else if (ch == 7) {
            cout << "   ID to remove: "; string id; getline(cin, id);
            if (sys.removeFaculty(id)) cout << "   [ Removed ]\n";
            else cout << "   [ Not found ]\n";
        }
        else if (ch == 8) {
            cout << "   Subject Code: "; string code; getline(cin, code);
            cout << "   Name: "; string c_n; getline(cin, c_n);
            if (sys.addSubject(code, c_n)) cout << "   [ Added ]\n";
            else cout << "   [ Failed ]\n";
        }
        else if (ch == 9) {
            cout << "   Code to remove: "; string code; getline(cin, code);
            if (sys.removeSubject(code)) cout << "   [ Subject removed ]\n";
            else cout << "   [ Not found ]\n";
        }
        else if (ch == 10) {
            cout << "   Subject Code: "; string code; getline(cin, code);
            cout << "   Faculty ID: "; string id; getline(cin, id);
            if (sys.assignSub(code, id)) cout << "   [ Assigned ]\n";
            else cout << "   [ Failed ]\n";
        }
        else if (ch == 11) {
            cout << "   Student ID: "; string id; getline(cin, id);
            cout << "   Subject Code: "; string c_code; getline(cin, c_code);
            if (sys.enrollStudent(id, c_code)) cout << "   [ Enrolled ]\n";
            else cout << "   [ Failed ]\n";
        }
        else if (ch == 12) {
            for (int i = 0; i < sys.subCount; i++) sys.subjects[i].printDetails();
        }
        else if (ch == 13) {
            for (int i = 0; i < sys.subCount; i++) sys.subjects[i].printDetails();
        }
        else cout << "   Invalid.\n";
    }
}