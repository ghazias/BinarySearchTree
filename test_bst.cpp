#include <unordered_map>
#include <vector>

#include "binary_search_tree.hpp"
#include "binary_search_tree.hpp"  // test include guard
#include "catch.hpp"

TEST_CASE("Empty constructor") {
  dsc::BinarySearchTree<int> tree;
  REQUIRE(tree.empty());
}

TEST_CASE("Copy constructor") {
  dsc::BinarySearchTree<int> original{};
  std::vector<int> values = {12, 25, 6, 3, 7, 99};

  for (auto n : values) {
    original.add(n);
  }

  dsc::BinarySearchTree<int> copy(original);

  SECTION("Copy has all values") {
    for (auto v : values) {
      REQUIRE(copy.contains(v));
    }
  }

  SECTION("Copy is deep") {
    for (auto v : values) {
      REQUIRE(&copy.get(v) != &original.get(v));
    }
  }

  SECTION("Copy operations don't affect original") {
    copy.remove(6);
    REQUIRE(original.contains(6));
  }
}

TEST_CASE("Move Constructor") {
  dsc::BinarySearchTree<char> source{};
  std::vector<char> values = {'a', 'b', 'c', 'd'};
  std::unordered_map<char, char*> addresses;

  for (auto v : values) {
    source.add(v);
    addresses[v] = &source.get(v);
    // TODO fix address tracking and iteration for address check
  }

  dsc::BinarySearchTree<char> moved = std::move(source);

  SECTION("Element memory locations haven't changed") {
    for (auto [v, addr] : addresses) {
      REQUIRE(&moved.get(v) == addr);
    }
  }

  SECTION("Assign after move") {
    moved.add('e');
    REQUIRE(moved.contains('e'));
  }

  SECTION("Source list is nulled") { REQUIRE(source.empty()); }
}

TEST_CASE("Copy assignment from a populated list to a new one") {
  dsc::BinarySearchTree<int> original{};
  std::vector<int> values = {349, 12, 18, 590, 445, 351, 1999};

  for (auto v : values) {
    original.add(v);
  }

  SECTION("Empty =") {
    dsc::BinarySearchTree<int> copy = original;

    for (auto v : values) {
      REQUIRE(copy.contains(v));
      REQUIRE(&copy.get(v) != &original.get(v));
    }
  }

  SECTION("Nonempty =") {
    dsc::BinarySearchTree<int> copy;
    for (int i = 14; i < 1000; i *= i) {
      copy.add(i);
    }

    copy = original;

    for (auto v : values) {
      REQUIRE(copy.contains(v));
      REQUIRE(&copy.get(v) != &original.get(v));
    }
  }

  SECTION("Self =") {
    dsc::BinarySearchTree<int>* addr = &original;
    original = original;
    REQUIRE(&original == addr);
  }
}

TEST_CASE("Copy assignment from an empty list to a new one") {
  dsc::BinarySearchTree<int> original{};

  SECTION("Empty =") {
    dsc::BinarySearchTree<int> copy = original;
    REQUIRE(copy.empty());
    REQUIRE(&copy != &original);
  }

  SECTION("Nonempty =") {
    dsc::BinarySearchTree<int> copy{};
    copy.add(500);
    copy.add(250);
    copy.add(750);

    REQUIRE_FALSE(copy.empty());
    copy = original;

    REQUIRE(copy.empty());
    REQUIRE(&copy != &original);
  }

  SECTION("Self =") {
    dsc::BinarySearchTree<int>* addr = &original;
    original = original;

    REQUIRE(original.empty());
    REQUIRE(&original == addr);
  }
}

TEST_CASE("Move assignment") {
  dsc::BinarySearchTree<char> source;
  std::vector<char> values = {'f', 'a', 'm'};
  std::vector<char*> addresses{};
  for (auto v : values) {
    source.add(v);
    addresses[v] = &source.get(v);
  }

  dsc::BinarySearchTree<char> moved{};
  moved.add('c');
  moved.add('k');

  moved = source;

  for (auto v : values) {
    REQUIRE(moved.contains(v));
    REQUIRE(&moved.get(v) == addresses[v]);
  }
}

// TODO == operator implementation and tests

TEST_CASE("add()") {
  dsc::BinarySearchTree<int> tree{};

  tree.add(20);  // add a root
  REQUIRE(tree.contains(20));

  tree.add(10);  // add a left child
  REQUIRE(tree.contains(10));

  tree.add(30);  // add a right child
  REQUIRE(tree.contains(30));
}

TEST_CASE("contains()") {
  dsc::BinarySearchTree<int> tree{};
  std::vector<int> values = {100, 25, 250, 115, 670};

  for (auto n : values) {
    tree.add(n);
  }

  for (auto n : values) {
    REQUIRE(tree.contains(n));
  }

  REQUIRE_FALSE(tree.contains(1));  // invalid search
}

TEST_CASE("get()") {
  dsc::BinarySearchTree<int> tree{};
  std::vector<int> values{50, 60, 70, 80, 65};

  for (auto v : values) {
    tree.add(v);
    REQUIRE(tree.contains(v));
    REQUIRE(tree.get(v) == v);  // strange test
  }
}

TEST_CASE("size()") {
  dsc::BinarySearchTree<int> tree{};
  REQUIRE(tree.size() == 0);

  std::vector<int> values{50, 60, 70, 80, 65};

  for (auto v : values) {
    tree.add(v);
  }

  REQUIRE(tree.size() == values.size());
}

TEST_CASE("remove()") {
  dsc::BinarySearchTree<int> tree{};
  std::vector<int> values{5748, 4893, 920, 400000,
                          21900};  // root at beginning, replacement root at end

  for (auto v : values) {
    tree.add(v);
  }

  SECTION("Stress test") {
    for (auto v : values) {
      REQUIRE(tree.contains(v));
      tree.remove(v);
      REQUIRE_FALSE(tree.contains(v));
    }
  }

  SECTION("Remove root") {
    tree.remove(*values.begin());

    REQUIRE(tree.size() == values.size() - 1);
    REQUIRE_FALSE(tree.contains(values.front()));
  }
}

TEST_CASE("Remove right child with no children - edge case") {
  dsc::BinarySearchTree<int> tree{};
  std::vector<int> values{100, 50, 150, 175, 125};

  for (auto v : values) {
    tree.add(v);
  }

  tree.remove(150);
  REQUIRE_FALSE(tree.contains(150));
  REQUIRE(tree.size() == values.size() - 1);
}

TEST_CASE("empty()") {
  dsc::BinarySearchTree<int> empty_tree{};
  dsc::BinarySearchTree<int> nonempty_tree{};
  nonempty_tree.add(88);

  REQUIRE_FALSE(nonempty_tree.empty());
  REQUIRE(empty_tree.empty());
}

TEST_CASE("in_order()") {
  dsc::BinarySearchTree<int> tree{};
  std::vector<int> values = {10, 40, 50, 60};

  for (auto n : values) {
    tree.add(n);
  }
}

#if 0
TEST_CASE("initializer list constructor") {
  dsc::BinarySearchTree<int> tree = {20, 394};

  REQUIRE(tree.contains(20));
  REQUIRE(tree.contains(394));
}
#endif
