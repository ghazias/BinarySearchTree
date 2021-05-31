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
	//TODO: add assertion for return by ref	
	
}

TEST_CASE("remove()") {
	dsc::BinarySearchTree<int> tree{};
	std::vector<int> values{ 5748, 4893, 920, 400000, 21900};
	
	for (auto n : values) {
		tree.add(n);
	}
	
	for (auto n : values) {
		REQUIRE(tree.contains(n));
		tree.remove(n);
		REQUIRE_FALSE(tree.contains(n));
	}
}

TEST_CASE("remove() stress test") {
	dsc::BinarySearchTree<int> tree{};
	
	for (std::size_t i = 0; i < N; ++i) {
		tree.add(i);
	}
	
	for (std::size_t i = 0; i < N; ++i) {
		REQUIRE(tree.contains(i));
		tree.remove(i);
		REQUIRE_FALSE(tree,contains(i));
	}
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

	void value_2x(int value) { return value * 2; }
	tree.in_order(value2x());
	
	for (auto n : values) {
		REQUIRE(tree.contains(n * 2);
	}
}

TEST_CASE("ptr_to()") {
	
}
