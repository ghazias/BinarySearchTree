#include "binary_search_tree.hpp"
#include <vector>

int main() {
  dsc::BinarySearchTree<int> original{};
  std::vector<int> vals = {100, 50, 150, 25, 125, 175, 200, 210};

  for (auto n : vals) {
    original.add(n);
  }

  original.remove(100);
}
