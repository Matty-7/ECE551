#include <queue>

#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!

  priority_queue_t pq;

  for (int i = 0; i < 256; i++) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  while (pq.size() > 1) {
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();

    Node * parent = new Node(left, right);
    pq.push(parent);
  }

  return pq.top();
}
