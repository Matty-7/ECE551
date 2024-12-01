#include "ShipSelector.hpp"
#include <limits>
#include <iostream>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap)
    : shipMap(shipMap) {
}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    std::cerr << "Debug: Starting search for cargo " << cargo.name 
              << " (weight: " << cargo.weight << ")" << std::endl;
              
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > nodes = shipMap.preOrderDump();
    
    std::cerr << "Debug: Got " << nodes.size() << " capacity levels to check" << std::endl;
    
    Ship* bestShip = NULL;
    uint64_t bestExtraCapacity = std::numeric_limits<uint64_t>::max();
    
    // Find the ship with minimum extra capacity that can carry the cargo
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (i % 1000 == 0) {  
            std::cerr << "Debug: Checked " << i << " nodes..." << std::endl;
        }
        
        uint64_t currentCapacity = nodes[i].first.first;
        if (currentCapacity >= cargo.weight) {  // Check if capacity is sufficient
            uint64_t extraCapacity = currentCapacity - cargo.weight;
            
            if (extraCapacity < bestExtraCapacity) {
                const std::set<Ship*, ShipNameCompare> & ships = nodes[i].first.second;
                std::cerr << "Debug: Checking " << ships.size() 
                         << " ships at capacity level " << currentCapacity << std::endl;
                         
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
    
    std::cerr << "Debug: Search completed" << std::endl;
    return bestShip;
}

void ShipSelector::updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    // Remove ship from its old position
    shipMap.remove(oldRemainingCapacity, ship);
    
    // Add ship at its new position
    shipMap.add(newRemainingCapacity, ship);
}
