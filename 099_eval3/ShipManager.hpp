#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <stdint.h>

#include <map>
#include <string>

class ShipManager {
 public:
  bool loadShipsFromFile(const std::string & filename);
  void printRouteCapacities() const;

 private:
  struct Ship {
    std::string name;
    std::string source;
    std::string destination;
    uint64_t capacity;
  };

  bool parseShipLine(const std::string & line, Ship & ship);
  std::map<std::string, uint64_t> routeCapacities;
};

#endif  // SHIPMANAGER_HPP
