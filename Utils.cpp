
#include "Utils.h"


namespace offset {

	const std::array<uint32_t, 8> C8sigma1 = {
		/* 0 */	Mult<Factorial2<8, 1>::value, Power<3, 0>::value>::value,
		/* 1 */	Mult<Factorial2<8, 1>::value, Power<3, 1>::value>::value,
		/* 2 */	Mult<Factorial2<8, 1>::value, Power<3, 2>::value>::value,
		/* 3 */	Mult<Factorial2<8, 1>::value, Power<3, 3>::value>::value,
		/* 4 */	Mult<Factorial2<8, 1>::value, Power<3, 4>::value>::value,
		/* 5 */	Mult<Factorial2<8, 1>::value, Power<3, 5>::value>::value,
		/* 6 */	Mult<Factorial2<8, 1>::value, Power<3, 6>::value>::value,
		/* 7 */	Mult<Factorial2<8, 1>::value, Power<3, 7>::value>::value
	};

	const std::array<uint32_t, 7> C8sigma2 = {
		/* 0 */	Factorial2<8, 8>::value,
		/* 1 */	Factorial2<8, 7>::value,
		/* 2 */	Factorial2<8, 6>::value,
		/* 3 */	Factorial2<8, 5>::value,
		/* 4 */	Factorial2<8, 4>::value,
		/* 5 */	Factorial2<8, 3>::value,
		/* 6 */	Factorial2<8, 2>::value
	};

	const std::array<uint32_t, 11> DISPO12 = {
		/* 0 */	Factorial2<12, 12>::value,
		/* 1 */	Factorial2<12, 11>::value,
		/* 2 */ Factorial2<12, 10>::value,
		/* 3 */ Factorial2<12, 9>::value,
		/* 4 */ Factorial2<12, 8>::value,
		/* 5 */ Factorial2<12, 7>::value,
		/* 6 */ Factorial2<12, 6>::value,
		/* 7 */ Factorial2<12, 5>::value,
		/* 8 */ Factorial2<12, 4>::value,
		/* 9 */ Factorial2<12, 3>::value,
		/* 10 */ Factorial2<12, 2>::value,
	};
}


// STRINGS

std::vector<std::string> string_split(const std::string& s, const char delim) {
	std::vector<std::string> elems;
	string_split(s, delim, std::back_inserter(elems));
	return elems;
}



// OUTPUT & DEBUG
