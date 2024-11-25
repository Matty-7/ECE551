#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

struct Cargo {
    std::string name;
    std::string source;
    std::string destination;
    uint64_t weight;
    std::vector<std::string> properties;
};

class Ship {
public:
    std::string name;
    std::string source;
    std::string destination;
    uint64_t capacity;
    uint64_t usedCapacity;
    unsigned int slots;
    std::vector<std::string> hazmatCapabilities;
    std::vector<Cargo> loadedCargo;

    Ship() : usedCapacity(0), slots(0) {}

    bool canLoadCargo(const Cargo & cargo) const {
        // I need to check if the ship has enough capacity and slots
        if (usedCapacity + cargo.weight > capacity || slots <= loadedCargo.size()) {
            return false;
        }
        // I need to check if the ship can carry the hazardous materials
        for (const std::string & property : cargo.properties) {
            if (std::find(hazmatCapabilities.begin(), hazmatCapabilities.end(), property) == hazmatCapabilities.end()) {
                return false;
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
