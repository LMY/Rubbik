
#include <array>
#include <cstdint>
#include <tuple>
#include <numeric>	// for std::inner_product
#include <iostream> // for debug
#include <string>	// for debug


enum class Color { // Y, R, G, O, B, W
	Yellow='Y',
	Red='R', Green = 'G', Orange = 'O', Blue = 'B',
	White = 'W'
};

enum FACE { // U, F, R, B, L, D
	Up = 'U',											// Y
	Front = 'F', Right = 'R', Back = 'B', Left = 'L',	// R, G, O, B
	Down = 'D'											// W
};

char toChar(Color c) {
	switch (c) {
		case Color::Yellow: return 'Y';
		case Color::Red: return 'R';
		case Color::Green: return 'G';
		case Color::Orange: return 'O';
		case Color::Blue: return 'B';
		case Color::White: return 'W';
		default: return '?';
	}
}

enum DIR {
	U, Ui,
	L, Li,
	R, Ri,
	D, Di,
	F, Fi,
	B, Bi
};

typedef std::array<Color, 3> CubeAngle;
typedef std::array<Color, 2> CubeMid;

const std::array<const CubeAngle, 8> angles({
	CubeAngle({ Color::Red, Color::Yellow, Color::Blue }),
	CubeAngle({ Color::Green, Color::Yellow, Color::Red }),
	CubeAngle({ Color::Orange, Color::Yellow, Color::Green }),
	CubeAngle({ Color::Blue, Color::Yellow, Color::Orange }),

	CubeAngle({ Color::Red, Color::Blue, Color::White }),
	CubeAngle({ Color::Green, Color::Red, Color::White }),
	CubeAngle({ Color::Orange, Color::Green, Color::White }),
	CubeAngle({ Color::Blue, Color::Orange, Color::White })
});
const std::array<const CubeMid, 12> mids({
	CubeMid({ Color::Red, Color::Yellow }),
	CubeMid({ Color::Green, Color::Yellow }),
	CubeMid({ Color::Orange, Color::Yellow }),
	CubeMid({ Color::Blue, Color::Yellow }),

	CubeMid({ Color::Red, Color::White }),
	CubeMid({ Color::Green, Color::White }),
	CubeMid({ Color::Orange, Color::White }),
	CubeMid({ Color::Blue, Color::White }),

	CubeMid({ Color::Green, Color::Red }),
	CubeMid({ Color::Orange, Color::Green }),
	CubeMid({ Color::Blue, Color::Orange }),
	CubeMid({ Color::Red, Color::Blue })
});


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

#include "MetaMath.h"

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

const std::array<uint32_t, 8> C8sigma1 = {
/* 0 */	Mult<Factorial2<8, 2>::value, Power<3, 1>::value>::value,
/* 1 */	Mult<Factorial2<8, 2>::value, Power<3, 2>::value>::value,
/* 2 */	Mult<Factorial2<8, 2>::value, Power<3, 3>::value>::value,
/* 3 */	Mult<Factorial2<8, 2>::value, Power<3, 4>::value>::value,
/* 4 */	Mult<Factorial2<8, 2>::value, Power<3, 5>::value>::value,
/* 5 */	Mult<Factorial2<8, 2>::value, Power<3, 6>::value>::value,
/* 6 */	Mult<Factorial2<8, 2>::value, Power<3, 7>::value>::value,
/* 7 */	Mult<Factorial2<8, 2>::value, Power<3, 8>::value>::value
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

template<typename id>
class KubeState {
	uint32_t C12  : 29;		// mid-latis disposition. Dividing C12->5, C5 would still be 29 bits. Any other division costs +1bit.
	uint32_t S2   : 12;		// mid-latis state
	uint32_t C8s3 : 28;		// vertices: disposition offset state. Not offsetting costs +1bit. dividing costs +1bit.

public: // debug line. leave these static functions private in release
	template<const size_t n>
	inline static auto offsetExtract(uint32_t& c, const std::array<uint32_t, n> offsets)
	{
		std::array<id, n> relative;

		for (int i = n-1; i >= 0; i--) {
			relative[i] = static_cast<id>(c / offsets[i]);
			c -= relative[i] * offsets[i];
		}

		return relative;
	}

	template<const size_t n>
	inline static auto offsetCalculate(const std::array<id, n> data, const std::array<uint32_t, n> offsets)
	{
		return std::inner_product(data.begin(), data.end(), offsets.begin(), 0);
	}

	template<const size_t n>
	static auto relativePositions(const std::array<id, n> relative)
	{
		std::array<id, n+1> res;
		std::array<id, n+1> indices = make_index_array<id, n+1>();

		for (size_t i = 0; i < n; i++) {
			res[i] = indices[relative[i]];					// pop

			std::rotate(indices.begin() + relative[i],		// shift
						indices.begin() + relative[i] + 1,
						indices.end() - i);					// last i positions not used
		}
		res[n] = indices[0];

		return res;
	}

	template<const size_t n>
	static auto absolutePositions(const std::array<id, n> c)
	{
		std::array<id, n-1> absolute;

		for (size_t i = 0; i < n-1; i++) {
			absolute[i] = c[i];

			for (size_t k = 0; k < i; k++)
				if (c[k] < c[i])
					--absolute[i];
		}

		return absolute;
	}

	inline static auto getDispoC12(uint32_t c12)
	{
		const auto relative = offsetExtract(c12, DISPO12);
		return relativePositions(relative);
	}

	inline static auto getDispoC8sigma(uint32_t c8s3)
	{
		const auto state = offsetExtract(c8s3, C8sigma1);
		const auto relative = relativePositions(offsetExtract(c8s3, C8sigma2));

		return std::make_tuple(relative, state);
	}

	inline static uint32_t setDispoC8sigma(const std::array<id, 8> c, const std::array<id, 8> sigma)
	{
		const auto absolute = absolutePositions(c);
		return offsetCalculate(absolute, C8sigma2) + offsetCalculate(sigma, C8sigma1);
	}

	inline static uint32_t setDispoC12(const std::array<id, 12> c)
	{
		const auto absolute = absolutePositions(c);
		return offsetCalculate(absolute, DISPO12);
	}

	inline static auto getSigma12(uint32_t s2)
	{
		std::array<id, 12> x;

		for (int i = 0; i < 12; i++)
			x[i] = s2&(1 << (2 * i)) * 2 + s2&(1 << (2 * i + 1));

		return x;
	}

	inline static uint32_t setSigma12(const std::array<id, 12> x)
	{
		uint32_t ret = 0;

		for (int i = 0; i < 12; i++)
			ret |= (3 << (2 * i)) & x[i];

		return ret;
	}


public:
	KubeState() :  KubeState(0, 0, 0) {}
	KubeState(uint32_t _C12, uint32_t _S2, uint32_t _C8s3) : C12(_C12), S2(_S2), C8s3(_C8s3) {}
	KubeState(const KubeState&) = default;

	// mid faces states
	auto get12Sigma2() const {
		return getSigma12(S2);
	}
	void set12Sigma2(std::array<id, 12> x) {
		S2 = setSigma12(x);
	}

	// mid faces
	auto getC12() const {
		return getDispoC12(C12);
	}
	void setC12(std::array<id, 12> c12) {
		C12 = setDispoC12(c12);
	}

	// vertexes with states
	auto getC8sigma3() const {
		return getDispoC8sigma(C8s3);
	}
	void setC8sigma3(std::array<id, 8> c8, std::array<id, 8> sigma3) {
		C8s3 = setDispoC8sigma(c8, sigma3);
	}

	void out() {
		std::cout << "C12 = " << C12 << std::endl;
		std::cout << "12-Sigma2 = " << S2 << std::endl;
		std::cout << "C8-8Sigma3 = " << C8s3 << std::endl;
		std::cout << std::endl;
	}
};


template<class T=unsigned char>
class Kube {
	KubeState<T> state;

public:
	Kube() : state() {}

	void command(DIR dir) {}

	void out() {
		state.out();

		auto c12 = state.getC12();
		auto s2 = state.get12Sigma2();
		doOut("C12", c12);
		doOut("12S2", s2);

		std::array<T, 8> c8;
		std::array<T, 8> s3;
		std::tie(s3, c8) = state.getC8sigma3();
		doOut("C8", c8);
		doOut("8S3", s3);

		std::cout << std::endl;
	}
};

template<typename T>
void testMid(const std::array<T, 12> dispo) {

	auto res = KubeState<T>::setDispoC12(dispo);
	auto dispo1 = KubeState<T>::getDispoC12(res);

	if (dispo != dispo1) {
		std::cout << "FAILED MIDS" << std::endl;
		doOut("dispo", dispo);
		doOut("dispo1", dispo1);
	}
}

template<typename T = unsigned char>
void testMids() {
	testMid<T>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
	testMid<T>({ 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 });
	testMid<T>({ 0, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 11 });
	testMid<T>({ 1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10 });
}

template<typename T>
void testVertex(const std::array<T, 8> dispo, const std::array<T, 8> state) {
	auto res = KubeState<T>::setDispoC8sigma(dispo, state);
	std::array<T, 8> dispo1;
	std::array<T, 8> state1;
	std::tie(dispo1, state1) = KubeState<T>::getDispoC8sigma(res);

	if (dispo != dispo1 || state != state1) {
		std::cout << "FAILED VERTICES" << std::endl;
		doOut("dispo", dispo);
		doOut("dispo1", dispo1);
		doOut("state", state);
		doOut("state1", state1);
	}
}

template<typename T = unsigned char>
void testVertices() {
	testVertex<T>({ 7, 6, 5, 4, 3, 2, 1, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1 });
	testVertex<T>({ 0, 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1 });
	testVertex<T>({ 0, 2, 4, 6, 1, 3, 5, 7 }, { 1, 0, 1, 0, 1, 0, 1, 0 });
	testVertex<T>({ 1, 3, 5, 7, 0, 2, 4, 6 }, { 0, 1, 0, 1, 0, 1, 0, 1 });
}

int main()
{
	//Kube<> cube;
	//std::cout << std::endl << "U:" << std::endl;
	//cube.command(DIR::U);
	//cube.out();

	testVertices();
	testMids();

	char x;
	std::cin >> x;

	return 0;
}

