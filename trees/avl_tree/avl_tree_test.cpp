#include <gtest/gtest.h>
#include "avl_tree.h"

using data_structures::trees::avl_tree;

class avl_tree_test: public testing::Test {
public:
	avl_tree<int> tree;
};

TEST_F(avl_tree_test, isCreatedEmpty) {
	EXPECT_EQ(0, tree.size());
}

TEST_F(avl_tree_test, insert) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);
	EXPECT_EQ(3, tree.size());
	EXPECT_TRUE(tree.has(42));
	EXPECT_TRUE(tree.has(13));
	EXPECT_TRUE(tree.has(1963));
}

TEST_F(avl_tree_test, inOrderIsOrdered) { 
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);

	auto in_order = tree.in_order();
	ASSERT_TRUE(in_order.size() > 0);

	auto before = in_order.begin();
	for (auto it = ++in_order.begin(); it != in_order.end(); ++it) {
		EXPECT_TRUE(*before < *it);
		++before;
	}
}

TEST_F(avl_tree_test, preOrderIsPreOrdered) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);

	/**
	 * Tree would be:
	 *     42
	 *    /  \
	 *  13   1963
	 */

	auto pre_order = tree.pre_order();
	ASSERT_TRUE(pre_order.size() > 0);

	auto before = pre_order.begin();
	EXPECT_EQ(42, *before);
	++before;
	EXPECT_EQ(13, *before);
	++before;
	EXPECT_EQ(1963, *before);
}

TEST_F(avl_tree_test, postOrderIsPostOrdered) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);

	/**
	 * Tree would be:
	 *     42
	 *    /  \
	 *  13   1963
	 */

	auto post_order = tree.post_order();
	ASSERT_TRUE(post_order.size() > 0);

	auto before = post_order.begin();
	EXPECT_EQ(13, *before);
	++before;
	EXPECT_EQ(1963, *before);
	++before;
	EXPECT_EQ(42, *before);
}

TEST_F(avl_tree_test, insertionsAreBalanced) {
	tree.insert(13);
	tree.insert(42);
	tree.insert(1963);

	/**
	 * Tree would be:
	 * 13
	 *   \
	 *   42
	 *     \
	 *     1963
	 *
	 * So it should be balanced to:
	 *   42
	 *  /  \
	 * 13  1963
	 */

	auto pre_order = tree.pre_order();
	ASSERT_TRUE(pre_order.size() > 0);

	auto before = pre_order.begin();
	EXPECT_EQ(42, *before);
	++before;
	EXPECT_EQ(13, *before);
	++before;
	EXPECT_EQ(1963, *before);
}
