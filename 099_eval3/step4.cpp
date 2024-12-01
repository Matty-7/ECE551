#include <cstdlib>
#include <iostream>
#include "ShipManager.hpp"
#include "CargoManager.hpp"
#include "ShipSelector.hpp"
#include "avlmultimap03.hpp"

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

    
    std::stable_sort(cargoList.begin(), cargoList.end(), compareCargoByWeight);

    
    AVLMultiMap<uint64_t, Ship*, std::less<uint64_t>, ShipNameCompare> shipMap;
    manager.loadShipsIntoMap(shipMap);

    
    ShipSelector selector(shipMap);

    
    for (std::vector<Cargo>::iterator cargoIt = cargoList.begin(); cargoIt != cargoList.end(); ++cargoIt) {
        Cargo & cargo = *cargoIt;

        Ship * bestShip = selector.findBestShip(cargo);

        if (bestShip != NULL) {
            
            uint64_t oldRemainingCapacity = bestShip->capacity - bestShip->usedCapacity;

            
            bestShip->loadCargo(cargo);

            
            uint64_t newRemainingCapacity = bestShip->capacity - bestShip->usedCapacity;

            
            selector.updateShipInMap(bestShip, oldRemainingCapacity, newRemainingCapacity);

            
            std::cout << "Loading " << cargo.name << " onto " << bestShip->name << " from " << cargo.source << " to " << cargo.destination << std::endl;
        } else {
            
            std::cout << "Could not load " << cargo.name << " from " << cargo.source << " to " << cargo.destination << std::endl;
        }
    }

    std::cout << "---Done Loading---Here are the ships---" << std::endl;
    manager.printShipDetails();

    return EXIT_SUCCESS;
}
