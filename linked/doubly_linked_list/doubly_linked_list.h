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

namespace data_structures { namespace linked {

using abstract::list;

template<typename T>
class doubly_linked_list: public list<T> {
private:
	struct node {
	public:
		node(node* pred, node* succ, const T& item): _pred(pred), _succ(succ), _item(item) {}

		node* _pred;
		node* _succ;
		T _item;
	};

	template<typename NodeT>
	class iterator_base: public std::iterator<std::bidirectional_iterator_tag, NodeT> {		
	public:
		iterator_base(): _ptr(nullptr) {}
		iterator_base(node* ptr): _ptr(ptr) {}
		iterator_base(const iterator_base& other): _ptr(other._ptr) {}

		iterator_base& operator=(const iterator_base& rhs) {
			_ptr = rhs._ptr;
			return *this;
		}
		
		iterator_base& operator=(iterator_base&& rhs) {
			_ptr = rhs._ptr;
			rhs._ptr = nullptr;
			return *this;
		}

		iterator_base& operator++() {
			if (_ptr == nullptr)
				throw std::out_of_range("Iterating beyond list end.");
			_ptr = _ptr->_succ;
			return *this;
		}

		iterator_base operator++(int) {
			node* old = _ptr;
			++(*this);
			return {old};
		}

		iterator_base& operator--() {
			if (_ptr == nullptr)
				throw std::out_of_range("Iterating beyond list begin.");
			_ptr = _ptr->_pred;
			return *this;
		}

		iterator_base operator--(int) {
			node* old = _ptr;
			--(*this);
			return {old};
		}

		NodeT& operator*() const {
			return _ptr->_item;
		}

		NodeT* operator->() const {
			return &(_ptr->_item);
		}
		
		friend bool operator==(const iterator_base& lhs, const iterator_base& rhs) {
			return lhs._ptr == rhs._ptr;
		}

		friend bool operator!=(const iterator_base& lhs, const iterator_base& rhs){
			return !(lhs == rhs);
		}

	private:
		node* _ptr;
	};

	using parent = list<T>;
	using self = doubly_linked_list<T>;
	using size_type = std::size_t;

public:
	doubly_linked_list(): _front(nullptr), _back(nullptr), _size(0) {}

	doubly_linked_list(const self& other): doubly_linked_list() {
		for (auto e : other)
			push_back(e);
	}
	
	doubly_linked_list(self&& other): _front(other._front), _back(other._back), _size(other._size) {
		other._front = nullptr;
		other._back = nullptr;
		other._size = 0;
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
		if (position < 0 || position >= _size)
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
		return {_front};
	}

	iterator end() {
		return {nullptr};
	}

	iterator rbegin() {
		return {_back};
	}

	iterator rend() {
		return {nullptr};
	}

	using const_iterator = iterator_base<const T>;

	const_iterator begin() const {
		return {_front};
	}

	const_iterator end() const {
		return {nullptr};
	}

	const_iterator rbegin() const {
		return {_back};
	}

	const_iterator rend() const {
		return {nullptr};
	}

	self& operator=(self rhs) {
		swap(*this, rhs);
		return *this;
	}
	
	self& operator=(self&& rhs) {
		_front = rhs._front;
		_back = rhs._back;
		_size = rhs._size;
		
		rhs._front = nullptr;
		rhs._back = nullptr;
		rhs._size = 0;
	}

	friend bool operator==(const self& lhs, const self& rhs) {
		if (lhs._size != rhs._size)
			return false;
		
		for (const_iterator a = lhs.begin(), b = rhs.begin(); a != lhs.end() && b != rhs.end(); ++a, ++b)
			if (*a != *b)
				return false;
		return true;
	}

	friend bool operator!=(const self& lhs, const self& rhs) {
		return !(lhs == rhs);
	}

	friend void swap(self& a, self& b) {
		using std::swap;
		
		swap(a._front, b._front);
		swap(a._back, b._back);
		swap(a._size, b._size);
	}
	
	template<typename Iterator, typename Compare = std::less<T>>
	void sort(Iterator begin, Iterator end, Compare cmp = Compare()) {
		using std::distance;
		using std::next;
		using std::prev;
		using std::swap;
		
		auto dist = distance(begin, end);
		if (dist > 0) {
			/* find pivot */
			iterator pivot = next(begin, dist >> 1);
			
			/* partition */
			swap(pivot, begin);
			auto i = next(begin), j = next(begin);
			
			while (j != end) {
				if (cmp(*j, *begin)) {
					swap(*i, *j);
					++i;
				}
				++j;
			}
			
			pivot = prev(i);
			
			/* sort slices */
			sort(begin, prev(pivot), cmp);
			sort(next(pivot), end, cmp);
		}
	}

private:
	void empty_check() const {
		if (!_size)
			throw std::out_of_range("Empty list.");
	}

	node* _front;
	node* _back;
	size_type _size;
};

}}

#endif /* DOUBLY_LINKED_LIST_H_ */
