#include <cassert>
#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  void testDefaultConstructor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  void testAdd() {
    IntList il;
    il.addFront(1);  // [1]
    assert(il.getSize() == 1);
    assert(il.head != NULL);
    assert(il.tail == il.head);
    assert(il.head->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    il.addFront(2);  // [2,1]
    assert(il.getSize() == 2);
    assert(il.head != NULL);
    assert(il.head->next != NULL);
    assert(il.tail == il.head->next);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.head->next->next == NULL);

    il.addBack(3);  // [2,1,3]
    assert(il.getSize() == 3);
    assert(il.head->data == 2);
    assert(il.head->next->data == 1);
    assert(il.head->next->next->data == 3);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == il.head->next);
    assert(il.head->next == il.tail->prev);
    assert(il.head->next->prev == il.head);
  }

  void testRuleOfThree() {
    IntList list1;
    list1.addFront(1);
    list1.addBack(2);  // [1,2]

    IntList list2(list1);  // Copy constructor
    assert(list2.getSize() == 2);
    assert(list2.head->data == 1);
    assert(list2.head->next->data == 2);
    assert(list2.head->next == list2.tail);
    assert(list2.tail->prev == list2.head);
    assert(list2.head->prev == NULL);
    assert(list2.tail->next == NULL);

    list1.remove(2);  // [1]
    list2 = list1;    // Assignment operator
    assert(list2.getSize() == 1);
    assert(list2.head->data == 1);
    assert(list2.head == list2.tail);
    assert(list2.head->next == NULL);
    assert(list2.head->prev == NULL);
  }

  void testRemoval() {
    IntList il;
    il.addFront(1);
    il.addBack(2);  // [1,2]

    bool flag = il.remove(2);  // Remove 2 -> [1]
    assert(flag == true);
    assert(il.getSize() == 1);
    assert(il.head->data == 1);
    assert(il.head == il.tail);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    il.addFront(2);       // [2,1]
    flag = il.remove(2);  // Remove 2 -> [1]
    assert(flag == true);
    assert(il.getSize() == 1);
    assert(il.head->data == 1);
    assert(il.head == il.tail);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    flag = il.remove(2);  // Try to remove 2 again -> [1]
    assert(flag == false);
    assert(il.getSize() == 1);
    assert(il.head->data == 1);
    assert(il.head == il.tail);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    il.addFront(1);       // [1,1]
    flag = il.remove(1);  // Remove first 1 -> [1]
    assert(flag == true);
    assert(il.getSize() == 1);
    assert(il.head->data == 1);
    assert(il.head == il.tail);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    flag = il.remove(1);  // Remove second 1 -> []
    assert(flag == true);
    assert(il.getSize() == 0);
    assert(il.head == NULL);
    assert(il.tail == NULL);

    il.addFront(1);
    il.addFront(3);
    il.addFront(2);       // [2,3,1]
    flag = il.remove(3);  // Remove 3 -> [2,1]
    assert(flag == true);
    assert(il.getSize() == 2);
    assert(il.head->data == 2);
    assert(il.tail->data == 1);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
  }
};

int main() {
  Tester t;
  t.testDefaultConstructor();
  t.testAdd();
  t.testRemoval();
  t.testRuleOfThree();
  return EXIT_SUCCESS;
}
