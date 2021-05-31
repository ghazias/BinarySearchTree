#include "binary_search_tree.hpp"
#include "binary_search_tree.hpp" // test include guard
#include "catch.hpp"
#include <vector>

TEST_CASE("Empty constructor") { 
  dsc::BinarySearchTree<int> tree; 
  REQUIRE(tree.empty());
}

TEST_CASE("Copy Constructor") {
  dsc::BinarySearchTree<int> original{};
  std::vector<int> values = {12, 25, 6, 3, 7, 99};

  for (auto n : values) {
    original.add(n);
  }

  dsc::BinarySearchTree<int> copy;
	  SECTION("is deep") {
		copy = original;	
		REQUIRE(&copy != &original);
		REQUIRE(copy.root_ != original.root_);
	}
}

TEST_CASE("Move Constructor") {
	dsc::BinarySearchTree<char> original{};
	
}

TEST_CASE("add()") {
	dsc::BinarySearchTree<int> tree{};
	std::vector<int> values = {100, 25, 250, 115, 670};

	for (auto n : values) {
		tree.add(n);
	}
	
	for (auto n : values) {
		REQUIRE(tree.contains(n));
	}

}

TEST_CASE("add() stress test") {
	dsc::BinarySearchTree<int> tree{};
	
	for (std::size_t i = 0; i < N; ++i) {
		tree.add(i);
	}

	for (std::size_t i = 0; i < N; ++i) {
		REQUIRE(tree.contains(i));
	}
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

}

TEST_CASE("get()") {
	dsc::BinarySearchTree<int> tree;
	std::vector<int> values{50, 60, 70, 80, 65};	

	for (auto n : values) {
		tree.add(n);
	}
	
	for (auto n : values) {
		REQUIRE(tree.get(n) == n);
		REQUIRE(&tree.get(n) != &n);
	}
}

TEST_CASE("get() stress test") {
	dsc::BinarySearchTree<int> tree;
	for (std::size_t i = 0; i < N; ++i) {
		tree.add(i);
	}
	
	for (std::size_t i = 0; i < N; ++i) {
		REQUIRE(tree.get(i) == i);
	}
	
	
}
