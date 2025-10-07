#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../include/user.h"

using namespace std;

const string USERS_FILE = "../data/accounts.txt";

void addUser() {
    string username, password, role;

    cout << "=== Add New User ===\n";

    // กรอก username
    cout << "Enter username: ";
    getline(cin, username);
    if (username.empty()) {
        cout << "Username cannot be empty!\n";
        return;
    }

    // กรอก password
    cout << "Enter password: ";
    getline(cin, password);
    if (password.empty()) {
        cout << "Password cannot be empty!\n";
        return;
    }

    // เลือก role
    do {
        cout << "Enter role (admin/staff): ";
        getline(cin, role);
        if (role != "admin" && role != "staff") {
            cout << "Invalid role! Please enter 'admin' or 'staff'.\n";
        }
    } while (role != "admin" && role != "staff");

    // เช็คว่ามี username นี้อยู่แล้วหรือไม่
    ifstream infile(USERS_FILE);
    string line;
    while (getline(infile, line)) {
        if (line.substr(0, line.find(':')) == username) {
            cout << "Username already exists!\n";
            infile.close();
            return;
        }
    }
    infile.close();

    // บันทึกผู้ใช้ใหม่
    ofstream outfile(USERS_FILE, ios::app);
    outfile << username << ":" << password << ":" << role << "\n";
    outfile.close();

    cout << "User added successfully!\n";
}
