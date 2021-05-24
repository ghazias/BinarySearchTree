#include "binary_search_tree.hpp"
#include "binary_search_tree.hpp" // test include guard
#include "catch.hpp"

TEST_CASE("Empty constructor") { dsc::BinarySearchTree<int> tree; }

TEST_CASE("Copy Constructor") {
  dsc::BinarySearchTree<int> original{};
  original.add(12);
  original.add(88);
  original.add(2);
  original.add(39);
  original.add(200);
  original.add(77);

  dsc::BinarySearchTree<int> copy;
  SECTION("is deep") {}
}