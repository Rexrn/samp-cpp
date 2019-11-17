// File description:
// Implements time measuring class and adds useful aliases to agdk namespace.
#pragma once
#include SAMPCPP_PCH




namespace samp_cpp
{
namespace chrono		= std::chrono;
using seconds_f			= chrono::duration<float>;
using seconds_d			= chrono::duration<double>;
using milliseconds_f	= chrono::duration<float,	std::milli>;
using milliseconds_d	= chrono::duration<double,	std::milli>;
using microseconds_f	= chrono::duration<float,	std::micro>;
using microseconds_d	= chrono::duration<double,	std::micro>;
using nanoseconds_f		= chrono::duration<float,	std::nano>;
using nanoseconds_d		= chrono::duration<double,	std::nano>;

/// <summary>
/// Class that is used to measure time durations.
/// </summary>
/// <remarks>
/// <para>Duration is expressed in units returned by std::chrono::steady_clock::now().time_since_epoch().</para>
/// </remarks>
class Clock
{
public:
	// Time point unit of this clock
	using TimePoint = chrono::steady_clock::time_point;
	// Duration unit of this clock.
	using Duration = TimePoint::duration;
	

	/// <summary>
	/// Initializes a new instance of the <see cref="Clock"/> class.
	/// </summary>
	Clock();
	
	/// <summary>
	/// Restarts clock. 
	/// </summary>
	/// <returns>Time elapsed since clock was created or restarted.</returns>
	Duration restart();
	
	/// <summary>
	/// Returns elapsed time.
	/// </summary>
	/// <returns>Time elapsed since object was created or clock was restarted.</returns>
	Duration getElapsedTime() const;

	/// <summary>
	/// Returns current point in time.
	/// </summary>
	/// <returns>Current time point.</returns>
	static TimePoint now();

	/// <summary>
	/// Returns time passed since the epoch started.
	/// Epoch started at 1st January 1970.
	/// </summary>
	/// <returns>Time passed since the epoch started.</returns>
	static Duration sinceEpoch();
protected:
	TimePoint m_startPoint; /// Holds starting time to count from.
};
}