#ifndef CPPEXPERIMENT_TYPE_TRAIT_H
#define CPPEXPERIMENT_TYPE_TRAIT_H

#include <type_traits>
#include <utility>

namespace experiment {
	namespace swap_details {
		using std::swap;

		template <typename T>
		class is_nothrow_swappable_impl {
			template <typename TT>
			static auto check(int) -> std::integral_constant<bool, noexcept(swap(std::declval<TT&>(), std::declval<TT&>()))>;

			template <typename>
			static std::false_type check(...);

		public:
			using type = decltype(check<T>(0));
		};

		template <typename T>
		class is_swappable_impl {
			template <typename TT, typename = decltype(swap(std::declval<TT&>(), std::declval<TT&>()))>
			static auto check(int);

			template <typename>
			static std::false_type check(...);

		public:
			using type = decltype(check<T>(0));
		};
	}

	template<typename T>
	struct is_nothrow_swappable : swap_details::is_nothrow_swappable_impl<T>::type {
	};

	template<typename T>
	struct is_swappable : swap_details::is_nothrow_swappable_impl<T>::type {
	};

}
#endif //CPPEXPERIMENT_TYPE_TRAIT_H
