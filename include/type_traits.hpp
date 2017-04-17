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
			template <typename TT>
			static auto check(int) -> decltype(swap(std::declval<TT&>(), std::declval<TT&>()), void(), std::true_type());

			template <typename>
			static std::false_type check(...);

		public:
			using type = decltype(check<T>(0));
		};
	}

	namespace details {
		template <typename F, typename T, typename U>
		class has_binary_functor_support {
			template <typename FF, typename TT, typename UU>
			static auto check(int) -> decltype(std::declval<FF>()(std::declval<TT>(), std::declval<UU>()), void(), std::true_type());

			template <typename>
			static std::false_type check(...);

		public:
			using type = decltype(check<F, T, U>(0));
		};

		template <typename F, typename T>
		class has_unary_functor_support {
			template <typename FF, typename TT>
			static auto check(int) -> decltype(std::declval<FF>()(std::declval<TT>()), void(), std::true_type());

			template <typename>
			static std::false_type check(...);

		public:
			using type = decltype(check<F, T>(0));
		};
	}

	template <typename T>
	struct is_nothrow_swappable : swap_details::is_nothrow_swappable_impl<T>::type {
	};

	template <typename T>
	struct is_swappable : swap_details::is_nothrow_swappable_impl<T>::type {
	};

	template <typename F, typename T, typename U = T>
	struct has_binary_functor_support : details::has_binary_functor_support<F, T, U>::type {
	};

	template <typename F, typename T>
	struct has_unary_functor_support : details::has_unary_functor_support<F, T>::type {
	};



	template <typename T, typename U = T>
	struct has_plus : has_binary_functor_support<std::plus<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_minus : has_binary_functor_support<std::minus<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_multiplies : has_binary_functor_support<std::multiplies<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_divides : has_binary_functor_support<std::divides<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_modulus : has_binary_functor_support<std::modulus<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_negate : has_unary_functor_support<std::negate<>, T> {
	};



	template <typename T, typename U = T>
	struct has_equal_to : has_binary_functor_support<std::equal_to<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_not_equal_to : has_binary_functor_support<std::not_equal_to<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_greater : has_binary_functor_support<std::greater<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_less : has_binary_functor_support<std::less<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_greater_equal : has_binary_functor_support<std::greater_equal<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_less_equal : has_binary_functor_support<std::less_equal<>, T, U> {
	};



	template <typename T, typename U = T>
	struct has_logical_and : has_binary_functor_support<std::logical_and<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_logical_or : has_binary_functor_support<std::logical_or<>, T, U> {
	};

	template <typename T>
	struct has_logical_not : has_unary_functor_support<std::logical_not<>, T> {
	};



	template <typename T, typename U = T>
	struct has_bit_and : has_binary_functor_support<std::bit_and<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_bit_not : has_unary_functor_support<std::bit_not<>, T> {
	};

	template <typename T, typename U = T>
	struct has_bit_or : has_binary_functor_support<std::bit_or<>, T, U> {
	};

	template <typename T, typename U = T>
	struct has_bit_xor : has_binary_functor_support<std::bit_xor<>, T, U> {
	};
}
#endif //CPPEXPERIMENT_TYPE_TRAIT_H
