#pragma once

#include MATH_PCH

// Note: \/ this is already implemented inside /Core/TypeTraits.hpp
namespace agdk::typetraits
{
template <typename TType>
struct removeCVRef {
	using type = std::remove_reference_t < std::remove_cv_t<TType> >;
};
template <typename TType>
using removeCVRefT = typename removeCVRef<TType>::type;

template <typename TType>
struct isCVRef {
	static constexpr bool value = std::is_same_v<TType, removeCVRefT<TType> >;
};

template <typename TType>
constexpr bool isCVRefV = isCVRef<TType>::value;

template <typename TType>
struct isMathScalar {
	static constexpr bool value = isCVRefV<TType> && std::is_arithmetic_v<TType> && !std::is_same_v<TType, bool>;
};

template <typename TType>
constexpr bool isMathScalarV = isMathScalar<TType>::value;


template<class TNonRatioType>
struct isRatio {
	static constexpr bool value = false;
};

template<intmax_t _ratioNumerator, intmax_t _ratioDenumerator>
struct isRatio<std::ratio<_ratioNumerator, _ratioDenumerator> > {
	static constexpr bool value = true;
};

template<class TNonRatioType>
constexpr bool isRatioV = false;

template<intmax_t _ratioNumerator, intmax_t _ratioDenumerator>
constexpr bool isRatioV<std::ratio<_ratioNumerator, _ratioDenumerator> > = true;


}

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
bool nearlyEquals(TType const & a_, TType const & b_, TType const & equalityTolerance_); // Internal compiler error // = constants::MediumTolerance<TType>);

/// <summary>
/// Clamps `current_` value between `lowerBoundary_` and `upperBoundary_`. Makes sure that `lowerBoundary_` is <= `upperBoundary_`.
/// </summary>
/// <param name="current_">The current.</param>
/// <param name="lowerBoundary_">The lower boundary.</param>
/// <param name="upperBoundary_">The upper boundary.</param>
/// <returns>Clamped value.</returns>
template <typename TType>
TType clampChecked(TType const & current_, TType const & lowerBoundary_, TType const & upperBoundary_);

} // namespace

#include "Helper.inl"