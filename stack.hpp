#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
	template<class T, class Container = vector<T> >
	class stack {
	protected:
		Container c;
	public:
		typedef typename Container::value_type value_type;
		typedef Container container_type;
		typedef typename Container::size_type size_type;
		//methods
		explicit stack(const container_type& ctnr = container_type())
				:c(ctnr) { }

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		value_type& top()
		{
			return c.back();
		}

		const value_type& top() const
		{
			return c.back();
		}

		void push(const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}

		friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return lhs.c==rhs.c;
		}

		friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return lhs.c!=rhs.c;
		}

		friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return lhs.c<rhs.c;
		}

		friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return !(rhs.c<lhs.c);
		}

		friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return rhs.c<lhs.c;
		}

		friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return !(lhs.c<rhs.c);
		}
	};
}
#endif