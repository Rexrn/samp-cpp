#include "SAMP-EDGEngine-UnitTestsPCH.hpp"	// PCH

// Unit test namespace:
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Unit test:
namespace UnitTests
{		
	TEST_CLASS(MathLengthUnitTest)
	{
	public:
		
		TEST_METHOD(LightYearsValueTest)
		{
			namespace math = agdk::math;

			math::LightYears const fiveLightYears = 5;
			// Compute how many metres 5ly is:
			math::Meters const metresValue = fiveLightYears;

			Assert::AreEqual( metresValue.value, 5 * 9460730472580800.0 );
		}

	};
}