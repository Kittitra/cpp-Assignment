#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
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
    string filename = "data/accounts.txt";
    string username, password;

    system("cls");
    cout << "Log In: " << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (checkLogin(filename, username, password)) {
        cout << "Login success\n";
    } else {
        cout << "Login fail\n";
    }

    // รอผู้ใช้กด Enter ก่อนกลับไปเมนู
    cout << "Press Enter to continue...";
    cin.ignore(); // ล้าง buffer ของ cin (เพราะก่อนหน้านี้ใช้ >>)
    cin.get();    // รอ Enter

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