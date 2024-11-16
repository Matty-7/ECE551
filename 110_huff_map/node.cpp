#include "node.h"

#include <cassert>
#include <map>

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    theMap[sym] = b;
  }
  else {
    assert(left != NULL && right != NULL);
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
