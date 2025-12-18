// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"

class Portal;

class Admin : public Person {
public:
    string fullName;
    Admin();
    void setup(const string& n, const string& u, const string& p);
    string getType() const override;
    void showMenu(Portal& sys, int idx) override;
    void save(ofstream& out) const;
    void load(ifstream& in);
};

#endif