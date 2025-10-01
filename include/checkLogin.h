#pragma once
#include <string>
using namespace std;

struct Account {
    string username;
    string password;
    string role;
};

Account checkLogin(const string& filename, const string& user, const string& pass);
