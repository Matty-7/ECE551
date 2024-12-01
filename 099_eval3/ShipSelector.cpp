#include "ShipSelector.hpp"
#include <vector>
#include <limits>
#include <stdint.h>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap) : shipMap(shipMap) {}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    Ship * bestShip = NULL;
    uint64_t minRemainingCapacity = std::numeric_limits<uint64_t>::max();
    
    
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > nodes = 
        shipMap.preOrderDump();
    
    
    size_t left = 0;
    size_t right = nodes.size();
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        uint64_t capacity = nodes[mid].first.first;
        
        if (capacity >= cargo.weight) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    
    for (size_t i = left; i < nodes.size(); i++) {
        uint64_t remainingCapacity = nodes[i].first.first;
        const std::set<Ship*, ShipNameCompare>& ships = nodes[i].first.second;
        
        
        if (remainingCapacity - cargo.weight > minRemainingCapacity) {
            break;
        }
        
        
        for (std::set<Ship*, ShipNameCompare>::const_iterator shipIt = ships.begin(); 
             shipIt != ships.end(); ++shipIt) {
            Ship * ship = *shipIt;
            if (ship->canLoadCargo(cargo)) {
                uint64_t remainingAfterLoad = remainingCapacity - cargo.weight;
                if (remainingAfterLoad < minRemainingCapacity || 
                    (remainingAfterLoad == minRemainingCapacity && ship->name < bestShip->name)) {
                    bestShip = ship;
                    minRemainingCapacity = remainingAfterLoad;
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
