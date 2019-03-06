
extern "C" {

	__declspec(dllexport) int return42() {
		return 42;
	}

	/*__declspec(dllexport) double sum(double* tab, int tabSize) {
		auto total = 0.0;

	}*/

	__declspec(dllexport) double* create_array(int tabSize) {
		auto tab = new double[tabSize];

		for (auto i = 0; i < tabSize; i++) {
			tab[i] = i;
		}
		return tab;
	}


	__declspec(dllexport) void delete_array(double* tab) {
		delete[] tab;
	}
}