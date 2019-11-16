#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/Core/Clock.hpp>

namespace samp_cpp
{

/// <summary>
/// Interface for every object that need to be updated every frame.
/// </summary>
struct IUpdatable
{
	using Clock		= std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration	= TimePoint::duration;

	/// <summary>
	/// Updates object every frame.
	/// </summary>
	/// <param name="deltaTime_">Number of seconds passed since last update.</param>
	/// <param name="timeMoment_">The point of time in which update happened.</param>
	virtual void update(double deltaTime_, TimePoint timeMoment_) = 0;
};


}

