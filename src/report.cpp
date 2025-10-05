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
    cout << "\n======== Product Report ========\n";
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

    map<string, double> dailySales, dailyCost, dailyProfit;
    map<string, double> monthlySales, monthlyCost, monthlyProfit;

    string line;
    double totalSalesAll = 0, totalCostAll = 0, totalProfitAll = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t dateStart = line.find('[');
        size_t dateEnd = line.find(']');
        if (dateStart == string::npos || dateEnd == string::npos) continue;

        string date = line.substr(dateStart + 1, dateEnd - dateStart - 1);
        string dayKey = date;
        string monthKey = date.substr(0, 7);

        size_t salePos = line.find("Sale:");
        size_t totalPos = line.find("Total=");
        if (salePos == string::npos || totalPos == string::npos) continue;

        string itemsPart = line.substr(salePos + 5, totalPos - (salePos + 5));

        stringstream ss(itemsPart);
        string item;
        double daySales = 0, dayCost = 0, dayProfit = 0;

        while (getline(ss, item, ',')) {
            if (item.empty()) continue;

            // ตัวอย่าง: bigRjx5@Sell=10@Cost=5@Profit=25
            size_t xPos = item.find('x');
            if (xPos == string::npos) continue;

            string name = item.substr(0, xPos);
            int qty = 0;
            double sell = 0, cost = 0, profit = 0;

            try {
                qty = stoi(item.substr(xPos + 1, item.find('@') - xPos - 1));
            } catch (...) { qty = 0; }

            size_t sellPos = item.find("Sell=");
            if (sellPos != string::npos)
                try { sell = stod(item.substr(sellPos + 5)); } catch (...) {}

            size_t costPos = item.find("Cost=");
            if (costPos != string::npos)
                try { cost = stod(item.substr(costPos + 5)); } catch (...) {}

            size_t profitPos = item.find("Profit=");
            if (profitPos != string::npos)
                try { profit = stod(item.substr(profitPos + 7)); } catch (...) {}
            else
                profit = (sell - cost) * qty;

            daySales += sell * qty;
            dayCost += cost * qty;
            dayProfit += profit;
        }

        dailySales[dayKey] += daySales;
        dailyCost[dayKey] += dayCost;
        dailyProfit[dayKey] += dayProfit;

        monthlySales[monthKey] += daySales;
        monthlyCost[monthKey] += dayCost;
        monthlyProfit[monthKey] += dayProfit;

        totalSalesAll += daySales;
        totalCostAll += dayCost;
        totalProfitAll += dayProfit;
    }

    cout << "\n=== Sales & Profit Report ===\n";

    cout << "\n------------------- Summary By Day -------------------\n";
    cout << left << setw(12) << "Date" 
         << setw(15) << "Sales(THB)"
         << setw(15) << "Cost(THB)"
         << setw(15) << "Profit(THB)" << endl;
    cout << string(57, '-') << endl;
    for (auto &d : dailySales) {
        cout << left << setw(12) << d.first
             << setw(15) << fixed << setprecision(2) << dailySales[d.first]
             << setw(15) << dailyCost[d.first]
             << setw(15) << dailyProfit[d.first] << endl;
    }

    cout << "\n------------------- Summary By Month -------------------\n";
    cout << left << setw(12) << "Month" 
         << setw(15) << "Sales(THB)"
         << setw(15) << "Cost(THB)"
         << setw(15) << "Profit(THB)" << endl;
    cout << string(57, '-') << endl;
    for (auto &m : monthlySales) {
        cout << left << setw(12) << m.first
             << setw(15) << fixed << setprecision(2) << monthlySales[m.first]
             << setw(15) << monthlyCost[m.first]
             << setw(15) << monthlyProfit[m.first] << endl;
    }

    cout << "\n==========================================================\n";
    cout << "Total Sales Overall : " << fixed << setprecision(2) << totalSalesAll << " THB\n";
    cout << "Total Cost Overall  : " << fixed << setprecision(2) << totalCostAll << " THB\n";
    cout << "Total Profit Overall: " << fixed << setprecision(2) << totalProfitAll << " THB\n";
    cout << "==========================================================\n";
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
        cout << "======== REPORT MENU ========\n";
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
