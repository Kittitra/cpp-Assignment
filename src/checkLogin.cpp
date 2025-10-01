#include "checkLogin.h"
#include <fstream>
#include <iostream>
using namespace std;

bool checkLogin(const string& filename, const string& user, const string& pass) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cerr << "can't open the file: " << filename << '\n';
        return false;
    }

    string fileUser, filePass;
    while (getline(infile, fileUser, ':') && getline(infile, filePass)) {
        if (fileUser == user && filePass == pass) {
            return true;
        }
    }
    return false;
}
