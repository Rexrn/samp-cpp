#include "UnitTestsPCH.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Unit test:
namespace UnitTests
{
	TEST_CLASS(MathVector3UnitTest)
	{
	public:

		TEST_METHOD(lengthTest)
		{
			namespace math = agdk::math;
			math::Vector3f simpleVector{ 3, 4, 0 };

			// Check if std::sqrt(3*3 + 4*4) = 5
			Assert::AreEqual(simpleVector.length(), 5.f);
		}
	};
}