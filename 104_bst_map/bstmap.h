#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  struct Node {
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & key, const V & value) :
        key(key), value(value), left(NULL), right(NULL) {}
  };

  Node * root;

  Node * add(Node * current, const K & key, const V & value) {
    if (current == NULL) {
      return new Node(key, value);
    }
    if (key < current->key) {
      current->left = add(current->left, key, value);
    }
    else if (key > current->key) {
      current->right = add(current->right, key, value);
    }
    else {
      current->value = value;
    }
    return current;
  }

  const V & lookup(Node * current, const K & key) const throw(std::invalid_argument) {
    if (current == NULL) {
      throw std::invalid_argument("Key not found");
    }
    if (key == current->key) {
      return current->value;
    }
    else if (key < current->key) {
      return lookup(current->left, key);
    }
    else {
      return lookup(current->right, key);
    }
  }

  Node * remove(Node * current, const K & key) {
    if (current == NULL) {
      throw std::invalid_argument("Key not found");
    }
    if (key < current->key) {
      current->left = remove(current->left, key);
    }
    else if (key > current->key) {
      current->right = remove(current->right, key);
    }
    else {
      if (current->left == NULL) {
        Node * temp = current->right;
        delete current;
        return temp;
      }
      else if (current->right == NULL) {
        Node * temp = current->left;
        delete current;
        return temp;
      }
      else {
        Node * successor = findMin(current->right);
        current->key = successor->key;
        current->value = successor->value;
        current->right = remove(current->right, successor->key);
      }
    }
    return current;
  }

  Node * findMin(Node * current) {
    while (current->left != NULL) {
      current = current->left;
    }
    return current;
  }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

 public:
  BstMap() : root(NULL) {}

  virtual ~BstMap() { destroy(root); }

  void add(const K & key, const V & value) { root = add(root, key, value); }

  const V & lookup(const K & key) const { return lookup(root, key); }

  void remove(const K & key) { root = remove(root, key); }
};

#endif
