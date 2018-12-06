#pragma once

#include <SAMP-EDGEngine/Core/Clock.hpp>

namespace samp_edgengine
{

/// <summary>
/// Interface for every object that need to be updated every frame.
/// </summary>
struct IUpdatable
{
	using ClockType = std::chrono::high_resolution_clock;
	using TimePointType = ClockType::time_point;
	using DurationType = TimePointType::duration;

	/// <summary>
	/// Updates object every frame.
	/// </summary>
	/// <param name="deltaTime_">Number of seconds passed since last update.</param>
	/// <param name="timeMoment_">The point of time in which update happened.</param>
	virtual void update(double const deltaTime_, TimePointType const & timeMoment_) = 0;
};


}

