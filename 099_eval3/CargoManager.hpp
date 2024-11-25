#ifndef CARGOMANAGER_HPP
#define CARGOMANAGER_HPP

#include <string>
#include <vector>
#include <limits>

struct Cargo {
    std::string name;
    std::string source;
    std::string destination;
    unsigned long weight;
    std::vector<std::string> properties;
};

bool parseCargoLine(const std::string & line, Cargo & cargo);
std::vector<Cargo> loadCargoFromFile(const std::string & filename);

#endif // CARGOMANAGER_HPP
