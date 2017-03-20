#pragma once

// Sum<1,2,3,4,5>...
template<unsigned long...> struct Sum;
template<unsigned long Head, unsigned long ...Rest>struct Sum<Head, Rest...> {
	static constexpr unsigned long value = Head + Sum<Rest...>::value;
};
template<>struct Sum<> {
	static constexpr unsigned long value = 0;
};

// Mult<....>
template<unsigned long...> struct Mult;
template<unsigned long Head, unsigned long ...Rest>struct Mult<Head, Rest...> {
	static constexpr unsigned long value = Head * Mult<Rest...>::value;
};
template<>struct Mult<> {
	static constexpr unsigned long value = 1;
};

// Count<...>
template<unsigned long...> struct Count;
template<unsigned long Head, unsigned long ...Rest>struct Count<Head, Rest...> {
	static constexpr unsigned long value = 1 + Count<Rest...>::value;
};
template<>struct Count<> {
	static constexpr unsigned long value = 0;
};

// x!
template<unsigned long n>struct Factorial {
	static constexpr unsigned long value = Factorial<n - 1>::value*n;
};
template<>struct Factorial<0> {
	static constexpr unsigned long value = 1;
};

// a!/b!
//template<unsigned long a, unsigned long b>struct Factorial2 {
//	static constexpr unsigned long value = a*Factorial2<a-1, b>::value;
//};
//template<unsigned long a>struct Factorial2<a,a> {
//	static constexpr unsigned long value = 1;
//};
template<unsigned long a, unsigned long b>struct Factorial2 {
	static constexpr unsigned long value = Factorial<a>::value / Factorial<b>::value;
};

// x^n
template<unsigned long x, unsigned long n>struct Power {
	static constexpr unsigned long value = x*Power<x, n - 1>::value;
};
template<unsigned long x>struct Power<x, 0> {
	static constexpr unsigned long value = 1;
};



namespace detail {
	template<typename T, T... Ns>
	constexpr auto make_index_array(T const offset, std::integer_sequence<T, Ns...>) noexcept ->std::array<T, sizeof...(Ns)> {
		return { { static_cast<T>(Ns + offset)... } };	// static cast for T=(u)char
	}
}

template<typename T, T N>
constexpr auto make_index_array(T const offset = {}) noexcept {
	static_assert(N >= T{}, "no negative sizes");
	return detail::make_index_array<T>(offset, std::make_integer_sequence<T, N>{});
}
