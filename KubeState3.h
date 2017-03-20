#pragma once

/**
* KubeState3 is a 41bit representation of a 3x3x3 cube edges state
* sizeof(KubeState3) + sizeof(KubeState2) = 69bit ie the min possible. (you wish. padding etc...)
* This is a study on possible representations only, in order to apply a move on a state, the state is decoded into larger arrays.
**/

#include <array>
#include <cstdint>
#include "Utils.h"

namespace rubik {
	namespace state {

		template<typename id>
		class KubeState3 {
			uint32_t C12 : 29;		// edges disposition. Splitting C12->5, C5 would still be 29 bits. Any other division costs +1bit.
			uint32_t S2 : 12;		// edges state


			inline static auto getDispoC12(uint32_t c12)
			{
				const auto relative = offset::extract<id>(c12, offset::DISPO12);
				return offset::relativePositions(relative);
			}

			inline static uint32_t setDispoC12(const std::array<id, 12> c)
			{
				const auto absolute = offset::absolutePositions(c);
				return offset::calculate(absolute, offset::DISPO12);
			}

			inline static auto getSigma12(uint32_t s2)
			{
				std::array<id, 12> x;

				for (int i = 0; i < 12; i++)
					x[i] = ((s2&(1 << i)) != 0);

				return x;
			}

			inline static uint32_t setSigma12(const std::array<id, 12> x)
			{
				uint32_t ret = 0;

				for (int i = 0; i < 12; i++)
					ret |= (x[i] << i);

				return ret;
			}


		public:
			KubeState3() : KubeState3(0, 0) {}
			KubeState3(uint32_t _C12, uint32_t _S2) : C12(_C12), S2(_S2) {}
			KubeState3(const KubeState3&) = default;

			auto getState() const {
				return getSigma12(S2);
			}
			void setState(const std::array<id, 12> x) {
				S2 = setSigma12(x);
			}

			auto getDisposition() const {
				return getDispoC12(C12);
			}
			void setDisposition(const std::array<id, 12> c12) {
				C12 = setDispoC12(c12);
			}

			void out() const {
				std::cout << "C12 = " << C12 << std::endl;
				std::cout << "12-Sigma2 = " << S2 << std::endl;
			}

			bool isSolved() const {
				return C12 == 0 && S2 == 0;
			}
		};
	}
}
