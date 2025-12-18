// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>

using namespace std;

// Inline use kiya taake multiple files mein error na aye
inline int getInt(ifstream& reader) {
    string line;
    if (!getline(reader, line)) return 0;
    try {
        return stoi(line);
    }
    catch (...) {
        return 0;
    }
}

#endif