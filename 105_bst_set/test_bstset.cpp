#include <cassert>
#include <iostream>

#include "bstset.h"

void testBstSet() {
  BstSet<int> bst;

  // Test add
  bst.add(10);
  bst.add(5);
  bst.add(15);
  bst.add(10);  // Duplicate, should be ignored
  assert(bst.contains(10));
  assert(bst.contains(5));
  assert(bst.contains(15));
  assert(!bst.contains(20));

  // Test remove
  bst.remove(10);
  assert(!bst.contains(10));
  assert(bst.contains(5));
  assert(bst.contains(15));

  // Test edge cases
  bst.remove(100);  // Non-existent key
  bst.remove(5);
  bst.remove(15);
  assert(!bst.contains(5));
  assert(!bst.contains(15));

  std::cout << "All tests passed!" << std::endl;
}

int main() {
  testBstSet();
  return 0;
}
