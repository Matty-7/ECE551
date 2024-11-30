#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include "CargoManager.hpp"

class Ship {
public:
    Ship() : usedCapacity(0) {}
    virtual ~Ship() {}

    virtual bool canLoadCargo(const Cargo & cargo) const = 0;
    virtual void loadCargo(const Cargo & cargo) = 0;
    virtual void printShipDetails() const = 0;

    std::string name;
    std::string source;
    std::string destination;
    unsigned long capacity;
    unsigned long usedCapacity;
};

#endif // SHIP_HPP
