// Portal.h
#ifndef PORTAL_H
#define PORTAL_H

#include "Student.h"
#include "Faculty.h"
#include "Admin.h"
#include "Subject.h"

class Portal {
public:
    Student students[50];
    int stdCount;

    Faculty facList[20];
    int facCount;

    Subject subjects[30];
    int subCount;

    Admin admin;

    Portal();
    void seedData();
    bool removeSubject(const string& code);
    void saveAdmin() const;
    void saveStudents() const;
    void saveFaculty() const;
    void saveSubjects() const;
    void saveRegs() const;
    void saveAttend() const;
    void saveScores() const;
    void saveAll() const;
    void loadAdmin();
    void loadStudents();
    void loadFaculty();
    void loadSubjects();
    void loadRegs();
    void loadAttend();
    void loadScores();
    void loadAll();
    int findStudentUser(const string& u) const;
    int findFacultyUser(const string& u) const;
    int findStudent(const string& id) const;
    int findFaculty(const string& id) const;
    int findSubject(const string& code) const;
    Person* login(const string& u, const string& p, int& outIndex, string& outRole);
    bool addStudent(const string& id, const string& nm, const string& uname, const string& pw);
    bool removeStudent(const string& id);
    bool addFaculty(const string& id, const string& nm, const string& uname, const string& pw);
    bool removeFaculty(const string& id);
    bool addSubject(const string& code, const string& nm);
    bool assignSub(const string& code, const string& fid);
    bool enrollStudent(const string& sid, const string& code);
    void listStudents() const;
    void listFaculty() const;
    void listSubjects() const;
};

#endif