#include "ShipSelector.hpp"
#include <limits>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap)
    : shipMap(shipMap) {
}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    // Start with the smallest remaining capacity that could fit the cargo
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > nodes = shipMap.preOrderDump();
    
    // Find the first ship with sufficient capacity that can carry the cargo
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i].first.first >= cargo.weight) {  // Check if capacity is sufficient
            // Check each ship with this capacity
            const std::set<Ship*, ShipNameCompare> & ships = nodes[i].first.second;
            for (std::set<Ship*, ShipNameCompare>::const_iterator shipIt = ships.begin(); 
                 shipIt != ships.end(); 
                 ++shipIt) {
                if ((*shipIt)->canLoadCargo(cargo)) {
                    return *shipIt;
                }
            }
        }
    }
    
    return NULL;
}

void ShipSelector::updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    // Remove ship from its old position
    shipMap.remove(oldRemainingCapacity, ship);
    
    // Add ship at its new position
    shipMap.add(newRemainingCapacity, ship);
}
