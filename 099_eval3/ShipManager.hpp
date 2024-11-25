#ifndef SHIPMANAGER_HPP
#define SHIPMANAGER_HPP

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include "Ship.hpp"

class ShipManager {
 public:
  bool loadShipsFromFile(const std::string & filename);
  void printRouteCapacities() const;
  std::vector<Ship>& getShips();
  void printShipDetails() const {
    for (std::vector<Ship>::const_iterator it = ships.begin(); it != ships.end(); ++it) {
        const Ship& ship = *it;
        std::cout << "The Container Ship " << ship.name << "(" << ship.usedCapacity 
                  << "/" << ship.capacity << ") is carrying : " << std::endl;
        
        // 打印已装载的货物
        for (std::vector<Cargo>::const_iterator cargo = ship.loadedCargo.begin();
             cargo != ship.loadedCargo.end(); ++cargo) {
            std::cout << "  " << cargo->name << "(" << cargo->weight << ")" << std::endl;
        }
        
        std::cout << "  (" << (ship.slots - ship.loadedCargo.size()) 
                  << ") slots remain" << std::endl;
    }
}

 private:
  std::vector<Ship> ships;

  bool parseShipLine(const std::string & line, Ship & ship);
  std::map<std::string, uint64_t> routeCapacities;
};

#endif  // SHIPMANAGER_HPP
