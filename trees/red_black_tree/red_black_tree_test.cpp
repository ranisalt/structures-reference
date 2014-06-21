#include <gtest/gtest.h>
#include "red_black_tree.h"

using data_structures::trees::red_black_tree;

class red_black_tree_test: public testing::Test {
public:
	red_black_tree<int> tree;
};

TEST_F(red_black_tree_test, isCreatedEmpty) {
	EXPECT_EQ(0, tree.size());
}

TEST_F(red_black_tree_test, insert) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);
	EXPECT_EQ(3, tree.size());
	EXPECT_TRUE(tree.has(42));
	EXPECT_TRUE(tree.has(13));
	EXPECT_TRUE(tree.has(1963));
}

TEST_F(red_black_tree_test, remove) {
	tree.insert(42);
	tree.remove(42);
	EXPECT_FALSE(tree.has(42));
	EXPECT_EQ(0, tree.size());
}
