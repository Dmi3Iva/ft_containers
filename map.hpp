#ifndef MAP_HPP
#define MAP_HPP

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "Tree.hpp"
#include "Node.hpp"
#include "tree_iterator.hpp"

namespace ft {
	template< class Key,
			class T,
			class Compare = less<Key>,
			class Alloc = std::allocator<Node<const Key, T> >
	>
	class map {

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef Compare key_compare;

		class value_compare {
			friend class map;
		protected:
			Compare comp;
			value_compare(Compare c)
					:comp(c) { }
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef tree_iterator<const Key, T> iterator;
		typedef const_tree_iterator<const Key, T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

	private:
		Tree<const Key, T, Compare, Alloc> _tree;
		key_compare _key_compare;
		allocator_type _alloc;
//		value_compare _value_compare;
		typedef Node<const Key, T>* NodePointer;

	public:

		explicit map(
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
		)
				:_tree(), _key_compare(comp), _alloc(alloc) { }

		template< class InputIterator >
		map(InputIterator
		first,
				InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
		)
				:
				_tree(), _key_compare(comp), _alloc(alloc)
		{
			while (first!=last) {
				_tree.insert(first);
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
			_tree = x._tree;
			return *this;
		}

		iterator begin()
		{
			return _tree.begin();
		}
		const_iterator begin() const
		{
			return const_iterator(_tree.begin());
		}

		iterator end()
		{
			return _tree.end();
		}
		const_iterator end() const
		{
			return const_iterator(_tree.end());
		}

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(begin()); }

		bool empty() const { return _tree.getSize()==0; }

		size_type size() const { return _tree.getSize(); }

		size_type max_size() const { return _tree.max_size(); }

		mapped_type& operator[](const key_type& k)
		{
			ft::pair<iterator, bool> res = insert(ft::pair<Key, mapped_type>(k, _tree.search(k)->data->second));
			return res.first->second;
		}

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			return _tree.insert(val);;
		}

		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			ft::pair<iterator, bool> result = _tree.insert(val);
			return result.first;
		}

		template< class InputIterator >
		void insert(InputIterator first, InputIterator last)
		{
			while (first!=last) {
				_tree.insert(first);
				++first;
			}
		}
		void erase(iterator position)
		{
			_tree.remove(position->first);
		}
		size_type erase(const key_type& k)
		{
			return _tree.remove(k) ? 1 : 0;
		}
		void erase(iterator first, iterator last)
		{
			Key key;
			while (first!=last && first!=end()) {
				key = first->first;
				++first;
				_tree.remove(key);
			}
		}

		void swap(map& x)
		{
			_tree.swap(x._tree);
		}

		void clear()
		{
			_tree.clear();
		}

		key_compare key_comp() const { return _key_compare; }

		value_compare value_comp() const { return value_compare(Compare()); }

		iterator find(const key_type& k) { return iterator(_tree.search(k)); }
		const_iterator find(const key_type& k) const { return const_iterator(_tree.search(k)); }

		mapped_type& at(const Key& key)
		{
			iterator it = find(key);
			if (it==end()) {
				throw std::out_of_range("map");
			}
			return it->second;
		}
		const mapped_type& at(const Key& key) const
		{
			iterator it = find(key);
			if (it==end()) {
				throw std::out_of_range("map");
			}
			return it->second;
		}

		size_type count(const key_type& k) const { return _tree.search(k)!=end() ? 1 : 0; }

		iterator lower_bound(const key_type& k) { return iterator(_tree.lower_bound(k)); }
		const_iterator lower_bound(const key_type& k) const { return const_iterator(_tree.lower_bound(k)); }

		iterator upper_bound(const key_type& k) { return iterator(_tree.upper_bound(k)); }
		const_iterator upper_bound(const key_type& k) const { return const_iterator(_tree.upper_bound(k)); }

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const { return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }
		pair<iterator, iterator> equal_range(const key_type& k) { return pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }

		allocator_type get_allocator() const { return _alloc; }

		friend bool operator==(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs)
		{
			if (lhs.size()!=rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		friend
		bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs)
		{

			return !(lhs==rhs);
		}

		friend bool operator<(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs)
		{
			const_iterator lb = lhs.begin();
			const_iterator le = lhs.end();
			const_iterator rb = rhs.begin();
			const_iterator re = rhs.end();
			return ft::lexicographical_compare(lb, le, rb, re);
		}

		friend bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs)
		{
			return !(rhs<lhs);
		}

		friend bool operator>(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs)
		{
			return rhs<lhs;
		}

		friend bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs)
		{
			return !(lhs<rhs);
		}
	};
}
#endif
