#include <iostream>
#include "ShipManager.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <ships_file>" << std::endl;
        return EXIT_FAILURE;
    }

    ShipManager manager;
    if (!manager.loadShipsFromFile(argv[1])) {
        return EXIT_FAILURE;
    }

    manager.printRouteCapacities();
    return EXIT_SUCCESS;
}
