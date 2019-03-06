#include <stdlib.h>
#include "Source.h"
#include <time.h>

extern "C" {
	__declspec(dllexport) int return42() {
		return 121;
	}

	__declspec(dllexport) double* create_model(int nb_input) {
		double* tab = (double*) malloc((nb_input + 1) * sizeof(double));

		for (int i = 0; i < nb_input; i++)
		{
			double scale = (rand() / (double) RAND_MAX) * 2 - 1;
			tab[i] = scale;
		}
		return tab;
	}


	__declspec(dllexport) int sign(double nb)
	{
		if (nb < 0)
			return -1;
		return 1;
	}

	__declspec(dllexport) double inference_linear_classif(double* model, int modelSize, double* input, int inputSize)
	{
		double total = model[0];
		for (int i = 1; i <= inputSize; i++)
		{
			total += model[i] + input[i - 1];
		}
		return total;
	}

	__declspec(dllexport) int sign_inference_linear_classif(double* model, int modelSize, double* input, int inputSize)
	{
		return sign(inference_linear_classif(model, modelSize, input, inputSize));
	}

	__declspec(dllexport) double inference_linear_regression(double* model, int modelSize, double* input)
	{
		double total = 0;
		for (int i = 1; i <= modelSize; i++)
		{
			total += model[i] + input[i - 1];
		}
		return total;
	}

	__declspec(dllexport) void train_linear_classif(double* model,
												      int size_model,
													  double* inputs,
													  int size_inputs,
													  int dimension_size,
													  double* expected_outputs,
													  int expected_outputs_size,
													  double learning_rate,
												      int nb_epochs)
	{
		for (int i = 0; i < nb_epochs; i++)
		{
			for (int j = 0; i < size_inputs; j = j + dimension_size)
			{
				int k = j / dimension_size;
				double* input = &inputs[j];
				int gxK = sign_inference_linear_classif(model, size_model, input, dimension_size);
				double yK = expected_outputs[k];
				for (int w = 0; w <= dimension_size; w++)
				{
					double temp;
					if (w == 0)
						temp = 1;
					else
						temp = input[w - 1];
					model[w] += learning_rate * (yK - gxK) * temp;
				}
			}
		}
	}
}  