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
    for (const std::string & prop : cargo.properties) {
        if (prop == "liquid" || prop == "gas") {
            hasLiquidOrGas = true;
            break;
        }
    }
    if (!hasLiquidOrGas) {
        return false;
    }

    
    int cargoMinTemp = std::numeric_limits<int>::min();
    int cargoMaxTemp = std::numeric_limits<int>::max();
    for (const std::string & prop : cargo.properties) {
        if (prop.compare(0, 8, "mintemp=") == 0) {
            cargoMinTemp = atoi(prop.substr(8).c_str());
        } else if (prop.compare(0, 8, "maxtemp=") == 0) {
            cargoMaxTemp = atoi(prop.substr(8).c_str());
        }
    }
    if (cargoMaxTemp < minTemp || cargoMinTemp > maxTemp) {
        return false;
    }

    
    for (const std::string & prop : cargo.properties) {
        if (prop.compare(0, 10, "hazardous-") == 0) {
            std::string hazmat = prop.substr(10);
            if (std::find(hazmatCapabilities.begin(), hazmatCapabilities.end(), hazmat) ==
                hazmatCapabilities.end()) {
                return false;
            }
        }
    }

    unsigned long perTankCapacity = capacity / numTanks;
    unsigned long remainingWeight = cargo.weight;

    std::vector<unsigned long> tempTankCapacities = tankCapacities;

    for (unsigned int i = 0; i < numTanks && remainingWeight > 0; ++i) {
        
        if (tankCargoTypes[i] == "" || tankCargoTypes[i] == cargo.name) {
            unsigned long availableCapacity = perTankCapacity - tempTankCapacities[i];
            if (availableCapacity > 0) {
                unsigned long loadAmount = std::min(availableCapacity, remainingWeight);
                tempTankCapacities[i] += loadAmount;
                remainingWeight -= loadAmount;
            }
        }
    }

    return remainingWeight == 0;
}

void TankerShip::loadCargo(const Cargo & cargo) {
    usedCapacity += cargo.weight;
    loadedCargo.push_back(cargo);

    unsigned long perTankCapacity = capacity / numTanks;
    unsigned long remainingWeight = cargo.weight;

    for (unsigned int i = 0; i < numTanks && remainingWeight > 0; ++i) {
        if (tankCargoTypes[i] == "" || tankCargoTypes[i] == cargo.name) {
            unsigned long availableCapacity = perTankCapacity - tankCapacities[i];
            if (availableCapacity > 0) {
                unsigned long loadAmount = std::min(availableCapacity, remainingWeight);
                tankCapacities[i] += loadAmount;
                tankCargoTypes[i] = cargo.name;
                remainingWeight -= loadAmount;
            }
        }
    }

    if (remainingWeight > 0) {
        std::cerr << "Error: Could not fully load cargo " << cargo.name << " onto ship " << name << std::endl;
    }
}

void TankerShip::printShipDetails() const {
    std::cout << "The Tanker Ship " << name << "(" << usedCapacity << "/" << capacity << ") is carrying : " << std::endl;
    for (const Cargo & cargo : loadedCargo) {
        std::cout << "  " << cargo.name << "(" << cargo.weight << ")" << std::endl;
    }
    
    unsigned int tanksUsed = 0;
    for (unsigned int i = 0; i < numTanks; ++i) {
        if (tankCapacities[i] > 0) {
            ++tanksUsed;
        }
    }

    std::cout << "  " << tanksUsed << " / " << numTanks << " tanks used" << std::endl;
}
