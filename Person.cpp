// Person.cpp
#include "Person.h"

Person::Person() : uID(""), passKey("") {}

void Person::setAuth(const string& u, const string& p) {
    uID = u; passKey = p;
}

bool Person::verifyAuth(const string& u, const string& p) const {
    return uID == u && passKey == p;
}

string Person::getID() const { return uID; }

Person::~Person() {}

void Person::saveAuth(ofstream& out) const {
    out << uID << "\n" << passKey << "\n";
}

void Person::loadAuth(ifstream& in) {
    getline(in, uID);
    getline(in, passKey);
}