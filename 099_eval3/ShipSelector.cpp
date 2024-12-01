#include "ShipSelector.hpp"
#include <vector>
#include <limits>
#include <stdint.h>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap) 
    : shipMap(shipMap) {}

Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    uint64_t cargoWeight = cargo.weight;
    AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare>::Node * curr = shipMap.root;
    Ship * bestShip = NULL;
    uint64_t minRemainingCapacity = std::numeric_limits<uint64_t>::max();

    while (curr != NULL) {
        if (curr->key < cargoWeight) {
            curr = curr->right;
        } else {
            // Current node's capacity is sufficient, check ships in this node
            for (std::set<Ship*, ShipNameCompare>::const_iterator it = curr->vals.begin(); it != curr->vals.end(); ++it) {
                Ship * ship = const_cast<Ship*>(*it);
                if (ship->canLoadCargo(cargo)) {
                    uint64_t remainingCapacity = ship->capacity - ship->usedCapacity - cargoWeight;
                    if (remainingCapacity < minRemainingCapacity || 
                        (remainingCapacity == minRemainingCapacity && ship->name < bestShip->name)) {
                        bestShip = ship;
                        minRemainingCapacity = remainingCapacity;
                    }
                }
            }
            // Continue to left subtree to find a ship with smaller capacity
            curr = curr->left;
        }
    }
    return bestShip;
}

void ShipSelector::updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    shipMap.remove(oldRemainingCapacity, ship);
    shipMap.add(newRemainingCapacity, ship);
}
