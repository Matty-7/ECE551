#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void read_lines(std::istream & stream, std::vector<std::string> & lines) {
  std::string line;
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
}

void sort_and_print_lines(std::vector<std::string> & lines) {
  std::sort(lines.begin(), lines.end());
  for (const auto & line : lines) {
    std::cout << line << '\n';
  }
}

int main(int argc, char * argv[]) {
  std::vector<std::string> lines;

  if (argc == 1) {
    read_lines(std::cin, lines);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream file(argv[i]);
      if (!file) {
        std::cerr << "Error: Could not open the file" << argv[i] << '\n';
        return EXIT_FAILURE;
      }
      read_lines(file, lines);
    }
  }

  sort_and_print_lines(lines);

  return EXIT_SUCCESS;
}
