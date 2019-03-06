#include <stdlib.h>
#include "Source.h"
#include <time.h>

extern "C" {
	__declspec(dllexport) int return42() {
		return 42;
	}

	__declspec(dllexport) double* create_model(int nb_input) {
		double* tab = (double*) malloc(nb_input * sizeof(double));

		for (int i = 0; i < 10; i++)
		{
			double scale = rand() % 2;
			if (scale == 0)
				tab[i] = -1;
			else
				tab[i] = 1;
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

	__declspec(dllexport) void train_linear_classif(double* model,
												      int size_model,
													  double* inputs,
													  int size_inputs,
													  double* expected_outputs,
													  int expected_outputs_size,
													  double learning_rate,
												      int nb_epochs)
	{
		for (int i = 0; i < nb_epochs; i++)
		{
			for (int j = 0; i < size_inputs; j = j + 2)
			{
				int k =(int) inputs[j];
				double* input = &inputs[j + 1];
				int gxK = sign_inference_linear_classif(model, size_model, input);
				double yK = expected_outputs[k];
				for (int w = 0; w <= size_inputs; w++)
				{
					int temp;
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