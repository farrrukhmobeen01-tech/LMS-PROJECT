// Faculty.h
#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"
#include "Utils.h"

class Portal;

class Faculty : public Person {
public:
    string empID;
    string fullName;
    string allocs[30];
    int allocCount;

    Faculty();
    void setup(const string& id, const string& n, const string& u, const string& p);
    void assignSubLocal(const string& code);
    string getType() const override;
    void showMenu(Portal& sys, int idx) override;
    void save(ofstream& out) const;
    void load(ifstream& in);
    void loadAllocList(ifstream& in);
};

#endif