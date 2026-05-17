#include "regions.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::cout << "Cправочник регионов России\n>>> ";
    int requestsCount = 0;
    std::cout << "Введите количество запросов (N):\n>>> "; 
    if (!(std::cin >> requestsCount) || requestsCount <= 0) {
        std::cout << "Некорректное количество запросов.\n";
        return 0;
    }

    // Избавляемся от остаточного символа перевода строки '\n' в буфере потока после cin
    std::string dummy;
    std::getline(std::cin, dummy);

    std::string inputLine;
    
    // Выполняем ровно N успешных команд
    for (int i = 0; i < requestsCount; ++i) {
        std::cout << ">>> ";
        if (!std::getline(std::cin, inputLine)) {
            break;
        }

        // Если введена пустая строка, пропускаем ее без уменьшения счетчика шагов цикла
        if (inputLine.empty()) {
            --i;
            continue;
        }

        // Парсинг строки ввода
        std::stringstream ss(inputLine);
        std::string command;
        ss >> command;

        if (command == "CHANGE") { 
            std::string region, center;
            if (ss >> region >> center) {
                handleChange(region, center);
            } else {
                std::cout << "Ошибка: Неверный формат. Ожидалось: CHANGE <регион> <центр>\n";
                --i; // Не считаем ошибочный ввод за выполненный запрос
            }
        } 
        else if (command == "RENAME") { 
            std::string oldCenter, newCenter;
            if (ss >> oldCenter >> newCenter) {
                handleRename(oldCenter, newCenter);
            } else {
                std::cout << "Ошибка: Неверный формат. Ожидалось: RENAME <старый_центр> <новый_центр>\n";
                --i;
            }
        } 
        else if (command == "ABOUT") { 
            std::string region;
            if (ss >> region) {
                handleAbout(region);
            } else {
                std::cout << "Ошибка: Неверный формат. Ожидалось: ABOUT <регион>\n";
                --i;
            }
        } 
        else if (command == "ALL") { 
            handleAll();
        } 
        else if (command == "EXIT" || command == "exit") {
            std::cout << "Досрочное завершение программы.\n";
            break;
        }
        else {
            std::cout << "Ошибка: Неизвестная команда. Доступны: CHANGE, RENAME, ABOUT, ALL\n";
            --i;
        }
    }

    return 0;
}