/*
 * binary_search_tree_test.cpp
 *
 *  Created on: 29/05/2014
 *      Author: ranieri
 */

#include <gtest/gtest.h>
#include "binary_search_tree.h"
#include "linked/doubly_linked_list/doubly_linked_list.h"

using data_structures::trees::binary_search_tree;
using data_structures::linked::doubly_linked_list;

class binary_search_tree_test: public testing::Test {
public:
	binary_search_tree<int> tree;
};

TEST_F(binary_search_tree_test, isCreatedEmpty) {
	doubly_linked_list<int> list;
	EXPECT_EQ(list, tree.in_order());
}

TEST_F(binary_search_tree_test, pushPushes) {
	tree.push(42);
	EXPECT_TRUE(tree.has(42));
}

TEST_F(binary_search_tree_test, popPops) {
	tree.push(42);
	tree.pop(42);
	EXPECT_FALSE(tree.has(42));
}

TEST_F(binary_search_tree_test, insertionsAreBalancedAsExpected) {
	tree.push(42);
	tree.push(1963);
	tree.push(13);
	tree.push(22);

	doubly_linked_list<int> list;
	list.push_back(13);
	list.push_back(22);
	list.push_back(42);
	list.push_back(1963);

	EXPECT_EQ(list, tree.in_order());
}

TEST_F(binary_search_tree_test, inOrderReturnsOrderedCollection) {
	// TODO: how would this test be different from the above?
}

TEST_F(binary_search_tree_test, preOrderReturnsPreOrderedCollection) {
	tree.push(42);
	tree.push(1963);
	tree.push(13);
	tree.push(22);

	doubly_linked_list<int> list;
	list.push_back(42);
	list.push_back(13);
	list.push_back(22);
	list.push_back(1963);

	EXPECT_EQ(list, tree.pre_order());
}

TEST_F(binary_search_tree_test, postOrderReturnsPostOrderedCollection) {
	tree.push(42);
	tree.push(1963);
	tree.push(13);
	tree.push(22);

	doubly_linked_list<int> list;
	list.push_back(22);
	list.push_back(13);
	list.push_back(1963);
	list.push_back(42);

	EXPECT_EQ(list, tree.post_order());
}
