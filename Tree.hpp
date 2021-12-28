//
// Created by Shandy Mephesto on 12/16/21.
//

#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "tree_iterator.hpp"
#include <iostream>

namespace ft {

	template< class T1, class T2, class Compare, class Alloc >
	class Tree {
	public:
		typedef tree_iterator<T1, T2> iterator;
		typedef const_tree_iterator<T1, T2> const_iterator;

	private:
		typedef Alloc allocator_type;
		typedef Node<T1, T2> NodeParamed;
		typedef ft::pair<const T1, T2> value_type;
		typename allocator_type::template rebind<NodeParamed>::other _alloc;
		typedef NodeParamed* NodePointer;
		NodePointer nil;
		NodePointer head;
		Compare _cmp;
		size_t _size;

		NodePointer _search(NodePointer np, T1 key) const
		{
			if (np!=nil) {
				if (np->data->first==key) return np;
				else if (_cmp(key, np->data->first)) return _search(np->left, key);
				else return _search(np->right, key);
			}
			return NodePointer(nil);
		}

		NodePointer _lower_bound(T1 key) const
		{
			if (head==nil)
				return NodePointer(nil);
			else {
				NodePointer t = head;
				NodePointer remembered = t;
				while (t!=nil) {
					if (key==t->data->first) {
						return t;
					}
					if (_cmp(key, t->data->first)) {
						remembered = t;
						t = t->left;
					}
					else {
						t = t->right;
					}
				}
				return _cmp(key, remembered->data->first) ? remembered : nil;
			}
		}

		NodePointer _upper_bound(T1 key) const
		{
			if (head==nil)
				return NodePointer(nil);
			else {
				NodePointer t = head;
				NodePointer remembered = t;
				while (t!=nil) {
//					if (key==t->data->first) {
//						return t;
//					}
					if (_cmp(key, t->data->first)) {
						remembered = t;
						t = t->left;
					}
					else {
						t = t->right;
					}
				}
				return _cmp(key, remembered->data->first) ? remembered : nil;
			}
		}

		void _freeNode(const NodePointer& np)
		{
			_alloc.destroy(np);
			_alloc.deallocate(np, 1);
		}

		bool _remove(T1 key, NodePointer v = NULL)
		{
			NodePointer t = _search(v ? v : head, key);
			if (t==nil) return false;
			_deleteNode(t);
			--_size;
			return true;
		}

		void _removeTheWholeThree(NodePointer& t)
		{
			if (t==NULL || t==nil) return;
			if (t->left) _removeTheWholeThree(t->left);
			if (t->right) _removeTheWholeThree(t->right);
			if (t==head) {
				_freeNode(head);
				head = nil;
				nil->parent = NULL;
				_size = 0;
			}
			else {
				_freeNode(t);
			}
		}

		void _rotateLeft(NodePointer x)
		{

			/**************************
			 *  rotate node x to left *
			 **************************/

			NodePointer y = x->right;

			/* establish x->right link */
			x->right = y->left;
			if (y->left!=nil) y->left->parent = x;

			/* establish y->parent link */
			if (y!=nil) y->parent = x->parent;
			if (x->parent!=nil) {
				if (x==x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			else {
				head = y;
			}

			/* link x and y */
			y->left = x;
			if (x!=nil) x->parent = y;
		}

		void _rotateRight(NodePointer x)
		{

			/****************************
			 *  rotate node x to right  *
			 ****************************/

			NodePointer y = x->left;

			/* establish x->left link */
			x->left = y->right;
			if (y->right!=nil) y->right->parent = x;

			/* establish y->parent link */
			if (y!=nil) y->parent = x->parent;
			if (x->parent!=nil) {
				if (x==x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
			}
			else {
				head = y;
			}

			/* link x and y */
			y->right = x;
			if (x!=nil) x->parent = y;
		}

		void _insertFixup(NodePointer x)
		{

			/*************************************
			 *  maintain Red-Black tree balance  *
			 *  after inserting node x           *
			 *************************************/

			/* check Red-Black properties */
			while (x!=head && x->parent->nodeType==redNodeType) {
				/* we have a violation */
				if (x->parent==x->parent->parent->left) {
					NodePointer y = x->parent->parent->right;
					if (y->nodeType==redNodeType) {

						/* uncle is redNodeType */
						x->parent->nodeType = blackNodeType;
						y->nodeType = blackNodeType;
						x->parent->parent->nodeType = redNodeType;
						x = x->parent->parent;
					}
					else {

						/* uncle is blackNodeType */
						if (x==x->parent->right) {
							/* make x a left child */
							x = x->parent;
							_rotateLeft(x);
						}

						/* recolor and rotate */
						x->parent->nodeType = blackNodeType;
						x->parent->parent->nodeType = redNodeType;
						_rotateRight(x->parent->parent);
					}
				}
				else {

					/* mirror image of above code */
					NodePointer y = x->parent->parent->left;
					if (y->nodeType==redNodeType) {

						/* uncle is redNodeType */
						x->parent->nodeType = blackNodeType;
						y->nodeType = blackNodeType;
						x->parent->parent->nodeType = redNodeType;
						x = x->parent->parent;
					}
					else {

						/* uncle is blackNodeType */
						if (x==x->parent->left) {
							x = x->parent;
							_rotateRight(x);
						}
						x->parent->nodeType = blackNodeType;
						x->parent->parent->nodeType = redNodeType;
						_rotateLeft(x->parent->parent);
					}
				}
			}
			head->nodeType = blackNodeType;
		}

		ft::pair<NodePointer, bool> _add(T1 key, T2 value)
		{
			NodePointer current, parent, x;

			/***********************************************
			 *  allocate node for data and insert in tree  *
			 ***********************************************/

			/* find where node belongs */
			current = head;
			parent = nil;
			while (current!=nil) {
				if (key==current->data->first) return ft::pair<NodePointer, bool>(current, false);
				parent = current;
				current = _cmp(key, current->data->first) ?
						  current->left : current->right;
			}
			x = _alloc.allocate(1);
			_alloc.construct(x, NodeParamed(key, value, nil, redNodeType));
			x->parent = parent;

			/* insert node in tree */
			if (parent!=nil) {
				if (_cmp(key, parent->data->first))
					parent->left = x;
				else
					parent->right = x;
			}
			else {
				head = x;
			}

			_insertFixup(x);
			nil->parent = maximum(head);
			++_size;
			return ft::pair<NodePointer, bool>(x, true);
		}

		void deleteFixup(NodePointer x)
		{

			/*************************************
			 *  maintain Red-Black tree balance  *
			 *  after deleting node x            *
			 *************************************/

			while (x!=head && x->nodeType==blackNodeType) {
				if (x==x->parent->left) {
					NodePointer w = x->parent->right;
					if (w->nodeType==redNodeType) {
						w->nodeType = blackNodeType;
						x->parent->nodeType = redNodeType;
						_rotateLeft(x->parent);
						w = x->parent->right;
					}
					if (w->left->nodeType==blackNodeType && w->right->nodeType==blackNodeType) {
						w->nodeType = redNodeType;
						x = x->parent;
					}
					else {
						if (w->right->nodeType==blackNodeType) {
							w->left->nodeType = blackNodeType;
							w->nodeType = redNodeType;
							_rotateRight(w);
							w = x->parent->right;
						}
						w->nodeType = x->parent->nodeType;
						x->parent->nodeType = blackNodeType;
						w->right->nodeType = blackNodeType;
						_rotateLeft(x->parent);
						x = head;
					}
				}
				else {
					NodePointer w = x->parent->left;
					if (w->nodeType==redNodeType) {
						w->nodeType = blackNodeType;
						x->parent->nodeType = redNodeType;
						_rotateRight(x->parent);
						w = x->parent->left;
					}
					if (w->right->nodeType==blackNodeType && w->left->nodeType==blackNodeType) {
						w->nodeType = redNodeType;
						x = x->parent;
					}
					else {
						if (w->left->nodeType==blackNodeType) {
							w->right->nodeType = blackNodeType;
							w->nodeType = redNodeType;
							_rotateLeft(w);
							w = x->parent->left;
						}
						w->nodeType = x->parent->nodeType;
						x->parent->nodeType = blackNodeType;
						w->left->nodeType = blackNodeType;
						_rotateRight(x->parent);
						x = head;
					}
				}
			}
			if (x->nodeType!=nilNodeType)
				x->nodeType = blackNodeType;
		}

		void _deleteNode(NodePointer z)
		{
			NodePointer x, y;

			/*****************************
			 *  delete node z from tree  *
			 *****************************/

			if (z==nil) return;

			if (z->left==nil || z->right==nil) {
				/* y has a NIL node as a child */
				y = z;
			}
			else {
				/* find tree successor with a NIL node as a child */
				y = z->right;
				while (y->left!=nil) y = y->left;
			}

			/* x is y's only child */
			if (y->left!=nil)
				x = y->left;
			else
				x = y->right;

			/* remove y from the parent chain */
			if (x!=nil)
				x->parent = y->parent;
			if (y->parent!=nil)
				if (y==y->parent->left)
					y->parent->left = x;
				else
					y->parent->right = x;
			else
				head = x;

			if (y!=z) {
				delete z->data;
				z->data = new value_type(y->data->first, y->data->second);
			}

			if (y->nodeType==blackNodeType)
				deleteFixup(x);

			_alloc.destroy(y);
			_alloc.deallocate(y, 1);
			nil->parent = maximum(head);
		}

	public:

		Tree()
				:_alloc(), nil(_alloc.allocate(1)), head(nil), _cmp(Compare()), _size(0)
		{
			_alloc.construct(nil, NodeParamed(T1(), T2(), NULL, nilNodeType));
		}

		~Tree()
		{
			_removeTheWholeThree(head);
			_freeNode(nil);
		}

		Tree& operator=(const Tree& t)
		{
			clear();
			_cmp = t.getCompare();
			iterator it = t.begin();
			iterator ite = t.end();
			for (; it!=ite; ++it)
				insert(it);
			return *this;
		}

		iterator begin()
		{
			return iterator(minimum(getRoot()));
		}

		iterator begin() const
		{
			return iterator(minimum(getRoot()));
		}

		iterator end()
		{
			return iterator(nil);
		}

		iterator end() const
		{
			return iterator(nil);
		}

		void clear()
		{
			_removeTheWholeThree(head);
		}

		NodePointer getRoot() const
		{
			return head;
		}

		NodePointer maximum(NodePointer node) const
		{
			while (node!=nil && node->right!=nil) {
				node = node->right;
			}
			return node;
		}

		NodePointer minimum(NodePointer node) const
		{
			while (node!=nil && node->left!=nil) {
				node = node->left;
			}
			return node;
		}

		ft::pair<NodePointer, bool> insert(ft::pair<T1, T2> pair)
		{
			return _add(pair.first, pair.second);
		}

		ft::pair<NodePointer, bool> insert(NodePointer np, ft::pair<T1, T2> pair)
		{
			(void)np;
			return _add(pair.first, pair.second);
		}

		template< class InputIterator >
		ft::pair<NodePointer, bool> insert(InputIterator it)
		{
			return _add(it->first, it->second);
		}

		NodePointer search(T1 key) const
		{
			return _search(head, key);
		}

		bool remove(T1 key)
		{
			return _remove(key);
		}

		size_t getSize() const
		{
			return _size;
		}

		Compare getCompare() const
		{
			return _cmp;
		}

		void setNil(NodePointer newNil) { nil = newNil; }
		void setHead(NodePointer newHead) { head = newHead; }
		void setCmp(Compare cmp) { _cmp = cmp; }
		void setSize(size_t newSize) { _size = newSize; }

		void swap(Tree& t)
		{

			NodePointer tmpNil = nil;
			NodePointer tmpHead = head;
			Compare tmpCmp = _cmp;
			size_t tmpSize = _size;

			setNil(t.nil);
			setHead(t.getRoot());
			setCmp(t.getCompare());
			setSize(t.getSize());

			t.setNil(tmpNil);
			t.setHead(tmpHead);
			t.setCmp(tmpCmp);
			t.setSize(tmpSize);
		}

		NodePointer lower_bound(const T2 k) const
		{
			return _lower_bound(k);
		}

		NodePointer upper_bound(const T2 k) const
		{
			return _upper_bound(k);
		}

		size_t max_size() const
		{
			return _alloc.max_size();
		}

	};
}

#endif
