#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void do_sort(std::istream & is) {
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(is, line)) {
    lines.push_back(line);
  }

  if (is.bad()) {
    std::cerr << "Error: Failed to read from the input stream." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::sort(lines.begin(), lines.end());

  for (const auto & str : lines) {
    std::cout << str << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc <= 0) {
    std::cerr << "Error: Invalid argument count." << std::endl;
    exit(EXIT_FAILURE);
  }

  if (argc == 1) {
    do_sort(std::cin);
  }
  else {
    for (int i = 1; i < argc; ++i) {
      std::ifstream file(argv[i]);
      if (!file) {
        std::cerr << "Error: Failed to open file " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      do_sort(file);
    }
  }

  return EXIT_SUCCESS;
}
