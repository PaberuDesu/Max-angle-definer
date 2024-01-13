#include "pch.h"
#include <CppUnitTest.h>
#include "../src/Max angle definer/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests) {
	public:
		TEST_METHOD(IsNotCollinear) {
			Quadrangle quad;
			quad.create_point(0, 0);
			quad.create_point(1, 1);
			quad.create_point(1, 0);
			quad.create_point(2, 2);
			Quadrangle quad1;
			quad1.create_point(0, 0);
			quad1.create_point(1, 1);
			quad1.create_point(1, 0);
			quad1.create_point(0, 1);
			Assert::IsFalse(quad.not_collinear());
			Assert::IsTrue(quad1.not_collinear());
		}

		TEST_METHOD(IsNotConvex) {
			Quadrangle quad;
			quad.create_point(0, 0);
			quad.create_point(10, 1);
			quad.create_point(1, 10);
			quad.create_point(2, 3);
			Quadrangle quad1;
			quad1.create_point(0, 0);
			quad1.create_point(10, 1);
			quad1.create_point(1, 10);
			quad1.create_point(5, 20);
			Assert::AreEqual(quad.define_max_angle(), 0.0f);
			Assert::AreNotEqual(quad1.define_max_angle(), 0.0f);
		}

		TEST_METHOD(GetCorrectAngle) {
			Quadrangle quad;
			quad.create_point(0, 1);
			quad.create_point(1, 0);
			quad.create_point(1, 2);
			quad.create_point(2, 1);
			Quadrangle quad1;
			quad1.create_point(0, 0);
			quad1.create_point(5, 1);
			quad1.create_point(0, 1);
			quad1.create_point(4, 0);
			Assert::AreEqual(quad.define_max_angle(), 90.0f);
			Assert::AreEqual(quad1.define_max_angle(), 135.0f);
		}
	};
}
