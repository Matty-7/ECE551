#ifndef OUR_AVL_TREE_HPP
#define OUR_AVL_TREE_HPP

#include <algorithm>
#include <functional>
#include <set>

template<typename K, typename V, typename CompareK = std::less<K>, typename CompareV = std::less<V>>
class AVLMultiMap {
 private:
  class Node {
   public:
    K key;
    std::set<V, CompareV> vals;
    int height;
    Node* left;
    Node* right;

    Node(const K& key_, const V& val_)
        : key(key_), vals(), height(0), left(NULL), right(NULL) {
      vals.insert(val_);
    }
    int getLeftChildHeight() const { return left == NULL ? -1 : left->height; }
    int getRightChildHeight() const { return right == NULL ? -1 : right->height; }
    void updateHeight() {
      height = 1 + std::max(getLeftChildHeight(), getRightChildHeight());
    }
  };

  Node* root;
  CompareK cmp;

  Node* insertHelper(Node* curr, const K& key, const V& val);
  Node* deleteHelper(Node* curr, const K& key, const V& val);
  Node* findLowerBoundHelper(Node* node, const K& key) const;
  Node* findNextInOrder(Node* node) const;
  Node* findFirstMatchingNode(Node* node, const std::function<bool(Node*)>& condition) const;
  Node* rebalance(Node* curr);
  void recursiveDelete(Node* curr);

 public:
  AVLMultiMap() : root(NULL), cmp() {}
  ~AVLMultiMap() { recursiveDelete(root); }

  void add(const K& key, const V& val) { root = insertHelper(root, key, val); }
  void remove(const K& key, const V& val) { root = deleteHelper(root, key, val); }
  Node* findLowerBound(const K& key) const { return findLowerBoundHelper(root, key); }
  Node* getNext(Node* current, const std::function<bool(Node*)>& condition) const;

  Node* next(Node* node) const { return findNextInOrder(node); }
};

// Implementation of helper functions
template<typename K, typename V, typename CompareK, typename CompareV>
typename AVLMultiMap<K, V, CompareK, CompareV>::Node* 
AVLMultiMap<K, V, CompareK, CompareV>::insertHelper(Node* curr, const K& key, const V& val) {
  if (curr == NULL) {
    return new Node(key, val);
  }
  if (cmp(key, curr->key)) {
    curr->left = insertHelper(curr->left, key, val);
  } else if (cmp(curr->key, key)) {
    curr->right = insertHelper(curr->right, key, val);
  } else {
    curr->vals.insert(val);
    return curr;
  }
  return rebalance(curr);
}

template<typename K, typename V, typename CompareK, typename CompareV>
typename AVLMultiMap<K, V, CompareK, CompareV>::Node* 
AVLMultiMap<K, V, CompareK, CompareV>::deleteHelper(Node* curr, const K& key, const V& val) {
  if (curr == NULL) {
    return NULL;
  }
  if (cmp(key, curr->key)) {
    curr->left = deleteHelper(curr->left, key, val);
  } else if (cmp(curr->key, key)) {
    curr->right = deleteHelper(curr->right, key, val);
  } else {
    curr->vals.erase(val);
    if (!curr->vals.empty()) {
      return curr;
    }
    if (curr->left == NULL || curr->right == NULL) {
      Node* tmp = curr->left ? curr->left : curr->right;
      delete curr;
      return tmp;
    }
    Node* successor = curr->right;
    while (successor->left != NULL) {
      successor = successor->left;
    }
    curr->key = successor->key;
    curr->vals = successor->vals;
    curr->right = deleteHelper(curr->right, successor->key, *successor->vals.begin());
  }
  return rebalance(curr);
}

template<typename K, typename V, typename CompareK, typename CompareV>
typename AVLMultiMap<K, V, CompareK, CompareV>::Node* 
AVLMultiMap<K, V, CompareK, CompareV>::findLowerBoundHelper(Node* node, const K& key) const {
  Node* bestMatch = NULL;
  while (node != NULL) {
    if (!cmp(node->key, key)) {
      bestMatch = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return bestMatch;
}

template<typename K, typename V, typename CompareK, typename CompareV>
typename AVLMultiMap<K, V, CompareK, CompareV>::Node* 
AVLMultiMap<K, V, CompareK, CompareV>::findNextInOrder(Node* node) const {
  if (node->right != NULL) {
    Node* current = node->right;
    while (current->left != NULL) {
      current = current->left;
    }
    return current;
  }
  Node* successor = NULL;
  Node* ancestor = root;
  while (ancestor != NULL) {
    if (cmp(node->key, ancestor->key)) {
      successor = ancestor;
      ancestor = ancestor->left;
    } else if (cmp(ancestor->key, node->key)) {
      ancestor = ancestor->right;
    } else {
      break;
    }
  }
  return successor;
}

template<typename K, typename V, typename CompareK, typename CompareV>
typename AVLMultiMap<K, V, CompareK, CompareV>::Node* 
AVLMultiMap<K, V, CompareK, CompareV>::findFirstMatchingNode(
    Node* node, const std::function<bool(Node*)>& condition) const {
  if (node == NULL) {
    return NULL;
  }
  if (condition(node)) {
    return node;
  }
  Node* leftResult = findFirstMatchingNode(node->left, condition);
  if (leftResult != NULL) {
    return leftResult;
  }
  return findFirstMatchingNode(node->right, condition);
}

template<typename K, typename V, typename CompareK, typename CompareV>
typename AVLMultiMap<K, V, CompareK, CompareV>::Node* 
AVLMultiMap<K, V, CompareK, CompareV>::getNext(Node* current, const std::function<bool(Node*)>& condition) const {
  Node* nextNode = findNextInOrder(current);
  while (nextNode != NULL) {
    if (condition(nextNode)) {
      return nextNode;
    }
    nextNode = findNextInOrder(nextNode);
  }
  return NULL;
}

template<typename K, typename V, typename CompareK, typename CompareV>
void AVLMultiMap<K, V, CompareK, CompareV>::recursiveDelete(Node* curr) {
  if (curr == NULL) {
    return;
  }
  recursiveDelete(curr->left);
  recursiveDelete(curr->right);
  delete curr;
}

#endif
