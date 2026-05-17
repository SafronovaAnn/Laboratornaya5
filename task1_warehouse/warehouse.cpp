#include "warehouse.h"

using namespace std;

map<string, Cell> warehouse;

void initWarehouse() {
    // Генерация адресов
    vector<char> zones = {'A', 'B'};
    
    for (char zone : zones) {
        for (int rack = 1; rack <= RACKS; rack++) {
            for (int section = 1; section <= SECTIONS; section++) {
                for (int shelf = 1; shelf <= SHELVES; shelf++) {
                    string addr;
                    addr += zone;
                    // Стеллаж: всегда 2 цифры
                    if (rack < 10) addr += "0";
                    addr += to_string(rack);
                    addr += to_string(section);
                    addr += to_string(shelf);
                    warehouse[addr] = {"", 0};
                }
            }
        }
    }
    
    // Для отладки - выводим количество адресов
    cout << "Создано " << warehouse.size() << " ячеек" << endl;
}

bool isValidAddress(const string& addr) {
    if (addr.length() != 5) return false;
    
    char zone = addr[0];
    if (zone != 'A' && zone != 'B') return false;
    
    string rackStr = addr.substr(1, 2);

    int rack;
    try {
        rack = stoi(rackStr);
    } catch (...) {
        return false;   // если не число - адрес неверный
    }

    if (rack < 1 || rack > RACKS) return false;
    
    int section = addr[3] - '0';
    if (section < 1 || section > SECTIONS) return false;
    
    int shelf = addr[4] - '0';
    if (shelf < 1 || shelf > SHELVES) return false;
    
    return true;
}

void handleAdd(const string& product, int qty, const string& addr) {
    if (!isValidAddress(addr)) {
        cout << "Ошибка: Неверный адрес " << addr << endl;
        return;
    }
    
    Cell& cell = warehouse[addr];
    
    if (!cell.name.empty() && cell.name != product) {
        cout << "Ошибка: Ячейка " << addr << " занята товаром " << cell.name << endl;
        return;
    }
    
    if (cell.quantity + qty > MAX_CELL) {
        cout << "Ошибка: Превышена вместимость (максимум " << MAX_CELL << ")" << endl;
        return;
    }
    
    if (cell.name.empty()) {
        cell.name = product;
    }
    cell.quantity += qty;
    
    cout << "Добавлено " << qty << " " << product << " в " << addr << endl;
}

void handleRemove(const string& product, int qty, const string& addr) {
    if (!isValidAddress(addr)) {
        cout << "Ошибка: Неверный адрес " << addr << endl;
        return;
    }
    
    Cell& cell = warehouse[addr];
    
    if (cell.name != product || cell.quantity == 0) {
        cout << "Ошибка: Товар " << product << " не найден в ячейке " << addr << endl;
        return;
    }
    
    if (cell.quantity < qty) {
        cout << "Ошибка: Недостаточно товаров для удаления" << endl;
        return;
    }
    
    cell.quantity -= qty;
    
    cout << "Удалено " << qty << " " << product;
    if (cell.quantity > 0) {
        cout << " (остаток: " << cell.quantity << ")" << endl;
    } else {
        cout << " (ячейка освобождена)" << endl;
        cell.name = "";
    }
}

void handleInfo() {
    int totalItems = 0;
    int zoneAItems = 0;
    int zoneBItems = 0;
    int cellsPerZone = (RACKS * SECTIONS * SHELVES);
    int maxZoneCapacity = cellsPerZone * MAX_CELL;
    int maxTotalCapacity = cellsPerZone * ZONES * MAX_CELL;
    
    vector<string> filled;
    vector<string> empty;
    
    for (const auto& [addr, cell] : warehouse) {
        if (cell.quantity > 0) {
            totalItems += cell.quantity;
            if (addr[0] == 'A') zoneAItems += cell.quantity;
            if (addr[0] == 'B') zoneBItems += cell.quantity;
            filled.push_back(addr + ": " + cell.name + " (" + to_string(cell.quantity) + ")");
        } else {
            empty.push_back(addr);
        }
    }
    
    cout << fixed << setprecision(2);
    cout << "----------------------------------------" << endl;
    cout << "Загруженность склада: " << (double)totalItems / maxTotalCapacity * 100 << "%" << endl;
    cout << "Загруженность зоны A: " << (double)zoneAItems / maxZoneCapacity * 100 << "%" << endl;
    cout << "Загруженность зоны B: " << (double)zoneBItems / maxZoneCapacity * 100 << "%" << endl;
    
    cout << "\nЗаполненные ячейки:" << endl;
    if (filled.empty()) {
        cout << "  (нет)" << endl;
    } else {
        for (const auto& s : filled) {
            cout << "  " << s << endl;
        }
    }
    
    cout << "\nПустые ячейки:" << endl;
    if (empty.empty()) {
        cout << "  (нет)" << endl;
    } else {
        cout << "  ";
        for (size_t i = 0; i < empty.size() && i < 20; i++) {
            cout << empty[i];
            if (i < 19 && i < empty.size() - 1) cout << ", ";
        }
        if (empty.size() > 20) {
            cout << "... и еще " << (empty.size() - 20) << " ячеек";
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
}

void processCommand(const string& line) {
    stringstream ss(line);
    string cmd;
    ss >> cmd;
    
    if (cmd == "ADD") {
        string product, addr;
        int qty;
        if (ss >> product >> qty >> addr) {
            handleAdd(product, qty, addr);
        } else {
            cout << "Формат: ADD <товар> <количество> <адрес>" << endl;
        }
    }
    else if (cmd == "REMOVE") {
        string product, addr;
        int qty;
        if (ss >> product >> qty >> addr) {
            handleRemove(product, qty, addr);
        } else {
            cout << "Формат: REMOVE <товар> <количество> <адрес>" << endl;
        }
    }
    else if (cmd == "INFO") {
        handleInfo();
    }
    else {
        cout << "Неизвестная команда" << endl;
    }
}