#pragma once
extern "C" {
	__declspec(dllexport) int return42();
	__declspec(dllexport) double* create_model(int nb_input);
	__declspec(dllexport) int sign(double nb);
	__declspec(dllexport) double inference_linear_classif(double* model, int modelSize, double* input);
	__declspec(dllexport) int sign_inference_linear_classif(double* model, int modelSize, double* input);
	__declspec(dllexport) double inference_linear_regression(double* model, int modelSize, double* input);
}