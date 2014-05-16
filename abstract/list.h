#ifndef LIST_H_
#define LIST_H_

#include <stdexcept>

namespace data_structures {
namespace abstract {

template<typename T>
class list {
public:
	/**< Destructor is trivial, we only have _length */
	virtual ~list() {}

	virtual T back() const = 0;
	virtual T front() const = 0;

	int length() const {
		return _length;
	}

	/**< Removal operations */
	virtual T pop(int) = 0;
	virtual T pop_back() = 0;
	virtual T pop_front() = 0;

	/**< Insertion operations */
	virtual void push(int, const T&) = 0;
	virtual void push_back(const T&) = 0;
	virtual void push_front(const T&) = 0;

	class iterator;
	class const_iterator;

protected:
	class iterator_base;

	void empty_check() const {
		if (!_length)
			throw std::out_of_range("Empty list.");
	}

	int _length;
};

}
}

#endif /* LIST_H_ */
