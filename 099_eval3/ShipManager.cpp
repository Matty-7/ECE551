#include "ShipManager.hpp"
#include "Ship.hpp"
#include <stdint.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

bool ShipManager::loadShipsFromFile(const std::string & filename) {
  std::ifstream infile(filename.c_str());
  if (!infile) {
    std::cerr << "There is an error during opening the file: " << filename << std::endl;
    return false;
  }

  // Use a set to check for duplicates
  std::set<std::string> shipNames;
  std::string line;
  while (std::getline(infile, line)) {
    Ship ship;
    if (!parseShipLine(line, ship)) {
      std::cerr << "There is an error during parsing the line: " << line << std::endl;
      return false;
    }
    if (!shipNames.insert(ship.name).second) {
      std::cerr << "There is a duplicate ship name: " << ship.name << std::endl;
      return false;
    }
    std::string route = "(" + ship.source + " -> " + ship.destination + ")";
    routeCapacities[route] += ship.capacity;
    ships.push_back(ship);
  }
  return true;
}

std::vector<Ship>& ShipManager::getShips() {
    return ships;
}

bool ShipManager::parseShipLine(const std::string & line, Ship & ship) {
    std::istringstream iss(line);
    std::string segment;
    std::vector<std::string> segments;

    while (std::getline(iss, segment, ':')) {
        segments.push_back(segment);
    }

    if (segments.size() < 5)
        return false;

    ship.name = segments[0];

    // Parse type info from segment[1]
    std::istringstream typeInfo(segments[1]);
    std::string typeSegment;
    std::vector<std::string> typeSegments;
    
    while (std::getline(typeInfo, typeSegment, ',')) {
        if (!typeSegment.empty()) {
            typeSegments.push_back(typeSegment);
        }
    }

    if (typeSegments.empty())
        return false;

    // Parse slots (second element in type info)
    if (typeSegments.size() > 1) {
        std::istringstream slotsStream(typeSegments[1]);
        unsigned int slots;
        if (!(slotsStream >> slots)) {
            return false;
        }
        ship.slots = slots;
    }

    // Parse hazmat capabilities (remaining elements in type info)
    for (size_t i = 2; i < typeSegments.size(); ++i) {
        ship.hazmatCapabilities.push_back(typeSegments[i]);
    }

    ship.source = segments[2];
    ship.destination = segments[3];

    // Parse capacity
    std::istringstream capacityStream(segments[4]);
    uint64_t capacity;
    if (!(capacityStream >> capacity)) {
        return false;
    }
    ship.capacity = capacity;

    return true;
}

void ShipManager::printRouteCapacities() const {
  // Sort the routes by their names
  std::vector<std::pair<std::string, uint64_t> > sortedRoutes(routeCapacities.begin(),
                                                              routeCapacities.end());
  std::sort(sortedRoutes.begin(), sortedRoutes.end());

  for (std::vector<std::pair<std::string, uint64_t> >::const_iterator it =
           sortedRoutes.begin();
       it != sortedRoutes.end();
       ++it) {
    std::cout << it->first << " has total capacity " << it->second << std::endl;
  }
}

void ShipManager::printShipDetails() const {
    for (std::vector<Ship>::const_iterator it = ships.begin(); it != ships.end(); ++it) {
        const Ship& ship = *it;
        std::cout << "The Container Ship " << ship.name << "(" << ship.usedCapacity 
                  << "/" << ship.capacity << ") is carrying : " << std::endl;
        
        for (std::vector<Cargo>::const_iterator cargo = ship.loadedCargo.begin();
             cargo != ship.loadedCargo.end(); ++cargo) {
            std::cout << "  " << cargo->name << "(" << cargo->weight << ")" << std::endl;
        }
        
        std::cout << "  (" << (ship.slots - ship.loadedCargo.size()) 
                  << ") slots remain" << std::endl;
    }
}
