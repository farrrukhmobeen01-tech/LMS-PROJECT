// Student.cpp
#include "Student.h"
#include "Portal.h" // Needed to access Portal methods
#include "Subject.h"

Student::Student() { rollNo = ""; fullName = ""; subCount = 0; }

void Student::setup(const string& id, const string& n, const string& u, const string& p) {
    rollNo = id; fullName = n;
    setAuth(u, p);
    subCount = 0;
}

void Student::addSubLocal(const string& code) {
    for (int i = 0; i < subCount; i++) if (mySubs[i] == code) return;
    if (subCount < 30) mySubs[subCount++] = code;
}

void Student::removeSubLocal(const string& code) {
    int pos = -1;
    for (int i = 0; i < subCount; i++) if (mySubs[i] == code) { pos = i; break; }
    if (pos == -1) return;
    for (int i = pos; i < subCount - 1; i++) mySubs[i] = mySubs[i + 1];
    mySubs[subCount - 1] = ""; subCount--;
}

string Student::getType() const { return "student"; }

void Student::save(ofstream& out) const {
    saveAuth(out);
    out << rollNo << "\n" << fullName << "\n";
}

void Student::load(ifstream& in) {
    loadAuth(in);
    if (!getline(in, rollNo)) return;
    if (!getline(in, fullName)) return;
}

void Student::loadSubList(ifstream& in) {
    subCount = getInt(in);
    for (int i = 0; i < subCount && i < 30; i++) {
        if (!getline(in, mySubs[i])) return;
    }
}

// Menu Implementation
void Student::showMenu(Portal& sys, int idx) {
    while (true) {
        cout << "\n********************************************************\n";
        cout << "           Student Menu (" << fullName << ")\n";
        cout << "********************************************************\n";
        cout << "   1. My Subjects\n   2. Attendance\n   3. Lectures/Notes\n   4. Assignments/Tasks\n   5. Scores\n   6. Review/Feedback\n   7. Profile\n   8. Logout\n   >> Choose: ";
        int ch; if (!(cin >> ch)) { cin.clear(); cin.ignore(10000, '\n'); continue; }
        cin.ignore(100, '\n');
        if (ch == 8) break;
        if (ch == 1) {
            if (subCount == 0) cout << "   No subjects.\n";
            else {
                cout << "   [ My Subjects ]\n";
                for (int i = 0; i < subCount; i++) cout << "    - " << mySubs[i] << "\n";
            }
        }
        else if (ch == 2) {
            if (subCount == 0) cout << "   No subjects.\n";
            else {
                cout << "   [ Attendance Record ]\n";
                for (int i = 0; i < subCount; i++) {
                    int ci = sys.findSubject(mySubs[i]);
                    if (ci != -1) sys.subjects[ci].showPresence(rollNo);
                    else cout << "    " << mySubs[i] << " -> Error\n";
                }
            }
        }
        else if (ch == 3) {
            cout << "   Enter Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            sys.subjects[ci].showNotes();
        }
        else if (ch == 4) {
            cout << "   Enter Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            sys.subjects[ci].showTasks();
        }
        else if (ch == 5) {
            cout << "   [ Scores ]\n";
            for (int i = 0; i < subCount; i++) {
                int ci = sys.findSubject(mySubs[i]);
                if (ci == -1) { cout << "    " << mySubs[i] << " -> Error\n"; continue; }
                string g = sys.subjects[ci].getScore(rollNo);
                cout << "    " << mySubs[i] << " : " << (g.empty() ? "N/A" : g) << "\n";
            }
        }
        else if (ch == 6) {
            cout << "   Enter Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            cout << "   Enter Feedback: ";
            string fb; getline(cin, fb);
            string msg = fullName + " (" + rollNo + "): " + fb;
            sys.subjects[ci].addReview(msg);
            cout << "   [ Submitted ]\n";
        }
        else if (ch == 7) {
            cout << "\n   [ Profile ]\n    Name: " << fullName << "\n    Roll: " << rollNo << "\n    User: " << getID() << "\n   [ Subjects ]\n";
            for (int i = 0; i < subCount; i++) cout << "     - " << mySubs[i] << "\n";
        }
        else cout << "   Invalid choice.\n";
    }
}