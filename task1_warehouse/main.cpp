#include "warehouse.h"

using namespace std;

int main() {
    initWarehouse();
    cout << "Учет товаров на складе" << endl;
    cout << "Стеллажи: 01-15, секции: 1-3, полки: 1-5" << endl;

    
    string line;
    while (true) {
        cout << "\n>>> ";
        getline(cin, line);
        
        if (line == "EXIT" || line == "exit") {
            cout << "Программа завершена" << endl;
            break;
        }
        
        processCommand(line);
    }
    
    return 0;
}