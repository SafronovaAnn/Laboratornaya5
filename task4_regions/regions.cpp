#include "regions.h"
#include <iostream>

// Определение глобальных контейнеров
std::map<std::string, std::string> regionToCenter;
std::map<std::string, std::string> centerToRegion;

// Создание региона или изменение его центра (если это допустимо)
void handleChange(const std::string& region, const std::string& center) {
    // Проверка 1: Создан ли уже такой регион
    if (regionToCenter.find(region) != regionToCenter.end()) {
        std::cout << "Ошибка: Регион " << region << " уже создан\n"; 
        return;
    }

    // Проверка 2: Является ли город уже центром какого-то другого региона
    if (centerToRegion.find(center) != centerToRegion.end()) {
        std::cout << "Ошибка: " << center << " уже является административным центром другого региона\n"; 
        return;
    }

    // Добавление новой взаимно-однозначной связи
    regionToCenter[region] = center;
    centerToRegion[center] = region;
    std::cout << "Новый регион " << region << " с административным центром " << center << "\n"; 
}

// Переименование существующего административного центра
void handleRename(const std::string& oldCenter, const std::string& newCenter) {
    // Проверка 1: Совпадение старого и нового названия
    if (oldCenter == newCenter) {
        std::cout << "Ошибка: Нельзя переименовать " << oldCenter << " в то же название\n"; 
        return;
    }

    // Проверка 2: Существует ли переименовываемый старый центр
    auto itOld = centerToRegion.find(oldCenter);
    if (itOld == centerToRegion.end()) {
        std::cout << "Ошибка: Административный центр " << oldCenter << " не найден\n"; 
        return;
    }

    // Проверка 3: Не занято ли новое название центра другим регионом
    if (centerToRegion.find(newCenter) != centerToRegion.end()) {
        std::cout << "Ошибка: " << newCenter << " уже является административным центром другого региона\n"; 
        return;
    }

    // Извлекаем имя региона, привязанного к старому названию города
     std::string region = (*itOld).second;

    // Удаляем устаревшую запись из карты центров
    centerToRegion.erase(itOld);

    // Перезаписываем обновленные связи в обе карты
    centerToRegion[newCenter] = region;
    regionToCenter[region] = newCenter;

    std::cout << "Административный центр " << oldCenter << " переименован в административный центр " << newCenter << "\n"; 
}

// Поиск информации об административном центре региона
void handleAbout(const std::string& region) {
    auto it = regionToCenter.find(region);
    if (it == regionToCenter.end()) {
        std::cout << "Ошибка: Регион " << region << " не найден\n"; 
        return;
    }
    std::cout << "Регион " << region << " имеет административный центр " << it->second << "\n"; 
}

// Вывод всего справочника регионов
void handleAll() {
    if (regionToCenter.empty()) {
        std::cout << "Справочник пуст.\n";
        return;
    }

    bool first = true;
    for (const auto& [region, center] : regionToCenter) {
        if (!first) {
            std::cout << ", "; 
        }
        std::cout << region << " – " << center; 
        first = false;
    }
    std::cout << "\n";
}