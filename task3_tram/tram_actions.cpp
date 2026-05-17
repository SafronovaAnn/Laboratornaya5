#include "tram_actions.h"
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

// Определение глобальных контейнеров
map<string, TramRoute> tramRoutes;

// Создание трамвая
void handleCreateTram(const string& args) {
    stringstream ss(args);
    string tramName;
    int stopsCount;
    
    ss >> tramName >> stopsCount;
    
    // Проверка: существует ли уже такой трамвай
    if (tramRoutes.find(tramName) != tramRoutes.end()) {
        cout << "Ошибка: Трамвай с именем " << tramName << " уже создан" << endl;
        return;
    }
    
    // Проверка: количество остановок должно быть больше 1
    if (stopsCount <= 1) {
        cout << "Ошибка: Трамвай не может быть создан с одной остановкой" << endl;
        return;
    }
    
    vector<string> stops;
    
    for (int i = 0; i < stopsCount; ++i) {
        string stop;
        ss >> stop;
        if (stop.empty()) {
            cout << "Ошибка: Недостаточно названий остановок" << endl;
            return;
        }
        stops.push_back(stop);
    }
    
    // Проверка: нет одинаковых остановок подряд
    for (size_t i = 0; i < stops.size() - 1; ++i) {
        if (stops[i] == stops[i + 1]) {
            cout << "Ошибка: Трамвай не может быть создан с двумя одинаковыми остановками" << endl;
            return;
        }
    }
    
    tramRoutes[tramName] = {tramName, stops};
    cout << "Трамвай " << tramName << " создан" << endl;
}

// Вывод всех трамваев на остановке
void handleTramsInStop(const string& stopName) {
    vector<string> tramsOnStop;
    
    for (const auto& [tramName, route] : tramRoutes) {
        for (const auto& stop : route.stops) {
            if (stop == stopName) {
                tramsOnStop.push_back(tramName);
                break;
            }
        }
    }
    
    if (tramsOnStop.empty()) {
        cout << "Ошибка: Остановка " << stopName << " не найдена" << endl;
        return;
    }
    
    cout << "Трамвай на остановке " << stopName << ": ";
    for (size_t i = 0; i < tramsOnStop.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << tramsOnStop[i];
    }
    cout << endl;
}

// Вывод всех остановок трамвая
void handleStopsInTram(const string& tramName) {
    if (tramRoutes.find(tramName) == tramRoutes.end()) {
        cout << "Ошибка: Трамвай " << tramName << " не найден" << endl;
        return;
    }
    
    const TramRoute& route = tramRoutes[tramName];
    
    cout << "Остановки трамвая " << tramName << ": ";
    for (size_t i = 0; i < route.stops.size(); ++i) {
        if (i > 0) cout << " ";
        cout << route.stops[i];
    }
    cout << endl;
    
    // Вывод для каждой остановки, какие трамваи проезжают
    for (const auto& stop : route.stops) {
        vector<string> otherTrams;
        for (const auto& [otherTram, otherRoute] : tramRoutes) {
            if (otherTram == tramName) continue;
            for (const auto& otherStop : otherRoute.stops) {
                if (otherStop == stop) {
                    otherTrams.push_back(otherTram);
                    break;
                }
            }
        }
        
        cout << "Остановка " << stop << ": ";
        if (otherTrams.empty()) {
            cout << "-";
        } else {
            for (size_t i = 0; i < otherTrams.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << otherTrams[i];
            }
        }
        cout << endl;
    }
}

// Вывод всех трамваев
void handleTrams() {
    if (tramRoutes.empty()) {
        cout << "Ошибка: Трамваи не найдены" << endl;
        return;
    }
    
    for (const auto& [tramName, route] : tramRoutes) {
        cout << "Трамвай " << tramName << ": ";
        for (size_t i = 0; i < route.stops.size(); ++i) {
            if (i > 0) cout << " ";
            cout << route.stops[i];
        }
        cout << endl;
    }
}