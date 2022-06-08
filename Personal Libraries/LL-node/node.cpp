#include <cstddef>

#include "node.hpp"

node::node() {
  next = nullptr
}

node::node(int d) {
  data = d;
  next = nullptr;
}

node::node(int d, node *n) {
  data = d;
  next = n;
}
