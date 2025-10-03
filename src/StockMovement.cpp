#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
#include "../include/product.h"
#include "../include/StockMovement.h"
#include "../include/manageProductMenu.h"   // ✅ เพิ่มมาเพื่อใช้ load/save Products
//ลบ quantity ผิดดันไปลบ unit size แทน
using namespace std;

const string STOCK_FILE = "../data/stock.txt";

// ───────────────────────────────
// บันทึก Stock Movement ลงไฟล์
// ───────────────────────────────
void saveStockMovement(const StockMovement& sm) {
    ofstream outfile(STOCK_FILE, ios::app);
    outfile << sm.productName << "|"
            << sm.movementType << "|"
            << sm.fullUnits << "|"
            << sm.loosePieces << "|"
            << sm.unitName << "|"
            << sm.unitSize << "|"
            << sm.remarks << "|"
            << sm.date << "\n";
}

// ───────────────────────────────
// แสดงวันที่ปัจจุบัน
// ───────────────────────────────
string currentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
    return string(buf);
}

// ───────────────────────────────
// อัปเดตจำนวนสินค้าใน products.txt
// ───────────────────────────────
void updateProductStock(const StockMovement& sm) {
    vector<Product> products = loadProducts();
    bool found = false;

    for (auto &p : products) {
        if (p.name == sm.productName) {
            found = true;

            // ปรับจำนวนสินค้าตาม movement
            if (sm.movementType == "IN") {
                p.fullUnits += sm.fullUnits;
                p.loosePieces += sm.loosePieces;
            }
            else if (sm.movementType == "OUT") {
                // ลบจากหน่วยเต็มก่อน ถ้าไม่พอให้ใช้ loosePieces
                int totalPieces = p.fullUnits * p.unitSize + p.loosePieces;
                int removePieces = sm.fullUnits * p.unitSize + sm.loosePieces;
                totalPieces -= removePieces;
                if (totalPieces < 0) totalPieces = 0;

                p.fullUnits = totalPieces / p.unitSize;
                p.loosePieces = totalPieces % p.unitSize;
            }
            else if (sm.movementType == "ADJUST") {
                // ปรับเป็นจำนวนใหม่ตรงๆ
                p.fullUnits = sm.fullUnits;
                p.loosePieces = sm.loosePieces;
            }

            // ปรับสถานะสินค้า
            p.status = (p.fullUnits == 0 && p.loosePieces == 0) ? "Unavailable" : "Available";
            break;
        }
    }

    // ถ้าไม่เจอสินค้า และเป็นการรับเข้า (IN) → สร้างสินค้าใหม่
    if (!found && sm.movementType == "IN") {
        Product newP;
        newP.name = sm.productName;
        newP.category = "Uncategorized";  // หรือให้ user กรอกเพิ่ม
        newP.costPrice = 0;
        newP.sellPrice = 0;
        newP.fullUnits = sm.fullUnits;
        newP.loosePieces = sm.loosePieces;
        newP.unitName = sm.unitName;
        newP.unitSize = sm.unitSize;
        newP.status = "Available";
        products.push_back(newP);
    }

    saveProducts(products);
}


// ───────────────────────────────
// ฟังก์ชันเพิ่ม/เบิก/ปรับสต็อก
// ───────────────────────────────
void stockMovementMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== Stock Movements ===\n";
        cout << "1. Receive Stock (IN)\n";
        cout << "2. Issue Stock (OUT)\n";
        cout << "3. Adjust Stock\n";
        cout << "4. View Stock Movements\n";
        cout << "0. Back to Admin Menu\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1 || choice == 2 || choice == 3) {
            StockMovement sm;
            sm.movementType = (choice == 1 ? "IN" : (choice == 2 ? "OUT" : "ADJUST"));

            cout << "Product name: ";
            getline(cin, sm.productName);

            cout << "Full units: ";
            cin >> sm.fullUnits;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Loose pieces: ";
            cin >> sm.loosePieces;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Unit name: ";
            getline(cin, sm.unitName);

            cout << "Pieces per unit: ";
            cin >> sm.unitSize;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Remarks: ";
            getline(cin, sm.remarks);

            sm.date = currentDate();

            saveStockMovement(sm);
            updateProductStock(sm);

            cout << "Stock movement saved & product stock updated!\n";
        }
        else if (choice == 4) {
            ifstream infile(STOCK_FILE);
            string line;
            cout << "\n=== Stock Movements ===\n";
            cout << left << setw(5) << "No"
                << setw(12) << "Date"
                << setw(8) << "Type"
                << setw(20) << "Product"
                << setw(8) << "Full"
                << setw(8) << "Loose"
                << setw(8) << "Unit"
                << setw(15) << "Remarks" << endl;
            cout << string(84, '-') << endl;

            int count = 1;
            while (getline(infile, line)) {
                if (line.empty()) continue;
                    // แยกข้อมูลโดยใช้ | เป็นตัวแบ่ง
                    stringstream ss(line);
                    string productName, movementType, fullUnitsStr, loosePiecesStr, unitName, unitSizeStr, remarks, date;
                    getline(ss, productName, '|');
                    getline(ss, movementType, '|');
                    getline(ss, fullUnitsStr, '|');
                    getline(ss, loosePiecesStr, '|');
                    getline(ss, unitName, '|');
                    getline(ss, unitSizeStr, '|'); // เราอาจไม่ใช้ตอนแสดงก็ได้
                    getline(ss, remarks, '|');
                    getline(ss, date, '|');

                    cout << left << setw(5) << count
                            << setw(12) << date
                            << setw(8) << movementType
                            << setw(20) << productName
                            << setw(8) << fullUnitsStr
                            << setw(8) << loosePiecesStr
                            << setw(8) << unitName
                            << setw(15) << remarks
                            << endl;
                    count++;
            }
        }
        else if (choice == 0) {
            cout << "Back to Admin Menu...\n";
        }
        else {
            cout << "Invalid option!\n";
        }

        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}
