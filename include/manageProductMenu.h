#pragma once
#include <vector>
#include <string> 
#include "product.h"
using namespace std;

// ฟังก์ชันสำหรับจัดการสินค้า
bool manageProductsMenu();
void addProduct();
void editProduct();
void deleteProduct();
void showProducts();
void salesMenu();
void reportMenu(const string &userRole);
int Login();
bool showAdminMenu(string role);
bool showStaffMenu(string role);

// ฟังก์ชัน load/save product สำหรับใช้ใน StockMovement
std::vector<Product> loadProducts();
void saveProducts(const std::vector<Product>& products);
