#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_

#include <cassert>
#include <functional>
#include <vector>

namespace dsc {
template <typename T>
class BinarySearchTree {
 public:
  BinarySearchTree() = default;                        // empty constructor
  BinarySearchTree(const BinarySearchTree& original);  // copy constructor
  BinarySearchTree(BinarySearchTree&& other);          // move constructor
  BinarySearchTree& operator=(
      const BinarySearchTree& original);                     // copy assignment
  BinarySearchTree& operator=(BinarySearchTree&& original);  // move assignment
  ~BinarySearchTree();                                       // destructor

  void add(const T& element);             // adds element to tree
  bool contains(const T& element) const;  // checks if query is present in tree
  T& get(const T& element);               // captures element by reference
  void remove(const T& element);          // removes element from tree
  bool empty() const { return root_ == nullptr; }  // checks if tree is empty
  void in_order(std::function<void(const T&)>)
      const;  // functional method for applying in order
  std::size_t size() const { return size_impl(root_); }

 private:
  struct Node {
    T element;
    Node* parent;
    Node* left;
    Node* right;
  };

  Node* root_{};

  void destroy(Node* current);
  Node* copy(Node* parent, Node* current);
  void in_order_impl(Node* current, std::function<void(const T&)> func) const;
  Node* search(const T& element) const;
  Node* search_impl(Node* current, const T& element) const;
  void add_impl(Node* current, const T& element);
  void remove_impl(Node* current, const T& element);

  Node** ptr_to(Node* current);   // determines node position
  Node* find_min(Node* current);  // finds replacement node
  Node* prune(Node* current);     // removes node without deleting
  std::size_t size_impl(Node* start) const;
};
}  // namespace dsc

template <typename T>
std::size_t dsc::BinarySearchTree<T>::size_impl(Node* current) const {
  if (current == nullptr) {
    return 0;
  }

  std::size_t left = size_impl(current->left);
  std::size_t right = size_impl(current->right);
  return left + right + 1;
}

template <typename T>
dsc::BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& original) {
  root_ = copy(nullptr, original.root_);
}  // copy constructor

template <typename T>
auto dsc::BinarySearchTree<T>::copy(Node* parent, Node* current) -> Node* {
  if (!current) {
    return nullptr;
  }

  auto new_node = new Node{current->element, parent, nullptr, nullptr};
  new_node->left = copy(new_node, current->left);
  new_node->right = copy(new_node, current->right);
  return new_node;
}  // copy implementation

template <typename T>
dsc::BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& other)
    : root_{other.root_} {
  other.root_ = nullptr;
}  // move constructor

template <typename T>
dsc::BinarySearchTree<T>& dsc::BinarySearchTree<T>::operator=(
    const BinarySearchTree<T>& original) {
  if (this != &original) {
    destroy(root_);
    root_ = copy(nullptr, original.root_);
  }

  return *this;
}  // copy assignment

template <typename T>
dsc::BinarySearchTree<T>& dsc::BinarySearchTree<T>::operator=(
    BinarySearchTree<T>&& other) {
  if (this != &other) {
    destroy();
    root_ = other.root_;
    other.root_ = nullptr;
  }

  return *this;
}  // move assignment

template <typename T>
dsc::BinarySearchTree<T>::~BinarySearchTree() {
  destroy(root_);
  root_ = nullptr;
}  // destructor

template <typename T>
void dsc::BinarySearchTree<T>::destroy(Node* current) {
  if (current != nullptr) {
    destroy(current->left);
    destroy(current->right);
    delete current;
  }
}  // destructor implementation

template <typename T>
void dsc::BinarySearchTree<T>::in_order(
    std::function<void(const T&)> func) const {
  in_order_impl(root_, func);
}

template <typename T>
void dsc::BinarySearchTree<T>::in_order_impl(
    Node* current, std::function<void(const T&)> func) const {
  if (current != nullptr) {
    in_order_impl(current->left, func);
    func(current->element);
    in_order_impl(current->right, func);
  }
}

template <typename T>
T& dsc::BinarySearchTree<T>::get(const T& element) {
  return search(element)->element;
}

template <typename T>
auto dsc::BinarySearchTree<T>::search(const T& element) const -> Node* {
  return search_impl(root_, element);
}

template <typename T>
auto dsc::BinarySearchTree<T>::search_impl(Node* current,
                                           const T& element) const -> Node* {
  if (current == nullptr) {
    return nullptr;
  }

  if (current->element == element) {
    return current;
  }

  if (current->element < element) {
    return search_impl(current->right, element);
  }

  return search_impl(current->left, element);
}

template <typename T>
void dsc::BinarySearchTree<T>::add(const T& element) {
  if (root_ == nullptr) {
    root_ = new Node{element, nullptr, nullptr, nullptr};
  } else {
    add_impl(root_, element);
  }
}

template <typename T>
void dsc::BinarySearchTree<T>::add_impl(Node* current, const T& element) {
  if (element < current->element) {
    if (current->left == nullptr) {
      current->left = new Node{element, current, nullptr, nullptr};
      return;
    } else {
      add_impl(current->left, element);
    }
  } else {
    if (current->right == nullptr) {
      current->right = new Node{element, current, nullptr, nullptr};
      return;
    } else {
      add_impl(current->right, element);
    }
  }
}

template <typename T>
bool dsc::BinarySearchTree<T>::contains(const T& element) const {
  return search(element);
}

template <typename T>
void dsc::BinarySearchTree<T>::remove(const T& element) {
  remove_impl(root_, element);
}

template <typename T>
void dsc::BinarySearchTree<T>::remove_impl(Node* current, const T& element) {
  if (current == nullptr) {
    return;
  }
  if (element < current->element) {
    remove_impl(current->left, element);  // recurse to left subtree
  }

  if (element > current->element) {
    remove_impl(current->right, element);  // recurse to right subtree
  }

  if (current->element == element) {
    prune(current);
    delete current;
  }
}

template <typename T>
auto dsc::BinarySearchTree<T>::ptr_to(Node* current) -> Node** {
  if (current->parent == nullptr) {
    return &root_;
  }

  if (current->parent->left == current) {
    return &current->parent->left;
  }

  assert(current->parent->right == current);
  return &current->parent->right;
}

template <typename T>
auto dsc::BinarySearchTree<T>::find_min(Node* current) -> Node* {
  return current->left == nullptr ? current : find_min(current->left);
}

template <typename T>
auto dsc::BinarySearchTree<T>::prune(Node* current) -> Node* {
  if (current == nullptr) {
    return nullptr;
  }

  if (current->left == nullptr && current->right == nullptr) {
    *ptr_to(current) = nullptr;
    return current;
  }  // node is leaf

  if (current->left != nullptr && current->right == nullptr) {
    *ptr_to(current) = current->left;
    current->left->parent = current->parent;
    return current;
  }  // left child only

  if (current->right != nullptr && current->left == nullptr) {
    *ptr_to(current) = current->right;
    current->right->parent = current->parent;
    return current;
  }  // right child only

  assert(current->left != nullptr &&
         current->right != nullptr);           // two children
  Node* successor = find_min(current->right);  // find successor
  prune(successor);
  successor->parent = current->parent;  // update successor's pointers
  successor->left = current->left;
  successor->right = current->right;

  *ptr_to(current) = successor;  // update current->parent to point to successor
  current->left->parent =
      successor;  // update current children to point to successor
  if (current->right != nullptr) {
    // if current->right had no left children, then successor IS current->right
    // and was pruned so current doesn't have a right child
    current->right->parent = successor;
  }

  return current;
}

#endif
