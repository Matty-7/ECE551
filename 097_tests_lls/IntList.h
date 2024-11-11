#ifndef INTLIST_H
#define INTLIST_H

#include <cstddef>  // For size_t

class IntList {
 private:
  class Node {
   public:
    int data;
    Node * next;
    Node * prev;
    Node() : data(0), next(nullptr), prev(nullptr) {}
    explicit Node(int d) : data(d), next(nullptr), prev(nullptr) {}
  };

  Node * head;
  Node * tail;
  size_t size;

 public:
  IntList();
  IntList(const IntList & rhs);
  IntList & operator=(const IntList & rhs);
  ~IntList();

  void addFront(int item);
  void addBack(int item);
  bool remove(int item);
  int & operator[](size_t index);
  const int & operator[](size_t index) const;
  int find(int item) const;
  size_t getSize() const;
};

#endif  // INTLIST_H
