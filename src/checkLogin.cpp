#include "../include/checkLogin.h"
#include <fstream>
#include <iostream>

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

Account checkLogin(const string& filename, const string& user, const string& pass) {
    ifstream infile(filename);
    if (!infile) return {"", "", ""};

    string line;
    while (getline(infile, line)) {
        size_t pos1 = line.find(':');
        size_t pos2 = line.rfind(':');
        if (pos1 == string::npos || pos2 == string::npos) continue;

        string fileUser = trim(line.substr(0, pos1));
        string filePass = trim(line.substr(pos1+1, pos2-pos1-1));
        string fileRole = trim(line.substr(pos2+1));

        if (fileUser == user && filePass == pass)
            return {fileUser, filePass, fileRole};
    }
    return {"", "", ""};
}
