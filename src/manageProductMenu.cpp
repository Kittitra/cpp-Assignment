#include <iostream>
#include <limits>
#include "../include/manageProducts.h"
using namespace std;

void manageProductsMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== Manage Products ===\n";
        cout << "1. Add Product\n";
        cout << "2. Edit Product\n";
        cout << "3. Delete Product\n";
        cout << "0. Back\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: cout << "Add Product selected\n"; break;
            case 2: cout << "Edit Product selected\n"; break;
            case 3: cout << "Delete Product selected\n"; break;
            case 0: break;
            default: cout << "Invalid option\n";
        }

        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while(choice != 0);
}
