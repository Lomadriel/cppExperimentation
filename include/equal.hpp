#ifndef CPPEXPERIMENT_EQUAL_H
#define CPPEXPERIMENT_EQUAL_H

#include <type_traits>

namespace experiment {
	namespace details {
		template <typename T, typename U, typename R, typename = R>
		struct has_equal_impl : std::false_type {};

		template <typename T, typename U, typename R>
		struct has_equal_impl<T, U, R, decltype(std::declval<T>() == std::declval<U>())>
				: std::true_type {};
	}

	template<typename T, typename U, typename R = bool>
	struct has_equal_to : details::has_equal_impl<T, U, R> {};
}
#endif //CPPEXPERIMENT_EQUAL_H
