#ifndef UTILS_HPP
#define UTILS_HPP

#include "iterator_traits.hpp"
#include <memory>
#include <utility>

namespace ft {
	template<class InputIt, class NoThrowForwardIt>
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

	template<typename T>
	void destroy(T* p)
	{
		p->~T();
	}

	template<class InputIt, class NoThrowForwardIt>
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

	template<bool B, class T = void>
	struct enable_if {
	};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<class _T1, class _T2>
	struct pair {
		typedef _T1 first_type;
		typedef _T2 second_type;

		_T1 first;
		_T2 second;

		pair()
				:first(), second() { }

		template<class U, class V>
		pair(const pair<U, V>& pr)
				: first(pr.first), second(pr.second) { }

		pair(const first_type& a, const second_type& b)
				:first(a), second(b) { }

		pair& operator=(const pair& pr)
		{
			first = std::move(pr.first);
			second = std::move(pr.second);
			return *this;
		}

		template<class _U1, class _U2>
		pair&
		operator=(pair<_U1, _U2>& __p)
		{
			first = std::move(__p.first);
			second = std::move(__p.second);
			return *this;
		}

		template<class _MY_T1, class _MY_T2>
		friend bool operator==(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }

		template<class _MY_T1, class _MY_T2>
		friend bool operator!=(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return !(lhs==rhs); }

		template<class _MY_T1, class _MY_T2>
		friend bool operator<(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

		template<class _MY_T1, class _MY_T2>
		friend bool operator<=(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return !(rhs<lhs); }

		template<class _MY_T1, class _MY_T2>
		friend bool operator>(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return rhs<lhs; }

		template<class _MY_T1, class _MY_T2>
		friend bool operator>=(const pair<_MY_T1, _MY_T2>& lhs, const pair<_MY_T1, _MY_T2>& rhs) { return !(lhs<rhs); }
	};

	template<class _Arg1, class _Arg2, class _Result>
	struct binary_function {
		typedef _Arg1 first_argument_type;
		typedef _Arg2 second_argument_type;
		typedef _Result result_type;
	};

	template<class _Tp>
	struct less : binary_function<_Tp, _Tp, bool> {
		bool operator()(const _Tp& __x, const _Tp& __y) const { return __x<__y; }
	};

	template<class _T1, class _T2>
	pair<_T1, _T2> make_pair(_T1 x, _T2 y)
	{
		return (pair<_T1, _T2>(x, y));
	}
}
#endif
