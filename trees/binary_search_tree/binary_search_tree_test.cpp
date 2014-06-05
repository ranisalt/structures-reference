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
	tree.find(42);
}
