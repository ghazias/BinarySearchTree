#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_

namespace dsc {
template <typename T> class BinarySearchTree {
public:
  BinarySearchTree() = default;                       // empty tree constructor
  BinarySearchTree(const BinarySearchTree &original); // copy constructor
  BinarySearchTree(BinarySearchTree &&other);         // move constructor
  // copy assignment
  // move assignment
  ~BinarySearchTree(); // destructor
  void add(T element);
  bool contains(T element) const;
  T get(T element); // could be const?
  Node search(T element);

private:
  struct Node {
    T element;
    Node *parent;
    Node *left;
    Node *right;
  };
};
} // namespace dsc

template <typename T> dsc::BinarySearchTree::Node search(T element) {}

template <typename T> void dsc::BinarySearchTree<T>::add(T element) {
  Node *current = root; // how to define root in class?
  if current
    ->element
}

#endif