// Faculty.cpp
#include "Faculty.h"
#include "Portal.h"
#include "Subject.h"

Faculty::Faculty() { empID = ""; fullName = ""; allocCount = 0; }

void Faculty::setup(const string& id, const string& n, const string& u, const string& p) {
    empID = id; fullName = n;
    setAuth(u, p);
    allocCount = 0;
}

void Faculty::assignSubLocal(const string& code) {
    for (int i = 0; i < allocCount; i++) if (allocs[i] == code) return;
    if (allocCount < 30) allocs[allocCount++] = code;
}

string Faculty::getType() const { return "faculty"; }

void Faculty::save(ofstream& out) const {
    saveAuth(out);
    out << empID << "\n" << fullName << "\n";
}

void Faculty::load(ifstream& in) {
    loadAuth(in);
    if (!getline(in, empID)) return;
    if (!getline(in, fullName)) return;
}

void Faculty::loadAllocList(ifstream& in) {
    allocCount = getInt(in);
    for (int i = 0; i < allocCount && i < 30; i++) {
        if (!getline(in, allocs[i])) return;
    }
}

// Menu Implementation
void Faculty::showMenu(Portal& sys, int idx) {
    while (true) {
        cout << "\n********************************************************\n";
        cout << "           Faculty Menu (" << fullName << ")\n";
        cout << "********************************************************\n";
        cout << "   1. My Courses\n   2. Mark Attendance\n   3. Upload Note\n   4. Upload Task\n   5. Upload Score\n   6. View Students\n   7. View Feedback\n   8. Logout\n   >> Choose: ";
        int ch; if (!(cin >> ch)) { cin.clear(); cin.ignore(10000, '\n'); continue; }
        cin.ignore(100, '\n');
        if (ch == 8) break;
        if (ch == 1) {
            if (allocCount == 0) cout << "   No subjects allocated.\n";
            else {
                cout << "   [ Allocated Subjects ]\n";
                for (int i = 0; i < allocCount; i++) cout << "    - " << allocs[i] << "\n";
            }
        }
        else if (ch == 2) {
            cout << "   Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            if (sys.subjects[ci].facID != empID) { cout << "   Not yours.\n"; continue; }
            sys.subjects[ci].takeAttendance();
        }
        else if (ch == 3) {
            cout << "   Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            if (sys.subjects[ci].facID != empID) { cout << "   Not yours.\n"; continue; }
            cout << "   Note Text: ";
            string txt; getline(cin, txt);
            sys.subjects[ci].addNote(txt);
            cout << "   [ Uploaded ]\n";
        }
        else if (ch == 4) {
            cout << "   Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            if (sys.subjects[ci].facID != empID) { cout << "   Not yours.\n"; continue; }
            cout << "   Task Text: ";
            string txt; getline(cin, txt);
            sys.subjects[ci].addTask(txt);
            cout << "   [ Uploaded ]\n";
        }
        else if (ch == 5) {
            cout << "   Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            if (sys.subjects[ci].facID != empID) { cout << "   Not yours.\n"; continue; }
            sys.subjects[ci].printDetails();
            cout << "   Student ID: ";
            string sid; getline(cin, sid);
            cout << "   Score: ";
            string g; getline(cin, g);
            sys.subjects[ci].setScore(sid, g);
            cout << "   [ Saved ]\n";
        }
        else if (ch == 6) {
            cout << "   Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            if (sys.subjects[ci].facID != empID) { cout << "   Not yours.\n"; continue; }
            sys.subjects[ci].printDetails();
        }
        else if (ch == 7) {
            cout << "   Subject Code: ";
            string code; getline(cin, code);
            int ci = sys.findSubject(code);
            if (ci == -1) { cout << "   Invalid.\n"; continue; }
            if (sys.subjects[ci].facID != empID) { cout << "   Not yours.\n"; continue; }
            sys.subjects[ci].showReviews();
        }
        else cout << "   Invalid.\n";
    }
}