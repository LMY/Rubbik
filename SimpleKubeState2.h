#pragma once

#include <array>
#include "Utils.h"		// doOut
#include "MetaMath.h"	// make_index_array

namespace rubik {
	namespace state {

		template<typename id>
		class SimpleKubeState2 {
			std::array<id, 8> C8;
			std::array<id, 8> S3;

		public:
			SimpleKubeState2() : C8(make_index_array<id, 8>()), S3() {}

			auto getDispositionState() const {
				return std::make_tuple(C8, S3);
			}
			void setDispositionState(const std::array<id, 8> c8, const std::array<id, 8> s3) {
				C8 = c8;
				S3 = s3;
			}

			void out() const {
				doOut("pC", C8);
				doOut("sC", s3);
			}

			bool isSolved() const {
				return std::is_sorted(C8.begin(), C8.end()) && std::count(S3.begin(), S3.end(), 0) == S3.size();
			}
		};
	}
}
