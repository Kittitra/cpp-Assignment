#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <limits>
#include "../include/manageProductMenu.h"
#include "../include/product.h"

using namespace std;

const string PRODUCTS_FILE = "../data/products.txt";
const string SALES_FILE = "../data/sales.txt";
const string STOCK_FILE = "../data/stock.txt";

// ───────────────────────────────
// แสดงรายงานสินค้า
// ───────────────────────────────
void showProductReport() {
    vector<Product> products = loadProducts();
    cout << "\n=== Product Report ===\n";
    if (products.empty()) {
        cout << "No product data found.\n";
        return;
    }

    cout << left << setw(20) << "Product" 
         << setw(15) << "Category"
         << setw(10) << "SellPrice"
         << setw(10) << "FullUnits"
         << setw(10) << "Loose"
         << setw(10) << "Unit"
         << setw(12) << "Status" << endl;
    cout << string(80, '-') << endl;

    for (auto &p : products) {
        cout << left << setw(20) << p.name 
             << setw(15) << p.category
             << setw(10) << p.sellPrice
             << setw(10) << p.fullUnits
             << setw(10) << p.loosePieces
             << setw(10) << p.unitName
             << setw(12) << p.status << endl;
    }
}

// ───────────────────────────────
// แสดงรายงานยอดขาย (ตามวัน/เดือน)
// ───────────────────────────────
void showSalesReport() {
    ifstream file(SALES_FILE);
    if (!file) {
        cout << "No sales data found.\n";
        return;
    }

    map<string, double> dailySales;
    map<string, double> monthlySales;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t dateStart = line.find('[');
        size_t dateEnd = line.find(']');
        if (dateStart == string::npos || dateEnd == string::npos) continue;

        string date = line.substr(dateStart + 1, dateEnd - dateStart - 1);
        string dayKey = date;                  // เช่น 2025-10-04
        string monthKey = date.substr(0, 7);   // เช่น 2025-10

        size_t totalPos = line.find("Total=");
        if (totalPos != string::npos) {
            double total = 0;
            stringstream ss(line.substr(totalPos + 6));
            ss >> total;

            dailySales[dayKey] += total;
            monthlySales[monthKey] += total;
        }
    }

    cout << "\n=== Sales Report ===\n";
    cout << "\n--- By Day ---\n";
    for (auto &d : dailySales)
        cout << d.first << " : " << fixed << setprecision(2) << d.second << " THB\n";

    cout << "\n--- By Month ---\n";
    for (auto &m : monthlySales)
        cout << m.first << " : " << fixed << setprecision(2) << m.second << " THB\n";
}

// ───────────────────────────────
// แสดงรายงานการเคลื่อนไหวสต็อก
// ───────────────────────────────
void showStockMovementReport() {
    ifstream file(STOCK_FILE);
    if (!file) {
        cout << "No stock movement data found.\n";
        return;
    }

    cout << "\n=== Stock Movement History ===\n";
    cout << left << setw(15) << "Date" 
         << setw(15) << "Product" 
         << setw(10) << "Type"
         << setw(10) << "Full"
         << setw(10) << "Loose"
         << setw(10) << "Unit"
         << setw(10) << "UnitSize"
         << setw(20) << "Remarks" << endl;
    cout << string(90, '-') << endl;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string date, product, type, full, loose, unit, unitSize, remarks;

        getline(ss, product, '|');
        getline(ss, type, '|');
        getline(ss, full, '|');
        getline(ss, loose, '|');
        getline(ss, unit, '|');
        getline(ss, unitSize, '|');
        getline(ss, remarks, '|');
        getline(ss, date, '|');

        cout << left << setw(15) << date
             << setw(15) << product
             << setw(10) << type
             << setw(10) << full
             << setw(10) << loose
             << setw(10) << unit
             << setw(10) << unitSize
             << setw(20) << remarks << endl;
    }
}

// ───────────────────────────────
// เมนูรายงานหลัก
// ───────────────────────────────
void reportMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== REPORT MENU ===\n";
        cout << "1. Product Report\n";
        cout << "2. Sales Report (by Day/Month)\n";
        cout << "3. Stock Movement Report\n";
        cout << "0. Back to Main Menu\n";
        cout << "------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: showProductReport(); break;
            case 2: showSalesReport(); break;
            case 3: showStockMovementReport(); break;
            case 0: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid option!\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}
