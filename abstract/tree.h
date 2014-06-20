#ifndef TREE_H_
#define TREE_H_

#include "list.h"

namespace data_structures { namespace abstract {

template<typename T, template<typename> class Container = list>
class tree {
protected:
	using size_type = std::size_t;

public:
	virtual ~tree() {};

	virtual bool has(const T& item) const = 0;
	virtual size_type size() const = 0;

	virtual void insert(const T& item) = 0;
	virtual void remove(const T& item) = 0;

	virtual Container<T> in_order() const = 0;
	virtual Container<T> pre_order() const = 0;
	virtual Container<T> post_order() const = 0;
};

}}

#endif /* TREE_H_ */
