//
// Created by Shandy Mephesto on 11/1/21.
//

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "common_iterator.hpp"

// TOOD::remove it
//#include <iostream>

// https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01052_source.html

namespace ft {
	template<class Itr>
	class reverse_iterator : public ft::common_iterator<typename iterator_traits<Itr>::pointer> {
	private:
		Itr _itr;

	public:
		typedef typename iterator_traits<Itr>::value_type value_type;
		typedef typename iterator_traits<Itr>::reference reference;
		typedef typename iterator_traits<Itr>::pointer pointer;
		typedef typename iterator_traits<Itr>::iterator_category iterator_category;
		typedef typename iterator_traits<Itr>::difference_type difference_type;

		reverse_iterator() { }

		explicit reverse_iterator(const Itr& itr)
				:_itr(itr) { }

		reverse_iterator(const reverse_iterator& itr)
				:_itr(itr.base()) { }

		template<typename S>
		reverse_iterator(const reverse_iterator<S>& itr)
				:_itr(itr.base()) { }

		reference operator*() const
		{
			Itr tmp = _itr;
			return *--tmp;
		}

		pointer operator->() const { return &(operator*()); }

		Itr base() const
		{
			return _itr;
		}

		reverse_iterator& operator++()
		{
			--_itr;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--_itr;
			return tmp;
		}

		reverse_iterator& operator--()
		{
			++_itr;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++_itr;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_itr-n); }

		reverse_iterator operator+=(difference_type n)
		{
			_itr -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_itr+n); }

		difference_type operator-(const reverse_iterator& rhs) const { return (rhs.base()-_itr.base()); }

		reverse_iterator operator-=(difference_type n)
		{
			_itr += n;
			return *this;
		}

		reference operator[](int n) const { return *(_itr-n-1); }

		template<class U, class W>
		friend bool operator==(const reverse_iterator<U>& lhs, const reverse_iterator<W>& rhs)
		{
			return lhs.base()==rhs.base();
		}

		template<class U, class W>
		friend bool operator!=(const reverse_iterator<U>& lhs, const reverse_iterator<W>& rhs) { return lhs.base()!=rhs.base(); }

		friend reverse_iterator operator+(int n, const reverse_iterator& rhs) { return reverse_iterator(rhs.base()-n); }

		template<typename U, typename W>
		friend bool operator<(const reverse_iterator<U>& lhs, const reverse_iterator<W>& rhs) { return rhs.base()<lhs.base(); }

		template<typename U, typename W>
		friend bool operator>(const reverse_iterator<U>& lhs, const reverse_iterator<W>& rhs) { return rhs<lhs; }

		template<typename U, typename W>
		friend bool operator<=(const reverse_iterator<U>& lhs, const reverse_iterator<W>& rhs) { return !(rhs<lhs); }

		template<typename U, typename W>
		friend bool operator>=(const reverse_iterator<U>& lhs, const reverse_iterator<W>& rhs) { return !(lhs<rhs); }

		template<typename U>
		friend typename reverse_iterator<U>::difference_type operator-(const reverse_iterator<U>& lhs, const reverse_iterator<U>& rhs) { return (rhs.base-lhs.base()); }
	};
}
#endif
