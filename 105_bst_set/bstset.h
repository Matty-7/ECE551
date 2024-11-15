#ifndef __BSTSET_H__
#define __BSTSET_H__

#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

  void deleteTree(Node * current) {
    if (current != NULL) {
      deleteTree(current->left);
      deleteTree(current->right);
      delete current;
    }
  }

  Node * copyTree(const Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * newNode = new Node(current->key);
    newNode->left = copyTree(current->left);
    newNode->right = copyTree(current->right);
    return newNode;
  }

  Node * removeNode(Node * current, const T & key) {
    if (current == NULL) {
      return NULL;
    }
    if (key < current->key) {
      current->left = removeNode(current->left, key);
    }
    else if (key > current->key) {
      current->right = removeNode(current->right, key);
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
        Node * successor = current->right;
        while (successor->left != NULL) {
          successor = successor->left;
        }
        current->key = successor->key;
        current->right = removeNode(current->right, successor->key);
      }
    }
    return current;
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) : root(NULL) { root = copyTree(rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      deleteTree(root);
      root = copyTree(rhs.root);
    }
    return *this;
  }
  virtual void add(const T & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else if (key > (*current)->key) {
        current = &(*current)->right;
      }
      else {
        return;  // Key already exists
      }
    }
    *current = new Node(key);
  }
  virtual bool contains(const T & key) const {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return true;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }
  virtual void remove(const T & key) { root = removeNode(root, key); }
  virtual ~BstSet() { deleteTree(root); }
};

#endif
