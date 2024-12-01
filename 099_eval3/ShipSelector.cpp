#include "ShipSelector.hpp"
#include <limits>
#include <set>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare>& shipMap)
    : shipMap(shipMap) {}

Ship* ShipSelector::findBestShip(const Cargo& cargo) {
    Ship* bestShip = NULL;
    uint64_t bestRemainingCapacity = std::numeric_limits<uint64_t>::max();

    auto* current = shipMap.findLowerBound(cargo.weight);

    while (current != NULL) {
        uint64_t currentCapacity = current->key;

        if (currentCapacity < cargo.weight) {
            current = shipMap.getNext(current, [](auto* node) { return true; });
            continue;
        }

        uint64_t remainingAfterLoad = currentCapacity - cargo.weight;

        if (bestShip != NULL && remainingAfterLoad > bestRemainingCapacity) {
            break;
        }

        const std::set<Ship*, ShipNameCompare>& ships = current->vals;
        for (auto it = ships.begin(); it != ships.end(); ++it) {
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

        current = shipMap.getNext(current, [](auto* node) { return true; });
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
