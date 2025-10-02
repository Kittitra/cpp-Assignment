#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "../include/manageItems.h"
using namespace std;

const string PRODUCT_FILE = "../data/products.txt";

struct Product {
    string name;
    string category;
    double costPrice;
    double sellPrice;
    int quantity;
    string unitName;
    int unitSize;
    string status; // "Available" or "Unavailable"
};

// แปลง product → string (บันทึกไฟล์)
string productToString(const Product& p) {
    stringstream ss;
    ss << p.name << "|" 
       << p.category << "|" 
       << p.costPrice << "|" 
       << p.sellPrice << "|" 
       << p.quantity << "|" 
       << p.unitName << "|" 
       << p.unitSize << "|" 
       << p.status;
    return ss.str();
}

// แปลง string → product (อ่านจากไฟล์)
Product stringToProduct(const string& line) {
    Product p;
    stringstream ss(line);
    getline(ss, p.name, '|');
    getline(ss, p.category, '|');
    ss >> p.costPrice; ss.ignore();
    ss >> p.sellPrice; ss.ignore();
    ss >> p.quantity; ss.ignore();
    getline(ss, p.unitName, '|');
    ss >> p.unitSize; ss.ignore();
    getline(ss, p.status, '|');
    return p;
}

// โหลดสินค้าทั้งหมดจากไฟล์
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

// บันทึกสินค้าทั้งหมดลงไฟล์
void saveProducts(const vector<Product>& products) {
    ofstream outfile(PRODUCT_FILE, ios::trunc);
    for (auto& p : products) {
        outfile << productToString(p) << endl;
    }
}

// แสดงสินค้าทั้งหมด
void showProducts() {
    vector<Product> products = loadProducts();
    cout << "\n=== Product List ===\n";
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }
    for (size_t i = 0; i < products.size(); i++) {
        cout << i+1 << ". " << products[i].name 
             << " | Category: " << products[i].category
             << " | Cost: " << products[i].costPrice
             << " | Sell: " << products[i].sellPrice
             << " | Qty: " << products[i].quantity
             << " " << products[i].unitName 
             << "(x" << products[i].unitSize << ")"
             << " | Status: " << products[i].status
             << endl;
    }
}

// เพิ่มสินค้า
void addProduct() {
    Product p;
    int statusInput;
    cout << "Enter product name: "; getline(cin, p.name);
    cout << "Enter category: "; getline(cin, p.category);
    cout << "Enter cost price: "; cin >> p.costPrice;
    cout << "Enter sell price: "; cin >> p.sellPrice;
    cout << "Enter quantity: "; cin >> p.quantity;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter unit name (e.g. pack, box): "; getline(cin, p.unitName);
    cout << "Enter unit size: "; cin >> p.unitSize;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter status (1 = Available, 0 = Unavailable): ";
    cin >> statusInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (statusInput == 1)
        p.status = "Available";
    else
        p.status = "Unavailable";

    ofstream outfile("../data/products.txt", ios::app);
    if (outfile.is_open()) {
        outfile << p.name << "," 
                << p.category << "," 
                << p.costPrice << "," 
                << p.sellPrice << "," 
                << p.quantity << "," 
                << p.unitName << "," 
                << p.status << "\n";
        outfile.close();
        cout << "Product saved successfully!\n";
    } else {
        cerr << "Error: cannot open products file.\n";
    }

    // vector<Product> products = loadProducts();
    // products.push_back(p);
    // saveProducts(products);
    // cout << "Product added successfully.\n";
}

// แก้ไขสินค้า
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

    Product &p = products[index-1];
    cout << "Editing " << p.name << endl;

    cout << "Enter new name (" << p.name << "): ";
    string temp; getline(cin, temp);
    if (!temp.empty()) p.name = temp;

    cout << "Enter new category (" << p.category << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.category = temp;

    cout << "Enter new cost price (" << p.costPrice << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.costPrice = stod(temp);

    cout << "Enter new sell price (" << p.sellPrice << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.sellPrice = stod(temp);

    cout << "Enter new quantity (" << p.quantity << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.quantity = stoi(temp);

    cout << "Enter new unit name (" << p.unitName << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.unitName = temp;

    cout << "Enter new unit size (" << p.unitSize << "): ";
    getline(cin, temp);
    if (!temp.empty()) p.unitSize = stoi(temp);

    cout << "Enter new status (" << p.status << ") [1=Available, 0=Unavailable]: ";
    getline(cin, temp);
    if (!temp.empty()) {
        if (temp == "1")
            p.status = "Available";
        else if (temp == "0")
            p.status = "Unavailable";
        else
            cout << "Invalid input, keeping old status.\n";
    }

    saveProducts(products);
    cout << "Product updated successfully.\n";
}

// ลบสินค้า
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

// เมนูหลัก Manage Products
void manageItemsMenu() {
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
            case 0: cout << "Back to Admin Menu...\n"; break;
            default: cout << "Invalid option.\n";
        }

        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}
