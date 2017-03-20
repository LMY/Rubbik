
#include "Kube3.h"

#include <iostream> // for debug
#include <string>	// for debug
#include <vector>


#define USE_SIMPLE_STATE
#undef USE_SIMPLE_STATE


#ifdef  USE_SIMPLE_STATE
	// naive representation
	// 2x2x2 = 16 byte on x86
	// 3x3x3 = 40 byte on x86
	#include "SimpleKubeState2.h"
	#include "SimpleKubeState3.h"

	typedef rubik::Kube2<rubik::state::SimpleKubeState2> Rubik2;
	typedef rubik::Kube3<rubik::state::SimpleKubeState3, rubik::state::SimpleKubeState2> Rubik3;
#else
	// min-bit representation
	// 2x2x2 = 28 bit ( 4 byte on x86)
	// 3x3x3 = 69 bit (12 byte on x86)
	#include "KubeState2.h"
	#include "KubeState3.h"

	typedef rubik::Kube2<rubik::state::KubeState2> Rubik2;
	typedef rubik::Kube3<rubik::state::KubeState3, rubik::state::KubeState2> Rubik3;
#endif



template<typename Cube = Rubik3>
auto orbit(const std::vector<rubik::KubeMove> moves) {

	Cube cube;

	int i = 0;

	do {
		++i;
		for (const auto x : moves)
			cube.command(x);
	} while (!cube.isSolved());

	return i;
}

auto out_orbit(const std::vector<rubik::KubeMove> moves) {
	std::cout << "Orbit " << toString(moves) << " is: ";
	const auto ret = orbit(moves);
	std::cout << ret << std::endl;
	return ret;
}

template<typename Cube = Rubik3>
void out_result(rubik::KubeMove move, bool outinit = false) {
	Cube cube;
	if (outinit) cube.out();
	std::cout << toString(move) << std::endl;
	cube.command(move);
	cube.out();
	std::cout << std::endl;
}

template<typename Cube = Rubik3>
void out_result(const std::vector<rubik::KubeMove> moves, bool outinit = false) {
	Cube cube;
	if (outinit) cube.out();
	std::cout << toString(moves) << std::endl;
	for (const auto x : moves)
		cube.command(x);
	cube.out();
	std::cout << std::endl;
}

template<typename Cube = Rubik3>
void trace_result(const std::vector<rubik::KubeMove> moves, bool outinit = true) {
	std::cout << toString(moves) << std::endl;
	Cube cube;
	if (outinit) cube.out();
	for (const auto x : moves) {
		std::cout << toString(x) << std::endl;
		cube.command(x);
		cube.out();
	}
	std::cout << std::endl;
}

template<typename Cube = Rubik3>
void play(Cube cube = Cube()) {

	do {
		cube.out();

		std::string input;
		std::cin >> input;
		if (input[0] == 'q') break;
		const auto move = rubik::atoMove(input);
		
		if (move == rubik::KubeMove::INVALID)
			std::cout << "Invalid move" << std::endl;
		else
			cube.command(move);

		if (cube.isSolved())
			std::cout << "Solved" << std::endl;

	} while (true);

}

#include <random>

template<typename Cube = Rubik3>
auto scramble(size_t n = 24, Cube cube = Cube()) {

	std::mt19937 rng;
	rng.seed(std::random_device()());
	const std::uniform_int_distribution<std::mt19937::result_type> dist(0, 11);

	for (size_t i = 0; i < n; i++) {
		const rubik::KubeMove x = static_cast<rubik::KubeMove>(dist(rng));
		cube.command(x);
	}

	return cube;
}


int main()
{
	//std::cout << "sizeof(Rubik2) = " << sizeof(Rubik2) << std::endl;
	//std::cout << "sizeof(Rubik3) = " << sizeof(Rubik3) << std::endl;

	//auto orbit6 = rubik::atoMoves("R,U,Ri,Ui");
	//auto rearrange_yellows = rubik::atoMoves("R,U,Ri,U,R,U,U,Ri");
	//auto rearrange_corners = rubik::atoMoves("Ri,F,Ri,B,B,R,Fi,Ri,B,B,R,R");
	//auto pll_rotate_cw = rubik::atoMoves("R,Ui,R,U,R,U,R,Ui,Ri,Ui,R,R");
	//auto pll_rotate_ccw = rubik::atoMoves("R,R,U,R,U,Ri,Ui,Ri,Ui,Ri,U,Ri");

	//out_orbit(pll_rotate_cw);
	//out_orbit(pll_rotate_ccw);
	//out_orbit(rearrange_corners);
	//out_orbit(rearrange_yellows);

	//out_orbit(orbit6);
	//out_orbit({ rubik::KubeMove::Li, rubik::KubeMove::Ui, rubik::KubeMove::L });
	//out_orbit(rubik::atoMoves("R,R,L,L,U,U,D,D,F,F,B,B"));

	play(scramble());


	return 0;
}
