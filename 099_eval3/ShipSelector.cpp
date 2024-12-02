#include "ShipSelector.hpp"
#include <limits>

// Here I initializes ShipSelector with a reference to the AVL tree map of ships
ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap)
    : shipMap(shipMap) {
}

// Here I find the best ship with the smallest remaining capacity for a given cargo by searching through the AVL tree map
Ship * ShipSelector::findBestShip(const Cargo & cargo) {
    Ship * bestShip = NULL;
    uint64_t bestExtraCapacity = std::numeric_limits<uint64_t>::max();
    shipMap.findBestShip(cargo.weight, cargo, bestShip, bestExtraCapacity);
    return bestShip;
}

void ShipSelector::updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity) {
    shipMap.remove(oldRemainingCapacity, ship);
    shipMap.add(newRemainingCapacity, ship);
}
