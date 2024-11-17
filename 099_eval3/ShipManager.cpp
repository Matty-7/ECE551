#include "ShipManager.hpp"

#include <algorithm>
<<<<<<< HEAD
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
=======
#include <stdint.h>
>>>>>>> d17a2fd7a96a5313075b0f9744f5993e7853dbe0

bool ShipManager::loadShipsFromFile(const std::string & filename) {
  std::ifstream infile(filename.c_str());
  if (!infile) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return false;
  }

  // Use a set to check for duplicates
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

<<<<<<< HEAD
  // Convert capacity from string to uint64_t
  std::istringstream capacityStream(segments[4]);
  uint64_t capacity;
  if (!(capacityStream >> capacity)) {
    return false;
  }
  ship.capacity = capacity;
=======
    // Convert capacity from string to uint64_t using stringstream
    std::istringstream capacityStream(segments[4]);
    uint64_t capacity;
    if (!(capacityStream >> capacity)) {
        return false;
    }
    ship.capacity = capacity;
>>>>>>> d17a2fd7a96a5313075b0f9744f5993e7853dbe0

  return true;
}

void ShipManager::printRouteCapacities() const {
  // Sort the routes by their names
  std::vector<std::pair<std::string, uint64_t> > sortedRoutes(routeCapacities.begin(),
                                                              routeCapacities.end());
  std::sort(sortedRoutes.begin(), sortedRoutes.end());

<<<<<<< HEAD
  for (const auto & route : sortedRoutes) {
    std::cout << route.first << " has total capacity " << route.second << std::endl;
  }
=======
    for (std::vector<std::pair<std::string, uint64_t> >::const_iterator it = sortedRoutes.begin();
         it != sortedRoutes.end(); ++it) {
        std::cout << it->first << " has total capacity " << it->second << std::endl;
    }
>>>>>>> d17a2fd7a96a5313075b0f9744f5993e7853dbe0
}
