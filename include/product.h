#pragma once
#include <string>

struct Product {
    std::string name;        // ชื่อสินค้า
    std::string category;    // ประเภทสินค้า
    double costPrice;        // ราคาทุน
    double sellPrice;        // ราคาขาย
    int fullUnits;           // จำนวนหน่วยเต็ม เช่น กี่แพ็ค กี่กล่อง
    int unitSize;            // จำนวนต่อหน่วย เช่น 1 แพ็ค = 12 ชิ้น
    int loosePieces;         // จำนวนชิ้นที่เหลือจากหน่วยที่ถูกแกะ
    std::string unitName;    // เช่น "แพ็ค" หรือ "กล่อง"
    std::string status;      // "Available" หรือ "Unavailable"
};
