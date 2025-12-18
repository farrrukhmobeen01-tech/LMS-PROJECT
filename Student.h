// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "Utils.h"

class Portal; // Forward declaration

class Student : public Person {
public:
    string rollNo;
    string fullName;
    string mySubs[30];
    int subCount;

    Student();
    void setup(const string& id, const string& n, const string& u, const string& p);
    void addSubLocal(const string& code);
    void removeSubLocal(const string& code);
    string getType() const override;
    void showMenu(Portal& sys, int idx) override;
    void save(ofstream& out) const;
    void load(ifstream& in);
    void loadSubList(ifstream& in);
};

#endif