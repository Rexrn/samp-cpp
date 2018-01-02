#include "stdafx.h"				// PCH.

// Custom includes:
#include <Misc/Random.hpp>		// The `Random` header.

// Standard includes:
#include <chrono>				// for std::chrono::system_clock

namespace agdk
{
	constexpr bool cxprNoRandomDevice = false;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::mt19937 &Random::getEngine()
	{
		// Note: older platforms can crash on std::random_device. If it crashes set `cxprNoRandomDevice` to true.
		if constexpr (cxprNoRandomDevice)
		{
			// We need to convert system_clock::time_point::duration to int32_t seconds.
			// Simple static_cast could give incorrect values (losing precision), so we use duration_cast to int32_t seconds.
			// std::mt19937 engine constructor requires std::uint32_t seed, so best we can do is just taking an absolute value.
			// Steps of generating seed:
			//   1. Take time since epoch (system_clock::time_point::duration | most likely duration<std::int64_t, std::nano>);
			//   2. Cast it to duration<std::int32_t>;
			//   3. Get count of seconds (allow negative values) - std::int32_t;
			//   4. Get absolute seconds value;
			//   5. Cast it to std::uint32_t.
			// This method is used to prevent crashing when somebody set system time to pre-epoch (needs verification).

			using int32seconds = std::chrono::duration<std::int32_t>;
			static std::mt19937 mtEngine{
				static_cast<std::uint32_t>( std::abs( std::chrono::duration_cast<int32seconds>(std::chrono::system_clock::now().time_since_epoch()).count() ) )
			};
			return mtEngine;
		}
		else
		{
			static std::mt19937 mtEngine{ std::random_device{}() };
			return mtEngine;
		}
	}
}