#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "bitstring.h"
#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  //WRITE YOUR CODE HERE!
  //open the input file for reading

  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter

  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor

  //but you probably need to close your input file.

  std::ifstream input(inFile, std::ios::binary);
  if (!input.is_open()) {
    std::cerr << "Error: Could not open input file" << inFile << std::endl;
    exit(EXIT_FAILURE);
  }

  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  char ch;
  while (input.get(ch)) {
    std::map<unsigned, BitString>::const_iterator it =
        theMap.find(static_cast<unsigned char>(ch));
    if (it == theMap.end()) {
      std::cerr << "Error: Character" << ch << "not found in map!" << std::endl;
      exit(EXIT_FAILURE);
    }
    bfw.writeBitString(it->second);
  }

  std::map<unsigned, BitString>::const_iterator eofIt = theMap.find(256);
  if (eofIt == theMap.end()) {
    std::cerr << "Error: EOF marker not found in map!" << std::endl;
    exit(EXIT_FAILURE);
  }
  bfw.writeBitString(eofIt->second);
  input.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this

  uint64_t * counts = readFrequencies(argv[1]);
  if (counts == NULL) {
    return EXIT_FAILURE;
  }

  Node * root = buildTree(counts);
  delete[] counts;

  std::map<unsigned, BitString> theMap;
  root->buildMap(BitString(), theMap);
  delete root;

  writeCompressedOutput(argv[1], argv[2], theMap);
  return EXIT_SUCCESS;
}
