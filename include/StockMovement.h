#ifndef STOCKMOVEMENT_H
#define STOCKMOVEMENT_H

#include <string>

struct StockMovement {
    std::string productName;   // ชื่อสินค้า
    std::string movementType;  // IN / OUT / ADJUST
    int fullUnits;             // จำนวนหน่วยเต็ม (กล่อง/แพ็ค)
    int loosePieces;           // จำนวนชิ้นที่หลุด
    std::string unitName;      // หน่วย เช่น แพ็ค, กล่อง
    int unitSize;              // จำนวนต่อหน่วย
    std::string remarks;       // หมายเหตุ
    std::string date;          // วันที่
};

// ประกาศฟังก์ชันที่ใช้ใน cpp
void stockMovementMenu();

#endif // STOCKMOVEMENT_H
