#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

struct Ship {
    std::string name;
    std::string source;
    std::string destination;
    uint64_t capacity;
};

// It can parse a line from the ships file and fills in the Ship struct
bool parseShipLine(const std::string& line, Ship& ship) {
    std::istringstream iss(line);
    std::string segment;
    std::vector<std::string> segments;

    // It can split the line into segments by using ':' as the delimiter
    while (std::getline(iss, segment, ':')) {
        segments.push_back(segment);
    }

    // I need to check if there are 5 fields: Name, Type info, Source, Destination, and Capacity
    if (segments.size() != 5) return false;

    ship.name = segments[0];
    ship.source = segments[2];
    ship.destination = segments[3];
    try {
        ship.capacity = std::stoull(segments[4]); // Here I convert the capacity from string to uint64_t
    } catch (...) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <ships_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "There was an error opening the file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    std::map<std::string, uint64_t> routeCapacities;

    // I use a set to check for duplicates
    std::set<std::string> shipNames;

    std::string line;
    while (std::getline(infile, line)) {
        Ship ship;
        if (!parseShipLine(line, ship)) {
            std::cerr << "There was an error parsing the line: " << line << std::endl;
            return EXIT_FAILURE;
        }
        if (!shipNames.insert(ship.name).second) {
            std::cerr << "There was a duplicate ship name: " << ship.name << std::endl;
            return EXIT_FAILURE;
        }
        std::string route = "(" + ship.source + " -> " + ship.destination + ")";
        routeCapacities[route] += ship.capacity;
    }

    std::vector<std::pair<std::string, uint64_t> > sortedRoutes(routeCapacities.begin(), routeCapacities.end());
    std::sort(sortedRoutes.begin(), sortedRoutes.end());

    for (std::vector<std::pair<std::string, uint64_t> >::const_iterator it = sortedRoutes.begin(); it != sortedRoutes.end(); ++it) {
        std::cout << it->first << " has total capacity " << it->second << std::endl;
    }

    return EXIT_SUCCESS;
}
