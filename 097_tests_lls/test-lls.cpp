#include <cassert>
#include <iostream>

class IntList {
 private:
  class Node {
   public:
    int data;
    Node * next;
    Node * prev;
    Node(int d = 0) : data(d), next(nullptr), prev(nullptr) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  IntList() : head(nullptr), tail(nullptr), size(0) {}
  IntList(const IntList & rhs) : head(nullptr), tail(nullptr), size(0) {
    Node * current = rhs.head;
    while (current != nullptr) {
      addBack(current->data);
      current = current->next;
    }
  }
  IntList & operator=(const IntList & rhs) {
    if (this != &rhs) {
      // 清空当前列表
      while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
      }
      tail = nullptr;
      size = 0;
      // 复制rhs
      Node * current = rhs.head;
      while (current != nullptr) {
        addBack(current->data);
        current = current->next;
      }
    }
    return *this;
  }
  ~IntList() {
    while (head != nullptr) {
      Node * temp = head;
      head = head->next;
      delete temp;
    }
  }
  void addFront(const int & item) {
    Node * newNode = new Node(item);
    newNode->next = head;
    if (head != nullptr) {
      head->prev = newNode;
    }
    else {
      tail = newNode;
    }
    head = newNode;
    size++;
  }
  void addBack(const int & item) {
    Node * newNode = new Node(item);
    newNode->prev = tail;
    if (tail != nullptr) {
      tail->next = newNode;
    }
    else {
      head = newNode;
    }
    tail = newNode;
    size++;
  }
  bool remove(const int & item) {
    Node * current = head;
    while (current != nullptr) {
      if (current->data == item) {
        if (current->prev != nullptr) {
          current->prev->next = current->next;
        }
        else {
          head = current->next;
        }
        if (current->next != nullptr) {
          current->next->prev = current->prev;
        }
        else {
          tail = current->prev;
        }
        delete current;
        size--;
        return true;
      }
      current = current->next;
    }
    return false;
  }
  int & operator[](int index) {
    assert(index >= 0 && index < size);
    Node * current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }
  const int & operator[](int index) const {
    assert(index >= 0 && index < size);
    Node * current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }
  int find(const int & item) {
    Node * current = head;
    int index = 0;
    while (current != nullptr) {
      if (current->data == item) {
        return index;
      }
      current = current->next;
      index++;
    }
    return -1;
  }
  int getSize() const { return size; }

  friend void testList();
};

void testList() {
  // []
  IntList I1;
  assert(I1.size == 0 && I1.getSize() == 0 && I1.head == nullptr && I1.tail == nullptr);
  IntList I2 = I1;
  assert(I2.size == 0 && I2.getSize() == 0 && I2.head == nullptr && I2.tail == nullptr);
  IntList I4(I1);
  assert(I4.size == 0 && I4.getSize() == 0 && I4.head == nullptr && I4.tail == nullptr);

  // [1]
  I1.addFront(1);
  assert(I1.head == I1.tail && I1.head->data == 1 && I1.head->prev == nullptr &&
         I1.head->next == nullptr && I1.size == 1 && I1.getSize() == 1 &&
         I1.find(1) == 0 && I1[0] == 1);
  I2 = I1;
  assert(I2.head == I2.tail && I2.head->data == 1 && I2.head->prev == nullptr &&
         I2.head->next == nullptr && I2.size == 1 && I2.getSize() == 1 &&
         I2.find(1) == 0 && I2[0] == 1);
  IntList I3(I1);
  assert(I3.head == I3.tail && I3.head->data == 1 && I3.head->prev == nullptr &&
         I3.head->next == nullptr && I3.size == 1 && I3.getSize() == 1 &&
         I3.find(1) == 0 && I3[0] == 1);

  assert(!I1.remove(0));
  assert(I1.head == I1.tail && I1.head->data == 1 && I1.head->prev == nullptr &&
         I1.head->next == nullptr && I1.size == 1 && I1.getSize() == 1 &&
         I1.find(1) == 0 && I1[0] == 1);
  assert(I1.remove(1));
  // []
  assert(I1.size == 0 && I1.getSize() == 0 && I1.head == nullptr && I1.tail == nullptr);

  // [1]
  I1.addFront(1);
  assert(I1.head == I1.tail && I1.head->data == 1 && I1.head->prev == nullptr &&
         I1.head->next == nullptr && I1.size == 1 && I1.getSize() == 1 &&
         I1.find(1) == 0 && I1[0] == 1);
  // []
  I1.remove(1);
  // [1]
  I1.addBack(1);
  assert(I1.head == I1.tail && I1.head->data == 1 && I1.head->prev == nullptr &&
         I1.head->next == nullptr && I1.size == 1 && I1.getSize() == 1 &&
         I1.find(1) == 0 && I1[0] == 1);
  // []
  I1.remove(1);
  // [1]
  I1.addBack(1);
  assert(I1.head == I1.tail && I1.head->data == 1 && I1.head->prev == nullptr &&
         I1.head->next == nullptr && I1.size == 1 && I1.getSize() == 1 &&
         I1.find(1) == 0 && I1[0] == 1);

  // [1 2]
  I1.addBack(2);
  assert(I1.head->next == I1.tail && I1.head->data == 1 && I1.head->prev == nullptr &&
         I1.head->next == I1.tail && I1.tail->data == 2 && I1.tail->prev == I1.head &&
         I1.tail->next == nullptr && I1.size == 2 && I1.getSize() == 2 &&
         I1.find(1) == 0 && I1[0] == 1 && I1[1] == 2 && I1.find(2) == 1);
  I2 = I1;
  assert(I2.head->next == I2.tail && I2.head->data == 1 && I2.head->prev == nullptr &&
         I2.head->next == I2.tail && I2.tail->data == 2 && I2.tail->prev == I2.head &&
         I2.tail->next == nullptr && I2.size == 2 && I2.getSize() == 2 &&
         I2.find(1) == 0 && I2[0] == 1 && I2[1] == 2 && I2.find(2) == 1);
  IntList I5(I1);
  assert(I5.head->next == I5.tail && I5.head->data == 1 && I5.head->prev == nullptr &&
         I5.head->next == I5.tail && I5.tail->data == 2 && I5.tail->prev == I5.head &&
         I5.tail->next == nullptr && I5.size == 2 && I5.getSize() == 2 &&
         I5.find(1) == 0 && I5[0] == 1 && I5[1] == 2 && I5.find(2) == 1);

  // [2 1]
  assert(I1.remove(2));
  I1.addFront(2);
  assert(I1.head->next == I1.tail && I1.head->data == 2 && I1.head->prev == nullptr &&
         I1.head->next == I1.tail && I1.tail->data == 1 && I1.tail->prev == I1.head &&
         I1.tail->next == nullptr && I1.size == 2 && I1.getSize() == 2 &&
         I1.find(1) == 1 && I1[0] == 2 && I1[1] == 1 && I1.find(2) == 0);

  I1.remove(2);
  I1.addBack(2);
  // [1 2 3]
  I1.addBack(3);
  I2 = I1;
  IntList I6(I1);
  assert(I2.head->next->next == I2.tail && I2.head->data == 1 &&
         I2.head->prev == nullptr && I2.tail->data == 3 &&
         I2.head->next == I2.tail->prev && I2.head->next->prev == I2.head &&
         I2.head->next->data == 2 && I2.tail->prev->prev == I2.head &&
         I2.tail->next == nullptr && I2.size == 3 && I2.getSize() == 3 &&
         I2.find(1) == 0 && I2.find(2) == 1 && I2.find(3) == 2 && I2[0] == 1 &&
         I2[1] == 2 && I2[2] == 3);

  assert(I6.head->next->next == I6.tail && I6.head->data == 1 &&
         I6.head->prev == nullptr && I6.tail->data == 3 &&
         I6.head->next == I6.tail->prev && I6.head->next->prev == I6.head &&
         I6.head->next->data == 2 && I6.tail->prev->prev == I6.head &&
         I6.tail->next == nullptr && I6.size == 3 && I6.getSize() == 3 &&
         I6.find(1) == 0 && I6.find(2) == 1 && I6.find(3) == 2 && I6[0] == 1 &&
         I6[1] == 2 && I6[2] == 3);
  assert(I1.head->next->next == I1.tail && I1.head->data == 1 &&
         I1.head->prev == nullptr && I1.tail->data == 3 &&
         I1.head->next == I1.tail->prev && I1.head->next->prev == I1.head &&
         I1.head->next->data == 2 && I1.tail->prev->prev == I1.head &&
         I1.tail->next == nullptr && I1.size == 3 && I1.getSize() == 3 &&
         I1.find(1) == 0 && I1.find(2) == 1 && I1.find(3) == 2 && I1[0] == 1 &&
         I1[1] == 2 && I1[2] == 3);

  // [1 3]
  I1.remove(2);
  assert(I1.head->next == I1.tail && I1.head->data == 1 && I1.head->prev == nullptr &&
         I1.head->next == I1.tail && I1.tail->data == 3 && I1.tail->prev == I1.head &&
         I1.tail->next == nullptr && I1.size == 2 && I1.getSize() == 2 &&
         I1.find(1) == 0 && I1[0] == 1 && I1[1] == 3 && I1.find(3) == 1);
}

int main() {
  testList();
  return 0;
}
