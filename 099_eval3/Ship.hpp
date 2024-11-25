#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "CargoManager.hpp"

class Ship {
public:
    std::string name;
    std::string source;
    std::string destination;
    unsigned long capacity;
    unsigned long usedCapacity;
    unsigned int slots;
    std::vector<std::string> hazmatCapabilities;
    std::vector<Cargo> loadedCargo;

    Ship() : usedCapacity(0), slots(0) {}

    bool canLoadCargo(const Cargo & cargo) const {
    // Check capacity
    if (usedCapacity + cargo.weight > capacity) {
        return false;
    }

    // Check slots
    if (loadedCargo.size() >= slots) {
        return false;
    }

    // Check hazardous materials only if cargo has properties
    if (!cargo.properties.empty()) {
        for (std::vector<std::string>::const_iterator it = cargo.properties.begin(); 
             it != cargo.properties.end(); 
             ++it) {
            if (std::find(hazmatCapabilities.begin(), hazmatCapabilities.end(), *it) 
                == hazmatCapabilities.end()) {
                return false;
            }
        }
    }

    return true;
}

    void loadCargo(const Cargo & cargo) {
        if (canLoadCargo(cargo)) {
            loadedCargo.push_back(cargo);
            usedCapacity += cargo.weight;
        }
    }
};

#endif // SHIP_HPP
