#pragma once

#include <array>

#include "Utils.h"		// doOut
#include "MetaMath.h"	// make_index_array

namespace rubik {
	namespace state {

		template<typename id>
		class SimpleKubeState3 {
			std::array<id, 12> C12;
			std::array<id, 12> S2;

		public:
			SimpleKubeState3() : C12(make_index_array<id, 12>()), S2() {}

			auto getState() const {
				return S2;
			}
			void setState(const std::array<id, 12> x) {
				S2 = x;
			}

			auto getDisposition() const {
				return C12;
			}
			void setDisposition(const std::array<id, 12> c12) {
				C12 = c12;
			}

			void out() const {
				doOut("pE", C12);
				doOut("sE", S2);
			}

			bool isSolved() const {
				return std::is_sorted(C12.begin(), C12.end()) && std::count(S2.begin(), S2.end(), 0) == S2.size();
			}
		};

		//template<const size_t N, typename id>
		//class SimpleEdgeState {
		//	std::array<id, N> C12;
		//	std::array<id, N> S2;

		//public:
		//	SimpleEdgeState() : C12(make_index_array<id, N>()), S2() {}

		//	auto getState() const {
		//		return S2;
		//	}
		//	void setState(const std::array<id, 12> x) {
		//		S2 = x;
		//	}

		//	auto getDisposition() const {
		//		return C12;
		//	}
		//	void setDisposition(const std::array<id, N> c12) {
		//		C12 = c12;
		//	}

		//	void out() const {
		//		doOut("pE", C12);
		//		doOut("sE", S2);
		//	}

		//	bool isSolved() const {
		//		return std::is_sorted(C12.begin(), C12.end()) && std::count(S2.begin(), S2.end(), 0) == N;
		//	}
		//};
	}
}
