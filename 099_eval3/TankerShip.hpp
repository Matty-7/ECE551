#ifndef TANKERSHIP_HPP
#define TANKERSHIP_HPP

#include "Ship.hpp"
#include <vector>
#include <string>

class ShipManager; // 前向声明

class TankerShip : public Ship {
public:
    TankerShip();
    virtual ~TankerShip() {}

    virtual bool canLoadCargo(const Cargo & cargo) const;
    virtual void loadCargo(const Cargo & cargo);
    virtual void printShipDetails() const;

private:
    int minTemp;
    int maxTemp;
    unsigned int numTanks;
    std::vector<std::string> hazmatCapabilities;
    std::vector<Cargo> loadedCargo;
    std::vector<unsigned long> tankCapacities;
    std::vector<std::string> tankCargoTypes;

    friend class ShipManager; // 将 ShipManager 声明为友元类
};

#endif // TANKERSHIP_HPP
