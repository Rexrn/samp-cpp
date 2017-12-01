#include "stdafx.h"				// The precompiled header.
#include <Misc/Random.hpp>		// The `Random` header.

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
			static std::mt19937 mtEngine{ std::chrono::system_clock::now().time_since_epoch().count() };
			return mtEngine;
		}
		else
		{
			static std::mt19937 mtEngine{ std::random_device{}() };
			return mtEngine;
		}
	}
}