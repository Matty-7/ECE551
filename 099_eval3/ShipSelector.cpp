#include "ShipSelector.hpp"
#include <limits>
#include <set>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare>& shipMap)
    : shipMap(shipMap) {}

Ship* ShipSelector::findBestShip(const Cargo& cargo) {
    Ship* bestShip = NULL;
    uint64_t bestRemainingCapacity = std::numeric_limits<uint64_t>::max();

    AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare>::Node* current = 
        shipMap.findLowerBound(cargo.weight);

    while (current != NULL) {
        uint64_t currentCapacity = current->key;

        if (currentCapacity < cargo.weight) {
            current = shipMap.getNext(current);
            continue;
        }

        uint64_t remainingAfterLoad = currentCapacity - cargo.weight;

        if (bestShip != NULL && remainingAfterLoad > bestRemainingCapacity) {
            break;
        }

        const std::set<Ship*, ShipNameCompare>& ships = current->vals;
        for (std::set<Ship*, ShipNameCompare>::const_iterator it = ships.begin(); it != ships.end(); ++it) {
            Ship* ship = const_cast<Ship*>(*it);

            if (ship->canLoadCargo(cargo)) {
                if (bestShip == NULL ||
                    remainingAfterLoad < bestRemainingCapacity ||
                    (remainingAfterLoad == bestRemainingCapacity && 
                     ship->name.compare(bestShip->name) < 0)) {
                    bestShip = ship;
                    bestRemainingCapacity = remainingAfterLoad;
                }
            }
        }

        if (bestShip != NULL && remainingAfterLoad == bestRemainingCapacity) {
            break;
        }

        current = shipMap.getNext(current);
    }

    return bestShip;
}

void ShipSelector::updateShipInMap(Ship* ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    if (ship == NULL) {
        return;
    }

    if (oldRemainingCapacity > 0) {
        shipMap.remove(oldRemainingCapacity, ship);
    }

    if (newRemainingCapacity > 0) {
        shipMap.add(newRemainingCapacity, ship);
    }
}
