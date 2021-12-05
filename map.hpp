#ifndef MAP_HPP
#define MAP_HPP

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "RBTree.hpp"
#include "tree_iterator.hpp"
#include "Node.hpp"
namespace ft {
	template<class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = less<Key>,                     // map::key_compare
			class Alloc = std::allocator<pair<const Key, T> >    // map::allocator_type
	>
	class map {

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Compare value_compare; // TODO:: is it right?
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef tree_iterator<value_type*> iterator;
		typedef tree_iterator<const value_type*> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

	private:
		RBTree<const Key, T> _tree;
		key_compare _key_compare;
		allocator_type _alloc;
		value_compare _value_compare;
		typedef Node<const Key, T>* NodePointer;

	public:

		explicit map(
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
		)
				:_tree(), _key_compare(comp), _alloc(alloc) { }

		template<class InputIterator>
		map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				:_tree(), _key_compare(comp), _alloc(alloc)
		{
			while (first!=last) {
				_tree.insert(first->first, first->second);
				++first;
			}
		}

		map(const map& x)
		{
			*this = x;
		}

		~map() { }

		map& operator=(const map& x)
		{
			_tree.getRoot() = x._tree.getRoot();// TODO:: should leek;
		}

		iterator begin()
		{
			return iterator(_tree.minimum(_tree.getRoot()));
		}
		const_iterator begin() const
		{
			return iterator(_tree.minimum(_tree.getRoot()));
		}

		iterator end()
		{
			return iterator(_tree.maximum(_tree.getRoot()));
		}
		const_iterator end() const
		{
			return iterator(_tree.maximum(_tree.getRoot()));
		}

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(begin()); }

		bool empty() const { return _tree.getRoot()==NULL; } // TODO:: I'm sure that can be incorrect

		size_type size() const { return 0; } // TODO::

		size_type max_size() const { return _alloc.max_size(); }

		mapped_type& operator[](const key_type& k) { return _tree.search(k); }

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			NodePointer np = _tree.insert(val.first, val.second);;
			return ft::pair<iterator, bool>(iterator(np), np!=NULL);
		}

		iterator insert(iterator position, const value_type& val)
		{
			_tree.insert(position.first, val.second);
			iterator it = iterator(_tree.search(val.first));
			return value_type(it, it!=NULL);
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first!=last) {
				_tree.insert(first.first, first.second);
				++first;
			}
		}

//		void erase(iterator position) { }
//		size_type erase(const key_type& k) { }
//		void erase(iterator first, iterator last) { }
//
//		void swap(map& x) { }
//
//		void clear() { }

		key_compare key_comp() const { return _key_compare; }

		value_compare value_comp() const { return _value_compare; }

//		iterator find(const key_type& k) { }
//		const_iterator find(const key_type& k) const { }
//
//		size_type count(const key_type& k) const { }
//
//		iterator lower_bound(const key_type& k) { }
//		const_iterator lower_bound(const key_type& k) const { }
//
//		iterator upper_bound(const key_type& k) { }
//		const_iterator upper_bound(const key_type& k) const { }
//
//		pair<const_iterator, const_iterator> equal_range(const key_type& k) const { }
//		pair<iterator, iterator> equal_range(const key_type& k) { }

		allocator_type get_allocator() const { return _alloc; }

	};
}
#endif
