// Portal.cpp
#include "Portal.h"

Portal::Portal() {
    stdCount = 0; facCount = 0; subCount = 0;
    admin.setup("System Admin", "admin", "000");
}

void Portal::seedData() {
    if (stdCount > 0 || facCount > 0 || subCount > 0) return;
    cout << "\n[System]: Fresh start detected. Adding default users.\n";
    addFaculty("saima", "Saima", "saima", "123");
    addFaculty("aleem", "Aleem", "aleem", "123");
    addStudent("farrukh", "Farrukh", "farrukh", "033");
}

bool Portal::removeSubject(const string& code) {
    int pos = findSubject(code);
    if (pos == -1) return false;

    for (int i = 0; i < stdCount; i++) {
        students[i].removeSubLocal(code);
    }

    for (int i = 0; i < facCount; i++) {
        if (facList[i].allocCount > 0) {
            int assign_pos = -1;
            for (int k = 0; k < facList[i].allocCount; k++) {
                if (facList[i].allocs[k] == code) { assign_pos = k; break; }
            }
            if (assign_pos != -1) {
                for (int k = assign_pos; k < facList[i].allocCount - 1; k++) {
                    facList[i].allocs[k] = facList[i].allocs[k + 1];
                }
                facList[i].allocs[facList[i].allocCount - 1] = "";
                facList[i].allocCount--;
            }
        }
    }

    for (int i = pos; i < subCount - 1; i++) {
        subjects[i] = subjects[i + 1];
    }
    subjects[subCount - 1] = Subject();
    subCount--;
    return true;
}

void Portal::saveAdmin() const {
    ofstream out("admin_data.txt");
    if (out.is_open()) {
        admin.save(out);
        out.close();
    }
}

void Portal::saveStudents() const {
    ofstream out("students_data.txt");
    if (out.is_open()) {
        out << stdCount << "\n";
        for (int i = 0; i < stdCount; i++) {
            students[i].save(out);
        }
        out.close();
    }
}

void Portal::saveFaculty() const {
    ofstream out("faculty_data.txt");
    if (out.is_open()) {
        out << facCount << "\n";
        for (int i = 0; i < facCount; i++) {
            facList[i].save(out);
        }
        out.close();
    }
}

void Portal::saveSubjects() const {
    ofstream out("subjects_data.txt");
    if (out.is_open()) {
        out << subCount << "\n";
        for (int i = 0; i < subCount; i++) {
            subjects[i].saveContent(out);
        }
        out.close();
    }
}

void Portal::saveRegs() const {
    ofstream out("registrations_data.txt");
    ofstream facOut("faculty_data.txt", ios::app);

    if (out.is_open() && facOut.is_open()) {
        for (int i = 0; i < subCount; i++) {
            subjects[i].saveRegs(out);
        }
        out << "STUDENT_REGS\n";
        for (int i = 0; i < stdCount; i++) {
            out << students[i].rollNo << "\n";
            out << students[i].subCount << "\n";
            for (int j = 0; j < students[i].subCount; j++) {
                out << students[i].mySubs[j] << "\n";
            }
        }
        facOut << "FACULTY_ALLOCS\n";
        for (int i = 0; i < facCount; i++) {
            facOut << facList[i].empID << "\n";
            facOut << facList[i].allocCount << "\n";
            for (int j = 0; j < facList[i].allocCount; j++) {
                facOut << facList[i].allocs[j] << "\n";
            }
        }
        out.close();
        facOut.close();
    }
}

void Portal::saveAttend() const {
    ofstream out("attendance_data.txt");
    if (out.is_open()) {
        out << subCount << "\n";
        for (int i = 0; i < subCount; i++) {
            subjects[i].saveAttend(out);
        }
        out.close();
    }
}

void Portal::saveScores() const {
    ofstream out("scores_data.txt");
    if (out.is_open()) {
        out << subCount << "\n";
        for (int i = 0; i < subCount; i++) {
            subjects[i].saveScores(out);
        }
        out.close();
    }
}

void Portal::saveAll() const {
    saveAdmin();
    saveStudents();
    saveFaculty();
    saveSubjects();
    saveRegs();
    saveAttend();
    saveScores();
    cout << "\n   [ Data saved successfully to disk! ]" << endl;;
}

void Portal::loadAdmin() {
    ifstream in("admin_data.txt");
    if (in.is_open()) {
        admin.load(in);
        in.close();
    }
}

void Portal::loadStudents() {
    ifstream in("students_data.txt");
    if (in.is_open()) {
        stdCount = getInt(in);
        for (int i = 0; i < stdCount && i < 50; i++) {
            students[i].load(in);
        }
        in.close();
    }
}

void Portal::loadFaculty() {
    ifstream in("faculty_data.txt");
    if (in.is_open()) {
        facCount = getInt(in);
        for (int i = 0; i < facCount && i < 20; i++) {
            facList[i].load(in);
        }
        in.close();
    }
}

void Portal::loadSubjects() {
    ifstream in("subjects_data.txt");
    if (in.is_open()) {
        subCount = getInt(in);
        for (int i = 0; i < subCount && i < 30; i++) {
            subjects[i].loadContent(in);
        }
        in.close();
    }
}

void Portal::loadRegs() {
    ifstream in("registrations_data.txt");
    ifstream facIn("faculty_data.txt");
    if (in.is_open()) {
        for (int i = 0; i < subCount; i++) {
            subjects[i].loadRegs(in);
        }
        string tag;
        if (getline(in, tag) && tag == "STUDENT_REGS") {
            for (int i = 0; i < stdCount; i++) {
                string sID;
                if (!getline(in, sID)) break;
                int si = findStudent(sID);
                if (si != -1) students[si].loadSubList(in);
                else {
                    getInt(in);
                    string dummy;
                    int count = getInt(in);
                    for (int k = 0; k < count; ++k) getline(in, dummy);
                }
            }
        }
        in.close();
    }
    if (facIn.is_open()) {
        int count = getInt(facIn);
        for (int i = 0; i < count; ++i) {
            string dummy;
            for (int j = 0; j < 4; ++j) getline(facIn, dummy);
        }
        string tag;
        if (getline(facIn, tag) && tag == "FACULTY_ALLOCS") {
            for (int i = 0; i < facCount; i++) {
                string fID;
                if (!getline(facIn, fID)) break;
                int ti = findFaculty(fID);
                if (ti != -1) facList[ti].loadAllocList(facIn);
                else {
                    getInt(facIn);
                    string dummy;
                    int count = getInt(facIn);
                    for (int k = 0; k < count; ++k) getline(facIn, dummy);
                }
            }
        }
        facIn.close();
    }
}

void Portal::loadAttend() {
    ifstream in("attendance_data.txt");
    if (in.is_open()) {
        int fc = getInt(in);
        for (int i = 0; i < subCount && i < fc; i++) {
            subjects[i].loadAttend(in);
        }
        in.close();
    }
}

void Portal::loadScores() {
    ifstream in("scores_data.txt");
    if (in.is_open()) {
        int fc = getInt(in);
        for (int i = 0; i < subCount && i < fc; i++) {
            subjects[i].loadScores(in);
        }
        in.close();
    }
}

void Portal::loadAll() {
    loadAdmin();
    loadStudents();
    loadFaculty();
    loadSubjects();
    seedData();
    loadRegs();
    loadAttend();
    loadScores();
    cout << "\n[ Data loaded from files. System ready. ]\n";
}

int Portal::findStudentUser(const string& u) const {
    for (int i = 0; i < stdCount; i++) if (students[i].getID() == u) return i;
    return -1;
}

int Portal::findFacultyUser(const string& u) const {
    for (int i = 0; i < facCount; i++) if (facList[i].getID() == u) return i;
    return -1;
}

int Portal::findStudent(const string& id) const {
    for (int i = 0; i < stdCount; i++) if (students[i].rollNo == id) return i;
    return -1;
}

int Portal::findFaculty(const string& id) const {
    for (int i = 0; i < facCount; i++) if (facList[i].empID == id) return i;
    return -1;
}

int Portal::findSubject(const string& code) const {
    for (int i = 0; i < subCount; i++) if (subjects[i].subCode == code) return i;
    return -1;
}

Person* Portal::login(const string& u, const string& p, int& outIndex, string& outRole) {
    for (int i = 0; i < stdCount; i++) if (students[i].verifyAuth(u, p)) { outIndex = i; outRole = "student"; return &students[i]; }
    for (int i = 0; i < facCount; i++) if (facList[i].verifyAuth(u, p)) { outIndex = i; outRole = "faculty"; return &facList[i]; }
    if (admin.verifyAuth(u, p)) { outIndex = 0; outRole = "admin"; return &admin; }
    outIndex = -1; outRole = ""; return nullptr;
}

bool Portal::addStudent(const string& id, const string& nm, const string& uname, const string& pw) {
    if (stdCount >= 50) return false;
    students[stdCount].setup(id, nm, uname, pw);
    stdCount++; return true;
}

bool Portal::removeStudent(const string& id) {
    int pos = findStudent(id);
    if (pos == -1) return false;
    for (int c = 0; c < subCount; c++) subjects[c].dropStudent(id);
    for (int i = pos; i < stdCount - 1; i++) students[i] = students[i + 1];
    stdCount--; return true;
}

bool Portal::addFaculty(const string& id, const string& nm, const string& uname, const string& pw) {
    if (facCount >= 20) return false;
    facList[facCount].setup(id, nm, uname, pw);
    facCount++; return true;
}

bool Portal::removeFaculty(const string& id) {
    int pos = findFaculty(id);
    if (pos == -1) return false;
    for (int c = 0; c < subCount; c++) if (subjects[c].facID == id) subjects[c].facID = "";
    for (int i = pos; i < facCount - 1; i++) facList[i] = facList[i + 1];
    facCount--; return true;
}

bool Portal::addSubject(const string& code, const string& nm) {
    if (subCount >= 30) return false;
    subjects[subCount].create(code, nm);
    subCount++; return true;
}

bool Portal::assignSub(const string& code, const string& fid) {
    int ci = findSubject(code);
    int ti = findFaculty(fid);
    if (ci == -1 || ti == -1) return false;
    subjects[ci].assignFac(fid);
    facList[ti].assignSubLocal(code);
    return true;
}

bool Portal::enrollStudent(const string& sid, const string& code) {
    int si = findStudent(sid);
    int ci = findSubject(code);
    if (si == -1 || ci == -1) return false;
    students[si].addSubLocal(code);
    subjects[ci].addStudent(sid);
    return true;
}

void Portal::listStudents() const {
    if (stdCount == 0) { cout << "No students.\n"; return; }
    cout << "\n   [ STUDENTS LIST ]\n";
    for (int i = 0; i < stdCount; i++)
        cout << "    " << i + 1 << ". " << students[i].rollNo << " - " << students[i].fullName << " (User: " << students[i].getID() << ")\n";
}

void Portal::listFaculty() const {
    if (facCount == 0) { cout << "No faculty.\n"; return; }
    cout << "\n   [ FACULTY LIST ]\n";
    for (int i = 0; i < facCount; i++)
        cout << "    " << i + 1 << ". " << facList[i].empID << " - " << facList[i].fullName << " (User: " << facList[i].getID() << ")\n";
}

void Portal::listSubjects() const {
    if (subCount == 0) { cout << "No subjects.\n"; return; }
    cout << "\n   [ SUBJECTS LIST ]\n";
    for (int i = 0; i < subCount; i++) subjects[i].printRow();
}