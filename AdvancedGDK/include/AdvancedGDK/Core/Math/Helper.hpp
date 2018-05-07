#pragma once

#include ADVANCEDGDK_PCH

#include "../TypeTraits.hpp"

namespace agdk::math
{

namespace constants
{
// Definition of Pi
template <typename TType>
constexpr TType Pi								= static_cast<TType>(3.14159265358979323846L);
// Make Pi available to const char* specialization:
template <>
constexpr const char* Pi<const char*>			= "Pi";
// Make Pi available to const wchar_t* specialization:
template <>
constexpr const wchar_t* Pi<const wchar_t*>		= L"Pi";

// Make Pi available to const char16_t* specialization:
template <>
constexpr const char16_t* Pi<const char16_t*>	= u"Pi";

// Make Pi available to const char32_t* specialization:
template <>
constexpr const char32_t* Pi<const char32_t*>	= U"Pi";

template <typename TType, typename = std::enable_if_t< std::is_floating_point_v<TType> || std::is_integral_v<TType> > >
constexpr TType LowTolerance			= static_cast<TType>(0.000'001);
template <typename TType, typename = std::enable_if_t< std::is_floating_point_v<TType> || std::is_integral_v<TType> > >
constexpr TType MediumTolerance		= static_cast<TType>(0.000'01);
template <typename TType, typename = std::enable_if_t< std::is_floating_point_v<TType> || std::is_integral_v<TType> > >
constexpr TType HighTolerance		= static_cast<TType>(0.000'1);
template <typename TType, typename = std::enable_if_t< std::is_floating_point_v<TType> || std::is_integral_v<TType> > >
constexpr TType VeryHighTolerance	= static_cast<TType>(0.001);
} // namespace constants

/// <summary>
/// Makes sure that `lower_` is <= `higher_`.
/// </summary>
/// <param name="lower_">The value that will be lower one of the two specified.</param>
/// <param name="higher_">The value that will be higher one of the two specified..</param>
template <typename TType>
void minMaxRef(TType & lower_, TType & higher_);

/// <summary>
/// Checks whether `a_` is nearly equal `b_`, using given equality tolerance.
/// </summary>
/// <param name="a_">The first component.</param>
/// <param name="b_">The second component.</param>
/// <param name="equalityTolerance_">The equality tolerance.</param>
/// <return>
///		<c>true</c> is `a_` is nearly equal `b_`; otherwise, <c>false</c>.
/// </return>
template <typename TType>
bool nearlyEqual(TType const & a_, TType const & b_, TType const & equalityTolerance_);

/// <summary>
/// Clamps `current_` value between `lowerBoundary_` and `upperBoundary_`. Makes sure that `lowerBoundary_` is <= `upperBoundary_`.
/// </summary>
/// <param name="current_">The current.</param>
/// <param name="lowerBoundary_">The lower boundary.</param>
/// <param name="upperBoundary_">The upper boundary.</param>
/// <returns>Clamped value.</returns>
template <typename TType>
TType clampChecked(TType const & current_, TType const & lowerBoundary_, TType const & upperBoundary_);

// Note: to be moved to QuickMaffs
template <typename TType,
	typename = std::enable_if_t< std::is_floating_point_v< type_traits::removeCVRefT<TType> > > >
constexpr std::intmax_t ceil(TType number_) {
	std::intmax_t ceiled = static_cast<std::intmax_t>(number_);
	if (number_ == static_cast<TType>(ceiled)) {
		return ceiled;
	}
	return ceiled + (number_ > 0 ? 1 : 0);
}

} // namespace

#include "Helper.inl"