#ifndef CONTAINERSHIP_HPP
#define CONTAINERSHIP_HPP

#include "Ship.hpp"
#include <vector>
#include <string>

class ShipManager; // 前向声明

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

    friend class ShipManager; // 将 ShipManager 声明为友元类
};

#endif // CONTAINERSHIP_HPP
