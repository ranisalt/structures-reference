/*
 * avl_tree.h
 *
 *  Created on: 29/05/2014
 *      Author: ranieri
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <algorithm>
#include <stdexcept>

namespace data_structures { namespace trees {

template<typename T>
class avl_tree {
private:
	struct node {
		node(const T& item) :
				item(item) {
		}

		void insert(const T& item) {
			if (item < this->item) {
				if (left)
					left->insert(item);
				else
					left = new node(item);
			} else {
				if (right)
					right->insert(item);
				else
					right = new node(item);
			}

			++height;

			int factor = left->height - right->height;
			if (factor == 2) {
				node* p = left;
				if (p->left->height - p->right->height == -1) {
					p->rotate_left();
				}
				rotate_right();
			} else {
				node* p = right;
				if (p->right->height - p->left->height == -1) {
					p->rotate_right();
				}
				rotate_left();
			}
		}

		void rotate_left() {
			node* p = right;
			right = right->left;
			p->left = this;

			height = std::max(right->height, left->height) + 1;
		}

		void rotate_right() {
			node* p = left;
			left = left->left;
			p->right = this;

			height = std::max(left->height, right->height) + 1;
		}

		node* left = 0;
		node* right = 0;
		int height = 0;
		T item;
	};

	node* root = 0;

public:
	avl_tree() {
	}

	bool empty() const {
		return root == 0;
	}

	void pop(const T& item) {
		if (root == 0) {
			throw std::out_of_range("Popping from empty list.");
		} else {

		}
	}

	void push(const T& item) {
		if (root == 0) {
			root = new node(item);
			return;
		} else {
			root->insert(item);
		}
	}
};

}}

#endif /* AVL_TREE_H_ */
