#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void DisplayStudent(string FN);

int main(){
    const string FileName = "restock.txt"; // กำหนดให้ลง file restock
    ifstream Infile;
    ofstream outfile;
    DisplayStudent(FileName); // Display รายงานออกทางหน้าจอ bro
    return 0;
}

// Function Show ข้อมูลออกทางหน้าจอ
void DisplayStudent(string FN){
    ifstream infile(FN.c_str(), ios_base::in);
    if(infile.is_open()){
        string Id, pro, type, note, created_by, created_at;
        int num;
        //Id = movement_id(ไอดีใน table:stock_movements) | pro = product(ชื่อสินค้า) | type = movement_type(ประเภทการเคลื่อนไหวของสินค้า)"in,out,adjust" 
        //num = qty_signed (บวก = เข้า, ลบ = ออก) | note = หมายเหตุ | created_by = สร้างโดย | created_at = สร้างตอนไหน
        
        string line(115,'-'); // กำหนด = ไป 115 ตัว ex"=================~~~~"
        int n = 0;
        cout << endl;
        cout << endl;
        cout << setfill(' ') << setw(68) << "Stock movement report\n";
        cout << line << endl; // show line =============
        cout << left << setw(16) << "     ID" << setw(16) << "Product" << setw(16) << "Type" << setw(16) << "Num"
        << setw(16) << "Note" << setw(16) << "Created By" << setw(16) << "Created At" << endl; // Navbar ตอน Show
        cout << line << endl; // show line =============
        
        while(infile >> Id >> pro >> type >> num >> note >> created_by >> created_at){
            //Id = movement_id(ไอดีใน table:stock_movements) | pro = product(ชื่อสินค้า) | type = movement_type(ประเภทการเคลื่อนไหวของสินค้า)"in,out,adjust" 
            //num = qty_signed (บวก = เข้า, ลบ = ออก) | note = หมายเหตุ | created_by = สร้างโดย | created_at = สร้างตอนไหน
            if(n == 5){
                cout << line << endl; // show line =============
                n = n - 5;
            }
            cout << "    " << setw(10) << Id << setw(18) << pro << setw(16) << type << setw(13) << num << setw(18) << note
            << setw(16) << created_by << setw(18) << created_at << endl;
            n = n + 1;
            // infile >> Id >> Name;
        }

        cout << line << endl;
        infile.close();
        char Wait;
        cin.get(Wait); // รอกด Enter
        cout << "Press Enter to continue"; // show comment
        cin.get(Wait); // รอกด Enter
    }
}