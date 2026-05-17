#include "queue_system.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::setlocale(LC_ALL, "Russian");

    int windowsCount = 0;
    std::cout << "Введите количество окон:\n>>> ";
    if (!(std::cin >> windowsCount) || windowsCount <= 0) {
        std::cout << "Ошибка: Неверное количество окон.\n";
        return 0;
    }

    // Инициализируем систему электронных очередей
    initQueueSystem(windowsCount);

    // Очищаем буфер после cin, чтобы getline работал корректно
    std::string dummy;
    std::getline(std::cin, dummy);

    std::cout << "\nСистема электронной очереди" << std::endl;
    std::cout << "Доступные команды: ENQUEUE <минуты>, DISTRIBUTE, EXIT\n" << std::endl;

    std::string inputLine;

    // Обработка пользовательского ввода
    while (true) {
        std::cout << ">>> ";
        if (!std::getline(std::cin, inputLine)) {
            break;
        }

        if (inputLine.empty()) continue;
        if (inputLine == "EXIT" || inputLine == "exit") break;

        // Разбор строки ввода (парсинг)
        std::stringstream ss(inputLine);
        std::string command;
        ss >> command;

        if (command == "ENQUEUE") {
            int duration;
            if (ss >> duration) {
                // Передаем параметр в логический блок
                handleEnqueue(duration);
            } else {
                std::cout << "Ошибка: Неверный формат команды ENQUEUE. Пример: ENQUEUE 10" << std::endl;
            }
        } 
        else if (command == "DISTRIBUTE") {
            // Запуск логики распределения и вывода отчета
            handleDistribute();
        } 
        else {
            std::cout << "Ошибка: Неизвестная команда. Доступны: ENQUEUE, DISTRIBUTE" << std::endl;
        }
    }

    return 0;
}