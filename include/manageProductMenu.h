#pragma once
#include <vector>
#include "product.h"

// ฟังก์ชันสำหรับจัดการสินค้า
void manageProductsMenu();
void addProduct();
void editProduct();
void deleteProduct();
void showProducts();
void salesMenu();

// ฟังก์ชัน load/save product สำหรับใช้ใน StockMovement
std::vector<Product> loadProducts();
void saveProducts(const std::vector<Product>& products);
