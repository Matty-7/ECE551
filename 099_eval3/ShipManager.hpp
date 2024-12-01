#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Ship.hpp"
#include "avlmultimap03.hpp"

class ShipManager {
 public:
  ~ShipManager();
  bool loadShipsFromFile(const std::string & filename);
  void printRouteCapacities() const;
  std::vector<Ship*>& getShips();
  void printShipDetails() const;

  void loadShipsIntoMap(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap);

 private:
  std::vector<Ship*> ships;
  bool parseShipLine(const std::string & line, Ship *& ship);
  std::map<std::string, uint64_t> routeCapacities;
};

#endif  // SHIPMANAGER_HPP
