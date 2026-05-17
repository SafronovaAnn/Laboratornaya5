#ifndef QUEUE_SYSTEM_H
#define QUEUE_SYSTEM_H

#include <string>
#include <vector>

// Структура для представления посетителя в очереди
struct Patient {
    std::string ticket;
    int duration;       
};

// Структура для представления окна обслуживания
struct Window {
    int totalMinutes = 0;              
    std::vector<std::string> tickets; 
};

// Глобальные переменные (объявление)
extern std::vector<Patient> inputQueue;
extern std::vector<Window> windows;
extern int ticketCounter;

// Объявления функций логики
void initQueueSystem(int windowsCount);
void handleEnqueue(int duration);
void handleDistribute();

#endif // QUEUE_SYSTEM_H