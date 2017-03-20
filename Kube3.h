#pragma once

/**
* Kube3 implements moves on a KubeState3 + KubeState2 (ie, a 3x3x3 cube)
**/

#include <array>

#include "Kube2.h"

namespace rubik {

	template<template<typename> typename StateEdges, template<typename> typename StateCorners, class T = unsigned char>
	class Kube3 {
		Kube2<StateCorners, T> state_corners;
		StateEdges<T> state_edges;

	public:
		Kube3() : state_corners(), state_edges() {}

		void command(const KubeMove dir) {

			// rotate corners
			state_corners.command(dir);

			const unsigned int move_int = static_cast<unsigned int>(dir);
			const bool move_is_inverse = move_int % 2 != 0;
			const auto permutation = constants::edges_permutations[move_int / 2];

			// permutation of edges
			auto c12 = state_edges.getDisposition();
			permutate(c12, permutation, move_is_inverse);
			state_edges.setDisposition(c12);

			// moves { F, Fi, B, Bi } toggle the state of affected edges
			if (dir == KubeMove::F || dir == KubeMove::Fi || dir == KubeMove::B || dir == KubeMove::Bi) {
				auto s2 = state_edges.getState();

				for (const auto p : permutation)
					s2[c12[p]] ^= 1;

				state_edges.setState(s2);
			}
		}

		void out() const {
			state_corners.out();

			//state_edges.out();

			const auto c12 = state_edges.getDisposition();
			const auto s2 = state_edges.getState();
			doOut("pE", c12);
			doOut("sE", s2);
		}

		bool isSolved() const {
			return state_corners.isSolved() && state_edges.isSolved();
		}
	};
}
