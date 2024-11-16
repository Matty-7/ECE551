#include <iostream>
#include <queue>

#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!

  priority_queue_t pq;

  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      std::cout << "Creating node for symbol: " << i << " with frequency: " << counts[i]
                << std::endl;
      pq.push(new Node(i, counts[i]));
    }
  }

  while (pq.size() > 1) {
    Node * n1 = pq.top();
    pq.pop();
    Node * n2 = pq.top();
    pq.pop();
    std::cout << "Combining nodes with frequencies: " << n1->freq << " and " << n2->freq
              << std::endl;
    Node * n3 = new Node(n1, n2);
    pq.push(n3);
  }

  return pq.top();
}
