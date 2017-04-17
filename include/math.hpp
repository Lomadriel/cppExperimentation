#ifndef CPPEXPERIMENT_MATH_H
#define CPPEXPERIMENT_MATH_H

#include <type_traits>
#include <cmath>
#include <limits>
#include <functional>

namespace experiment {
	template <typename T>
	constexpr std::decay_t<std::enable_if_t<std::is_signed<T>::value, T>> abs(T x) noexcept {
		return std::abs(x);
	}

	template <typename T>
	constexpr std::decay_t<std::enable_if_t<std::is_unsigned<T>::value, T>> abs(T x) noexcept {
		return std::abs(x);
	}

	template <typename T, typename U = T>
	constexpr std::enable_if_t<!std::is_floating_point<T>::value && !std::is_floating_point<U>::value, bool> equal(const T& a, const U& b) noexcept {
		return a == b;
	}

	template <typename T, typename U = T>
	constexpr std::enable_if_t<std::is_floating_point<T>::value || std::is_floating_point<U>::value, bool> equal(const T& a, const U& b) noexcept {
		return abs(a - b) < std::numeric_limits<decltype(a - b)>::epsilon();
	}

	template <typename T, typename U = T>
	struct equal_to : public std::binary_function<T, U, bool> {
		constexpr bool operator()(const T& first, const T& second) const noexcept {
			return equal(first, second);
		}
	};

	template <typename T, typename U>
	constexpr auto pow(T t, U u)
		-> std::enable_if_t<!std::is_floating_point<T>::value || !std::is_floating_point<U>::value, decltype(t * u)> {
		decltype(t * u) result(1);

		while (u != 0) {
			if (u % 2 == 1) {
				result *= t;
				--u;
			}

			t *= t;
			u >> 2;
		}

		return result;
	}
}
#endif //CPPEXPERIMENT_MATH_H
