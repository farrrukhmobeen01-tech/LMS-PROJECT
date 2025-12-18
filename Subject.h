// Subject.h
#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Utils.h"

using namespace std;

class Subject {
public:
    string subCode;
    string subName;
    string facID;
    string joined[50];
    int joinCount;
    int sessions;
    int presence[50];
    string scores[50];

    string notes[200];
    int noteCount;

    string tasks[200];
    int taskCount;

    string reviews[200];
    int reviewCount;

    Subject();
    void create(const string& c, const string& n);
    void assignFac(const string& fid);
    bool addStudent(const string& sID);
    bool dropStudent(const string& sID);
    int getStudentIndex(const string& sID) const;
    void takeAttendance();
    void showPresence(const string& sID) const;
    void addNote(const string& txt);
    void addTask(const string& txt);
    void addReview(const string& txt);
    void setScore(const string& sID, const string& g);
    string getScore(const string& sID) const;
    void showNotes() const;
    void showTasks() const;
    void showReviews() const;
    void printRow() const;
    void printDetails() const;
    void saveContent(ofstream& out) const;
    void loadContent(ifstream& in);
    void saveRegs(ofstream& out) const;
    void loadRegs(ifstream& in);
    void saveAttend(ofstream& out) const;
    void loadAttend(ifstream& in);
    void saveScores(ofstream& out) const;
    void loadScores(ifstream& in);
};

#endif