#pragma once

#include <array>
#include <cstdint>
#include <iterator>
#include <numeric>	// for std::inner_product
#include <sstream>
#include <string>
#include <vector>

#include "MetaMath.h"


namespace offset {

	template<typename id, const size_t n>
	inline auto extract(uint32_t& c, const std::array<uint32_t, n> offsets)
	{
		std::array<id, n> relative;

		for (int i = n - 1; i >= 0; i--) {
			relative[i] = static_cast<id>(c / offsets[i]);
			c -= relative[i] * offsets[i];
		}

		return relative;
	}

	template<typename id, const size_t n>
	inline auto calculate(const std::array<id, n> data, const std::array<uint32_t, n> offsets)
	{
		return std::inner_product(data.begin(), data.end(), offsets.begin(), 0);
	}

	template<typename id, const size_t n>
	auto relativePositions(const std::array<id, n> relative)
	{
		std::array<id, n + 1> res;
		std::array<id, n + 1> indices = make_index_array<id, n + 1>();

		for (size_t i = 0; i < n; i++) {
			res[i] = indices[relative[i]];					// pop

			//if (relative[i] < n-i)
			std::rotate(indices.begin() + relative[i],		// shift
				indices.begin() + relative[i] + 1,
				indices.end() - i);							// last i positions not used
		}
		res[n] = indices[0];

		return res;
	}

	template<typename id, const size_t n>
	auto absolutePositions(const std::array<id, n> c)
	{
		std::array<id, n - 1> absolute;

		for (size_t i = 0; i < n - 1; i++) {
			absolute[i] = c[i];

			for (size_t k = 0; k < i; k++)
				if (c[k] < c[i])
					--absolute[i];
		}

		return absolute;
	}

	extern const std::array<uint32_t, 8> C8sigma1;

	extern const std::array<uint32_t, 7> C8sigma2;
		
	extern const std::array<uint32_t, 11> DISPO12;
}


// STRINGS

// http://stackoverflow.com/questions/236129/split-a-string-in-c

template<typename Out>
void string_split(const std::string& s, const char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim))
		*(result++) = item;
}

std::vector<std::string> string_split(const std::string& s, const char delim);



// OUTPUT & DEBUG

template<const size_t len, typename T>
static void doOut(std::string incipit, std::array<T, len> v) {
	std::cout << incipit << " = {";
	for (int i = 0; i < len; i++)
		std::cout << static_cast<int>(v[i]) << (i != len - 1 ? ", " : "}");
	std::cout << std::endl;
}

// display char ->  int
//template<const size_t len, typename T,
//	typename std::enable_if_t<std::is_same<T, char>::value || std::is_same<T, signed char>::value || std::is_same<T, unsigned char>::value>
//>
//static void doOut(std::string incipit, std::array<T, len> v) {
//	std::cout << incipit << " = char{";
//	for (int i = 0; i < len; i++)
//		std::cout << static_cast<int>(v[i]) << (i != len - 1 ? ", " : "}");
//	std::cout << std::endl;
//}
