#ifndef SHIPSELECTOR_HPP
#define SHIPSELECTOR_HPP

#include <stdint.h>
#include "Ship.hpp"
#include "CargoManager.hpp"
#include "avlmultimap03.hpp"

class ShipSelector {
public:
    ShipSelector(AVLMultiMap<uint64_t, Ship*> & shipMap);
    Ship * findBestShip(const Cargo & cargo);
    void updateShipInMap(Ship * ship, uint64_t oldRemainingCapacity, uint64_t newRemainingCapacity);

private:
    AVLMultiMap<uint64_t, Ship*> & shipMap;
};

#endif // SHIPSELECTOR_HPP
