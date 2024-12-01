#include "ShipSelector.hpp"
#include <limits>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap)
    : shipMap(shipMap) {
}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    const std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > & nodes = shipMap.preOrderDump();
    
    Ship* bestShip = NULL;
    uint64_t bestExtraCapacity = std::numeric_limits<uint64_t>::max();
    
    for (std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> >::const_iterator nodeIt = nodes.begin();
         nodeIt != nodes.end();
         ++nodeIt) {
        
        const uint64_t currentCapacity = nodeIt->first.first;
        if (currentCapacity < cargo.weight) {
            continue;
        }
        
        const uint64_t extraCapacity = currentCapacity - cargo.weight;
        if (extraCapacity > bestExtraCapacity) {
            continue;
        }
        
        const std::set<Ship*, ShipNameCompare> & ships = nodeIt->first.second;
        
        for (std::set<Ship*, ShipNameCompare>::const_iterator shipIt = ships.begin();
             shipIt != ships.end();
             ++shipIt) {
            if ((*shipIt)->canLoadCargo(cargo)) {
                if (extraCapacity < bestExtraCapacity || bestShip == NULL) {
                    bestShip = *shipIt;
                    bestExtraCapacity = extraCapacity;
                }
                else if (extraCapacity == bestExtraCapacity && 
                         ShipNameCompare()(*shipIt, bestShip)) {
                    bestShip = *shipIt;
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
