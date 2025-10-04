#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "../include/product.h"
#include "../include/manageProductMenu.h"  // ต้องมี loadProducts()

using namespace std;

const string SALES_FILE = "../data/sales.txt";

struct SaleItem {
    string name;
    double price;
    int quantity;
    double subtotal;
};

// ─────────────────────────────
// ฟังก์ชันแสดงใบเสร็จ
// ─────────────────────────────
void printReceipt(const vector<SaleItem>& items, double total, double tax, double net, double cash, double change) {
    string line = "================================================\n";
    cout << "\n==================== RECEIPT ====================\n";
    cout << left << setw(20) << "Item" 
         << setw(10) << "Qty" 
         << setw(10) << "Price" 
         << setw(12) << "Subtotal" << endl;
    cout << string(49, '-') << endl;

    for (const auto& item : items) {
        cout << left << setw(20) << item.name
             << setw(10) << item.quantity
             << setw(10) << fixed << setprecision(2) << item.price
             << setw(12) << fixed << setprecision(2) << item.subtotal
             << endl;
    }

    cout << string(49, '-') << endl;
    cout << left << setw(35) << "Total:"     << right << setw(10) << total  << endl;
    cout << left << setw(35) << "Tax (7%):" << right << setw(10) << tax    << endl;
    cout << left << setw(35) << "Net:"      << right << setw(10) << net    << endl;
    cout << left << setw(35) << "Cash:"     << right << setw(10) << cash   << endl;
    cout << left << setw(35) << "Change:"   << right << setw(10) << change << endl;
    cout << line;
    cout << "Press Enter to continue...";
    cin.get();
}

// ─────────────────────────────
// ฟังก์ชันขายสินค้า
// ─────────────────────────────
void salesMenu() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products available to sell.\n";
        return;
    }

    vector<SaleItem> cart;

    // วนลูปเลือกสินค้า
    while (true) {
        system("cls");
        cout << "\n=== Product List ===\n";
        cout << left << setw(5) << "No" << setw(20) << "Product" << setw(10) << "Price" << setw(10) << "Status" << endl;
        cout << string(50, '-') << endl;
        for (size_t i = 0; i < products.size(); i++) {
            cout << left << setw(5) << (i+1)
                 << setw(20) << products[i].name
                 << setw(10) << products[i].sellPrice
                 << setw(10) << products[i].status
                 << endl;
        }

        int choice;
        cout << "\nEnter product number to add to cart (0 to finish): ";
        cin >> choice;

        if (choice == 0) break;  // ออกไปคิดเงิน
        if (choice < 1 || choice > (int)products.size()) {
            cout << "Invalid choice!\n";
            continue;
        }

        Product p = products[choice - 1];
        if (p.status == "Unavailable") {
            cout << "This product is unavailable.\n";
            continue;
        }

        int qty;
        cout << "Enter quantity: ";
        cin >> qty;

        SaleItem item;
        item.name = p.name;
        item.price = p.sellPrice;
        item.quantity = qty;
        item.subtotal = qty * p.sellPrice;
        cart.push_back(item);

        cout << "Added to cart: " << qty << " x " << p.name << endl;
    }

    if (cart.empty()) {
        cout << "No items selected.\n";
        return;
    }

    // คำนวณราคา
    double total = 0;
    for (auto &item : cart) total += item.subtotal;
    double tax = total * 0.07;  // ภาษี 7%
    double net = total + tax;

    // รับเงินลูกค้า
    double cash;
    do {
        cout << "\nTotal to pay: " << fixed << setprecision(2) << net << endl;
        cout << "Enter cash: ";
        cin >> cash;
        if (cash < net) cout << "Not enough cash. Try again.\n";
    } while (cash < net);

    double change = cash - net;

    // แสดงใบเสร็จ
    printReceipt(cart, total, tax, net, cash, change);

    // ✅ ดึงวันที่ปัจจุบัน
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char dateStr[20];
    sprintf(dateStr, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);

    // ✅ บันทึกลง sales.txt พร้อมวันที่
    ofstream outfile(SALES_FILE, ios::app);
    outfile << "[" << dateStr << "] Sale: ";
    for (auto &item : cart) {
        outfile << item.name << "x" << item.quantity << "@" << item.price << ",";
    }
    outfile << " Total=" << total << " Tax=" << tax << " Net=" << net 
            << " Cash=" << cash << " Change=" << change << "\n";
    outfile.close();

    cout << "\n✅ Sale recorded successfully on " << dateStr << "!\n";
}