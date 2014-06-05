/*
 * binary_search_tree.h
 *
 *  Created on: 30/05/2014
 *      Author: ranieri
 */

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <ostream>
#include <stdexcept>

namespace data_structures {
namespace trees {

template<typename T>
class binary_search_tree {
	struct node {
		node(const T& info) :
				_item(info) {
		}

		friend std::ostream& operator<<(std::ostream& out, const node& node) {
			out << '(';
			if (node._left) {
				out << *(node._left) << ',';
			}
			out << node._item;
			if (node._right) {
				out << ',' << *(node._right);
			}
			out << ')';
			return out;
		}

		node* _left = 0;
		node* _right = 0;
		T _item;
	};

	node*& find_leftmost(node*& root) {
		node* curr = root;
		while (curr->_left) {
			curr = curr->_left;
		}
		return curr;
	}

	node* find(node*& root, const T& item) {
		if (!root)
			return nullptr;
		if (item < root->_item)
			return find(root->_left, item);
		if (item > root->_item)
			return find(root->_right, item);
		if (item == root->_item)
			return root;
		throw std::out_of_range("Searching non-existent element.");
	}

	void insert(node*& root, const T& item) {
		if (!root) {
			root = new node(item);
		} else {
			if (item < root->_item) {
				insert(root->_left, item);
			} else if (item > root->_item) {
				insert(root->_right, item);
			} else {
				throw std::exception();
			}
		}
	}

	node* remove(node*& root, const T& item) {
		if (!root)
			return root;
		if (item < root->_item) {
			root->_left = remove(root->_left, item);
			return root;
		}
		if (item > root->_item) {
			root->_right = remove(root->_right, item);
			return root;
		}
		if (root->_left && root->_right) {
			node* succ = find_leftmost(root->_right);
			root->_item = succ->_item;
			root->_right = remove(root->_right, item);
			return root;
		}
		if (root->_left)
			return root->_left;
		if (root->_right)
			return root->_right;
		delete root;
		return 0;
	}

	node* root = 0;

public:
	binary_search_tree() {

	}

	bool empty() const {
		return root == 0;
	}

	bool find(const T& item) {
		return find(root, item) != nullptr;
	}

	void pop(const T& item) {
		remove(root, item);
	}

	void push(const T& item) {
		insert(root, item);
	}

	friend std::ostream& operator<<(std::ostream& out,
			const binary_search_tree& bst) {
		out << '(';
		if (bst.root->_left) {
			out << *(bst.root->_left) << ',';
		}
		out << bst.root->item;
		if (bst.root->_right) {
			out << ',' << *(bst.root->_right);
		}
		out << ')';
		return out;
	}
}
;

}
}

#endif /* BINARY_SEARCH_TREE_H_ */
