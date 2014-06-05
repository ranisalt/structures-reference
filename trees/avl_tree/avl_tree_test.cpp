/*
 * avl_tree_test.cpp
 *
 *  Created on: 29/05/2014
 *      Author: ranieri
 */

#include <gtest/gtest.h>
#include "avl_tree.h"

using data_structures::trees::avl_tree;

class avl_tree_test: public testing::Test {
public:
	avl_tree<int> tree;
};
