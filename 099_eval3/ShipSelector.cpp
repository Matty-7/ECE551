#include "ShipSelector.hpp"
#include <vector>
#include <stdint.h>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*> & shipMap) : shipMap(shipMap) {}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*> >, int> > preOrderList = shipMap.preOrderDump();

    for (std::vector<std::pair<std::pair<uint64_t, std::set<Ship*> >, int> >::iterator it = preOrderList.begin(); it != preOrderList.end(); ++it) {
        
        std::set<Ship*> ships = it->first.second;

        for (std::set<Ship*>::iterator shipIt = ships.begin(); shipIt != ships.end(); ++shipIt) {
            Ship * ship = *shipIt;
            if (ship->canLoadCargo(cargo)) {
                return ship;
            }
        }
    }

    return NULL;
}

void ShipSelector::updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    shipMap.remove(oldRemainingCapacity, ship);
    shipMap.add(newRemainingCapacity, ship);
}
