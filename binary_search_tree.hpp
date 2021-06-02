#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_

#include <functional>
#include <cassert>
#include <vector>

namespace dsc {
template <typename T>
class BinarySearchTree {
 public:
  // constructors and destructors
  BinarySearchTree() = default;                        // empty tree constructor
  BinarySearchTree(const BinarySearchTree& original); // copy constructor
  BinarySearchTree(BinarySearchTree&& other) = delete;          // move constructor
  BinarySearchTree& operator=(const BinarySearchTree& original) = delete; // copy assignment
  BinarySearchTree& operator=(BinarySearchTree&& original) = delete; // move assignment
  ~BinarySearchTree(); 

  // member functions
  void add(const T& element);
  bool contains(const T& element) const;
  T& get(const T& element);
  void remove(const T& element);
  bool empty() const { return root_ == nullptr; }
  void in_order(std::function<void(const T&)>) const;

 private:
  struct Node {
    T element;
    Node* parent;
    Node* left;
    Node* right;
  };

  Node* root_{};
  void destroy(Node* current);
  void copy(const BinarySearchTree& other);
  void in_order(Node* current, std::function<void(const T&)> func) const;
  Node* search(const T& element);
  Node* search(Node* current, const T& element);
  void add(Node* current, const T& element);
  void remove(Node* current, const T& element);
  Node** ptr_to(Node* current);
  Node* findMin(Node* current);
  Node* prune(Node* current);
};
}  // namespace dsc

template <typename T>
dsc::BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& original) {
  if (original.root_ == nullptr) {
    root_ = nullptr;
  } else {
  copy(this->root_, original);
  }
} // copy constructor

template <typename T>
dsc::BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& other) : root_{other.root_} {
    other.root_ = nullptr;
} // move constructor

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& original) {
  if (this != &original) {
    destroy();
    copy(original);
  }
  return *this;
} // copy assignment

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& other) {
  if (this != &other) {
    destroy();

    root_ = other.root_;

    other.root_ = nullptr;
}
  return *this;
} // move assignment

template <typename T>
void dsc::BinarySearchTree<T>::copy(Node*& current, Node*& original) {
  if (original == nullptr) {
    current = nullptr;
  }

  current = new Node{original->element, original->parent, original->left, original->right};
  copy(current->left, original->left);
  copy(current->right, original->right);
}

template <typename T>
dsc::BinarySearchTree<T>::~BinarySearchTree() {
  destroy(root_);
  root_ = nullptr;
}

template <typename T>
void dsc::BinarySearchTree<T>::destroy(Node* current) {
  if (current != nullptr) {
    destroy(current->left);
    destroy(current->right);
    delete current;
  }
}

template <typename T>
void dsc::BinarySearchTree<T>::in_order(
    std::function<void(const T&)> func) const {
  in_order(root_, func);
}

template <typename T>
void dsc::BinarySearchTree<T>::in_order(
    Node* current, std::function<void(const T&)> func) const {
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

template <typename T>
T& dsc::BinarySearchTree<T>::get(const T& element) {
  return search(element)->element;
}

template <typename T>
void dsc::BinarySearchTree<T>::remove(const T& element) {
  // TODO root removal special case

  remove(root_, element);
}

template <typename T>
void dsc::BinarySearchTree<T>::remove(Node* current, const T& element) {
  if (current == nullptr) {
    return;
  }
  if (element < current->element) {
    remove(current->left, element);  // recurse to left subtree
  }

  if (element > current->element) {
    remove(current->right, element);  // recurse to right subtree
  }

  if (current->element == element) {
    prune(current);
    delete current;
  }
}

  template <typename T>
  auto dsc::BinarySearchTree<T>::ptr_to(Node* current)->Node** {
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
  auto dsc::BinarySearchTree<T>::findMin(Node* current)->Node* {
    return current->left == nullptr ? current : findMin(current->left);
  }

  template <typename T>
  auto dsc::BinarySearchTree<T>::prune(Node* current) -> Node* {
      if (current == nullptr) {
    return nullptr;
  }

    if (current->left == nullptr &&
        current->right == nullptr) {  // node is leaf
        *ptr_to(current) = nullptr;
        return current;
      }

      if (current->left != nullptr &&
          current->right == nullptr) {  // left child only
        *ptr_to(current) = current->left;
        current->left->parent = current->parent;
        return current;
      }

      if (current->right != nullptr &&
          current->left == nullptr) {  // right child only
        *ptr_to(current) = current->right;
        current->right->parent = current->parent;
        return current;
      }

      assert(current->left != nullptr && current->right != nullptr); // two children
      Node* successor = findMin(current->right); // find successor
      prune(successor);
      successor->parent = current->parent; // update successor's pointers
      successor->left = current->left;
      successor->right = current->right;

      *ptr_to(current) = successor; // update current->parent to point to successor
      current->left->parent = successor; // update current children to point to successor
      current->right->parent = successor;

      return current;
    }

  template <typename T>
  bool contains(const T& element) {
    return search(element);
  }

#endif
