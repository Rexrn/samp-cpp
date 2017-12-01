#pragma once

#include <random>
#include <cinttypes>
#include <type_traits>

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
		/// <returns>Random unsigned 64-bit integer in specified range.</returns>
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
			using RawT = std::remove_cv_t<std::remove_reference_t<T>>;
			if constexpr(	std::is_same_v<RawT, short>		|| std::is_same_v<RawT, unsigned short>
						||	std::is_same_v<RawT, int>		|| std::is_same_v<RawT, unsigned int>
						||	std::is_same_v<RawT, long>		|| std::is_same_v<RawT, unsigned long>
						||	std::is_same_v<RawT, long long>	|| std::is_same_v<RawT, unsigned long long>)
			{
				return std::uniform_int_distribution<RawT>(
					std::min(static_cast<RawT>(from_), static_cast<RawT>(to_)),
					std::max(static_cast<RawT>(from_), static_cast<RawT>(to_))
				)(Random::getEngine()); // <--- It runs distribution on engine and result is returned.
			}
			else if (std::is_same_v<RawT, float> || std::is_same_v<RawT, double> || std::is_same_v< RawT, long double>)
			{
				return std::uniform_real_distribution<RawT>(
						std::min(static_cast<RawT>(from_), static_cast<RawT>(to_)),
						std::max(static_cast<RawT>(from_), static_cast<RawT>(to_))
				)(Random::getEngine()); // <--- It runs distribution on engine and result is returned.
			}
			else // Type is not supported.
			{
				static_assert(false, "Random does not support this type.");
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
	};
}
