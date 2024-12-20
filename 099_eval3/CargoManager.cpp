#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

struct Cargo {
    std::string name;
    std::string source;
    std::string destination;
    unsigned long weight;
    std::vector<std::string> properties;
};

bool parseCargoLine(const std::string & line, Cargo & cargo) {
    std::istringstream iss(line);
    std::string segment;
    std::vector<std::string> segments;

    while (std::getline(iss, segment, ',')) {
        segments.push_back(segment);
    }

    // Ensure minimum required 5 fields (name, source, destination, weight, at least one property)
    if (segments.size() < 5) {
        std::cerr << "Cargo to load has to have at least 5 parts, but "
                  << line << " has only " << segments.size() << std::endl;
        return false;
    }

    cargo.name = segments[0];
    cargo.source = segments[1];
    cargo.destination = segments[2];

    std::istringstream weightStream(segments[3]);
    if (!(weightStream >> cargo.weight)) {
        std::cerr << "Expected a number for weight, but found "
                  << segments[3] << std::endl;
        return false;
    }

    // Assign the remaining segments as properties
    cargo.properties.assign(segments.begin() + 4, segments.end());

    return true;
}

std::vector<Cargo> loadCargoFromFile(const std::string & filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cerr << "There is an error during opening the file: " << filename << std::endl;
        return std::vector<Cargo>();
    }

    std::vector<Cargo> cargoList;
    std::string line;
    while (std::getline(infile, line)) {
        
        if (line.empty()) {
            continue;
        }

        Cargo cargo;
        if (!parseCargoLine(line, cargo)) {
            
            return std::vector<Cargo>();
        }
        cargoList.push_back(cargo);
    }
    return cargoList;
}

bool compareCargoByWeight(const Cargo & a, const Cargo & b) {
    return a.weight > b.weight;
}
