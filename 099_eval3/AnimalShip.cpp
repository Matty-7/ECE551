#include "AnimalShip.hpp"
#include <algorithm>
#include <iostream>

// Here I initialize the AnimalShip with zero small cargo threshold and no roamer
AnimalShip::AnimalShip() : smallEnoughThreshold(0), hasRoamer(false) {}

bool AnimalShip::canLoadCargo(const Cargo & cargo) const {
    // Here I check the route and capacity
    if (source != cargo.source || destination != cargo.destination) {
        return false;
    }

    if (usedCapacity + cargo.weight > capacity) {
        return false;
    }

    bool isAnimal = false;
    bool isRoamer = false;
    std::vector<std::string>::const_iterator it;
    for (it = cargo.properties.begin(); it != cargo.properties.end(); ++it) {
        if (*it == "animal") {
            isAnimal = true;
        }
        if (*it == "roamer") {
            isRoamer = true;
        }

        // Here I check if the cargo is liquid or gas since the animal ship can't carry them
        if (*it == "liquid" || *it == "gas") {
            return false;
        }
        if (it->compare(0, 10, "hazardous-") == 0) {
            return false;
        }
    }

    if (isAnimal) {
        // Each ship can only have one roamer
        if (isRoamer) {
            if (hasRoamer) {
                return false;
            }
        }
    } else {
        if (cargo.weight > smallEnoughThreshold) {
            return false;
        }
    }

    return true;
}

void AnimalShip::loadCargo(const Cargo & cargo) {
    loadedCargo.push_back(cargo);
    usedCapacity += cargo.weight;

    // Here I update the roamer status
    std::vector<std::string>::const_iterator it;
    for (it = cargo.properties.begin(); it != cargo.properties.end(); ++it) {
        if (*it == "roamer") {
            hasRoamer = true;
            break;
        }
    }
}

void AnimalShip::printShipDetails() const {
    std::cout << "The Animals Ship " << name << "(" << usedCapacity << "/" << capacity << ") is carrying : " << std::endl;
    std::vector<Cargo>::const_iterator it;
    for (it = loadedCargo.begin(); it != loadedCargo.end(); ++it) {
        std::cout << "  " << it->name << "(" << it->weight << ")" << std::endl;
    }
    if (hasRoamer) {
        std::cout << "  has a roamer" << std::endl;
    } else {
        std::cout << "  does not have a roamer" << std::endl;
    }
}
