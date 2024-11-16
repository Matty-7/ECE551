#include "readFreq.h"

#include <stdio.h>

#include <cstdint>
#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * frequencies = new uint64_t[257]();

  std::ifstream file(fname, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file" << fname << std::endl;
    delete[] frequencies;
    return NULL;
  }
  char ch;
  while (file.get(ch)) {
    frequencies[static_cast<unsigned char>(ch)]++;
  }

  frequencies[256] = 1;

  file.close();

  return frequencies;
}
