#include "ShipSelector.hpp"
#include <vector>
#include <limits>
#include <algorithm>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap) 
    : shipMap(shipMap) {}

struct CompareByCapacity {
    bool operator()(const std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int>& node, 
                   const uint64_t& weight) const {
        return node.first.first < weight;
    }
    
    bool operator()(const uint64_t& weight,
                   const std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int>& node) const {
        return weight < node.first.first;
    }
};

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    Ship * bestShip = NULL;
    uint64_t bestRemainingCapacity = std::numeric_limits<uint64_t>::max();
    
    typedef std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> NodeInfo;
    std::vector<NodeInfo> nodes = shipMap.preOrderDump();
    
    
    std::vector<NodeInfo>::const_iterator it = 
        std::lower_bound(nodes.begin(), 
                        nodes.end(), 
                        cargo.weight,
                        CompareByCapacity());
    
    
    for (; it != nodes.end(); ++it) {
        uint64_t remainingCapacity = it->first.first;
        
        
        if (bestShip != NULL && remainingCapacity - cargo.weight >= bestRemainingCapacity) {
            break;
        }
        
        const std::set<Ship*, ShipNameCompare>& ships = it->first.second;
        for (std::set<Ship*, ShipNameCompare>::const_iterator shipIt = ships.begin(); 
             shipIt != ships.end(); 
             ++shipIt) {
            Ship * ship = *shipIt;
            
            
            if (ship->canLoadCargo(cargo)) {
                uint64_t remainingAfterLoad = remainingCapacity - cargo.weight;
                
                
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
    if (ship == NULL) {
        return;
    }
    
    
    shipMap.remove(oldRemainingCapacity, ship);
    
    
    shipMap.add(newRemainingCapacity, ship);
}
