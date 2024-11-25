#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include "Ship.hpp"

struct Ship {
    std::string name;
    std::string source;
    std::string destination;
    uint64_t capacity;
};

class ShipManager {
 public:
  bool loadShipsFromFile(const std::string & filename);
  void printRouteCapacities() const;
  std::vector<Ship>& getShips();
  void printShipDetails() const;

 private:
  std::vector<Ship> ships;

  bool parseShipLine(const std::string & line, Ship & ship);
  std::map<std::string, uint64_t> routeCapacities;
};

#endif  // SHIPMANAGER_HPP
