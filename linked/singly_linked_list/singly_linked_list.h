#ifndef SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_H_

#include <stdexcept>
#include "../../abstract/list.h"

namespace data_structures {

using abstract::list;

namespace linked {

template<typename T>
class singly_linked_list: public list<T> {
protected:
	struct node {
		node(node* succ, const T& value) :
				succ(succ), value(value) {
		}

		node* succ;
		T value;
	};

	template<typename NodeT>
	class iterator_base {
	public:
		iterator_base(node* ptr) :
				ptr(ptr) {
		}

		iterator_base& operator=(const iterator_base& other) {
			if (!this == other)
				return this(other);
			else
				return this;
		}

		iterator_base& operator++() {
			this->ptr = this->ptr->succ;
			return *this;
		}

		iterator_base& operator++(int) {
			iterator_base other(this);
			++this;
			return other;
		}

		bool operator==(const iterator_base& other) const {
			return this->ptr == other.ptr;
		}

		bool operator!=(const iterator_base& other) const {
			return !(*this == other);
		}

		NodeT& operator*() const {
			return this->ptr->value;
		}

		NodeT* operator->() const {
			return this->ptr->value;
		}

	private:
		node* ptr;
	};

	node* head;

public:
	using list<T>::empty_check;

	T back() const {
		empty_check();

		node* p = head;
		while (p->succ != 0)
			p = p->succ;
		return p->value;
	}

	T front() const {
		empty_check();

		return head->value;
	}

	/**< Removal operations */
	T pop(int position) {
		if (position < 0 && position >= this->_length)
			throw std::out_of_range("Empty list.");

		if (position == 0)
			return pop_front();

		node* p = head;
		for (int i = 1; i < position; ++i)
			p = p->succ;

		/**< Hold node, advance it and then delete the old one */
		node* aux = p->succ;
		T value(aux->value);
		p->succ = aux->succ;
		delete aux;

		--this->_length;
		return value;
	}

	T pop_back() {
		return pop(this->_length - 1);
	}

	T pop_front() {
		empty_check();

		/**< Hold head, advance it and then delete the old one */
		node* aux = head;
		T value(aux->value);
		head = aux->succ;
		delete aux;

		--this->_length;
		return value;
	}

	/**< Insertion operations */
	void push(int position, const T& value) {
		if (position < 0 && position > this->_length)
			throw std::out_of_range("Empty list.");

		if (position == 0) {
			push_front(value);
			return;
		}

		node* p = head;
		for (int i = 1; i < position; ++i)
			p = p->succ;
		p->succ = new node(p->succ, value);
		++this->_length;
	}

	void push_back(const T& value) {
		push(this->_length, value);
	}

	void push_front(const T& value) {
		head = new node(head, value);
		++this->_length;
	}

	typedef iterator_base<T> iterator;
	typedef iterator_base<const T> const_iterator;

	iterator begin() {
		return iterator(head);
	}

	iterator end() {
		return iterator(0);
	}

	const_iterator begin() const {
		return const_iterator(head);
	}

	const_iterator end() const {
		return const_iterator(0);
	}
};

}
}

#endif /* SINGLY_LINKED_LIST_H_ */
