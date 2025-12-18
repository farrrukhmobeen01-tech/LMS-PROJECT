// Person.h
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Portal; // Forward declaration zaroori hai

class Person {
protected:
    string uID;
    string passKey;
public:
    Person();
    void setAuth(const string& u, const string& p);
    bool verifyAuth(const string& u, const string& p) const;
    string getID() const;
    virtual string getType() const = 0;
    virtual void showMenu(Portal& sys, int idx) = 0;
    virtual ~Person();
    void saveAuth(ofstream& out) const;
    void loadAuth(ifstream& in);
};

#endif