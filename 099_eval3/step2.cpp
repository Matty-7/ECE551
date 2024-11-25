#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include "ShipManager.hpp"
#include "CargoManager.hpp"
#include "Ship.hpp"

bool compareShipsByName(const Ship* a, const Ship* b);

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "Here we use: " << argv[0] << " <ships_file> <cargo_file>" << std::endl;
        return EXIT_FAILURE;
    }

    ShipManager manager;
    if (!manager.loadShipsFromFile(argv[1])) {
        return EXIT_FAILURE;
    }

    std::vector<Cargo> cargoList = loadCargoFromFile(argv[2]);
    if (cargoList.empty()) {
        return EXIT_FAILURE;
    }

    for (std::vector<Cargo>::const_iterator cargo = cargoList.begin(); cargo != cargoList.end(); ++cargo) {
        std::vector<Ship*> eligibleShips;

        for (std::vector<Ship>::iterator ship = manager.getShips().begin(); ship != manager.getShips().end(); ++ship) {
            if (ship->canLoadCargo(*cargo)) {
                eligibleShips.push_back(&(*ship));
            }
        }

        std::sort(eligibleShips.begin(), eligibleShips.end(), compareShipsByName);

        if (eligibleShips.empty()) {
            std::cout << "There is no ship can carry the " << cargo->name << " from " << cargo->source << " to " << cargo->destination << std::endl;
        } else {
            std::cout << eligibleShips.size() << " ships can carry the " << cargo->name << " from " << cargo->source << " to " << cargo->destination << std::endl;
            for (std::vector<Ship*>::const_iterator ship = eligibleShips.begin(); ship != eligibleShips.end(); ++ship) {
                std::cout << "  " << (*ship)->name << std::endl;
            }
            eligibleShips.front()->loadCargo(*cargo);
            std::cout << "**Loading the cargo onto " << eligibleShips.front()->name << "**" << std::endl;
        }
    }

    std::cout << "---Done Loading---Here are the ships---" << std::endl;
    manager.printShipDetails();

    return EXIT_SUCCESS;
}

bool compareShipsByName(const Ship* a, const Ship* b) {
    return a->name < b->name;
}

