/*
 * doubly_linked_list.h
 *
 *  Created on: 13/06/2014
 *      Author: ranieri
 */

#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "abstract/list.h"

namespace data_structures {
namespace linked {

using abstract::list;

template<typename T>
class doubly_linked_list: public list<T> {
	using parent = list<T>;
	using self = doubly_linked_list<T>;
	using size_type = std::size_t;

	struct node {
	public:
		node(node* pred, node* succ, const T& item) :
				_pred(pred), _succ(succ), _item(item) {
		}

		node* _pred;
		node* _succ;
		T _item;
	};

	template<typename NodeT>
	class iterator_base {
		using self = iterator_base<NodeT>;

	public:
		iterator_base(node* ptr, size_type pos) :
				_ptr(ptr), _pos(pos) {
		}

		self operator=(self other) {
			using std::swap;
			swap(*this, other);
			return *this;
		}

		self& operator++() {
			if (_ptr == nullptr)
				throw std::out_of_range("Iterating beyond list end.");
			_ptr = _ptr->_succ;
			++_pos;
			return *this;
		}

		self operator++(int) {
			auto old = _ptr;
			++(*this);
			return {old};
		}

		self next(size_type n = 1) {
			self it{*this};
			std::advance(it, n);
			return it;
		}

		self& advance(size_type n = 1) {
			if (n > 0) {
				while (n) {
					++(*this);
				}
			} else {
				while (n) {
					--(*this);
				}
			}
		}

		self& operator--() {
			if (_ptr == nullptr)
				throw std::out_of_range("Iterating beyond list begin.");
			_ptr = _ptr->_pred;
			--_pos;
			return *this;
		}

		self operator--(int) {
			node* old = _ptr;
			--(*this);
			return {old};
		}

		bool operator==(const self& other) const {
			return _pos == other._pos;
		}

		bool operator!=(const self& other) const {
			return !(*this == other);
		}

		bool operator<(const self& other) const {
			return _pos < other._pos;
		}

		NodeT& operator*() const {
			return _ptr->_item;
		}

		NodeT* operator->() const {
			return &(_ptr->_item);
		}

		void swap(self& other) {
			using std::swap;
			swap(_ptr, other._ptr);
			swap(_pos, other._pos);
		}

	private:
		node* _ptr;
		size_type _pos;
	};

public:
	doubly_linked_list() :
			_front(nullptr), _back(nullptr), _size(0) {
	}

	doubly_linked_list(const self& other) {
		for (auto e : other)
			push_back(e);
	}

	~doubly_linked_list() {
		node* old;
		while (_front != nullptr) {
			old = _front;
			_front = _front->_succ;
			delete old;
		}
	}

	T at(size_type position) const {
		if (position < 0 || position >= this->_size)
			throw std::out_of_range("Out of range access.");

		node* p;
		if (position < (_size >> 1)) {
			p = _front;
			for (int i = 0; i < position; ++i)
				p = p->_succ;
		} else {
			p = _back;
			for (int i = _size - 1; i > position; --i)
				p = p->_pred;
		}
		return p->_item;
	}

	T back() const {
		empty_check();

		return _back->_item;
	}

	T front() const {
		empty_check();

		return _front->_item;
	}

	size_type size() const {
		return this->_size;
	}

	/**< Removal operations */
	T pop(size_type position) {
		if (position < 0 || position >= _size)
			throw std::out_of_range("Empty list.");

		if (position == 0)
			return pop_front();

		if (position == _size - 1)
			return pop_back();

		node* p;
		if (position < (_size >> 1)) {
			p = _front;
			for (int i = 0; i < position; ++i)
				p = p->_succ;
		} else {
			p = _back;
			for (int i = _size - 1; i > position; --i)
				p = p->_pred;
		}

		/**< Hold node, advance it and then delete the old one */
		T value{p->_item};
		p->_pred->_succ = p->_succ;
		p->_succ->_pred = p->_pred;
		delete p;

		--this->_size;
		return value;
	}

	T pop_back() {
		empty_check();

		node* aux = _back;
		T item{_back->_item};
		_back = _back->_pred;
		if (_back == nullptr) {
			_front = nullptr;
		} else {
			_back->_succ = nullptr;
		}
		delete aux;

		--this->_size;
		return item;
	}

	T pop_front() {
		empty_check();

		/**< Hold head, advance it and then delete the old one */
		node* aux = _front;
		T item(aux->_item);
		_front = _front->_succ;
		if (_front == nullptr) {
			_back = nullptr;
		} else {
			_front->_pred = nullptr;
		}
		delete aux;

		--this->_size;
		return item;
	}

	/**< Insertion operations */
	void push(size_type position, const T& item) {
		if (position < 0 || position > this->_size)
			throw std::out_of_range("Out of range access.");

		if (position == 0) {
			push_front(item);
			return;
		}

		if (position == this->_size) {
			push_back(item);
			return;
		}

		node* p;
		if (position < (_size >> 1)) {
			p = _front;
			for (int i = 0; i < position; ++i)
				p = p->_succ;
		} else {
			p = _back;
			for (int i = _size - 1; i > position; --i)
				p = p->_pred;
		}
		p->_pred = p->_pred->_succ = new node(p->_pred, p, item);
		++this->_size;
	}

	void push_back(const T& item) {
		if (!_size) {
			_front = _back = new node(nullptr, nullptr, item);
		} else {
			_back = _back->_succ = new node(_back, nullptr, item);
		}
		++this->_size;
	}

	void push_front(const T& item) {
		if (!_size) {
			_front = _back = new node(nullptr, nullptr, item);
		} else {
			_front = _front->_pred = new node(nullptr, _front, item);
		}
		++this->_size;
	}

	using iterator = iterator_base<T>;

	iterator begin() {
		return {_front, 1};
	}

	iterator end() {
		return {nullptr, _size + 1};
	}

	iterator rbegin() {
		return {_back, _size};
	}

	iterator rend() {
		return {nullptr, 0};
	}

	using const_iterator = iterator_base<const T>;

	const_iterator begin() const {
		return {_front, 1};
	}

	const_iterator end() const {
		return {nullptr, _size + 1};
	}

	const_iterator rbegin() const {
		return {_back, _size};
	}

	const_iterator rend() const {
		return {nullptr, 0};
	}

	self& operator=(self&& rhs) {
		swap(*this, rhs);
		return *this;
	}

	bool operator==(const self& rhs) const {
		if (_size == rhs.size()) {
			for (const_iterator a = begin(), b = rhs.begin();
					a != end() && b != rhs.end(); ++a, ++b)
				if (*a != *b)
					return false;
			return true;
		}
		return false;
	}

	bool operator!=(const self& rhs) const {
		return !(*this == rhs);
	}

	void swap(self& rhs) {
		using std::swap;

		swap(_front, rhs._front);
		swap(_back, rhs._back);
		swap(_size, rhs._size);
	}

private:
	void empty_check() const {
		if (!_size)
			throw std::out_of_range("Empty list.");
	}

	node* _front { nullptr };
	node* _back { nullptr };
	size_type _size { 0 };
};

}
}

#endif /* DOUBLY_LINKED_LIST_H_ */
