#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Ship.hpp"

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
