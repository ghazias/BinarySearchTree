#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_

#include <functional>

namespace dsc {
template <typename T>
class BinarySearchTree {
 public:
 // constructors and destructors
  BinarySearchTree() = default;                        // empty tree constructor
  BinarySearchTree(const BinarySearchTree& original);  // copy constructor
  BinarySearchTree(BinarySearchTree&& other);          // move constructor
  // copy assignment
  // move assignment
  ~BinarySearchTree();  // TODO destructor

  // member functions
  void add(const T& element);
  bool contains(const T& element) const;
  T& get(const T& element);
  void remove(const T& element);
  bool empty() const {return root_ == nullptr; }
  void in_order(std::function<void (const T&)>) const;

 private:
  struct Node {
    T element;
    Node* parent;
    Node* left;
    Node* right;
  };

  void in_order(Node* current, std::function<void (const T&)> func) const;
  Node* root_{};
  Node* search(const T& element);
  Node* search(Node* current, const T& element);
  void add(Node* current, const T& element); 
};
}  // namespace dsc

template <typename T>
dsc::BinarySearchTree<T>::~BinarySearchTree() { // TODO destructor
}

template <typename T>
void dsc::BinarySearchTree<T>::in_order(std::function<void (const T&)> func) const {
  in_order(root_, func); 
}

template <typename T>
void dsc::BinarySearchTree<T>::in_order(Node* current, std::function<void (const T&)> func) const {
  if (current != nullptr) {
    in_order(current->left, func);
    func(current->element);
    in_order(current->right, func);
  }
}

template <typename T>
auto dsc::BinarySearchTree<T>::search(const T& element) -> Node* {
  return search(root_, element);
}

template <typename T>
auto dsc::BinarySearchTree<T>::search(Node* current, const T& element)
    -> Node* {
  if (current == nullptr) {
    return nullptr;
  }

  if (current->element == element) {
    return current;
  }

  if (current->element < element) {
    return search(current->right, element);
  }

  return search(current->left, element);
}


template <typename T>
void dsc::BinarySearchTree<T>::add(const T& element) {
  if (root_ == nullptr) {
    root_ = new Node{element, nullptr, nullptr, nullptr};
  } else {
  add(root_, element);
  }
}

template <typename T>
void dsc::BinarySearchTree<T>::add(Node* current, const T& element) {
  if (element < current->element) {
    if (current->left == nullptr) {
     current->left = new Node{element, current, nullptr, nullptr};
     return;
    } else {
      add(current->left, element);
    }
  } else {
    if (current->right == nullptr) {
      current->right = new Node{element, current, nullptr, nullptr};
      return;
    } else {
      add(current->right, element);
    }
  }
}

#endif