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

bool showAdminMenu(string role) {
    int choice;
    do {
        system("cls");
        cout << "=== Admin Menu ===\n";
        cout << "1. Manage Product Categories\n";
        cout << "2. Manage Products\n";
        cout << "3. Stock Movements\n";
        cout << "4. Sales\n";
        cout << "5. Reports\n";
        cout << "6. AddUser\n";
        cout << "0. Logout\n";
        cout << "==================\n";
        // showAdminMenu();
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: manageCategoryMenu(); break;
            case 2: manageProductsMenu(); break;
            case 3: stockMovementMenu(); break;
            case 4: salesMenu(); break;
            case 5: reportMenu(role); break;
            case 6: addUser(); break;
            case 0: cout << "Logging out...\n"; 
                return true;
                break;
            default: cout << "Invalid option\n";
        }

        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while(choice != 0);
    return false;
}

bool showStaffMenu(string role) {
    int choice;
    do {
        system("cls");
        cout << "=== Staff Menu ===\n";
        cout << "1. Stock Movements\n";
        cout << "2. Sales\n";
        cout << "3. Reports\n";
        cout << "0. Logout\n";
        cout << "==================\n";
        // showStaffMenu();
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: stockMovementMenu(); break;
            case 2: salesMenu(); break;
            case 3: reportMenu(role); break;
            case 0: 
                cout << "Logging out...\n"; 
                return true;
                break;
            default: cout << "Invalid option\n";
        }

        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while(choice != 0);
    return false;
}