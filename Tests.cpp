//
//template<typename T>
//void testMid(const std::array<T, 12> dispo) {
//
//	auto res = KubeState<T>::setDispoC12(dispo);
//	auto dispo1 = KubeState<T>::getDispoC12(res);
//
//	if (dispo != dispo1) {
//		std::cout << "FAILED MIDS" << std::endl;
//		doOut("dispo", dispo);
//		doOut("dispo1", dispo1);
//	}
//}
//
//template<typename T = unsigned char>
//void testMids() {
//	testMid<T>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
//	testMid<T>({ 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 });
//	testMid<T>({ 0, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 11 });
//	testMid<T>({ 1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10 });
//}
//
//template<typename T>
//void testVertex(const std::array<T, 8> dispo, const std::array<T, 8> state) {
//	auto res = KubeState<T>::setDispoC8sigma(dispo, state);
//	std::array<T, 8> dispo1;
//	std::array<T, 8> state1;
//	std::tie(dispo1, state1) = KubeState<T>::getDispoC8sigma(res);
//
//	if (dispo != dispo1 || state != state1) {
//		std::cout << "FAILED VERTICES" << std::endl;
//		doOut("dispo", dispo);
//		doOut("dispo1", dispo1);
//		doOut("state", state);
//		doOut("state1", state1);
//	}
//}
//
//template<typename T = unsigned char>
//void testVertices() {
//	testVertex<T>({ 7, 6, 5, 4, 3, 2, 1, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1 });
//	testVertex<T>({ 0, 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1 });
//	testVertex<T>({ 0, 2, 4, 6, 1, 3, 5, 7 }, { 1, 0, 1, 0, 1, 0, 1, 0 });
//	testVertex<T>({ 1, 3, 5, 7, 0, 2, 4, 6 }, { 0, 1, 0, 1, 0, 1, 0, 1 });
//}