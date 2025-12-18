// Subject.cpp
#include "Subject.h"

Subject::Subject() {
    subCode = ""; subName = ""; facID = "";
    joinCount = 0;
    sessions = 0;
    noteCount = taskCount = reviewCount = 0;
    for (int i = 0; i < 50; i++) {
        presence[i] = 0;
        scores[i] = "";
        joined[i] = "";
    }
}

void Subject::create(const string& c, const string& n) {
    subCode = c; subName = n;
}

void Subject::assignFac(const string& fid) { facID = fid; }

bool Subject::addStudent(const string& sID) {
    if (joinCount >= 50) return false;
    for (int i = 0; i < joinCount; i++) if (joined[i] == sID) return true;

    joined[joinCount] = sID;
    presence[joinCount] = 0;
    scores[joinCount] = "";
    joinCount++;
    return true;
}

bool Subject::dropStudent(const string& sID) {
    int loc = -1;
    for (int i = 0; i < joinCount; i++) if (joined[i] == sID) { loc = i; break; }
    if (loc == -1) return false;

    for (int i = loc; i < joinCount - 1; i++) {
        joined[i] = joined[i + 1];
        presence[i] = presence[i + 1];
        scores[i] = scores[i + 1];
    }
    joined[joinCount - 1] = "";
    presence[joinCount - 1] = 0;
    scores[joinCount - 1] = "";
    joinCount--;
    return true;
}

int Subject::getStudentIndex(const string& sID) const {
    for (int i = 0; i < joinCount; i++) if (joined[i] == sID) return i;
    return -1;
}

void Subject::takeAttendance() {
    if (joinCount == 0) { cout << "No students joined here.\n"; return; }
    sessions++;
    cout << "\n >> Attendance for " << subCode << " - " << subName << " (Session " << sessions << ")\n";
    for (int i = 0; i < joinCount; i++) {
        cout << "   Student " << joined[i] << " present? (1 = yes, 0 = no): ";
        int p; while (!(cin >> p)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Enter 1 or 0: "; }
        if (p == 1) presence[i] += 1;
    }
    cin.ignore(100, '\n');
    cout << "   [Done]\n";
}

void Subject::showPresence(const string& sID) const {
    int idx = getStudentIndex(sID);
    if (idx == -1) { cout << "   " << subCode << " : Not joined.\n"; return; }
    cout << "   " << subCode << " - " << subName << " : " << presence[idx] << "/" << sessions << " present\n";
}

void Subject::addNote(const string& txt) {
    if (noteCount >= 200) { cout << "Storage full.\n"; return; }
    notes[noteCount++] = txt;
}

void Subject::addTask(const string& txt) {
    if (taskCount >= 200) { cout << "Storage full.\n"; return; }
    tasks[taskCount++] = txt;
}

void Subject::addReview(const string& txt) {
    if (reviewCount >= 200) { cout << "Storage full.\n"; return; }
    reviews[reviewCount++] = txt;
}

void Subject::setScore(const string& sID, const string& g) {
    int idx = getStudentIndex(sID);
    if (idx == -1) { cout << "Student not found.\n"; return; }
    scores[idx] = g;
}

string Subject::getScore(const string& sID) const {
    int idx = getStudentIndex(sID);
    if (idx == -1) return "";
    return scores[idx];
}

void Subject::showNotes() const {
    if (noteCount == 0) { cout << "   No notes for " << subCode << "\n"; return; }
    cout << "   Notes for " << subCode << ":\n";
    for (int i = 0; i < noteCount; i++) cout << "    " << i + 1 << ". " << notes[i] << "\n";
}

void Subject::showTasks() const {
    if (taskCount == 0) { cout << "   No tasks for " << subCode << "\n"; return; }
    cout << "   Tasks for " << subCode << ":\n";
    for (int i = 0; i < taskCount; i++) cout << "    " << i + 1 << ". " << tasks[i] << "\n";
}

void Subject::showReviews() const {
    if (reviewCount == 0) { cout << "   No reviews for " << subCode << "\n"; return; }
    cout << "   Reviews for " << subCode << ":\n";
    for (int i = 0; i < reviewCount; i++) cout << "    " << i + 1 << ". " << reviews[i] << "\n";
}

void Subject::printRow() const {
    cout << "   " << left << setw(8) << subCode << " - " << subName << " FacID: " << (facID.empty() ? "NA" : facID) << "\n";
}

void Subject::printDetails() const {
    cout << "\n   [ Subject " << subCode << " - " << subName << " ] (Joined: " << joinCount << ")\n";
    for (int i = 0; i < joinCount; i++) {
        cout << "    " << i + 1 << ". " << joined[i] << " | Pres: " << presence[i]
            << " | Score: " << (scores[i].empty() ? "N/A" : scores[i]) << "\n";
    }
}

void Subject::saveContent(ofstream& out) const {
    out << subCode << "\n" << subName << "\n" << facID << "\n";
    out << noteCount << "\n";
    for (int i = 0; i < noteCount; i++) out << notes[i] << "\n";
    out << taskCount << "\n";
    for (int i = 0; i < taskCount; i++) out << tasks[i] << "\n";
    out << reviewCount << "\n";
    for (int i = 0; i < reviewCount; i++) out << reviews[i] << "\n";
}

void Subject::loadContent(ifstream& in) {
    if (!getline(in, subCode)) return;
    if (!getline(in, subName)) return;
    if (!getline(in, facID)) return;
    noteCount = getInt(in);
    for (int i = 0; i < noteCount && i < 200; i++) {
        if (!getline(in, notes[i])) return;
    }
    taskCount = getInt(in);
    for (int i = 0; i < taskCount && i < 200; i++) {
        if (!getline(in, tasks[i])) return;
    }
    reviewCount = getInt(in);
    for (int i = 0; i < reviewCount && i < 200; i++) {
        if (!getline(in, reviews[i])) return;
    }
}

void Subject::saveRegs(ofstream& out) const {
    out << subCode << "\n";
    out << joinCount << "\n";
    for (int i = 0; i < joinCount; i++) {
        out << joined[i] << "\n";
    }
}

void Subject::loadRegs(ifstream& in) {
    string tempCode;
    if (!getline(in, tempCode) || tempCode != subCode) return;
    joinCount = getInt(in);
    for (int i = 0; i < joinCount && i < 50; i++) {
        if (!getline(in, joined[i])) return;
    }
}

void Subject::saveAttend(ofstream& out) const {
    out << subCode << "\n";
    out << sessions << "\n";
    for (int i = 0; i < joinCount; i++) {
        out << joined[i] << "\n";
        out << presence[i] << "\n";
    }
}

void Subject::loadAttend(ifstream& in) {
    string tempCode;
    if (!getline(in, tempCode) || tempCode != subCode) return;
    sessions = getInt(in);
    for (int i = 0; i < joinCount; i++) {
        string sID;
        if (!getline(in, sID)) return;
        int idx = getStudentIndex(sID);
        if (idx != -1) {
            presence[idx] = getInt(in);
        }
        else {
            getInt(in);
        }
    }
}

void Subject::saveScores(ofstream& out) const {
    out << subCode << "\n";
    for (int i = 0; i < joinCount; i++) {
        out << joined[i] << "\n";
        out << scores[i] << "\n";
    }
}

void Subject::loadScores(ifstream& in) {
    string tempCode;
    if (!getline(in, tempCode) || tempCode != subCode) return;
    for (int i = 0; i < joinCount; i++) {
        string sID;
        if (!getline(in, sID)) return;
        int idx = getStudentIndex(sID);
        if (idx != -1) {
            if (!getline(in, scores[idx])) return;
        }
        else {
            string dummy;
            if (!getline(in, dummy)) return;
        }
    }
}