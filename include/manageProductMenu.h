#pragma once
#include <vector>
#include <string> 
#include "product.h"
using namespace std;

// ฟังก์ชันสำหรับจัดการสินค้า
void manageProductsMenu();
void addProduct();
void editProduct();
void deleteProduct();
void showProducts();
void salesMenu();
void reportMenu(const string &userRole);
int Login();
void showAdminMenu(string role);
void showStaffMenu(string role);

// ฟังก์ชัน load/save product สำหรับใช้ใน StockMovement
std::vector<Product> loadProducts();
void saveProducts(const std::vector<Product>& products);
