#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "RBTree.hpp"
#include "iterator_traits.hpp"
#include "iterators_categories.hpp"

template<class _Iter>
class tree_iterator {
private:
	typedef _Iter iterator_type;

public:
	typedef bidirectional_iterator_tag iterator_category;
	typedef _Iter value_type;
	typedef ptrdiff_t difference_type;
	typedef _Iter* pointer;
	typedef _Iter& reference;

private:
	pointer _ptr;

	pointer maximum(pointer node)
	{
		while (node->right!=NULL) {
			node = node->right;
		}
		return node;
	}

	pointer minimum(pointer node)
	{
		while (node->left!=NULL) {
			node = node->left;
		}
		return node;
	}

	pointer successor(pointer x)
	{
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right!=NULL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		pointer y = x->parent;
		while (y!=NULL && x==y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// TODO:: looks like it is -- operation
	// find the predecessor of a given node
	pointer predecessor(pointer x)
	{
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the
		// left subtree
		if (x->left!=NULL) {
			return maximum(x->left);
		}

		pointer y = x->parent;
		while (y!=NULL && x==y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

public:
	tree_iterator(pointer ptr = NULL)
			:_ptr(ptr) { }

	template<class U, class V>
	tree_iterator(Node<U, V>* ptr)
			:_ptr(value_type(ptr->data.first, ptr->data.second)) { }

	tree_iterator(const tree_iterator& ti)
			:_ptr(ti._ptr) { }

	template<class S, class V>
	tree_iterator(const tree_iterator<S>& rhs)
			:_ptr(rhs._ptr) { }

	tree_iterator& operator=(const tree_iterator& ti)
	{
		_ptr = ti._ptr;
		return *this;
	};

	~tree_iterator() { }

	template<class U, class UT, class W, class WT>
	friend bool operator==(const tree_iterator<U>& lhs, const tree_iterator<W>& rhs) { return lhs._ptr->data->second==rhs._ptr->data->second; }

	template<class U, class UT, class W, class WT>
	friend bool operator!=(const tree_iterator<U>& lhs, const tree_iterator<W>& rhs) { return lhs._ptr->data->second!=rhs._ptr->data->second; }

	reference operator*() const { return _ptr->data; }

	pointer operator->() const { return _ptr->data; }

	tree_iterator& operator++()
	{
		_ptr = successor(_ptr);
		return *this;
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp(*this);
		_ptr = successor(_ptr);
		return tmp;
	}

	tree_iterator& operator--()
	{
		_ptr = predecessor(_ptr);
		return *this;
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp(*this);
		_ptr = predecessor(_ptr);
		return tmp;
	}
};

#endif
