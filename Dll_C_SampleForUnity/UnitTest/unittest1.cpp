#include "stdafx.h"
#include <iostream>
#include "CppUnitTest.h"
#include "../Dll_C_SampleForUnity/Source.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(Source_tests)
	{
	public:

		TEST_METHOD(should_return42_when_return42)
		{
			int res = return42();
			Assert::AreEqual(res, 42);
		}

		TEST_METHOD(should_create_tab_of_10_between_minus1_and_plus1)
		{
			double* res = create_model(10);
			for (int i = 0; i < 10; i++)
			{
				Assert::IsTrue(res[i] <= 1 && res[i] >= -1);
			}
		}

		TEST_METHOD(should_return_plus1_when_positif)
		{
			int res = sign(4);
			Assert::AreEqual(res, 1);
		}

		TEST_METHOD(should_return_minus1_when_negatif)
		{
			int res = sign(-5);
			Assert::AreEqual(res, -1);
		}

		TEST_METHOD(should_infer_linear_of_simple_input_give_total) {
			// given
			double model[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			int modelSize = 10;
			double input[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			// when
			int sut = inference_linear_classif(model, modelSize, input);
			// then
			int tot = model[0];
			for (int i = 1; i < 10; i++)
			{
				tot += model[i] + input[i - 1];
			}
			Assert::AreEqual(sut, tot);
		}

		TEST_METHOD(should_infer_linear_classif_of_simple_input_and_be_positif) {
			// given
			double model[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			int modelSize = 10;
			double input[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			// when
			int sut = sign_inference_linear_classif(model, modelSize, input);
			// then
			Assert::AreEqual(sut, 1);
		}

		TEST_METHOD(should_infer_linear_regression_of_simple_input_and_be_negatif) {
			// given
			double model[10] = { 1, 2, -3, -4, -5, -6, -7, -8, -9, -10 };
			int modelSize = 10;
			double input[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			// when
			int sut = inference_linear_regression(model, modelSize, input);
			// then
			int tot = 0;
			for (int i = 1; i < 10; i++)
			{
				tot += model[i] + input[i - 1];
			}
			Assert::AreEqual(sut, tot);
		}
	};
}