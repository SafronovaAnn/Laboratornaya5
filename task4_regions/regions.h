#ifndef REGIONS_H
#define REGIONS_H

#include <string>
#include <map>

// Глобальные контейнеры ассоциативных связей 
extern std::map<std::string, std::string> regionToCenter; // регион -> центр
extern std::map<std::string, std::string> centerToRegion; // центр -> регион

// Объявления функций логики обработки справочника
void handleChange(const std::string& region, const std::string& center);
void handleRename(const std::string& oldCenter, const std::string& newCenter);
void handleAbout(const std::string& region);
void handleAll();

#endif // REGIONS_H