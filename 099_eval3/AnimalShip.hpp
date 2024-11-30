#ifndef ANIMALSHIP_HPP
#define ANIMALSHIP_HPP

#include "Ship.hpp"
#include <vector>
#include <string>

class AnimalShip : public Ship {
public:
    AnimalShip();
    virtual ~AnimalShip() {}

    virtual bool canLoadCargo(const Cargo & cargo) const;
    virtual void loadCargo(const Cargo & cargo);
    virtual void printShipDetails() const;

private:
    unsigned int smallEnoughThreshold;
    bool hasRoamer;
    std::vector<Cargo> loadedCargo;

    friend bool parseShipLine(const std::string & line, Ship *& ship);
};

#endif // ANIMALSHIP_HPP
