#include <stdlib.h>
#include "Source.h"
#include <time.h>

extern "C" {
	__declspec(dllexport) int return42() {
		return 42;
	}

	__declspec(dllexport) double* create_model(int nb_input) {
		double* tab = (double*) malloc(nb_input * sizeof(double));
		srand(time(NULL));

		for (int i = 0; i < 10; i++)
		{
			tab[i] = (rand() % 2) - 1;
		}
		return tab;
	}

	__declspec(dllexport) int sign(double nb)
	{
		if (nb < 0)
			return -1;
		return 1;
	}

	__declspec(dllexport) double inference_linear_classif(double* model, int modelSize, double* input)
	{
		double total = model[0];
		for (int i = 1; i < modelSize; i++)
		{
			total += model[i] + input[i - 1];
		}
		return total;
	}

	__declspec(dllexport) int sign_inference_linear_classif(double* model, int modelSize, double* input)
	{
		return sign(inference_linear_classif(model, modelSize, input));
	}

	__declspec(dllexport) double inference_linear_regression(double* model, int modelSize, double* input)
	{
		double total = 0;
		for (int i = 1; i < modelSize; i++)
		{
			total += model[i] + input[i - 1];
		}
		return total;
	}
}  