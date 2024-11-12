#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node(const T & data) : data(data), next(NULL), prev(NULL) {}
  };

  Node * head;
  Node * tail;
  int size;

 public:
  class IndexOutOfRange : public std::exception {
   public:
    const char * what() const throw() { return "Index out of range"; }
  };

  LinkedList() : head(NULL), tail(NULL), size(0) {}

  ~LinkedList() {
    Node * current = head;
    while (current != NULL) {
      Node * next = current->next;
      delete current;
      current = next;
    }
  }

  LinkedList(const LinkedList & other) : head(NULL), tail(NULL), size(0) {
    Node * current = other.head;
    while (current != NULL) {
      addBack(current->data);
      current = current->next;
    }
  }

  LinkedList & operator=(LinkedList other) {
    swap(*this, other);
    return *this;
  }

  friend void swap(LinkedList & first, LinkedList & second) {
    std::swap(first.head, second.head);
    std::swap(first.tail, second.tail);
    std::swap(first.size, second.size);
  }

  void addFront(const T & item) {
    Node * new_node = new Node(item);
    new_node->next = head;
    if (head != NULL) {
      head->prev = new_node;
    }

    head = new_node;
    if (tail == NULL) {
      tail = new_node;
    }
    ++size;
  }

  void addBack(const T & item) {
    Node * new_node = new Node(item);
    new_node->prev = tail;
    if (tail != NULL) {
      tail->next = new_node;
    }
    tail = new_node;
    if (head == NULL) {
      head = new_node;
    }
    ++size;
  }

  bool remove(const T & item) {
    Node * current = head;
    while (current != NULL) {
      if (current->data == item) {
        if (current->prev) {
          current->prev->next = current->next;
        }
        else {
          head = current->next;
        }

        if (current->next) {
          current->next->prev = current->prev;
        }
        else {
          tail = current->prev;
        }

        delete current;
        --size;
        return true;
      }
      current = current->next;
    }
    return false;
  }

  T & operator[](int index) {
    if (index < 0 || index >= size)
      throw IndexOutOfRange();
    Node * current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }

    return current->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= size)
      throw IndexOutOfRange();
    Node * current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }

    return current->data;
  }

  int find(const T & item) const {
    Node * current = head;
    int index = 0;
    while (current != NULL) {
      if (current->data == item) {
        return index;
      }
      current = current->next;
      ++index;
    }
    return -1;
  }

  int getSize() const { return size; }
};

#endif
