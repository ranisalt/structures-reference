#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include <algorithm>
#include <stdexcept>
#include "abstract/tree.h"
#include "linked/doubly_linked_list/doubly_linked_list.h"

namespace data_structures {
namespace trees {

using abstract::tree;
using linked::doubly_linked_list;

template<typename T, template<typename> class Container = doubly_linked_list>
class red_black_tree: public tree<T, Container> {
	using size_type = std::size_t;

private:
	enum color { RED, BLACK };

	struct node {
		node(const T& item) :
			_color(BLACK), _parent(nullptr), _left(nullptr), _right(nullptr), _item(item) {
		}

		friend void swap(node& a, node& b) {
			using std::swap;

			swap(a._color, b._color);
			swap(a._parent, b._parent);
			swap(a._left, b._left);
			swap(a._right, b._right);
			swap(a._item, b._item);
		}

		color _color;
		node* _parent;
		node* _left;
		node* _right;
		T _item;
	};

	bool has(node* root, const T& item) const {
		if (root == nullptr)
			return false;
		if (root->_item > item)
			return has(root->_left, item);
		if (root->_item < item)
			return has(root->_right, item);
		return true;
	}

	node* grandparent(node* root) {
		if (root != nullptr && root->_parent != nullptr)
			return root->_parent->_parent;
		return nullptr;
	}

	node* uncle(node* root) {
		node* aux = grandparent(root);
		if (aux != nullptr) {
			if (root->_parent == aux->_left)
				return aux->_right;
			return aux->_left;
		}
		return nullptr;
	}

	node* sibling(node* root) {
		if (root->_parent->_left == root)
			return root->_parent->_right;
		return root->_parent->_left;
	}

	void repaint(node* root) {
		if (root->_parent == nullptr) {
			root->_color = BLACK;
			return;
		}

		if (root->_parent->_color == BLACK) {
			return;
		}

		node* aux = uncle(root);
		if (aux != nullptr && aux->_color == RED) {
			root->_parent->_color = BLACK;
			aux->_color = BLACK;
			aux->_parent->_color = RED;
			repaint(aux->_parent);
			return;
		}

		aux = grandparent(root);
		if (root->_parent->_right == root && root->_parent == aux->_left) {
			root->_parent = rotate_left(root->_parent);
			root = root->_left;
			return;
		}
		
		if (root->_parent->_left == root && root->_parent == aux->_right) {
			root->_parent = rotate_right(root->_parent);
			root = root->_right;
			return;
		}

		root->_parent->_color = BLACK;
		aux->_color = RED;
		if (root->_parent->_left == root)
			aux = rotate_right(aux);
		else
			aux = rotate_left(aux);
	}

	node* insert(node* root, const T& item) {
		if (root == nullptr) {
			root = new node(item);
			return root;
		}
			
		if (root->_item > item) {
			root->_left = insert(root->_left, item);
			root->_left->_parent = root;
			repaint(root->_left);
		}
		
		else if (root->_item < item) {
			root->_right = insert(root->_right, item);
			root->_right->_parent = root;
			repaint(root->_right);
		}

		else
			throw std::exception();
		
		return root;
	}

	node* remove(node* root, const T& item) {
		if (root == nullptr)
			throw std::exception();

		if (root->_item > item)
			root->_left = remove(root->_left, item);

		else if (root->_item < item)
			root->_right = remove(root->_right, item);

		else {
			if (root->_left == nullptr && root->_right == nullptr) {
				delete root;
				return nullptr;
			}

			if (root->_right == nullptr) {
				node* aux = root->_left;
				delete root;
				return aux;
			} 
			
			if (root->_left == nullptr) {
				node* aux = root->_right;
				delete root;
				return aux;
			}
			
			node* aux = root->_right;
			while (aux->_left != nullptr) {
				aux = aux->_left;
			}
			std::swap(root->_item, aux->_item);
			root->_right = remove(root->_right, item);
		}

		repaint(root);
		return root;
	}

	node* rotate_left(node* root) {
		node* aux;
		aux = root->_right;
		aux->_parent = root->_parent;
		root->_right = aux->_left;
		root->_right->_parent = root;
		aux->_left = root;
		aux->_left->_parent = aux;

		if (aux->_parent->_left == root)
			aux->_parent->_left = aux;
		else
			aux->_parent->_right = aux;

		return aux;
	}

	node* rotate_right(node* root) {
		node* aux;
		aux = root->_left;
		aux->_parent = root->_parent;
		root->_left = aux->_right;
		root->_left->_parent = root;
		aux->_right = root;
		aux->_right->_parent = aux;

		if (aux->_parent->_left == root)
			aux->_parent->_left = aux;
		else
			aux->_parent->_right = aux;

		return aux;
	}

public:
	red_black_tree() :
		_size(0), _root(nullptr) {
	}

	bool has(const T& item) const {
		return has(_root, item);
	};

	size_type size() const {
		return _size;
	};

	void insert(const T& item) {
		_root = insert(_root, item);
		++_size;
	};

	void remove(const T& item) {
		_root = remove(_root, item);
		--_size;
	};

	Container<T> in_order() const { return {}; };
	Container<T> pre_order() const { return {}; };
	Container<T> post_order() const { return {}; };

private:
	size_type _size;
	node* _root;
};

}
}

#endif /* RED_BLACK_TREE_H_ */
