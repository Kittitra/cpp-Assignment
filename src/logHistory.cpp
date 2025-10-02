#include "../include/logHistory.h"
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

void logLogin(const string& username, const string& role) {
    ofstream outfile("../data/login_history.txt", ios::app); 
    if (!outfile) {
        cerr << "Error: cannot open login_history.txt\n";
        return;
    }

    // ดึงเวลาปัจจุบัน
    time_t now = time(0);
    tm* ltm = localtime(&now);

    char buffer[50];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    // เขียนบันทึก
    outfile << "[" << buffer << "] "
            << "User: " << username 
            << " (Role: " << role << ") logged in." << endl;

    outfile.close();
}
