#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ShipManager.hpp"
#include "CargoManager.hpp"
#include "Ship.hpp"

bool compareShipsByName(const Ship* a, const Ship* b);
bool isCargoFileEmpty(const std::string & filename);

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <ships_file> <cargo_file>" << std::endl;
        return EXIT_FAILURE;
    }

    // Initialize and load ships from file
    ShipManager manager;
    if (!manager.loadShipsFromFile(argv[1])) {
        return EXIT_FAILURE;
    }

    
    std::vector<Cargo> cargoList = loadCargoFromFile(argv[2]);
    if (cargoList.empty()) {
        
        if (!isCargoFileEmpty(argv[2])) {
           
            return EXIT_FAILURE;
        }
        
    }

    
    for (std::vector<Cargo>::const_iterator cargo = cargoList.begin();
         cargo != cargoList.end(); ++cargo) {
        std::vector<Ship*> eligibleShips;

        std::vector<Ship*>& ships = manager.getShips();
        for (std::vector<Ship*>::iterator ship = ships.begin();
             ship != ships.end(); ++ship) {
            if ((*ship)->canLoadCargo(*cargo)) {
                eligibleShips.push_back(*ship);
            }
        }

        std::sort(eligibleShips.begin(), eligibleShips.end(),
                  compareShipsByName);

        if (eligibleShips.empty()) {
            std::cout << "No ships can carry the " << cargo->name
                      << " from " << cargo->source << " to "
                      << cargo->destination << std::endl;
        } else {
            std::cout << eligibleShips.size() << " ships can carry the "
                      << cargo->name << " from " << cargo->source
                      << " to " << cargo->destination << std::endl;
            for (std::vector<Ship*>::const_iterator ship = eligibleShips.begin();
                 ship != eligibleShips.end(); ++ship) {
                std::cout << "  " << (*ship)->name << std::endl;
            }

            Ship* bestShip = eligibleShips.front();
            bestShip->loadCargo(*cargo);
            std::cout << "  **Loading the cargo onto " << bestShip->name
                      << "**" << std::endl;
        }
    }

    std::cout << "---Done Loading---Here are the ships---" << std::endl;
    manager.printShipDetails();

    return EXIT_SUCCESS;
}

bool compareShipsByName(const Ship* a, const Ship* b) {
    return a->name < b->name;
}

// Look at the first character of the file to check if it's empty
bool isCargoFileEmpty(const std::string & filename) {
    std::ifstream infile(filename.c_str());
    return infile.peek() == std::ifstream::traits_type::eof();
}
