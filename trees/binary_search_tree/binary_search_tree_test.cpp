/*
 * binary_search_tree_test.cpp
 *
 *  Created on: 29/05/2014
 *      Author: ranieri
 */

#include <gtest/gtest.h>
#include "binary_search_tree.h"

using data_structures::trees::binary_search_tree;

class binary_search_tree_test: public testing::Test {
public:
	binary_search_tree<int> tree;
};

TEST_F(binary_search_tree_test, pushPushes) {
	tree.push(42);
	EXPECT_TRUE(tree.find(42));
}

TEST_F(binary_search_tree_test, popPops) {
	tree.push(42);
	tree.pop(42);
	EXPECT_FALSE(tree.find(42));
}

TEST_F(binary_search_tree_test, insertionsAreBalancedAsExpected) {
	tree.push(42);
	tree.push(1963);
	tree.push(13);
	tree.push(22);
	EXPECT_STREQ("((13,22),42,1963)", ((std::string)tree).c_str());
}
