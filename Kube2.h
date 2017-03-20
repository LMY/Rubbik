#pragma once

/**
* Kube2 implements moves on a KubeState2 (ie, a 2x2x2 cube, or the corners of a NxNxN cube)
**/

#include <array>

#include "KubeConstants.h"
#include "Utils.h"

namespace rubik {

	template<template<typename> typename StateCorners, class T = unsigned char>
	class Kube2 {
		StateCorners<T> state;

	public:
		Kube2() : state() {}

		void command(const KubeMove dir) {

			std::array<T, 8> c8;
			std::array<T, 8> s3;
			std::tie(c8, s3) = state.getDispositionState();

			const unsigned int move_int = static_cast<unsigned int>(dir);
			const bool move_is_inverse = move_int % 2 != 0;
			const auto permutation = constants::corners_permutations[move_int / 2];
			const int const_rot_axis = move_const_rot_axis(move_int);

			// calculate new states of corners
			for (const auto p : permutation)
				s3[c8[p]] = rotate_corner(s3[c8[p]], const_rot_axis);

			// permutation of corners
			permutate(c8, permutation, move_is_inverse);

			state.setDispositionState(c8, s3);
		}

		void out() const {
			//state.out();

			std::array<T, 8> c8;
			std::array<T, 8> s3;
			std::tie(c8, s3) = state.getDispositionState();
			doOut("pC", c8);
			doOut("sC", s3);
		}

		bool isSolved() const {
			return state.isSolved();
		}
	};
}
