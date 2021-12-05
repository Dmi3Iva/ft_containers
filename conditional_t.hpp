#ifndef CONDITIONAL_T
#define CONDITIONAL_T

namespace ft {

	template<bool B, typename T, typename F>
	struct conditional_t {
		typedef T type;
	};

	template<typename T, typename F>
	struct conditional_t<false, T, F> {
		typedef F type;
	};
}
#endif