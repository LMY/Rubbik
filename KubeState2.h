#pragma once

/**
* KubeState2 is a 28bit representation of a 2x2x2 cube state, that is the min possible length
* KubeState2 can be used as internal state of the corners of any NxNxN cube.
**/

#include <array>
#include <cassert>
#include <cstdint>
#include <tuple>
#include "Utils.h"

namespace rubik {
	namespace state {

		template<typename id>
		class KubeState2 {
			uint32_t C8s3 : 28;		// vertices: disposition offset state. Separating (dispo,state) costs +1bit. Then, splitting dispo costs another +1bit.


			inline static auto getDispoC8sigma(uint32_t c8s3)
			{
				const auto state = offset::extract<id>(c8s3, offset::C8sigma1);
				const auto relative = offset::relativePositions(offset::extract<id>(c8s3, offset::C8sigma2));

				return std::make_tuple(relative, state);
			}

			inline static uint32_t setDispoC8sigma(const std::array<id, 8> c, const std::array<id, 8> sigma)
			{
				const auto absolute = offset::absolutePositions(c);
				const uint32_t a1 = offset::calculate(absolute, offset::C8sigma2);
				const uint32_t a2 = offset::calculate(sigma, offset::C8sigma1);

				//std::cout << a1 << std::endl << a2 << std::endl;
				//assert((a1 & a2) == 0);

				return a1 + a2;
			}

		public:
			KubeState2() : KubeState2(0) {}
			KubeState2(uint32_t _C8s3) : C8s3(_C8s3) {}
			KubeState2(const KubeState2&) = default;

			auto getDispositionState() const {
				return getDispoC8sigma(C8s3);
			}
			void setDispositionState(const std::array<id, 8> c8, const std::array<id, 8> sigma3) {
				C8s3 = setDispoC8sigma(c8, sigma3);
			}

			void out() const {
				std::cout << "C8-8Sigma3 = " << C8s3 << std::endl;
				std::cout << std::endl;
			}

			bool isSolved() const {
				return C8s3 == 0;
			}
		};
	}
}
