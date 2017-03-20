#pragma once

#include <string>
#include <vector>

#include "Utils.h"


namespace rubik {
	namespace constants {
		enum CORNERS : unsigned char {
			CORNER_DFL = 0,
			CORNER_DFR = 1,
			CORNER_DBR = 2,
			CORNER_DBL = 3,
			CORNER_UFL = 4,
			CORNER_UFR = 5,
			CORNER_UBR = 6,
			CORNER_UBL = 7
		};

		const std::array<unsigned char, 4> corners_permF = { CORNER_DFL, CORNER_UFL, CORNER_UFR, CORNER_DFR };
		const std::array<unsigned char, 4> corners_permB = { CORNER_UBR, CORNER_UBL, CORNER_DBL, CORNER_DBR };
		const std::array<unsigned char, 4> corners_permU = { CORNER_UFR, CORNER_UFL, CORNER_UBL, CORNER_UBR };
		const std::array<unsigned char, 4> corners_permD = { CORNER_DFL, CORNER_DFR, CORNER_DBR, CORNER_DBL };
		const std::array<unsigned char, 4> corners_permR = { CORNER_DFR, CORNER_UFR, CORNER_UBR, CORNER_DBR };
		const std::array<unsigned char, 4> corners_permL = { CORNER_UFL, CORNER_DFL, CORNER_DBL, CORNER_UBL };

		const std::array<const std::array<unsigned char, 4>, 6> corners_permutations = {
			corners_permF,
			corners_permB,
			corners_permU,
			corners_permD,
			corners_permR,
			corners_permL
		};

		enum EDGES : unsigned char {
			EDGE_SW = 0,
			EDGE_SF = 1,
			EDGE_SE = 2,
			EDGE_SB = 3,
			EDGE_MFW = 4,
			EDGE_MFE = 5,
			EDGE_MBW = 6,
			EDGE_MBE = 7,
			EDGE_NL = 8,
			EDGE_NF = 9,
			EDGE_NE = 10,
			EDGE_NB = 11
		};

		const std::array<unsigned char, 4> edges_permF = { EDGE_MFE, EDGE_NF,  EDGE_MFW, EDGE_SF };
		const std::array<unsigned char, 4> edges_permB = { EDGE_SB,  EDGE_MBE, EDGE_NB,  EDGE_MBW };
		const std::array<unsigned char, 4> edges_permU = { EDGE_NF,  EDGE_NL,  EDGE_NB,  EDGE_NE };
		const std::array<unsigned char, 4> edges_permD = { EDGE_SW , EDGE_SF,  EDGE_SE,  EDGE_SB };
		const std::array<unsigned char, 4> edges_permR = { EDGE_MFE, EDGE_NE,  EDGE_MBW, EDGE_SE };
		const std::array<unsigned char, 4> edges_permL = { EDGE_MFW, EDGE_SW,  EDGE_MBE, EDGE_NL };
		const std::array<const std::array<unsigned char, 4>, 6> edges_permutations = {
			edges_permF,
			edges_permB,
			edges_permU,
			edges_permD,
			edges_permR,
			edges_permL
		};
	};


	// COMMANDS

	enum KubeMove : unsigned char {
		F = 0, Fi = 1,
		B = 2, Bi = 3,
		U = 4, Ui = 5,
		D = 6, Di = 7,
		R = 8, Ri = 9,
		L = 10, Li = 11,

		INVALID = 255 // will cause crashes, and this is intended (-fno-exceptions)
	};

	const std::vector<std::string> KubeMoveNames = { "F", "Fi", "B", "Bi", "U", "Ui", "D", "Di", "R", "Ri", "L", "Li" };

	std::string toString(KubeMove move) {
		return KubeMoveNames[static_cast<size_t>(move)];
	}

	KubeMove atoMove(const std::string name) {

		for (size_t i = 0; i < KubeMoveNames.size(); ++i)
			if (name == KubeMoveNames[i])
				return static_cast<KubeMove>(i);

		return KubeMove::INVALID;
	}

	std::string toString(const std::vector<KubeMove> moves) {

		std::string str = "";

		for (auto it = moves.begin(); it != moves.end(); ++it) {
			if (it != moves.begin())
				str += "-";
			str += toString(*it);
		}

		return str;
	}

	std::vector<KubeMove> atoMoves(std::vector<std::string> x) {
		std::vector<KubeMove> ret(x.size());

		for (size_t i = 0; i < x.size(); i++)
			ret[i] = atoMove(x[i]);

		return ret;
	}

	std::vector<KubeMove> atoMoves(const std::string x) {
		std::vector<std::string> tr = string_split(x, ',');
		return atoMoves(tr);
	}



	// PERMUTATIONS and RUBIK functions

	template<const size_t n, const size_t k, typename T, typename K>
	inline static void permutate(std::array<T, n>& data, const std::array<K, k> perm, bool inverse = false) {
		if (inverse) {
			const T temp = data[perm[0]];

			for (size_t i = 0; i<k - 1; i++)
				data[perm[i]] = data[perm[i + 1]];

			data[perm[k - 1]] = temp;
		}
		else {
			const T temp = data[perm[k - 1]];

			for (size_t i = k - 1; i>0; i--)
				data[perm[i]] = data[perm[i - 1]];

			data[perm[0]] = temp;
		}
	}

	// a rotation keep a state constant, and swaps the other two. states are { 0, 1, 2 } = { U/D, F/B, R/L }
	int rotate_corner(int x, int y) {
		if (x == y) return x;

		if (x == 0) return y == 1 ? 2 : 1;
		if (x == 1) return y == 0 ? 2 : 0;
		/*if (x == 2)*/ return y == 1 ? 0 : 1;
	}

	// for a given move, get the state that is left unchanged
	int move_const_rot_axis(const int value) {	// const int value =  static_cast<unsigned int>(dir);
		if (value < 4) return 1;		// F, B
		else if (value < 8) return 0;	// U, D
		else return 2;					// R, L
	}


	// unused stuff. for now...

	enum class Color : unsigned char { // Y, R, G, O, B, W
		Yellow='Y',
		Red='R', Green = 'G', Orange = 'O', Blue = 'B',
		White = 'W'
	};

	enum FACE : unsigned char { // U, F, R, B, L, D
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

	typedef std::array<Color, 3> CubeCorner;
	typedef std::array<Color, 2> CubeEdge;

	const std::array<const CubeCorner, 8> angles({
		CubeCorner({ Color::Red, Color::Yellow, Color::Blue }),
		CubeCorner({ Color::Green, Color::Yellow, Color::Red }),
		CubeCorner({ Color::Orange, Color::Yellow, Color::Green }),
		CubeCorner({ Color::Blue, Color::Yellow, Color::Orange }),

		CubeCorner({ Color::Red, Color::Blue, Color::White }),
		CubeCorner({ Color::Green, Color::Red, Color::White }),
		CubeCorner({ Color::Orange, Color::Green, Color::White }),
		CubeCorner({ Color::Blue, Color::Orange, Color::White })
	});

	const std::array<const CubeEdge, 12> mids({
		CubeEdge({ Color::Red, Color::Yellow }),
		CubeEdge({ Color::Green, Color::Yellow }),
		CubeEdge({ Color::Orange, Color::Yellow }),
		CubeEdge({ Color::Blue, Color::Yellow }),

		CubeEdge({ Color::Red, Color::White }),
		CubeEdge({ Color::Green, Color::White }),
		CubeEdge({ Color::Orange, Color::White }),
		CubeEdge({ Color::Blue, Color::White }),

		CubeEdge({ Color::Green, Color::Red }),
		CubeEdge({ Color::Orange, Color::Green }),
		CubeEdge({ Color::Blue, Color::Orange }),
		CubeEdge({ Color::Red, Color::Blue })
	});
};
