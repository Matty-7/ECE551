#include "ShipManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>

bool ShipManager::loadShipsFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // I use a set to check for duplicates
    std::set<std::string> shipNames;
    std::string line;
    while (std::getline(infile, line)) {
        Ship ship;
        if (!parseShipLine(line, ship)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            return false;
        }
        if (!shipNames.insert(ship.name).second) {
            std::cerr << "Duplicate ship name: " << ship.name << std::endl;
            return false;
        }
        std::string route = "(" + ship.source + " -> " + ship.destination + ")";
        routeCapacities[route] += ship.capacity;
    }
    return true;
}

// It can parse a line from the ships file and fills in the Ship struct
bool ShipManager::parseShipLine(const std::string& line, Ship& ship) {
    std::istringstream iss(line);
    std::string segment;
    std::vector<std::string> segments;

    // It can split the line into segments by using ':' as the delimiter
    while (std::getline(iss, segment, ':')) {
        segments.push_back(segment);
    }
    // I need to check if there are 5 fields: Name, Type info, Source, Destination, and Capacity
    if (segments.size() != 5) return false;
    ship.name = segments[0];
    ship.source = segments[2];
    ship.destination = segments[3];
    
    std::istringstream capacityStream(segments[4]);
    uint64_t capacity;
    if (!(capacityStream >> capacity)) {
        return false; // Conversion failed
    }
    ship.capacity = capacity;

    return true;
}

void ShipManager::printRouteCapacities() const {
    // I sort the routes by their capacity
    std::vector<std::pair<std::string, uint64_t> > sortedRoutes(routeCapacities.begin(), routeCapacities.end());
    std::sort(sortedRoutes.begin(), sortedRoutes.end());

    for (std::vector<std::pair<std::string, uint64_t> >::const_iterator it = sortedRoutes.begin(); it != sortedRoutes.end(); ++it) {
        std::cout << it->first << " has total capacity " << it->second << std::endl;
    }
}
