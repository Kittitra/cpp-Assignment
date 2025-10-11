#include <iostream>
#include <limits>
#include <cstdlib>
#include "../include/checkLogin.h"
#include "../include/logHistory.h"
#include "../include/manageCategory.h"
#include "../include/manageProductMenu.h"
#include "../include/StockMovement.h"
#include "../include/user.h"



int Login() {
    string filename = "../data/accounts.txt";
    string username, password;

    while (true) {
        system("cls");
        cout << "Log In (enter 0 to return to main menu):\n";

        cout << "Username: ";
        cin >> username;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (username == "0") break;

        cout << "Password: ";
        cin >> password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Account acc = checkLogin(filename, username, password);

        if (acc.username != "") {
            cout << "Login successful! Role: " << acc.role << endl;
            logLogin(acc.username, acc.role);
            cout << "Press Enter to continue...";
            cin.get();

            if (acc.role == "admin") {
                showAdminMenu("admin");
            }
            else if (acc.role == "staff") {
                showStaffMenu("staff");
            }

            break; // ออกจาก while login
        } else {
            cout << "Login failed! Press Enter to retry...";
            cin.get();
        }
    }
    return 0;
}

