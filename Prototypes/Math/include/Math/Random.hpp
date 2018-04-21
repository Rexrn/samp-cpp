// File description:
// Implements easy to use random engine using Mersenne's Twister.
#pragma once

// Precompiled header:
#include MATH_PCH

namespace agdk::math::random
{

namespace detail
{

/// <summary>
/// Returns reference to Mersenne Twister random number generator.
/// </summary>
/// <returns>Reference to Mersenne Twister random number generator.</returns>
std::mt19937& getGenerator();

/// <summary>
/// Returns reference to Mersenne Twister random engine (64 bit).
/// </summary>
/// <returns>Reference to Mersenne Twister random engine (64 bit).</returns>
std::mt19937_64& getGenerator64();

} // namespace detail

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
template <typename TType>
TType generate(TType const & from_, TType const & to_);

} // namespace

#include "Random.inl"