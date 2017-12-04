#pragma once

#include <chrono>
#include <type_traits>

namespace agdk
{
#ifdef AGDK_TIME_IMPL /* TODO: Remove this */
	/*
		Class for time manipulation
	*/
	class Time
	{
	public:
		/*
			Default constructor.
			Sets time to 0
		*/
		Time();

		/*
			Default copy constructor.
		*/
		Time(const Time &) = default;

		/*
			Creates time object using microseconds.
		*/
		static Time			fromMicroseconds(const long long microseconds);

		/*
			Returns how many microseconds are stored inside this Time object.
		*/
		long long			microseconds()	const { return m_microseconds; }

		/*
			Returns how many milliseconds are stored inside this Time object.
		*/
		double				milliseconds()	const { return static_cast<double>(m_microseconds) / 1000.0; }
		
		/*
			Returns how many seconds are stored inside this Time object
		*/
		double				seconds()		const { return static_cast<double>(m_microseconds) / 1000000.0; }

		// Defines 0 microseconds
		static const Time	Zero;

		/*
			Adds time from right side.
		*/
		void operator+=(const Time& rhs);
		
		/*
			Removes rhs time from left side.
		*/
		void operator-=(const Time& rhs);
	protected:
		/*
			Time constructor
			Use instead "fromMicroseconds" or agdk::microseconds, agdk::milliseconds, agdk::seconds
		*/
		explicit Time(double microseconds);

		long long	m_microseconds;		// How much microseconds passed
	};

	/*
		Adds Time objects.
	*/
	Time operator+(const Time& Left, const Time& Right);

	/*
		Subtracts 'Right' from 'Left' Time.
	*/
	Time operator-(const Time& Left, const Time& Right);

	/*
		Checks if left side is greater than right side.
	*/
	bool operator>(const Time& Left, const Time& Right);

	/*
		Checks if left side is lower than right side.
	*/
	bool operator<(const Time& Left, const Time& Right);

	/*
		Checks if time objects are equal.
	*/
	bool operator==(const Time& Left, const Time& Right);

	/*
		Checks if time object are not equal.
	*/
	bool operator!=(const Time& Left, const Time& Right);

	/*
		Checks if left side is greater or equal right side.
	*/
	bool operator>=(const Time& Left, const Time& Right);

	/*
		Checks if left side is lower or equal right side.
	*/
	bool operator<=(const Time& Left, const Time& Right);


	/*
		Creates Time object from microseconds (long long).
	*/
	Time microseconds(long long t);

	/*
		Creates Time object from milliseconds (double).
	*/
	Time milliseconds(double t);

	/*
		Creates Time object from seconds (double).
	*/
	Time seconds(double t);
#else
	namespace chrono		= std::chrono;
	using seconds_f			= chrono::duration<float>;
	using seconds_d			= chrono::duration<double>;
	using milliseconds_f	= chrono::duration<float,	std::milli>;
	using milliseconds_d	= chrono::duration<double,	std::milli>;
	using microseconds_f	= chrono::duration<float,	std::micro>;
	using microseconds_d	= chrono::duration<double,	std::micro>;
	using nanoseconds_f		= chrono::duration<float,	std::nano>;
	using nanoseconds_d		= chrono::duration<double,	std::nano>;
#endif

	/// <summary>
	/// Class that is used to measure time durations.
	/// </summary>
	/// <remarks>
	/// <para>Duration is expressed in units returned by std::chrono::steady_clock::now().time_since_epoch().</para>
	/// </remarks>
	class Clock
	{
	public:
		/// Duration unit of this clock.
		using duration = chrono::steady_clock::time_point::duration;

		/// <summary>
		/// Initializes a new instance of the <see cref="Clock"/> class.
		/// </summary>
		Clock();
		
		/// <summary>
		/// Restarts clock. 
		/// </summary>
		/// <returns>Time elapsed since clock was created or restarted.</returns>
		duration restart();
		
		/// <summary>
		/// Returns elapsed time.
		/// </summary>
		/// <returns>Time elapsed since object was created or clock was restarted.</returns>
		duration getElapsedTime() const;

		/// <summary>
		/// Returns time passed since the epoch started.
		/// Epoch started at 1st January 1970.
		/// </summary>
		/// <returns>Time passed since the epoch started.</returns>
		static duration now();
	protected:
		chrono::nanoseconds m_startTime; /// Holds starting time to count from.
	};

}