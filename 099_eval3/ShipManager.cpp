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

  // Split the line into segments using ':' as the delimiter
  while (std::getline(iss, segment, ':')) {
    segments.push_back(segment);
  }

  // Check if there are 5 fields
  if (segments.size() != 5)
    return false;

  ship.name = segments[0];
  ship.source = segments[2];
  ship.destination = segments[3];

  // Convert capacity from string to uint64_t using stringstream
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
        std::cout << "Ship Name: " << ship.name << ", Source: " << ship.source
                  << ", Destination: " << ship.destination << ", Capacity: " << ship.capacity << std::endl;
    }
}
