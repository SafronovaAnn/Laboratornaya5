#include "queue_system.h"
#include <iostream>

// Определение глобальных переменных
std::vector<Patient> inputQueue;
std::vector<Window> windows;
int ticketCounter = 1;

// Инициализация системы перед началом работы
void initQueueSystem(int windowsCount) {
    ticketCounter = 1;

    // Создаем заданное количество окон
    for (int i = 0; i < windowsCount; ++i) {
        windows.push_back(Window());
    }
}

// Постановка посетителя в очередь
void handleEnqueue(int duration) {
    if (duration <= 0) {
        std::cout << "Ошибка: Время приема должно быть больше 0.\n";
        return;
    }

    // Форматируем номер талона: Т + три цифры с ведущими нулями (T001, T002...)
    std::string ticket = "T";
    if (ticketCounter < 10) ticket += "00";
    else if (ticketCounter < 100) ticket += "0";
    ticket += std::to_string(ticketCounter);

    // Добавляем посетителя в общую очередь
    Patient p = { ticket, duration };
    inputQueue.push_back(p);

    std::cout << ticket << std::endl;
    ticketCounter++; // Увеличиваем счетчик для следующего талона
}

// Распределение очереди по окнам
void handleDistribute() {
    if (inputQueue.empty()) {
        std::cout << "Ошибка: Очередь пуста. Некого распределять.\n";
        return;
    }

    // Распределяем каждого посетителя из очереди
    for (const auto& patient : inputQueue) {
        size_t bestWindowIdx = 0;
        int minTime = windows[0].totalMinutes;

        // Ищем окно с минимальной текущей загрузкой
        for (size_t i = 1; i < windows.size(); ++i) {
            if (windows[i].totalMinutes < minTime) {
                minTime = windows[i].totalMinutes;
                bestWindowIdx = i;
            }
        }

        // Направляем посетителя в выбранное окно
        windows[bestWindowIdx].totalMinutes += patient.duration;
        windows[bestWindowIdx].tickets.push_back(patient.ticket);
    }

    // Выводим результаты работы окон
    int windowNum = 1;
    for (const auto& window : windows) {
        std::cout << "Окно " << windowNum << " (" << window.totalMinutes << " минут): ";
        
        if (window.tickets.empty()) {
            std::cout << "нет посетителей";
        } else {
            bool first = true;
            for (const auto& t : window.tickets) {
                if (!first) std::cout << ", ";
                std::cout << t;
                first = false;
            }
        }
        std::cout << std::endl;
        windowNum++;
    }

    // Очищаем входную очередь, так как все посетители распределены
    inputQueue.clear();
}
