#include "ShipSelector.hpp"
#include <vector>
#include <limits>
#include <algorithm>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap) 
    : shipMap(shipMap) {}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    Ship * bestShip = NULL;
    uint64_t bestRemainingCapacity = std::numeric_limits<uint64_t>::max();
    
    typedef std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> NodeInfo;
    std::vector<NodeInfo> nodes = shipMap.preOrderDump();
    
    // 从容量最小的船开始检查
    for (std::vector<NodeInfo>::const_iterator it = nodes.begin(); 
         it != nodes.end(); 
         ++it) {
        const uint64_t currentCapacity = it->first.first;
        
        // 如果当前容量不够，跳过
        if (currentCapacity < cargo.weight) {
            continue;
        }
        
        // 如果已经找到了匹配，且当前船的剩余容量会更大，可以停止
        uint64_t remainingAfterLoad = currentCapacity - cargo.weight;
        if (bestShip != NULL && remainingAfterLoad > bestRemainingCapacity) {
            break;
        }
        
        // 检查该容量级别的所有船只
        const std::set<Ship*, ShipNameCompare>& ships = it->first.second;
        for (std::set<Ship*, ShipNameCompare>::const_iterator shipIt = ships.begin(); 
             shipIt != ships.end(); 
             ++shipIt) {
            Ship * ship = const_cast<Ship*>(*shipIt);
            
            // 检查船只是否能装载货物（包括类型限制等）
            if (ship->canLoadCargo(cargo)) {
                // 如果这是第一个匹配，或者这艘船更好
                if (bestShip == NULL || 
                    remainingAfterLoad < bestRemainingCapacity || 
                    (remainingAfterLoad == bestRemainingCapacity && 
                     ship->name < bestShip->name)) {
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
