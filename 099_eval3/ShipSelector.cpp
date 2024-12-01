#include "ShipSelector.hpp"
#include <vector>
#include <limits>
#include <algorithm>
#include <set>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare>& shipMap)
    : shipMap(shipMap) {}

Ship* ShipSelector::findBestShip(const Cargo& cargo) {
    Ship* bestShip = NULL; 
    uint64_t bestRemainingCapacity = std::numeric_limits<uint64_t>::max(); 

    
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > nodes = shipMap.preOrderDump();

    
    for (size_t i = 0; i < nodes.size(); ++i) {
        uint64_t currentCapacity = nodes[i].first.first; 

        
        if (currentCapacity < cargo.weight) {
            continue;
        }

        uint64_t remainingAfterLoad = currentCapacity - cargo.weight;

        
        if (bestShip != NULL && remainingAfterLoad > bestRemainingCapacity) {
            continue;
        }

        
        const std::set<Ship*, ShipNameCompare>& ships = nodes[i].first.second;
        for (std::set<Ship*, ShipNameCompare>::const_iterator it = ships.begin(); it != ships.end(); ++it) {
            Ship* ship = const_cast<Ship*>(*it); 

            
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

void ShipSelector::updateShipInMap(Ship* ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    if (ship == NULL) {
        return;
    }
    
    shipMap.remove(oldRemainingCapacity, ship);

    shipMap.add(newRemainingCapacity, ship);
}
