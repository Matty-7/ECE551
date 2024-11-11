#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  void testDefCtor();
  void testAddFront();
  void testAddBack();
  void testRemove();
  void testOperatorAccess();
  void testFind();
  void testGetSize();
  void testCopyConstructor();
  void testAssignmentOperator();
};

// testing for default constructor is done for you
void Tester::testDefCtor() {
  IntList il;
  assert(il.head == NULL);
  assert(il.tail == NULL);
  assert(il.getSize() == 0);
}
// example of another method you might want to write
void Tester::testAddFront() {
  // WRITE ME
  IntList il;
  il.addFront(10);
  assert(il.head != NULL);
  assert(il.tail != NULL);
  assert(il.head->data == 10);
  assert(il.tail->data == 10);
  assert(il.getSize() == 1);

  il.addFront(20);
  assert(il.head->data == 20);
  assert(il.tail->data == 10);
  assert(il.getSize() == 2);

  il.addFront(30);
  assert(il.head->data == 30);
  assert(il.head->next->data == 20);
  assert(il.tail->data == 10);
  assert(il.getSize() == 3);
}
// many more tester methods

void Tester::testAddBack() {
  IntList il;
  il.addBack(10);
  assert(il.head != NULL);
  assert(il.tail != NULL);
  assert(il.head->data == 10);
  assert(il.tail->data == 10);
  assert(il.getSize() == 1);

  il.addBack(20);
  assert(il.head->data == 10);
  assert(il.tail->data == 20);
  assert(il.getSize() == 2);

  il.addBack(30);
  assert(il.head->data == 10);
  assert(il.head->next->data == 20);
  assert(il.tail->data == 30);
  assert(il.getSize() == 3);
}

void Tester::testRemove() {
  IntList il;
  il.addBack(10);
  il.addBack(20);
  il.addBack(30);
  il.addBack(40);

  assert(il.remove(20) == true);
  assert(il.head->data == 10);
  assert(il.head->next->data == 30);
  assert(il.tail->data == 40);
  assert(il.getSize() == 3);

  assert(il.remove(10) == true);
  assert(il.head->data == 30);
  assert(il.getSize() == 2);

  assert(il.remove(40) == true);
  assert(il.head->data == 30);
  assert(il.tail->data == 30);
  assert(il.getSize() == 1);

  assert(il.remove(30) == true);
  assert(il.head == NULL);
  assert(il.tail == NULL);
  assert(il.getSize() == 0);

  assert(il.remove(50) == false);
}

void Tester::testOperatorAccess() {
  IntList il;
  il.addBack(10);
  il.addBack(20);
  il.addBack(30);

  assert(il[0] == 10);
  assert(il[1] == 20);
  assert(il[2] == 30);

  il[1] = 25;
  assert(il[1] == 25);
}

void Tester::testFind() {
  IntList il;
  il.addBack(10);
  il.addBack(20);
  il.addBack(30);

  assert(il.find(10) == 0);
  assert(il.find(20) == 1);
  assert(il.find(30) == 2);
  assert(il.find(40) == -1);
}

void Tester::testGetSize() {
  IntList il;
  assert(il.getSize() == 0);

  il.addFront(10);
  assert(il.getSize() == 1);

  il.addBack(20);
  assert(il.getSize() == 2);

  il.remove(10);
  assert(il.getSize() == 1);

  il.remove(20);
  assert(il.getSize() == 0);
}

void Tester::testCopyConstructor() {
  IntList original;
  original.addBack(10);
  original.addBack(20);
  original.addBack(30);

  IntList copy(original);

  assert(copy.getSize() == 3);
  assert(copy[0] == 10);
  assert(copy[1] == 20);
  assert(copy[2] == 30);

  copy[0] = 100;
  assert(original[0] == 10);
}

void Tester::testAssignmentOperator() {
  IntList original;
  original.addBack(10);
  original.addBack(20);

  IntList assigned;
  assigned.addBack(30);
  assigned.addBack(40);

  assigned = original;

  assert(assigned.getSize() == 2);
  assert(assigned[0] == 10);
  assert(assigned[1] == 20);

  assigned[0] = 100;
  assert(original[0] == 10);
}

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRemove();
  t.testOperatorAccess();
  t.testFind();
  t.testGetSize();
  t.testCopyConstructor();
  t.testAssignmentOperator();
  std::cout << "All tests passed!!" << std::endl;

  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
