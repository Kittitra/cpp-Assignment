#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <limits>
#include "checkLogin.h"

using namespace std;

int Menu(); 
int Login();

int main() {
    int c;

    do
    {
        system("cls");
        c = Menu();

        switch (c) // ใช้ switch เลือก menu
        {
        case 1:
            Login();
            break;
        }
    } while (c != 0); // หากใส่ 0 loop จะหยุดทำงาน
    cout << "exit program." << endl;

    return 0;
}

int Login() {
    string filename = "../data/accounts.txt";
    string username, password;

    while (true) {
        system("cls");
        cout << "Log In (enter 0 to return to menu): " << endl;

        cout << "Username: ";
        cin >> username;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ล้าง buffer

        if (username == "0") {
            cout << "Returning to menu...\n";
            cout << "Press Enter to continue...";
            cin.get();
            break; // กลับไปเมนู
        }

        cout << "Password: ";
        cin >> password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ล้าง buffer

        if (checkLogin(filename, username, password)) {
            cout << "Login success!\n";
            cout << "Press Enter to continue...";
            cin.get();
            break; // login ถูก → กลับเมนู
        } else {
            cout << "Login fail! Please try again.\n";
            cout << "Press Enter to retry...";
            cin.get();   // รอ Enter
        }
    }

    return 0;
}

int Menu() { // แสดงหน้าจอเมนูที่มีสามตัวเลือกออกมา 
    string line(30, '=');
    int choose;
    cout << line << endl;
    cout << "         Main Menu            :\n";
    cout << line << endl;
    cout << ":        0 _ exit             :\n";
    cout << ":        1 _ Login            :\n";
    cout << line << endl;
    cout << "choose menu : ";
    cin >> choose;
    return (choose); //ส่งค่ากลับไปหา switchcase ที่ main
}