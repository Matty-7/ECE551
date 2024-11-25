#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct Cargo {
    std::string name;
    std::string source;
    std::string destination;
    uint64_t weight;
    std::vector<std::string> properties;
};

bool parseCargoLine(const std::string & line, Cargo & cargo) {
    std::istringstream iss(line);
    std::string segment;
    std::vector<std::string> segments;

    // Here I used ',' as the delimiter to split the line
    while (std::getline(iss, segment, ',')) {
        segments.push_back(segment);
    }

    if (segments.size() < 5)
        return false;

    cargo.name = segments[0];
    cargo.source = segments[1];
    cargo.destination = segments[2];

    // I convert weight from string to uint64_t
    std::istringstream weightStream(segments[3]);
    if (!(weightStream >> cargo.weight)) {
        return false;
    }

    // The remaining segments are properties here
    cargo.properties.assign(segments.begin() + 4, segments.end());

    return true;
}

std::vector<Cargo> loadCargoFromFile(const std::string & filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cerr << "There is an error during opening the file: " << filename << std::endl;
        return {};
    }

    std::vector<Cargo> cargoList;
    std::string line;
    while (std::getline(infile, line)) {
        Cargo cargo;
        if (!parseCargoLine(line, cargo)) {
            std::cerr << "There is an error during parsing the line: " << line << std::endl;
            continue;
        }
        cargoList.push_back(cargo);
    }
    return cargoList;
}
