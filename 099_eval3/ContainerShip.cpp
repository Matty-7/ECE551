#include "ContainerShip.hpp"
#include <algorithm>
#include <iostream>

ContainerShip::ContainerShip() : slots(0) {}

bool ContainerShip::canLoadCargo(const Cargo & cargo) const {
    
    if (usedCapacity + cargo.weight > capacity) {
        return false;
    }

    if (loadedCargo.size() >= slots) {
        return false;
    }

    bool hasContainerProperty = false;
    std::vector<std::string>::const_iterator it;
    for (it = cargo.properties.begin(); it != cargo.properties.end(); ++it) {
        if (*it == "container") {
            hasContainerProperty = true;
            break;
        }
    }
    if (!hasContainerProperty) {
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

    if (source != cargo.source || destination != cargo.destination) {
        return false;
    }

    return true;
}

void ContainerShip::loadCargo(const Cargo & cargo) {
    loadedCargo.push_back(cargo);
    usedCapacity += cargo.weight;
}

void ContainerShip::printShipDetails() const {
    std::cout << "The Container Ship " << name << "(" << usedCapacity << "/" << capacity << ") is carrying : " << std::endl;
    std::vector<Cargo>::const_iterator cargo;
    for (cargo = loadedCargo.begin(); cargo != loadedCargo.end(); ++cargo) {
        std::cout << "  " << cargo->name << "(" << cargo->weight << ")" << std::endl;
    }
    std::cout << "  (" << (slots - loadedCargo.size()) << ") slots remain" << std::endl;
}
