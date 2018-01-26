// File description:
// Implements easy to use random engine using Mersenne's Twister.
#pragma once

// Precompiled header:
#include "../../../stdafx.h"

namespace agdk
{
	/// <summary>
	/// Static class used to generate random numbers.
	/// </summary>
	class Random
	{
	public:

		/// <summary>
		/// Generates random number of type T.
		/// </summary>
		/// <param name="from_">Minimal value.</param>
		/// <param name="to_">Maximal value.</param>
		/// <returns>Random number in specified range.</returns>
		/// <remarks>
		/// <para>
		/// Supported types:
		///		- integers: short,		unsigned short,
		///					int,		unsigned int,
		///					long,		unsigned long,
		///					long long,	unsigned long long
		///		- floats:	float,
		///					double,
		///					long double
		/// </para>
		/// </remarks>
		template <typename T>
		static T next(T from_, T to_)
		{
			// Acquire raw type (without const/volatile).
			using RawType = std::remove_cv_t<T>;
            
			// Check at compile time if the type is an integer.
            constexpr bool cxprIsIntegerType = 	std::is_same_v<RawType, short>		|| std::is_same_v<RawType, unsigned short>
											||	std::is_same_v<RawType, int>		|| std::is_same_v<RawType, unsigned int>
											||	std::is_same_v<RawType, long>		|| std::is_same_v<RawType, unsigned long>
											||	std::is_same_v<RawType, long long>	|| std::is_same_v<RawType, unsigned long long>;

            // Check at compile time if the type is a floating point number.
            constexpr bool cxprIsFloatType = std::is_same_v<RawType, float> || std::is_same_v<RawType, double> || std::is_same_v< RawType, long double>;
            
			// Check if the type require 64 bit engine or not.
			constexpr bool cxprCanUse32BitEngine = sizeof(RawType) <= 4;

			// Assert compilation, when type is not supported.
            static_assert(cxprIsIntegerType || cxprIsFloatType, "Random does not support this type.");
            
			// Calculate min and max value:
			auto[minValue, maxValue] = std::minmax(static_cast<RawType>(from_), static_cast<RawType>(to_));


			// For every integer type:
			if constexpr(cxprIsIntegerType)
			{
				if constexpr(cxprCanUse32BitEngine)
					return std::uniform_int_distribution<RawType>(minValue, maxValue)(Random::getEngine());
				else
					return std::uniform_int_distribution<RawType>(minValue, maxValue)(Random::getEngine64());
			}
			else // For every real (floating point) type:
			{
				if constexpr(cxprCanUse32BitEngine)
					return std::uniform_real_distribution<RawType>(minValue, maxValue)(Random::getEngine());
				else
					return std::uniform_real_distribution<RawType>(minValue, maxValue)(Random::getEngine64());
			}
		}
	private:		
		/// <summary>
		/// Prevents instance of the <see cref="Random"/> class from being created.
		/// </summary>
		Random() = delete;
		
		/// <summary>
		/// Returns mersenne twister random engine.
		/// </summary>
		/// <returns>Mersenne twister random engine.</returns>
		static std::mt19937&	getEngine();

		/// <summary>
		/// Returns mersenne twister random engine (64 bit).
		/// </summary>
		/// <returns>Mersenne twister random engine (64 bit).</returns>
		static std::mt19937_64&	getEngine64();
	};
}
