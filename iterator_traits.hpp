//
// Created by Shandy Mephesto on 11/2/21.
//

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <stddef.h>
#include <iterator>

namespace ft {
	template< class Iterator >
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template< class T >
	struct iterator_traits<T*> {
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template< class T >
	struct iterator_traits<const T*> {
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	};
}
#endif
