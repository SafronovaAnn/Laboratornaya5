#ifndef TRAM_ACTIONS_H
#define TRAM_ACTIONS_H

#include <string>
#include <map>
#include <vector>
#include <set>

// Структура для хранения маршрута трамвая
struct TramRoute {
    std::string name;
    std::vector<std::string> stops;
};

// Глобальные контейнеры для хранения данных
extern std::map<std::string, TramRoute> tramRoutes;

// Объявления функций
void handleCreateTram(const std::string& args);
void handleTramsInStop(const std::string& stopName);
void handleStopsInTram(const std::string& tramName);
void handleTrams();

#endif // TRAM_ACTIONS_H