#include "ShipSelector.hpp"
#include <limits>

ShipSelector::ShipSelector(AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> & shipMap)
    : shipMap(shipMap) {
}

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
