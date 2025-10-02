#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "../include/manageProducts.h"

using namespace std;

const string CATEGORY_FILE = "../data/categories.txt";

// อ่าน category ทั้งหมดจากไฟล์
vector<string> loadCategories() {
    vector<string> categories;
    ifstream infile(CATEGORY_FILE);
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            categories.push_back(line);
        }
    }
    return categories;
}

// บันทึก category ทั้งหมดกลับไปที่ไฟล์
void saveCategories(const vector<string>& categories) {
    ofstream outfile(CATEGORY_FILE, ios::trunc);
    for (auto& c : categories) {
        outfile << c << endl;
    }
}

// แสดง category ทั้งหมด
void showCategories() {
    vector<string> categories = loadCategories();
    cout << "\n=== Product Categories ===\n";
    if (categories.empty()) {
        cout << "No categories found.\n";
    } else {
        for (size_t i = 0; i < categories.size(); i++) {
            cout << i+1 << ". " << categories[i] << endl;
        }
    }
}

// เพิ่ม category
void addCategory() {
    cout << "Enter new category name: ";
    string newCat;
    getline(cin, newCat);

    vector<string> categories = loadCategories();
    categories.push_back(newCat);
    saveCategories(categories);

    cout << "Category added successfully.\n";
}

// แก้ไข category
void editCategory() {
    vector<string> categories = loadCategories();
    if (categories.empty()) {
        cout << "No categories to edit.\n";
        return;
    }

    showCategories();
    cout << "Enter category number to edit: ";
    int index;
    cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > (int)categories.size()) {
        cout << "Invalid category number.\n";
        return;
    }

    cout << "Enter new name: ";
    string newName;
    getline(cin, newName);

    categories[index-1] = newName;
    saveCategories(categories);

    cout << "Category updated successfully.\n";
}

// ลบ category
void deleteCategory() {
    vector<string> categories = loadCategories();
    if (categories.empty()) {
        cout << "No categories to delete.\n";
        return;
    }

    showCategories();
    cout << "Enter category number to delete: ";
    int index;
    cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > (int)categories.size()) {
        cout << "Invalid category number.\n";
        return;
    }

    categories.erase(categories.begin() + index - 1);
    saveCategories(categories);

    cout << "Category deleted successfully.\n";
}

// เมนูย่อย Manage Products
void manageProductsMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== Manage Product Categories ===\n";
        cout << "1. Add Category\n";
        cout << "2. Edit Category\n";
        cout << "3. Delete Category\n";
        cout << "4. Show All Categories\n";
        cout << "0. Back to Admin Menu\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: addCategory(); break;
            case 2: editCategory(); break;
            case 3: deleteCategory(); break;
            case 4: showCategories(); break;
            case 0: cout << "Back to Admin Menu...\n"; break;
            default: cout << "Invalid option.\n";
        }

        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}
