#include <cassert>
#include <cstdlib>

#include "IntList.h"

void testList() {
  IntList lst;
  assert(lst.getSize() == 0);
  // []
  lst.addFront(1);
  assert(lst.getSize() == 1);
  assert(lst[0] == 1);
  // [1]
  lst.addBack(2);
  assert(lst.getSize() == 2);
  assert(lst[0] == 1);
  assert(lst[1] == 2);
  // [1,2]
  lst.remove(2);
  assert(lst.getSize() == 1);
  assert(lst[0] == 1);
  // [1]
  lst.addFront(2);
  assert(lst.getSize() == 2);
  assert(lst[0] == 2);
  assert(lst[1] == 1);
  assert(lst.find(2) == 0);
  assert(lst.remove(3) == false);
  // [2,1]
  bool success = lst.remove(2);
  assert(success == true);
  assert(lst.getSize() == 1);
  assert(lst[0] == 1);
  // [1]
  IntList lst2(lst);
  // [1]
  assert(lst2.getSize() == 1);
  assert(lst2[0] == 1);
  // [1]
  lst2.addBack(2);
  assert(lst2.getSize() == 2);
  assert(lst2[0] == 1);
  assert(lst2[1] == 2);
  // [1,2]
  lst2.remove(2);
  assert(lst2.getSize() == 1);
  assert(lst2[0] == 1);
  // [1]
  lst2.addFront(2);
  assert(lst2.getSize() == 2);
  assert(lst2[0] == 2);
  assert(lst2[1] == 1);
  assert(lst2.find(2) == 0);
  assert(lst2.remove(3) == false);
  // [2,1]
  success = lst2.remove(2);
  assert(success == true);
  assert(lst2.getSize() == 1);
  assert(lst2[0] == 1);
  lst2.addFront(3);
  // [3,1]
  lst2.addFront(2);
  assert(lst2.find(2) == 0);
  assert(lst2.find(3) == 1);
  assert(lst2.find(1) == 2);
  // [2,3,1]
  success = lst2.remove(3);
  assert(success == true);
  assert(lst2.getSize() == 2);
  assert(lst2[0] == 2);
  assert(lst2[1] == 1);
  // [2,1]
  lst2.remove(2);
  // [1]
  lst2.addBack(1);
  // [1,1]
  assert(lst2.getSize() == 2);
  assert(lst2[0] == 1);
  assert(lst2[1] == 1);
  assert(lst2.remove(3) == false);
  lst = lst2;
  // [1,1]
  assert(lst.getSize() == 2);
  assert(lst[0] == 1);
  assert(lst[1] == 1);
  assert(lst.remove(3) == false);
  lst.remove(1);
  // [1]
  assert(lst.getSize() == 1);
  assert(lst[0] == 1);
  assert(lst.find(2) == -1);
  lst.remove(1);
  // []
  assert(lst.getSize() == 0);
  for (int i = 0; i < 5; i++) {
    lst.addBack(i);
  }
  assert(lst.getSize() == 5);
  for (int i = 0; i < 5; i++) {
    assert(lst[i] == i);
  }
}

int main() {
  testList();
  return EXIT_SUCCESS;
}
