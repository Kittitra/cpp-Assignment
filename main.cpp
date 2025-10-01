#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Product{
    string name,category;
    int cost_price , sell_price , quantity;
    string dueDate;
    bool available;
    
public :
    Product(const string& name, const string& category, const string& dueDate , int cost_price , int sell_price , int quantity)
    : name(name), category(category), dueDate(dueDate), available(true) , cost_price{cost_price} , sell_price{sell_price} , quantity{quantity} {}

    string getName() const { return name; }
    string getCategory() const { return category; }
    string getDueDate() const { return dueDate; }
    int getCostPrice() const { return cost_price; }
    int getSellPrice() const { return sell_price; }
    int getQuantity() const { return quantity; }
    bool isavailable() const { return available; }


    void setName(const string& name) { this->name = name; }
    void setCategory(const string& category) { this->category = category; }
    void setDueDate(const string& dueDate) { this->dueDate = dueDate; }
    void setCostPrice(int cost_price) { this->cost_price = cost_price; }
    void setSellPrice(int sell_price) { this->sell_price = sell_price; }
    void setQuantity(int quantity) { this->quantity = quantity; }

    void MarkAvailable() { available = true; }
    void MarkNotAvailable() { available = false; }
    
    void displayProduct(int index) const {
        cout << index << ". " << name 
             << " (" << (available ? "Available" : "Not Available") << ")"
             << " - Due : " << dueDate << endl;
        cout << "   Category : " << category << endl;
        cout << "   Cost_Price : " << cost_price << setfill(' ') << setw(5) << " Sell_Price : " << sell_price << endl;
        cout << "   Quantity : " << quantity << " Amount" << endl;
    }
};

void SaveProductToFile(const vector<Product>& products, const string& filename = "db/product.txt"){
    ofstream file(filename);
    if(!file){
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    for (const auto& p : products){
        // บันทึกข้อมูลสินค้า
        file << p.getName() << " | "
             << p.getCategory() << " | "
             << p.getDueDate() << " | "
             << p.getCostPrice() << " | "
             << p.getSellPrice() << " | "
             << p.getQuantity() << " | "
             << (p.isavailable() ? "1" : "0") << endl;  
    }
    file.close(); 
}

void LoadProductFromFile(vector<Product>& products, const string& filename = "db/product.txt"){
    ifstream file(filename);
    if(!file) return; // ถ้าไฟล์ไม่พบ ให้คืนค่าออกไป

    string name,category;
    int cost_price , sell_price , quantity;
    string dueDate;
    bool available;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string costStr, sellStr, qtyStr, availStr;
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, dueDate, '|');
        getline(ss, costStr, '|');
        getline(ss, sellStr, '|');
        getline(ss, qtyStr, '|');
        getline(ss, availStr, '|');

        int cost_price   = stoi(costStr);
        int sell_price   = stoi(sellStr);
        int quantity     = stoi(qtyStr);
        bool available   = (availStr == "1" || availStr == "true");

        Product prod(name, category, dueDate, cost_price, sell_price, quantity);
        if (!available) prod.MarkNotAvailable();
        products.push_back(prod);

    }
    file.close();
}

void showMenu() {
    cout << setfill('=') << setw(30) << "" << endl;
    cout << setfill(' ') << setw(20) << " Product Manement " << endl;
    cout << setfill('=') << setw(30) << "" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Edit Product" << endl;
    cout << "3. Delete Product" << endl;
    cout << "4. Show Products" << endl;
    cout << "5. Mark Product as Available" << endl;
    cout << "6. Mark Product as Not Available" << endl;
    cout << "7. Return" << endl;
    cout << setfill('=') << setw(30) << "" << endl;
    cout << "Enter choice : ";
}

void AddProduct(vector<Product> & products) {
    string name, category, dueDate;
    int cost_price , sell_price , quantity;
    cin.ignore();
    cout << "Enter product name: ";
    getline(cin, name);
    cout << "Enter product category: ";
    getline(cin, category);
    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, dueDate);
    cout << "Enter cost price: ";
    cin >> cost_price;
    cout << "Enter sell price: ";
    cin >> sell_price;
    cout << "Enter quantity: ";
    cin >> quantity;
    products.emplace_back(name, category, dueDate , cost_price , sell_price , quantity);
    SaveProductToFile(products);
    cout << "Product added successfully!" << endl;
}

void displayProducts(const vector<Product>& products) {
    if (products.empty()) {
        cout << "No products to display!" << endl;
        return;
    }
    cout << "Product List:" << endl;
    for (size_t i = 0; i < products.size(); ++i) {
        products[i].displayProduct(i + 1);
    }
}

void deleteProduct(vector<Product>& products) {
    if (products.empty()) {
        cout << "No products to delete!" << endl;
        return;
    }
    displayProducts(products);
    int num;
    cout << "Enter product number to delete: ";
    cin >> num;
    if (num >= 1 && num <= products.size()) {
        products.erase(products.begin() + num - 1);
        cout << "Product deleted successfully!" << endl;
        SaveProductToFile(products);
    } else {
        cout << "Invalid product number!" << endl;
    }
}

void markProductAvailable(vector<Product>& products) {
    if (products.empty()) {
        cout << "No products to mark!" << endl;
        return;
    }
    displayProducts(products);
    int num;
    cout << "Enter product number to mark as Available: ";
    cin >> num;
    if (num >= 1 && num <= products.size()) {
        products[num-1].MarkAvailable();
        cout << "Product marked as Available!" << endl;
    } else {
        cout << "Invalid product number!" << endl;
    }
}

void markProductNotAvailable(vector<Product>& products) {
    if (products.empty()) {
        cout << "No products to mark!" << endl;
        return;
    }
    displayProducts(products);
    int num;
    cout << "Enter product number to mark as Not Available: ";
    cin >> num;
    if (num >= 1 && num <= products.size()) {
        products[num-1].MarkNotAvailable();
        cout << "Product marked as Not Available!" << endl;
    } else {
        cout << "Invalid product number!" << endl;
    }
}

void editProduct(vector<Product>& products) {
    if (products.empty()) {
        cout << "No products to edit!" << endl;
        return;
    }
    displayProducts(products);
    int num;
    cout << "Enter product number to edit: ";
    cin >> num;
    if (num >= 1 && num <= products.size()) {
        cin.ignore();
        string name, category, dueDate;
        int cost_price , sell_price , quantity;
        cout << "Enter ne= product name: ";
        getline(cin, name);
        cout << "Enter new product category: ";
        getline(cin, category);
        cout << "Enter new due date (YYYY-MM-DD): ";
        getline(cin, dueDate);
        cout << "Enter new cost price: ";
        cin >> cost_price;
        cout << "Enter new sell price: ";
        cin >> sell_price;
        cout << "Enter new quantity: ";
        cin >> quantity;

        products[num - 1].setName(name);
        products[num - 1].setCategory(category);
        products[num - 1].setDueDate(dueDate);
        products[num - 1].setCostPrice(cost_price);
        products[num - 1].setSellPrice(sell_price);
        products[num - 1].setQuantity(quantity);

        cout << "Product edited successfully!" << endl;
        SaveProductToFile(products);
    } else {
        cout << "Invalid product number!" << endl;
    }
}

int main(){
    vector<Product> products;

    LoadProductFromFile(products); // โหลดข้อมูลจากไฟล์ตอนเริ่มโปรแกรม

    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                AddProduct(products);
                break;
            case 2:
                editProduct(products);
                break;
            case 3:
                deleteProduct(products);
                break;
            case 4:
                displayProducts(products);
                break;
            case 5:
                markProductNotAvailable(products);
                break;
            case 6:
                markProductAvailable(products);
                break;
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);
    return 0;
}