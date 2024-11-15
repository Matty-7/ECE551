#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

#include "map.h"
using namespace std;

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    pair<K, V> data;
    Node * left;
    Node * right;
    Node() : data(0, 0), left(NULL), right(NULL) {}
    Node(K k, V v) : data(k, v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & m) : root(NULL) { copyTree(&root, m.root); }
  void copyTree(Node ** n, const Node * m) {
    if (m != NULL) {
      *n = new Node(m->data.first, m->data.second);
      copyTree(&(*n)->left, m->left);
      copyTree(&(*n)->right, m->right);
    }
  }
  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if ((*current)->data.first == key) {
        (*current)->data.second = value;
        return;
      }
      else if ((*current)->data.first > key) {
        current = &((*current)->left);
      }
      else
        current = &((*current)->right);
    }
    *current = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->data.first == key) {
        return current->data.second;
      }
      else if (current->data.first > key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("key does not exist");
  }
  Node ** find(const K & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if ((*current)->data.first == key) {
        return current;
      }
      else if ((*current)->data.first > key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    return NULL;
  }
  const BstMap & operator=(const BstMap & m) {
    if (&m != this) {
      BstMap temp = m;
      Node * t = root;
      root = temp.root;
      temp.root = t;
    }
    return *this;
  }
  virtual void remove(const K & key) {
    Node ** N = find(key);
    Node * N2 = *N;
    if (N2 == NULL) {
      return;
    }
    if (N2->left == NULL) {
      *N = N2->right;
    }
    else {
      Node ** vic = &N2->left;
      while ((*vic)->right != NULL) {
        vic = &(*vic)->right;
      }
      *N = *vic;
      *vic = (*vic)->left;
      (*N)->left = N2->left;
      (*N)->right = N2->right;
    }
    delete N2;
  }
  void freeBst(Node * r) {
    if (r == NULL) {
      return;
    }
    freeBst(r->left);
    freeBst(r->right);
    delete r;
  }
  Node * getRoot() { return root; }
  void print(Node * r) {
    if (r == NULL)
      return;
    print(r->left);
    cout << r->data.first << " " << r->data.second << endl;
    print(r->right);
  }
  virtual ~BstMap() {
    freeBst(root);
    root = NULL;
  }
};
