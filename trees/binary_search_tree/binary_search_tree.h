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
		node(const T& item) :
				_item(item) {
		}

		operator std::string() const {
			std::stringstream ss;
			if (_left != nullptr || _right != nullptr)
				ss << '(';
			if (_left != nullptr)
				ss << (std::string) *_left << ',';
			ss << _item;
			if (_right != nullptr)
				ss << ',' << (std::string) *_right;
			if (_left != nullptr || _right != nullptr)
				ss << ')';
			return ss.str();
		}

		node* _left { nullptr };
		node* _right { nullptr };
		T _item;
	};

	node* find_leftmost(node*& root) {
		node* curr = root;
		while (curr->_left)
			curr = curr->_left;
		return curr;
	}

	node* find(node*& root, const T& item) {
		if (root == nullptr || item == root->_item)
			return root;
		if (item < root->_item)
			return find(root->_left, item);
		if (item > root->_item)
			return find(root->_right, item);
		throw std::out_of_range("Searching non-existent element.");
	}

	void insert(node*& root, const T& item) {
		if (root == nullptr) {
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
		if (root == nullptr)
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

public:
	binary_search_tree() {
	}

	bool empty() const {
		return root == nullptr;
	}

	bool find(const T& item) {
		return find(root, item) != nullptr;
	}

	void pop(const T& item) {
		root = remove(root, item);
	}

	void push(const T& item) {
		insert(root, item);
	}

	operator std::string() const {
		return (std::string) (*root);
	}

private:
	node* root { nullptr };
};

}
}

#endif /* BINARY_SEARCH_TREE_H_ */
