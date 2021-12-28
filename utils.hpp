#ifndef UTILS_HPP
#define UTILS_HPP

#include "iterator_traits.hpp"
#include <memory>
#include <utility>

namespace ft {
	template< class InputIt, class NoThrowForwardIt >
	NoThrowForwardIt uninitialized_copy(InputIt first, InputIt last, NoThrowForwardIt d_first)
	{
		typedef typename ft::iterator_traits<NoThrowForwardIt>::value_type T;
		NoThrowForwardIt current = d_first;
		try {
			for (; first!=last; ++first, (void)++current) {
				::new(const_cast<void*>(static_cast<const volatile void*>(
						std::addressof(*current)))) T(*first);
			}
			return current;
		}
		catch (...) {
			for (; d_first!=current; ++d_first) {
				d_first->~T();
			}
			throw;
		}
	}

	template< typename T >
	void destroy(T* p)
	{
		p->~T();
	}

	template< class InputIt, class NoThrowForwardIt >
	NoThrowForwardIt uninitialized_move(InputIt first, InputIt last, NoThrowForwardIt d_first)
	{
		typedef typename ft::iterator_traits<NoThrowForwardIt>::value_type T;
		NoThrowForwardIt current = d_first;
		try {
			for (; first!=last; ++first, (void)++current) {
				::new(const_cast<void*>(static_cast<const volatile void*>(
						std::addressof(*current)))) T(*first);
				destroy(first.base());
			}
			return current;
		}
		catch (...) {
			for (; d_first!=current; ++d_first) {
				d_first->~T();
			}
			throw;
		}
	}

	template< bool B, class T = void >
	struct enable_if {
	};

	template< class T >
	struct enable_if<true, T> {
		typedef T type;
	};

	template< class _T1, class _T2 >
	struct pair {
		typedef _T1 first_type;
		typedef _T2 second_type;

		_T1 first;
		_T2 second;

		pair()
				:first(), second() { }

		template< class U, class V >
		pair(const pair<U, V>& pr)
				: first(pr.first), second(pr.second) { }

		pair(const first_type& a, const second_type& b)
				:first(a), second(b) { }

		pair& operator=(pair const& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}

		template< class _U1, class _U2 >
		pair&
		operator=(pair<_U1, _U2> const& __p)
		{
			first = __p.first;
			second = __p.second;
			return *this;
		}

		template< class _MY_T1, class _MY_T2 >
		friend bool operator==(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }

		template< class _MY_T1, class _MY_T2 >
		friend bool operator!=(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return !(lhs==rhs); }

		template< class _MY_T1, class _MY_T2 >
		friend bool operator<(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

		template< class _MY_T1, class _MY_T2 >
		friend bool operator<=(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return !(rhs<lhs); }

		template< class _MY_T1, class _MY_T2 >
		friend bool operator>(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return rhs<lhs; }

		template< class _MY_T1, class _MY_T2 >
		friend bool operator>=(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return !(lhs<rhs); }
	};

	template< class _Arg1, class _Arg2, class _Result >
	struct binary_function {
		typedef _Arg1 first_argument_type;
		typedef _Arg2 second_argument_type;
		typedef _Result result_type;
	};

	template< class _Tp >
	struct less : binary_function<_Tp, _Tp, bool> {
		bool operator()(const _Tp& __x, const _Tp& __y) const { return __x<__y; }
	};

	template< class _T1, class _T2 >
	pair<_T1, _T2> make_pair(_T1 x, _T2 y)
	{
		return (pair<_T1, _T2>(x, y));
	}

	template< class InputIterator1, class InputIterator2 >
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1) {
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1;
			++first2;
		}
		return (first2!=last2);
	}

	template< class InputIterator1, class InputIterator2, class Compare >
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp)
	{
		{
			while (first1!=last1) {
				if (first2==last2 || comp(*first2, *first1)) return false;
				else if (comp(*first1, *first2)) return true;
				++first1;
				++first2;
			}
			return (first2!=last2);
		}
	}

	template< class InputIterator1, class InputIterator2 >
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1) {
			if (!(*first1==*first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template< class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1) {
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template< class T, T v >
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() { return v; }
	};

	typedef integral_constant<bool, false> false_type;
	typedef integral_constant<bool, true> true_type;

	template< class T >
	struct is_integral : public false_type {
	};
	template< class T >
	struct is_integral<const T> : public is_integral<T> {
	};
	template< class T >
	struct is_integral<volatile const T> : public is_integral<T> {
	};
	template< class T >
	struct is_integral<volatile T> : public is_integral<T> {
	};
	template< >
	struct is_integral<unsigned char> : public true_type {
	};
	template< >
	struct is_integral<unsigned short> : public true_type {
	};
	template< >
	struct is_integral<unsigned int> : public true_type {
	};
	template< >
	struct is_integral<unsigned long> : public true_type {
	};
	template< >
	struct is_integral<signed char> : public true_type {
	};
	template< >
	struct is_integral<short> : public true_type {
	};
	template< >
	struct is_integral<int> : public true_type {
	};
	template< >
	struct is_integral<long> : public true_type {
	};
	template< >
	struct is_integral<char> : public true_type {
	};
	template< >
	struct is_integral<bool> : public true_type {
	};
	template< >
	struct is_integral<char32_t> : public true_type {
	};
	template< >
	struct is_integral<char16_t> : public true_type {
	};
	template< >
	struct is_integral<wchar_t> : public true_type {
	};
	template< >
	struct is_integral<long long> : public true_type {
	};
	template< >
	struct is_integral<unsigned long long> : public true_type {
	};
}
#endif
