#include "TankerShip.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <cstdlib>

TankerShip::TankerShip() : minTemp(0), maxTemp(0), numTanks(0) {}

bool TankerShip::canLoadCargo(const Cargo & cargo) const {
    
    if (source != cargo.source || destination != cargo.destination) {
        return false;
    }

    if (usedCapacity + cargo.weight > capacity) {
        return false;
    }

    bool hasLiquidOrGas = false;
    std::vector<std::string>::const_iterator it;
    for (it = cargo.properties.begin(); it != cargo.properties.end(); ++it) {
        if (*it == "liquid" || *it == "gas") {
            hasLiquidOrGas = true;
            break;
        }
    }
    if (!hasLiquidOrGas) {
        return false;
    }

    int cargoMinTemp = std::numeric_limits<int>::min();
    int cargoMaxTemp = std::numeric_limits<int>::max();
    for (it = cargo.properties.begin(); it != cargo.properties.end(); ++it) {
        if (it->compare(0, 8, "mintemp=") == 0) {
            cargoMinTemp = atoi(it->substr(8).c_str());
        } else if (it->compare(0, 8, "maxtemp=") == 0) {
            cargoMaxTemp = atoi(it->substr(8).c_str());
        }
    }
    if (cargoMaxTemp < minTemp || cargoMinTemp > maxTemp) {
        return false;
    }

    for (it = cargo.properties.begin(); it != cargo.properties.end(); ++it) {
        if (it->compare(0, 10, "hazardous-") == 0) {
            std::string hazmat = it->substr(10);
            if (std::find(hazmatCapabilities.begin(), hazmatCapabilities.end(), hazmat) ==
                hazmatCapabilities.end()) {
                return false;
            }
        }
    }

    return true;
}

void TankerShip::loadCargo(const Cargo & cargo) {
    loadedCargo.push_back(cargo);
    usedCapacity += cargo.weight;
}

void TankerShip::printShipDetails() const {
    std::cout << "The Tanker Ship " << name << "(" << usedCapacity << "/" << capacity << ") is carrying : " << std::endl;
    std::vector<Cargo>::const_iterator it;
    for (it = loadedCargo.begin(); it != loadedCargo.end(); ++it) {
        std::cout << "  " << it->name << "(" << it->weight << ")" << std::endl;
    }
    std::cout << "  " << tankCargoTypes.size() << " / " << numTanks << " tanks used" << std::endl;
}
