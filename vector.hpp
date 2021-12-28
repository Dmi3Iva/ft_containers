#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <algorithm>
#include "utils.hpp"
#include "common_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

	template< class T, class Allocator = std::allocator<T> >
	class vector {

	public:
		/**
		 * Member types
		 */
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef common_iterator<pointer> iterator;
		typedef common_iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

	private:
		pointer _ptr;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;

		template< class InputIterator >
		difference_type get_diff(InputIterator first, InputIterator last)
		{
			difference_type i = 0;
			while (first!=last) {
				++i;
				++first;
			}
			return i;
		}

		void move_right(difference_type offset, size_type n)
		{
			iterator position = begin()+offset;
			iterator ite = end();
			do {
				--ite;
				::new(const_cast<void*>(static_cast<const volatile void*>(
						std::addressof(*(ite+n))))) T(*(ite));
				ite->~T();
			}
			while (ite!=position);
			/*
			for (difference_type i = _size; i>=offset; --i) {
				::new(const_cast<void*>(static_cast<const volatile void*>(
						std::addressof(*(_ptr+i))))) T(*(_ptr+i-1));
			 */
		}

		void move_left(difference_type offset, size_type n)
		{
			iterator position = begin()+offset;
			iterator ite = end();
			while (position!=ite) {
				::new(const_cast<void*>(static_cast<const volatile void*>(
						std::addressof(*(position))))) T(*(position+n));
				(position+n)->~T();
				++position;
			}
		}

		void force_reserve(size_type n)
		{
			if (n==_capacity) return;
			pointer new_arr = _alloc.allocate(n);
			ft::uninitialized_copy(_ptr, _ptr+_size, new_arr);
			for (size_t i = 0; i<_capacity; ++i)
				(_ptr+i)->~T();
			_alloc.deallocate(_ptr, _capacity);
			_ptr = new_arr;
			_capacity = n;
		}

		void full_clear()
		{
			if (_ptr && _capacity!=0) {
				for (size_t i = 0; i<_size; ++i) {
					(_ptr+i)->~T();
				}
				_alloc.deallocate(_ptr, _capacity);
			}
			_ptr = NULL;
			_capacity = 0;
			_size = 0;
			_capacity = 0;
		}

	public:
		explicit vector(const allocator_type& alloc = allocator_type())
				:_ptr(0), _size(0), _capacity(0), _alloc(alloc) { }

		explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
				:_ptr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(n, val);
		}

		template< class InputIterator >
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
				:_ptr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(first, last);
		}

		vector(const vector& x)
				:_ptr(0), _size(0), _capacity(0), _alloc(allocator_type())
		{
			*this = x;
		}

		~vector()
		{
			if (_ptr) _alloc.deallocate(_ptr, _capacity);
		}

		vector& operator=(const vector& v)
		{
			full_clear();
			reserve(v.size());
			_size = 0;
			insert(iterator(_ptr), v.begin(), v.end());
			return *this;
		};

		/**
		 * Iterators
		 */
		iterator begin() { return iterator(_ptr); }

		const_iterator begin() const { return const_iterator(_ptr); }

		iterator end() { return iterator(_ptr+_size); }

		const_iterator end() const { return const_iterator(_ptr+_size); }

		reverse_iterator rbegin() { return reverse_iterator(end()); };

		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator(begin()); }

		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/**
		 * Capacity
		 */
		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

		void resize(size_type n, value_type val = value_type())
		{
			if (n>_capacity) {
				reserve(_capacity*2>=n ? _capacity*2 : n);
				for (size_type i = _size; i<n; ++i) {
					*(_ptr+i) = val;
				}
				_size = n;
			}
			else if (n>_size) {
				for (size_type i = _size; i<n; ++i) {
					*(_ptr+i) = val;
				}
				_size = n;
			}
			else if (n<_size) {
				erase(begin()+n, end());
			}
		}

		size_type capacity() const { return _capacity; }

		bool empty() const { return _size==0; }

		void reserve(size_type n)
		{
			if (n<=_capacity)return;
			size_type new_capacity = n<_capacity*2 ? _capacity*2 : n;
			pointer new_arr = _alloc.allocate(new_capacity);
			ft::uninitialized_copy(_ptr, _ptr+_size, new_arr);
			for (size_t i = 0; i<_size; ++i)
				(_ptr+i)->~T();
			_alloc.deallocate(_ptr, _capacity);
			_ptr = new_arr;
			_capacity = new_capacity;
		}

		/**
		 * Element Access
		 */
		reference operator[](size_type n) { return *(_ptr+n); }

		const_reference operator[](size_type n) const { return *(_ptr+n); }

		reference at(size_type n)
		{
			if (n<_size) return *(_ptr+n);
			else throw std::out_of_range("vector");
		}

		const_reference at(size_type n) const
		{
			if (n<_size) return *(_ptr+n);
			else throw std::out_of_range("vector");
		}

		reference front() { return *(_ptr); }

		const_reference front() const { return *(_ptr); }

		reference back() { return *(_ptr+_size-1); }

		const_reference back() const { return *(_ptr+_size-1); }

		/**
		 * Modifiers
		 */
		template< class InputIterator >
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			insert(iterator(_ptr), first, last);
		}

		void assign(size_type n, const value_type& val)
		{
			clear();
			insert(iterator(_ptr), n, val);
		}

		void push_back(const value_type& val)
		{
			if (_size==_capacity)
				reserve(_capacity==0 ? 1 : _capacity*2);
			new(_ptr+_size) T(val);
			++_size;
		}

		void pop_back()
		{
			--_size;
			(_ptr+_size)->~T();
		}

		iterator insert(iterator position, const value_type& val)
		{
			difference_type offset = _ptr!=0 ? position-begin() : 0;
			size_type old_capacity = _capacity;
			if (_size==_capacity) {
				reserve(_size+1);
			}
			if ((size_type)offset<_size)
				move_right(offset, 1);
			try {
				_alloc.construct(_ptr+offset, val);
			}
			catch (...) {
				move_left(offset, 1);
				force_reserve(old_capacity);
				throw;
			}
			++_size;
			return iterator(_ptr+offset);
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			difference_type offset = _size!=0 ? position-begin() : 0;
			size_type old_capacity = _capacity;
			reserve(_size+n);
			// first step free space
			if ((size_type)offset<_size)
				move_right(offset, n);
			// second step fill space
			try {
				for (size_type i = 0; i<n; ++i) {
					_alloc.construct(_ptr+offset+i, val);
				}
			}
			catch (...) {
				move_left(offset, n);
				force_reserve(old_capacity);
				throw;
			}
			_size += n;
		}

		template< class InputIterator >
		void insert(
				iterator position, InputIterator first,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
		)
		{
			size_type n = get_diff(first, last);
			difference_type offset = _size!=0 ? position-begin() : 0;
			size_type old_capacity = _capacity;
			reserve(_size+(size_type)n);
			if ((size_type)offset<_size)
				move_right(offset, n);
			difference_type i = 0;
			try {
				while (first!=last) {
					_alloc.construct(_ptr+offset+i, *first);
					++i;
					++first;
				}
			}
			catch (...) {
				move_left(offset, n);
				force_reserve(old_capacity);
				throw;
			}
			_size += n;
		}

		iterator erase(iterator position)
		{
			return erase(position, position+1);
		}

		iterator erase(iterator first, iterator last)
		{
			iterator trace = first;
			iterator start = first;
			iterator ite = end();
			_size -= last-first;
			while (trace!=last) {
				trace->~T();
				++trace;
			}
			if (ite!=last)
				ft::uninitialized_move(last, ite, start);
			return start;
		}

		void swap(vector& x)
		{
			std::swap(_ptr, x._ptr);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
		}

		void clear()
		{
			erase(begin(), end());
			_size = 0;
		}

		/**
		 * Allocator
		 */
		allocator_type get_allocator() const { return _alloc; }

		pointer data() { return _ptr; }


		/**
		 * non-member function overloads
		 */
		/**
		 * relation operators
		 */
		friend bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
		{
			if (lhs.size()!=rhs.size()) {
				return false;
			}
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		friend bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
		{
			return !(lhs==rhs);
		}

		friend bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
		{
			return !(rhs<lhs);
		}

		friend bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
		{
			return rhs<lhs;
		}

		friend bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
		{
			return !(lhs<rhs);
		}

		/**
		 * swap
		 */
		friend void swap(ft::vector<T, Allocator>& x, ft::vector<T, Allocator>& y)
		{
			std::swap(x._ptr, y._ptr);
			std::swap(x._size, y._size);
			std::swap(x._capacity, y._capacity);
			std::swap(x._alloc, y._alloc);
		}
	};

}

#endif
