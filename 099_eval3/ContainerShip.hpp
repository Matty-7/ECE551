#ifndef CONTAINERSHIP_HPP
#define CONTAINERSHIP_HPP

#include "Ship.hpp"
#include <vector>
#include <string>

class ContainerShip : public Ship {
public:
    ContainerShip();
    virtual ~ContainerShip() {}

    virtual bool canLoadCargo(const Cargo & cargo) const;
    virtual void loadCargo(const Cargo & cargo);
    virtual void printShipDetails() const;

private:
    unsigned int slots;
    std::vector<std::string> hazmatCapabilities;
    std::vector<Cargo> loadedCargo;

    friend bool parseShipLine(const std::string & line, Ship *& ship);
};

#endif // CONTAINERSHIP_HPP
