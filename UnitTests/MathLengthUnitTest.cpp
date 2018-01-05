#include "stdafx.h"			// PCH
#include "CppUnitTest.h"	// Unit test library.
// Unit test namespace:
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// AdvancedGDK:
#include <AdvancedGDK/AdvancedGDK.hpp>

// Standard includes:


// Unit test:
namespace UnitTests
{		
	TEST_CLASS(MathLengthUnitTest)
	{
	public:
		
		TEST_METHOD(LightYearsValueTest)
		{
			agdk::Lightyears fiveLightYears = 5;

			// Compute how many metres 5ly is:
			agdk::Meters metresValue = fiveLightYears;

			Assert::AreEqual( metresValue.value, 5 * 9460730472580800.0 );
		}

	};
}