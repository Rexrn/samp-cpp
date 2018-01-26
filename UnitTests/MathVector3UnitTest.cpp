#include "stdafx.h"			// PCH
#include "CppUnitTest.h"	// Unit test library.
// Unit test namespace:
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// AdvancedGDK:
#include <AdvancedGDK/AdvancedGDK.hpp>

// Unit test:
namespace UnitTests
{
	TEST_CLASS(MathVector3UnitTest)
	{
	public:

		TEST_METHOD(LengthTest)
		{
			agdk::Vector3 simpleVector{ 3, 4, 0 };

			// Check if std::sqrt(3*3 + 4*4) = 5
			Assert::AreEqual(simpleVector.length(), 5.f);
		}

		TEST_METHOD(CxprTest)
		{
			constexpr agdk::Vector3 cxprVector{3, 4, 0};

			// Check if 3*3 + 4*4 = 25
			// Remember: std::sqrt is not (possibly yet) constexpr function, so isn't the Vector3::length method.
			static_assert(cxprVector.lengthSquared() == 25.f, "3*3 + 4*4 is not equal 25! Math is broken :(");
		}
	};
}