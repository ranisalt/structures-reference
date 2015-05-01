#ifndef SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_H_

#include <algorithm>
#include <stdexcept>
#include "abstract/list.h"

namespace data_structures {
namespace linked {

using abstract::list;

template<typename T>
class singly_linked_list: public list<T> {
private:
	struct node {
	public:
		node(node* succ, const T& item) :
				_succ(succ), _item(item) {
		}

		node* _succ;
		T _item;
	};

	template<typename NodeT>
	class iterator_base {
	public:
		iterator_base(node* ptr) :
				_ptr(ptr) {
		}

		iterator_base operator=(const iterator_base& other) {
			return {other._ptr};
		}

		iterator_base& operator++() {
			if (!_ptr)
				throw std::out_of_range("Iterating beyond list end.");
			_ptr = _ptr->_succ;
			return *this;
		}

		iterator_base operator++(int) {
			node* old = _ptr;
			++(*this);
			return {old};
		}

		bool operator==(const iterator_base& other) const {
			return _ptr == other._ptr;
		}

		bool operator!=(const iterator_base& other) const {
			return _ptr != other._ptr;
		}

		NodeT& operator*() const {
			return _ptr->_item;
		}

		NodeT* operator->() const {
			return &(_ptr->_item);
		}

	private:
		node* _ptr;
	};

	using parent = list<T>;
	using self = singly_linked_list<T>;
	using size_type = std::size_t;

public:
	singly_linked_list() :
			_front(), _size() {
	}

	singly_linked_list(const self& other) {
		for (auto e : other)
			push_back(e);
	}

	~singly_linked_list() {
		node* old;
		while (_front) {
			old = _front;
			_front = _front->_succ;
			delete old;
		}
	}

	T at(size_type position) const {
		if (position < 0 || position >= this->_size)
			throw std::out_of_range("Out of range access.");

		node* p = _front;
		for (size_type i = 0; i < position; ++i)
			p = p->_succ;
		return p->_item;
	}

	T back() const {
		empty_check();

		node* p = _front;
		while (p->_succ != 0)
			p = p->_succ;
		return p->_item;
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
		if (position < 0 || position >= this->_size)
			throw std::out_of_range("Empty list.");

		if (position == 0)
			return pop_front();

		node* p = _front;
		for (size_type i = 1; i < position; ++i)
			p = p->_succ;

		/**< Hold node, advance it and then delete the old one */
		node* aux = p->_succ;
		T value(aux->_item);
		p->_succ = aux->_succ;
		delete aux;

		--this->_size;
		return value;
	}

	T pop_back() {
		return pop(this->_size - 1);
	}

	T pop_front() {
		empty_check();

		/**< Hold head, advance it and then delete the old one */
		node* aux = _front;
		T value(aux->_item);
		_front = aux->_succ;
		delete aux;

		--this->_size;
		return value;
	}

	/**< Insertion operations */
	void push(size_type position, const T& item) {
		if (position < 0 || position > this->_size)
			throw std::out_of_range("Out of range access.");

		if (position == 0) {
			push_front(item);
			return;
		}

		node* p = _front;
		for (size_type i = 1; i < position; ++i)
			p = p->_succ;
		p->_succ = new node(p->_succ, item);
		++this->_size;
	}

	void push_back(const T& value) {
		push(this->_size, value);
	}

	void push_front(const T& value) {
		_front = new node(_front, value);
		++this->_size;
	}

	using iterator = iterator_base<T>;

	iterator begin() {
		return {_front};
	}

	iterator end() {
		return {nullptr};
	}

	using const_iterator = iterator_base<const T>;

	const_iterator begin() const {
		return {_front};
	}

	const_iterator end() const {
		return {nullptr};
	}

	self& operator=(self&& rhs) {
		swap(*this, rhs);
		return *this;
	}

	bool operator==(const self& rhs) const {
		if (_size == rhs._size) {
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

	friend void swap(self& a, self& b) {
		using std::swap;

		swap(a._front, b._front);
		swap(a._size, b._size);
	}

private:
	void empty_check() const {
		if (!_size)
			throw std::out_of_range("Empty list.");
	}

	node* _front { nullptr };
	size_type _size { 0 };

};

}
}

#endif /* SINGLY_LINKED_LIST_H_ */
