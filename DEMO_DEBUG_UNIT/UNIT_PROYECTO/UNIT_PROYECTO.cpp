#include "pch.h"
#include "CppUnitTest.h"
#include <stdlib.h>
#include <stdio.h>
#include "../DEMO_DEBUG/numeros.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IRIUnitTest
{
	TEST_CLASS(IRIUnitTest)
	{
	public:
		TEST_METHOD(TestPitagoras)
		{
			Assert::AreEqual((float)4.24, pitagoras_iri(3.0, 3.0));
			//Assert::AreEqual((float)6.687, pitagoras_iri(3.0, 3.0)); // FALLA
		}
		TEST_METHOD(TestArea)
		{
			Assert::AreEqual((float)12.57, area_circulo(2));
			//Assert::AreEqual((float)92.31, area_circulo(2)); // FALLA
		}
		TEST_METHOD(TestPerimetro)
		{
			Assert::AreEqual((float)12.57, perimetro_circulo(2));
			//Assert::AreEqual((float)25.13, perimetro_circulo(2)); // FALLA
		}
		TEST_METHOD(TestVolumen)
		{
			Assert::AreEqual((float)25.13, volumen_esfera(2));
			//Assert::AreEqual((float)17.15, volumen_esfera(2)); // FALLA
		}
	};
}