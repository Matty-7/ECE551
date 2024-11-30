#include "ShipManager.hpp"
#include "ContainerShip.hpp"
#include "TankerShip.hpp"
#include "AnimalShip.hpp"

#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <cstdlib>

ShipManager::~ShipManager() {
    // 删除所有分配的船只对象，防止内存泄漏
    for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); ++it) {
        delete *it;
    }
}

bool ShipManager::loadShipsFromFile(const std::string & filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // 用于检测重复的船名
    std::set<std::string> shipNames;
    std::string line;
    while (std::getline(infile, line)) {
        Ship * ship = NULL;
        if (!parseShipLine(line, ship)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            delete ship;
            return false;
        }
        if (!shipNames.insert(ship->name).second) {
            std::cerr << "Duplicate ship name: " << ship->name << std::endl;
            delete ship;
            return false;
        }
        ships.push_back(ship);

        // 更新航线的总容量
        std::string route = "(" + ship->source + " -> " + ship->destination + ")";
        routeCapacities[route] += ship->capacity;
    }
    return true;
}

std::vector<Ship*>& ShipManager::getShips() {
    return ships;
}

void ShipManager::printRouteCapacities() const {
    // 按照航线名称排序并打印
    std::vector<std::pair<std::string, uint64_t> > sortedRoutes(routeCapacities.begin(),
                                                                routeCapacities.end());
    std::sort(sortedRoutes.begin(), sortedRoutes.end());

    for (std::vector<std::pair<std::string, uint64_t> >::const_iterator it = sortedRoutes.begin();
         it != sortedRoutes.end();
         ++it) {
        std::cout << it->first << " has total capacity " << it->second << std::endl;
    }
}

void ShipManager::printShipDetails() const {
    for (std::vector<Ship*>::const_iterator it = ships.begin(); it != ships.end(); ++it) {
        (*it)->printShipDetails();
    }
}

bool ShipManager::parseShipLine(const std::string & line, Ship *& ship) {
    std::istringstream iss(line);
    std::string segment;
    std::vector<std::string> segments;

    // 使用 ':' 分割行
    while (std::getline(iss, segment, ':')) {
        segments.push_back(segment);
    }

    if (segments.size() < 5) {
        return false;
    }

    // 提取公共属性
    std::string name = segments[0];
    std::string typeInfo = segments[1];
    std::string source = segments[2];
    std::string destination = segments[3];
    std::string capacityStr = segments[4];

    // 解析容量
    uint64_t capacity = 0;
    std::istringstream capacityStream(capacityStr);
    if (!(capacityStream >> capacity)) {
        return false;
    }

    // 解析类型信息
    std::istringstream typeStream(typeInfo);
    std::string type;
    std::getline(typeStream, type, ',');

    if (type == "Container") {
        // 创建 ContainerShip 实例
        ContainerShip * containerShip = new ContainerShip();

        // 解析 slots
        std::string slotsStr;
        if (!std::getline(typeStream, slotsStr, ',')) {
            delete containerShip;
            return false;
        }
        std::istringstream slotsStream(slotsStr);
        unsigned int slots = 0;
        if (!(slotsStream >> slots)) {
            delete containerShip;
            return false;
        }
        containerShip->slots = slots;

        // 解析 hazmatCapabilities
        std::string hazmat;
        while (std::getline(typeStream, hazmat, ',')) {
            containerShip->hazmatCapabilities.push_back(hazmat);
        }

        // 设置公共属性
        containerShip->name = name;
        containerShip->source = source;
        containerShip->destination = destination;
        containerShip->capacity = capacity;
        containerShip->usedCapacity = 0;

        ship = containerShip;
    }
    else if (type == "Tanker") {
        // 创建 TankerShip 实例
        TankerShip * tankerShip = new TankerShip();

        // 解析 minTemp
        std::string minTempStr;
        if (!std::getline(typeStream, minTempStr, ',')) {
            delete tankerShip;
            return false;
        }
        std::istringstream minTempStream(minTempStr);
        int minTemp = 0;
        if (!(minTempStream >> minTemp)) {
            delete tankerShip;
            return false;
        }
        tankerShip->minTemp = minTemp;

        // 解析 maxTemp
        std::string maxTempStr;
        if (!std::getline(typeStream, maxTempStr, ',')) {
            delete tankerShip;
            return false;
        }
        std::istringstream maxTempStream(maxTempStr);
        int maxTemp = 0;
        if (!(maxTempStream >> maxTemp)) {
            delete tankerShip;
            return false;
        }
        tankerShip->maxTemp = maxTemp;

        // 解析 numTanks
        std::string numTanksStr;
        if (!std::getline(typeStream, numTanksStr, ',')) {
            delete tankerShip;
            return false;
        }
        std::istringstream numTanksStream(numTanksStr);
        unsigned int numTanks = 0;
        if (!(numTanksStream >> numTanks)) {
            delete tankerShip;
            return false;
        }
        tankerShip->numTanks = numTanks;

        // 检查总容量是否是油舱数量的整数倍
        if (capacity % numTanks != 0) {
            std::cerr << "Total capacity is not a multiple of the number of tanks for ship: " << name << std::endl;
            delete tankerShip;
            return false;
        }

        // 初始化油舱容量
        unsigned long tankCapacity = capacity / numTanks;
        tankerShip->tankCapacities.assign(numTanks, 0);
        tankerShip->tankCargoTypes.assign(numTanks, "");

        // 解析 hazmatCapabilities
        std::string hazmat;
        while (std::getline(typeStream, hazmat, ',')) {
            tankerShip->hazmatCapabilities.push_back(hazmat);
        }

        // 设置公共属性
        tankerShip->name = name;
        tankerShip->source = source;
        tankerShip->destination = destination;
        tankerShip->capacity = capacity;
        tankerShip->usedCapacity = 0;

        ship = tankerShip;
    }
    else if (type == "Animals") {
        // 创建 AnimalShip 实例
        AnimalShip * animalShip = new AnimalShip();

        // 解析 smallEnoughThreshold
        std::string thresholdStr;
        if (!std::getline(typeStream, thresholdStr, ',')) {
            delete animalShip;
            return false;
        }
        std::istringstream thresholdStream(thresholdStr);
        unsigned int threshold = 0;
        if (!(thresholdStream >> threshold)) {
            delete animalShip;
            return false;
        }
        animalShip->smallEnoughThreshold = threshold;

        // 设置公共属性
        animalShip->name = name;
        animalShip->source = source;
        animalShip->destination = destination;
        animalShip->capacity = capacity;
        animalShip->usedCapacity = 0;
        animalShip->hasRoamer = false;

        ship = animalShip;
    }
    else {
        std::cerr << "Unknown ship type: " << type << std::endl;
        return false;
    }

    return true;
}
