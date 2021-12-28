//
// Created by Shandy Mephesto on 12/24/21.
//

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP
#include "utils.hpp"

namespace ft {
	template< class T1, class T2 >
	class tree_iterator {

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ft::pair<T1, T2> value_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;

	private:
		typedef Node<T1, T2>* NodePointer;
		NodePointer _ptr;

		NodePointer maximum(NodePointer node)
		{
			while (node->right->nodeType!=nilNodeType) {
				node = node->right;
			}
			return node;
		}

		NodePointer minimum(NodePointer node)
		{
			while (node->left->nodeType!=nilNodeType) {
				node = node->left;
			}
			return node;
		}

		// ++
		NodePointer successor(NodePointer x)
		{
			if (x->nodeType==nilNodeType)
				return x;
			// if the right subtree is not null,
			// the successor is the leftmost node in the
			// right subtree
			if (x->right->nodeType!=nilNodeType) {
				return minimum(x->right);
			}

			// else it is the lowest ancestor of x whose
			// left child is also an ancestor of x.
			NodePointer y = x->parent;
			while (y->nodeType!=nilNodeType && x==y->right) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		// find the predecessor of a given node
		NodePointer predecessor(NodePointer x)
		{
			if (x->nodeType==nilNodeType)
				return x->parent;
			// if the left subtree is not null,
			// the predecessor is the rightmost node in the
			// left subtree
			if (x->nodeType!=nilNodeType && x->left->nodeType!=nilNodeType) {
				return maximum(x->left);
			}

			NodePointer y = x->parent;
			while (y->nodeType!=nilNodeType && x==y->left) {
				x = y;
				y = y->parent;
			}

			return y->nodeType!=nilNodeType ? y : x;
		}

	public:
		tree_iterator(NodePointer ptr = NULL)
				:_ptr(ptr) { }

		NodePointer base() const
		{
			return _ptr;
		}

		tree_iterator(const tree_iterator& ti)
				:_ptr(ti._ptr) { }

		tree_iterator& operator=(const tree_iterator& ti)
		{
			_ptr = ti._ptr;
			return *this;
		};

		~tree_iterator() { }

		friend bool operator==(const tree_iterator<T1, T2>& lhs, const tree_iterator<T1, T2>& rhs)
		{
			return lhs._ptr==rhs._ptr;
		}

		friend bool operator!=(const tree_iterator<T1, T2>& lhs, const tree_iterator<T1, T2>& rhs)
		{
			return lhs._ptr!=rhs._ptr;
		}

		reference operator*() const { return *(_ptr->data); }

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
	template< class T1, class T2 >
	class const_tree_iterator {

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ft::pair<T1, T2> value_type;
		typedef ptrdiff_t difference_type;
		typedef const value_type* pointer;
		typedef const value_type& reference;
		typedef Node<T1, T2>* NodePointer;

	private:
		NodePointer _ptr;

		NodePointer maximum(NodePointer node)
		{
			while (node->right->nodeType!=nilNodeType) {
				node = node->right;
			}
			return node;
		}

		NodePointer minimum(NodePointer node)
		{
			while (node->left->nodeType!=nilNodeType) {
				node = node->left;
			}
			return node;
		}

		// ++
		NodePointer successor(NodePointer x)
		{
			if (x->nodeType==nilNodeType)
				return x;
			// if the right subtree is not null,
			// the successor is the leftmost node in the
			// right subtree
			if (x->right->nodeType!=nilNodeType) {
				return minimum(x->right);
			}

			// else it is the lowest ancestor of x whose
			// left child is also an ancestor of x.
			NodePointer y = x->parent;
			while (y->nodeType!=nilNodeType && x==y->right) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		// find the predecessor of a given node
		NodePointer predecessor(NodePointer x)
		{
			if (x->nodeType==nilNodeType)
				return x->parent;
			// if the left subtree is not null,
			// the predecessor is the rightmost node in the
			// left subtree
			if (x->nodeType!=nilNodeType && x->left->nodeType!=nilNodeType) {
				return maximum(x->left);
			}

			NodePointer y = x->parent;
			while (y->nodeType!=nilNodeType && x==y->left) {
				x = y;
				y = y->parent;
			}

			return y->nodeType!=nilNodeType ? y : x;
		}

	public:
		const_tree_iterator(NodePointer ptr = NULL)
				:_ptr(ptr) { }

		const_tree_iterator(const tree_iterator<T1, T2>& ti)
				:_ptr(ti.base()) { }

		NodePointer base() const
		{
			return _ptr;
		}

		const_tree_iterator(const const_tree_iterator& ti)
				:_ptr(ti._ptr) { }

//			template<class S>
//			const_tree_iterator(const const_tree_iterator<S>& rhs)
//					:_ptr(rhs._ptr) { }

		const_tree_iterator& operator=(const const_tree_iterator& ti)
		{
			_ptr = ti._ptr;
			return *this;
		};

		~const_tree_iterator() { }

		friend bool operator==(const const_tree_iterator<T1, T2>& lhs, const const_tree_iterator<T1, T2>& rhs)
		{
			return lhs._ptr==rhs._ptr;
		}

		friend bool operator!=(const const_tree_iterator<T1, T2>& lhs, const const_tree_iterator<T1, T2>& rhs)
		{
			return lhs._ptr!=rhs._ptr;
		}

		reference operator*() const { return *(_ptr->data); }
		const

		pointer operator->() const { return _ptr->data; }
		const

		const_tree_iterator& operator++()
		{
			_ptr = successor(_ptr);
			return *this;
		}

		const_tree_iterator operator++(int)
		{
			const_tree_iterator tmp(*this);
			_ptr = successor(_ptr);
			return tmp;
		}

		const_tree_iterator& operator--()
		{
			_ptr = predecessor(_ptr);
			return *this;
		}

		const_tree_iterator operator--(int)
		{
			const_tree_iterator tmp(*this);
			_ptr = predecessor(_ptr);
			return tmp;
		}

	};
}
#endif
