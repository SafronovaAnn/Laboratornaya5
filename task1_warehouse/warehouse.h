#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

// КОНФИГУРАЦИЯ ДЛЯ ВАРИАНТА 2
const int ZONES = 2;           // A, B
const int RACKS = 15;          // стеллажи 1-15
const int SECTIONS = 3;        // секции 1-3
const int SHELVES = 5;         // полки 1-5
const int MAX_CELL = 10;       // максимум 10 единиц

struct Cell {
    std::string name;
    int quantity;
};

void initWarehouse();
void handleAdd(const std::string& product, int qty, const std::string& addr);
void handleRemove(const std::string& product, int qty, const std::string& addr);
void handleInfo();
void processCommand(const std::string& line);

#endif