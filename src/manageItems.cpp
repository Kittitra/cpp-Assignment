#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>
#include "../include/manageProductMenu.h"
#include "../include/product.h"
using namespace std;

const string PRODUCT_FILE = "../data/products.txt";

// ──────────────────────────────
// Helper แปลง product ↔ string
// ──────────────────────────────
string productToString(const Product& p) {
    stringstream ss;
    ss << p.name << "|" 
       << p.category << "|" 
       << p.costPrice << "|" 
       << p.sellPrice << "|" 
       << p.fullUnits << "|" 
       << p.unitSize << "|" 
       << p.loosePieces << "|" 
       << p.unitName << "|" 
       << p.status;
    return ss.str();
}

Product stringToProduct(const string &line) {
    Product p;
    stringstream ss(line);
    string costStr, sellStr, fullStr, unitSizeStr, looseStr;

    getline(ss, p.name, '|');
    getline(ss, p.category, '|');
    getline(ss, costStr, '|');
    getline(ss, sellStr, '|');
    getline(ss, fullStr, '|');
    getline(ss, unitSizeStr, '|');
    getline(ss, looseStr, '|');
    getline(ss, p.unitName, '|');
    getline(ss, p.status, '|');

    // ✅ ปลอดภัย: ตรวจสอบก่อนแปลง
    try { p.costPrice = stod(costStr); } 
    catch (...) { p.costPrice = 0; }

    try { p.sellPrice = stod(sellStr); } 
    catch (...) { p.sellPrice = 0; }

    try { p.fullUnits = stoi(fullStr); } 
    catch (...) { p.fullUnits = 0; }

    try { p.unitSize = stoi(unitSizeStr); } 
    catch (...) { p.unitSize = 0; }

    try { p.loosePieces = stoi(looseStr); } 
    catch (...) { p.loosePieces = 0; }

    return p;
}


// ──────────────────────────────
// โหลด/บันทึกสินค้า
// ──────────────────────────────
vector<Product> loadProducts() {
    vector<Product> products;
    ifstream infile(PRODUCT_FILE);
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            products.push_back(stringToProduct(line));
        }
    }
    return products;
}

void saveProducts(const vector<Product>& products) {
    ofstream outfile(PRODUCT_FILE, ios::trunc);
    for (auto& p : products) {
        outfile << productToString(p) << endl;
    }
}

// ──────────────────────────────
// แสดงสินค้า
// ──────────────────────────────
void showshowProducts() {
    vector<Product> products = loadProducts();
    cout << "\n=== Product List ===\n";

    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }

    // แสดงหัวตาราง
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Product"
         << setw(15) << "Category"
         << setw(10) << "Cost"
         << setw(10) << "Sell"
         << setw(12) << "Full Units"
         << setw(12) << "Loose"
         << setw(15) << "Unit Name"
         << setw(10) << "Unit Size"
         << setw(12) << "Total"
         << setw(12) << "Status" << endl;

    cout << string(123, '-') << endl;

    // แสดงสินค้าแต่ละรายการ
    for (size_t i = 0; i < products.size(); i++) {
        int totalPieces = products[i].fullUnits * products[i].unitSize + products[i].loosePieces;

        cout << left
             << setw(5)  << (i+1)
             << setw(20) << products[i].name
             << setw(15) << products[i].category
             << setw(10) << products[i].costPrice
             << setw(10) << products[i].sellPrice
             << setw(12) << products[i].fullUnits
             << setw(12) << products[i].loosePieces
             << setw(15) << products[i].unitName
             << setw(10) << products[i].unitSize
             << setw(12) << totalPieces
             << setw(12) << products[i].status
             << endl;
    }
}


// ──────────────────────────────
// เพิ่มสินค้า
// ──────────────────────────────
void addProduct() {
    Product p;
    int statusInput;
    cout << "Enter product name: "; getline(cin, p.name);
    cout << "Enter category: "; getline(cin, p.category);
    cout << "Enter cost price: "; cin >> p.costPrice;
    cout << "Enter sell price: "; cin >> p.sellPrice;
    cout << "Enter number of full units: "; cin >> p.fullUnits;
    cout << "Enter unit size (pieces per unit): "; cin >> p.unitSize;
    p.loosePieces = 0; // เริ่มต้นยังไม่มีการแกะ
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter unit name (e.g. pack, box): "; getline(cin, p.unitName);
    cout << "Enter status (1 = Available, 0 = Unavailable): ";
    cin >> statusInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    p.status = (statusInput == 1) ? "Available" : "Unavailable";

    vector<Product> products = loadProducts();
    products.push_back(p);
    saveProducts(products);
    cout << "Product added successfully.\n";
}


// ──────────────────────────────
// แก้ไขสินค้า
// ──────────────────────────────
void editProduct() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products to edit.\n";
        return;
    }

    showProducts();
    cout << "Enter product number to edit: ";
    int index; cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > (int)products.size()) {
        cout << "Invalid product number.\n";
        return;
    }

    Product &p = products[index - 1];
    cout << "\nEditing product: " << p.name << endl;

    string temp;

    cout << "Enter new name (" << p.name << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.name = temp;

    cout << "Enter new category (" << p.category << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.category = temp;

    cout << "Enter new cost price (" << p.costPrice << "): ";
    getline(cin, temp);
    if (!temp.empty()) {
        try { p.costPrice = stod(temp); }
        catch (...) { cout << "Invalid input. Keeping old value.\n"; }
    }

    cout << "Enter new sell price (" << p.sellPrice << "): ";
    getline(cin, temp);
    if (!temp.empty()) {
        try { p.sellPrice = stod(temp); }
        catch (...) { cout << "Invalid input. Keeping old value.\n"; }
    }

    cout << "Enter new unit name (" << p.unitName << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.unitName = temp;

    cout << "Enter new status (" << p.status << ") [1=Available, 0=Unavailable]: ";
    getline(cin, temp);
    if (!temp.empty()) {
        if (temp == "1") p.status = "Available";
        else if (temp == "0") p.status = "Unavailable";
    }

    saveProducts(products);
    cout << "\n Product information updated successfully .\n";
}



// ──────────────────────────────
// ลบสินค้า
// ──────────────────────────────
void deleteProduct() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products to delete.\n";
        return;
    }

    showProducts();
    cout << "Enter product number to delete: ";
    int index; cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > (int)products.size()) {
        cout << "Invalid product number.\n";
        return;
    }

    cout << "Deleting " << products[index-1].name << endl;
    products.erase(products.begin() + index - 1);
    saveProducts(products);
    cout << "Product deleted successfully.\n";
}

// ──────────────────────────────
// เมนูหลัก Manage Products
// ──────────────────────────────
void manageProductsMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== Manage Products ===\n";
        cout << "1. Add Product\n";
        cout << "2. Edit Product\n";
        cout << "3. Delete Product\n";
        cout << "4. Show All Products\n";
        cout << "0. Back to Admin Menu\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: addProduct(); break;
            case 2: editProduct(); break;
            case 3: deleteProduct(); break;
            case 4: showProducts(); break;
            case 0: cout << "Back to Menu...\n"; break;
            default: cout << "Invalid option.\n";
        }

        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}
