#include <iostream>
#include <limits>
#include <cstdlib>
#include "../include/checkLogin.h"
#include "../include/logHistory.h"
#include "../include/manageCategory.h"
#include "../include/manageProductMenu.h"
#include "../include/StockMovement.h"
#include "../include/user.h"

using namespace std;

void showAdminMenu() {
    system("cls");
    cout << "=== Admin Menu ===\n";
    cout << "1. Manage Product Categories\n";
    cout << "2. Manage Products\n";
    cout << "3. Stock Movements\n";
    cout << "4. Sales\n";
    cout << "5. Reports\n";
    cout << "6. AddUser\n";
    cout << "0. Logout / Return to Main Menu\n";
    cout << "==================\n";
}

void showStaffMenu() {
    system("cls");
    cout << "=== Staff Menu ===\n";
    cout << "1. Stock Movements\n";
    cout << "2. Sales\n";
    cout << "3. Reports\n";
    cout << "0. Logout / Return to Main Menu\n";
    cout << "==================\n";
}

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

            int choice;

            if (acc.role == "admin") {
                do {
                    showAdminMenu();
                    cout << "Choose option: ";
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch(choice) {
                        case 1: manageCategory(); break;
                        case 2: manageProductsMenu(); break;
                        case 3: stockMovementMenu(); break;
                        case 4: salesMenu(); break;
                        case 5: reportMenu(acc.role); break;
                        case 6: addUser(); break;
                        case 0: cout << "Logging out...\n"; break;
                        default: cout << "Invalid option\n";
                    }

                    if (choice != 0) {
                        cout << "Press Enter to continue...";
                        cin.get();
                    }
                } while(choice != 0);
            }
            else if (acc.role == "staff") {
                do {
                    showStaffMenu();
                    cout << "Choose option: ";
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch(choice) {
                        case 1: stockMovementMenu(); break;
                        case 2: salesMenu(); break;
                        case 3: reportMenu(acc.role); break;
                        case 0: cout << "Logging out...\n"; break;
                        default: cout << "Invalid option\n";
                    }

                    if (choice != 0) {
                        cout << "Press Enter to continue...";
                        cin.get();
                    }
                } while(choice != 0);
            }

            break; // ออกจาก while login
        } else {
            cout << "Login failed! Press Enter to retry...";
            cin.get();
        }
    }
    return 0;
}

int main() {
    int c;
    do {
        system("cls");
        cout << "=== Main Menu ===\n";
        cout << "1. Login\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(c) {
            case 1: Login(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid option\n";
        }
    } while(c != 0);

    return 0;
}
