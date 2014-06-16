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
#include "linked/doubly_linked_list/doubly_linked_list.h"

namespace data_structures {
namespace trees {

template<typename T, template<typename> class Container = linked::doubly_linked_list>
class binary_search_tree {
	using size_type = std::size_t;

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

	size_type size(const node*& root) const {
		return root == nullptr ? 0 : 1 + size(root->_left) + size(root->_right);
	}

	node* find_leftmost(node*& root) {
		node* curr = root;
		while (curr->_left)
			curr = curr->_left;
		return curr;
	}

	bool has(node* const& root, const T& item) const {
		if (root == nullptr)
			return false;
		if (item == root->_item)
			return true;
		if (item < root->_item)
			return has(root->_left, item);
		if (item > root->_item)
			return has(root->_right, item);
		return false;
		//throw std::out_of_range("Searching non-existent element.");
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

	void in_order(node* const& root, Container<T>& container) const {
		if (root == nullptr)
			return;

		in_order(root->_left, container);
		container.push_back(root->_item);
		in_order(root->_right, container);
	}

public:
	binary_search_tree() {
	}

	bool empty() const {
		return root == nullptr;
	}

	size_type size() const {
		return size(root);
	}

	bool has(const T& item) const {
		return has(root, item);
	}

	void pop(const T& item) {
		root = remove(root, item);
	}

	void push(const T& item) {
		insert(root, item);
	}

	Container<T> in_order() const {
		Container<T> container;
		in_order(root, container);
		return container;
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
