#include "checkLogin.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// ฟังก์ชัน trim ตัด space, tab, newline, carriage return
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

bool checkLogin(const string& filename, const string& user, const string& pass) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cerr << "Can't open the file: " << filename << '\n';
        return false;
    }

    string fileUser, filePass;
    while (getline(infile, fileUser, ':') && getline(infile, filePass)) {
        fileUser = trim(fileUser);
        filePass = trim(filePass);

        if (fileUser == user && filePass == pass) {
            return true;
        }
    }
    return false;
}
