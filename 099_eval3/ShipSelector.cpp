#include "ShipSelector.hpp"
#include <vector>
#include <limits>
#include <stdint.h>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap) 
    : shipMap(shipMap) {}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    Ship * bestShip = NULL;
    uint64_t bestRemainingCapacity = std::numeric_limits<uint64_t>::max();
    
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > nodes = 
        shipMap.preOrderDump();
    
    for (size_t i = 0; i < nodes.size(); ++i) {
        uint64_t remainingCapacity = nodes[i].first.first;
        
        if (remainingCapacity < cargo.weight) {
            continue;
        }
        
        uint64_t remainingAfterLoad = remainingCapacity - cargo.weight;
        
        const std::set<Ship*, ShipNameCompare>& ships = nodes[i].first.second;
        for (std::set<Ship*, ShipNameCompare>::const_iterator shipIt = ships.begin(); 
             shipIt != ships.end(); ++shipIt) {
            Ship * ship = *shipIt;
            
            if (ship->canLoadCargo(cargo)) {
                if (bestShip == NULL || 
                    remainingAfterLoad < bestRemainingCapacity || 
                    (remainingAfterLoad == bestRemainingCapacity && ship->name < bestShip->name)) {
                    bestShip = ship;
                    bestRemainingCapacity = remainingAfterLoad;
                }
            }
        }
    }
    
    return bestShip;
}

void ShipSelector::updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    shipMap.remove(oldRemainingCapacity, ship);
    shipMap.add(newRemainingCapacity, ship);
}
