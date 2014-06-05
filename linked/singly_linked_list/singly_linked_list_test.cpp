/*
 * singly_linked_list_test.cpp
 *
 *  Created on: 03/06/2014
 *      Author: ranieri
 */

#include <gtest/gtest.h>
#include "singly_linked_list.h"

using data_structures::linked::singly_linked_list;

class singly_linked_list_test: public testing::Test {
public:
	singly_linked_list<int> list;
};

TEST_F(singly_linked_list_test, isCreatedEmpty) {
	EXPECT_EQ(0, list.size());
}

TEST_F(singly_linked_list_test, pushBackPushesOnBack) {
	list.push_back(42);
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(42, list.at(0));
	list.push_back(1963);
	EXPECT_EQ(42, list.at(0));
	EXPECT_EQ(1963, list.at(1));
	EXPECT_EQ(2, list.size());
}

TEST_F(singly_linked_list_test, pushFrontPushesOnFront) {
	list.push_front(42);
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(42, list.at(0));
	list.push_front(1963);
	EXPECT_EQ(1963, list.at(0));
	EXPECT_EQ(42, list.at(1));
	EXPECT_EQ(2, list.size());
}

TEST_F(singly_linked_list_test, insert) {
	list.push_back(42);
	list.push_back(13);
	list.push(1, 1963);
	EXPECT_EQ(42, list.at(0));
	EXPECT_EQ(1963, list.at(1));
	EXPECT_EQ(13, list.at(2));
	EXPECT_EQ(3, list.size());
}

TEST_F(singly_linked_list_test, popBack) {
	list.push_back(42);
	list.push_back(1963);
	EXPECT_EQ(1963, list.pop_back());
	EXPECT_EQ(1, list.size());
}

TEST_F(singly_linked_list_test, popFront) {
	list.push_back(42);
	list.push_back(1963);
	EXPECT_EQ(42, list.pop_front());
	EXPECT_EQ(1, list.size());
}

TEST_F(singly_linked_list_test, remove) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	EXPECT_EQ(1963, list.pop(1));
	EXPECT_EQ(2, list.size());
}

TEST_F(singly_linked_list_test, accessOutOfRange) {
	EXPECT_THROW(list.at(13), std::out_of_range);
	EXPECT_THROW(list.push(13, 42), std::out_of_range);
	EXPECT_THROW(list.pop(13), std::out_of_range);
}

TEST_F(singly_linked_list_test, boundariesWithNoProblems) {
	list.push(0, 42);
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(42, list.at(0));
	EXPECT_EQ(42, list.pop(0));
	EXPECT_EQ(0, list.size());
}

TEST_F(singly_linked_list_test, removalsFromEmptyThrow) {
	EXPECT_THROW(list.pop_back(), std::out_of_range);
	EXPECT_THROW(list.pop_front(), std::out_of_range);
	EXPECT_THROW(list.pop(13), std::out_of_range);
}

TEST_F(singly_linked_list_test, forwardIteratorIsCreatedCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.begin();
	EXPECT_EQ(42, *it);
}

TEST_F(singly_linked_list_test, forwardIteratorAdvance) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.begin();
	EXPECT_EQ(42, *it);
	++it;
	EXPECT_EQ(1963, *it);
	++it;
	EXPECT_EQ(13, *it);
}

/*TEST_F(singly_linked_list_test, backwardIteratorIsCreatedCorrect) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.rbegin();
	EXPECT_EQ(13, *it);
}

TEST_F(singly_linked_list_test, backwardIteratorAdvance) {
	list.push_back(42);
	list.push_back(1963);
	list.push_back(13);
	auto it = list.rbegin();
	EXPECT_EQ(13, *it);
	--it;
	EXPECT_EQ(1963, *it);
	--it;
	EXPECT_EQ(42, *it);
}*/
