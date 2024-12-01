#include "ShipSelector.hpp"
#include <vector>
#include <limits>
#include <stdint.h>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap) : shipMap(shipMap) {}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    Ship * bestShip = NULL;
    uint64_t minRemainingCapacity = std::numeric_limits<uint64_t>::max();

    std::vector<std::pair<std::pair<uint64_t, std::set<Ship*, ShipNameCompare> >, int> > preOrderList = shipMap.preOrderDump();

    for (size_t i = 0; i < preOrderList.size(); ++i) {
        uint64_t shipRemainingCapacity = preOrderList[i].first.first;
        std::set<Ship*, ShipNameCompare> ships = preOrderList[i].first.second;

        for (std::set<Ship*, ShipNameCompare>::iterator shipIt = ships.begin(); shipIt != ships.end(); ++shipIt) {
            Ship * ship = *shipIt;
            if (ship->canLoadCargo(cargo)) {
                if (shipRemainingCapacity >= cargo.weight) {
                    uint64_t remainingCapacityAfterLoading = shipRemainingCapacity - cargo.weight;
                    if (remainingCapacityAfterLoading < minRemainingCapacity) {
                        bestShip = ship;
                        minRemainingCapacity = remainingCapacityAfterLoading;
                    } else if (remainingCapacityAfterLoading == minRemainingCapacity) {
                        if (ship->name < bestShip->name) {
                            bestShip = ship;
                        }
                    }
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
