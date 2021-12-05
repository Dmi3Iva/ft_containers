//
// Created by Shandy Mephesto on 11/16/21.
//

#ifndef COMMON_ITERATOR_HPP
#define COMMON_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template<class _Iter>
	class common_iterator {

	private:
		typedef _Iter iterator_type;

	public:
		typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference reference;

	private:
		pointer _ptr;

	public:

		common_iterator(pointer ptr = NULL)
				:_ptr(ptr) { };

		~common_iterator() { };

		template<typename S>
		common_iterator(const common_iterator<S>& rhs)
				:_ptr(rhs.base()) { }

		pointer base() const
		{
			return _ptr;
		}

		common_iterator& operator=(const common_iterator& rhs)
		{
			_ptr = rhs._ptr;
			return *this;
		}

		bool operator==(const pointer& ptr) { return _ptr==ptr; }

		template<class U, class W>
		friend bool operator==(const common_iterator<U>& lhs, const common_iterator<W>& rhs) { return lhs._ptr==rhs._ptr; }

		template<class U, class W>
		friend bool operator!=(const common_iterator<U>& lhs, const common_iterator<W>& rhs) { return lhs._ptr!=rhs._ptr; }

		reference operator*() { return *_ptr; }

		pointer operator->() { return _ptr; }

		common_iterator& operator++()
		{
			++_ptr;
			return *this;
		}

		common_iterator operator++(int)
		{
			common_iterator tmp(*this);
			++_ptr;
			return tmp;
		}

		common_iterator operator-=(int n)
		{
			_ptr -= n;
			return *this;
		}

		common_iterator& operator--()
		{
			--_ptr;
			return *this;
		}

		common_iterator operator--(int)
		{
			common_iterator tmp(*this);
			--_ptr;
			return tmp;
		}

		common_iterator operator+=(int n)
		{
			_ptr += n;
			return *this;
		}

		common_iterator operator+(int n) const { return (_ptr+n); }

		friend common_iterator operator+(int n, const common_iterator& rhs) { return (rhs._ptr+n); }

		common_iterator operator-(int n) const { return (_ptr-n); }

		difference_type operator-(const common_iterator& rhs) const { return (_ptr-rhs._ptr); }

		template<typename U, typename W>
		friend bool operator>=(const common_iterator<U>& lhs, const common_iterator<W>& rhs) { return lhs._ptr>=rhs._ptr; }

		template<typename U, typename W>
		friend bool operator>(const common_iterator<U>& lhs, const common_iterator<W>& rhs) { return lhs._ptr>rhs._ptr; }

		template<typename U, typename W>
		friend bool operator<=(const common_iterator<U>& lhs, const common_iterator<W>& rhs) { return lhs._ptr<=rhs._ptr; }

		template<typename U, typename W>
		friend bool operator<(const common_iterator<U>& lhs, const common_iterator<W>& rhs) { return lhs._ptr<rhs._ptr; }

		reference operator[](int n) const { return *(_ptr+n); }
	};
}
#endif //CONTAINERS_NORMAL_ITERATOR_HPP
