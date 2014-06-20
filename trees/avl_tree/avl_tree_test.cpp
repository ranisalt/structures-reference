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

TEST_F(avl_tree_test, remove) {
	tree.insert(42);
	tree.remove(42);
	EXPECT_FALSE(tree.has(42));
	EXPECT_EQ(0, tree.size());
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

TEST_F(avl_tree_test, balancedInsertion) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);

	/**
	 * Tree would be:
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

TEST_F(avl_tree_test, leftLeftInsertion) {
	tree.insert(1963);
	tree.insert(42);
	tree.insert(13);

	/**
	 * Tree would be:
	 *     1963
	 *    /
	 *   42
	 *  /
	 * 13
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

TEST_F(avl_tree_test, leftRightInsertion) {
	tree.insert(1963);
	tree.insert(13);
	tree.insert(42);

	/**
	 * Tree would be:
	 *   1963
	 *  /
	 * 13
	 *   \
	 *   42
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

TEST_F(avl_tree_test, rightLeftInsertion) {
	tree.insert(13);
	tree.insert(1963);
	tree.insert(42);

	/**
	 * Tree would be:
	 * 13
	 *   \
	 *   1963
	 *  /
	 * 42
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

TEST_F(avl_tree_test, rightRightInsertion) {
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

TEST_F(avl_tree_test, leafRemoval) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);
	tree.remove(13);
	
	auto pre_order = tree.pre_order();
	ASSERT_TRUE(pre_order.size() > 0);

	auto before = pre_order.begin();
	EXPECT_EQ(42, *before);
	++before;
	EXPECT_EQ(1963, *before);
}

TEST_F(avl_tree_test, nodeWithLeftChildRemoval) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);
	tree.insert(7);
	tree.remove(13);
	
	auto pre_order = tree.pre_order();
	ASSERT_TRUE(pre_order.size() > 0);

	auto before = pre_order.begin();
	EXPECT_EQ(42, *before);
	++before;
	EXPECT_EQ(7, *before);
	++before;
	EXPECT_EQ(1963, *before);
}

TEST_F(avl_tree_test, nodeWithRightChildRemoval) {
	tree.insert(42);
	tree.insert(7);
	tree.insert(1963);
	tree.insert(13);
	tree.remove(7);
	
	auto pre_order = tree.pre_order();
	ASSERT_TRUE(pre_order.size() > 0);

	auto before = pre_order.begin();
	EXPECT_EQ(42, *before);
	++before;
	EXPECT_EQ(13, *before);
	++before;
	EXPECT_EQ(1963, *before);
}

TEST_F(avl_tree_test, nodeWithBothChildRemoval) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);
	tree.remove(42);
	
	auto pre_order = tree.pre_order();
	ASSERT_TRUE(pre_order.size() > 0);

	auto before = pre_order.begin();
	EXPECT_EQ(1963, *before);
	++before;
	EXPECT_EQ(13, *before);
}

TEST_F(avl_tree_test, repeatedInsertionThrows) {
	tree.insert(42);
	EXPECT_THROW(tree.insert(42), std::exception);
}

TEST_F(avl_tree_test, valueNotPresentRemovalThrows) {
	EXPECT_THROW(tree.remove(42), std::exception);
}

TEST_F(avl_tree_test, copyConstructIsCreatedCorrect) {
	tree.insert(42);
	tree.insert(13);
	tree.insert(1963);
}
