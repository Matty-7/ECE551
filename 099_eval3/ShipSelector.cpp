#include "ShipSelector.hpp"
#include <limits>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap)
    : shipMap(shipMap) {
}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > nodes = shipMap.preOrderDump();
    
    Ship* bestShip = NULL;
    uint64_t bestExtraCapacity = std::numeric_limits<uint64_t>::max();
    
    // Find the ship with minimum extra capacity that can carry the cargo
    for (size_t i = 0; i < nodes.size(); ++i) {
        uint64_t currentCapacity = nodes[i].first.first;
        if (currentCapacity >= cargo.weight) {  // Check if capacity is sufficient
            uint64_t extraCapacity = currentCapacity - cargo.weight;
            
            // Only check ships with less extra capacity than our current best
            if (extraCapacity < bestExtraCapacity) {
                const std::set<Ship*, ShipNameCompare> & ships = nodes[i].first.second;
                for (std::set<Ship*, ShipNameCompare>::const_iterator shipIt = ships.begin(); 
                     shipIt != ships.end(); 
                     ++shipIt) {
                    if ((*shipIt)->canLoadCargo(cargo)) {
                        bestShip = *shipIt;
                        bestExtraCapacity = extraCapacity;
                        break;  // Found a ship at this capacity level
                    }
                }
            }
        }
    }
    
    return bestShip;
}

void ShipSelector::updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    // Remove ship from its old position
    shipMap.remove(oldRemainingCapacity, ship);
    
    // Add ship at its new position
    shipMap.add(newRemainingCapacity, ship);
}
