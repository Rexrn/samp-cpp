// File description:
// Implements basic length class and aliases.
#pragma once

// Precompiled header:
#include MATH_PCH

#include "Helper.hpp"

namespace agdk::math
{

/// <summary>
/// Provides implementation of base length unit.
/// </summary>
template < typename TLengthType = double, typename TRatioType = std::ratio<1, 1> >
class Length
{
public:
	using RatioType		= TRatioType;
	using ValueType		= TLengthType;

	static_assert(type_traits::isRatioV<RatioType>, "Second template parameter must be a valid std::ratio type.");
	static_assert(std::is_floating_point_v<ValueType>, "Length can only be represented by floating point values.");

	ValueType value;
			
	/// <summary>
	/// Returns maximal possible value.
	/// </summary>
	/// <returns>Maximal possible value.</returns>
	constexpr static ValueType max()
	{
		return std::numeric_limits<ValueType>::max();
	}

	/// <summary>
	/// Returns minimal possible value.
	/// </summary>
	/// <returns>Minimal possible value.</returns>
	constexpr static ValueType min()
	{
		return std::numeric_limits<ValueType>::min();
	}

	/// <summary>
	/// Returns zero-length.
	/// </summary>
	/// <returns>Zero-length object.</returns>
	constexpr static Length<ValueType, RatioType> zero()
	{
		return {};
	}

	/// <summary>
	/// Default constructor.
	/// </summary>
	constexpr Length(ValueType value_ = ValueType{ 0 })
		: value(value_)
	{
	}

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="rhs_">Other length object.</param>
	template <typename TLengthType2nd, typename TRatioType2nd>
	constexpr Length(const Length<TLengthType2nd, TRatioType2nd> &rhs_)
		: value(rhs_.value
				* std::ratio_divide<TRatioType2nd, RatioType>::num
				/ std::ratio_divide<TRatioType2nd, RatioType>::den)
	{
	}

	/// <summary>
	/// Copy assignment operator.
	/// </summary>
	/// <param name="rhs_">Other length object.</param>
	template <typename TLengthType2nd, typename TRatioType2nd>
	constexpr Length<ValueType, RatioType>& operator=(const Length<TLengthType2nd, TRatioType2nd> &rhs_)
	{
		value = rhs_.value
			* std::ratio_divide<TRatioType2nd, RatioType>::num
			/ std::ratio_divide<TRatioType2nd, RatioType>::den;
	}

	/// <summary>
	/// Converts value to other length unit.
	/// </summary>
	template <typename TLengthType2nd, typename TRatioType2nd>
	constexpr explicit operator Length<TLengthType2nd, TRatioType2nd>() const
	{
		using div_ratio = std::ratio_divide<TRatioType2nd, RatioType>;
		return { static_cast<TLengthType2nd>(value) * div_ratio::num / div_ratio::den };
	}

	/// <summary>
	/// Determines whether rhs_ length is *exactly* equal.
	/// </summary>
	/// <param name="rhs_">The right hand side length.</param>
	/// <returns>
	///   <c>true</c> if equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename TLengthType2nd, typename TRatioType2nd>
	constexpr bool equals(Length<TLengthType2nd, TRatioType2nd> const &rhs_) const
	{
		using div_ratio = std::ratio_divide<TRatioType2nd, RatioType>;
		return value == (static_cast<TLengthType2nd>(rhs_.value) * div_ratio::num / div_ratio::den);
	}

	/// <summary>
	/// Determines whether rhs_ length is nearly equal.
	/// </summary>
	/// <param name="rhs_">The right hand side length.</param>
	/// <param name="tolerance">The tolerance.</param>
	/// <returns>
	///   <c>true</c> if nearly equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename TLengthType2nd, typename TRatioType2nd>
	constexpr bool nearlyEquals(Length<TLengthType2nd, TRatioType2nd> const &rhs_, ValueType const tolerance_ = constants::MediumTolerance<ValueType>) const
	{
		using div_ratio = std::ratio_divide<TRatioType2nd, RatioType>;
		return nearlyEquals(value, static_cast<ValueType>(static_cast<TLengthType2nd>(rhs_.value) * div_ratio::num / div_ratio::den), tolerance_);
	}
};
		
/// <summary>
/// Adds rhs_ length to lhs_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Sum of two lengths.</returns>
/// <remarks>
/// <para>Resulting type matches lhs_ type.</para>
/// </remarks>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd >
inline constexpr Length<TLengthType1st, TRatioType1st> operator+(Length<TLengthType1st, TRatioType1st> const & lhs_, Length<TLengthType2nd, TRatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<TRatioType2nd, TRatioType1st>;
	return { lhs_.value + (static_cast<TLengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den) };
}

/// <summary>
/// Subtracts rhs_ length from lhs_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Difference of two lengths.</returns>
/// <remarks>
/// <para>Resulting type matches lhs_ type.</para>
/// </remarks>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd >
inline constexpr Length<TLengthType1st, TRatioType1st> operator-(Length<TLengthType1st, TRatioType1st> const & lhs_, Length<TLengthType2nd, TRatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<TRatioType2nd, TRatioType1st>;
	return { lhs_.value - (static_cast<TLengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den) };
}

/// <summary>
/// Returns lhs_ multiplied by a scalar_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="scalar_">The scalar_.</param>
/// <returns>Product of lhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <	typename TLengthType, typename RatioType, typename TScalarType,
			typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<TScalarType> > > > >
inline constexpr Length<TLengthType, RatioType> operator*(Length<TLengthType, RatioType> const & lhs_, TScalarType const scalar_)
{
	return { lhs_.value * scalar_ };
}

/// <summary>
/// Returns lhs_ divided by a scalar_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="scalar_">The scalar_.</param>
/// <returns>Quotient of lhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <	typename TLengthType, typename RatioType, typename TScalarType,
			std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<TScalarType> > > > >
inline constexpr Length<TLengthType, RatioType> operator/(Length<TLengthType, RatioType> const & lhs_, TScalarType const scalar_)
{
	return { lhs_.value / scalar_ };
}

/// <summary>
/// Returns rhs_ multiplied by a scalar_.
/// </summary>
/// <param name="scalar_">The scalar_.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Product of rhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <	typename TScalarType, typename TLengthType, typename RatioType,
			typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<TScalarType> > > > >
inline constexpr Length<TLengthType, RatioType> operator*(TScalarType const scalar_, Length<TLengthType, RatioType> const & rhs_)
{
	return { rhs_.value * scalar_ };
}

/// <summary>
/// Returns lhs_ divided by a scalar_.
/// </summary>
/// <param name="scalar_">The scalar_.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Quotient of rhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <	typename TScalarType, typename TLengthType, typename RatioType,
			typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<TScalarType> > > > >
inline constexpr Length<TLengthType, RatioType> operator/(TScalarType const scalar_, Length<TLengthType, RatioType> const & rhs_)
{
	return { rhs_.value / scalar_ };
}

/// <summary>
/// Checks if lhs_ length is *nearly* equal rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if nearly equal; otherwise, <c>false</c>.
/// </returns>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd>
inline constexpr bool operator==(Length<TLengthType1st, TRatioType1st> const & lhs_, Length<TLengthType2nd, TRatioType2nd> const & rhs_)
{
	return lhs_.nearlyEquals(rhs_);
}

/// <summary>
/// Checks if lhs_ length is not *nearly* equal rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>false</c> if nearly equal; otherwise, <c>true</c>.
/// </returns>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd>
inline constexpr bool operator!=(Length<TLengthType1st, TRatioType1st> const & lhs_, Length<TLengthType2nd, TRatioType2nd> const & rhs_)
{
	return !lhs_.nearlyEquals(rhs_);
}

/// <summary>
/// Checks if lhs_ length is greater than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is greater; otherwise, <c>false</c>.
/// </returns>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd>
inline constexpr bool operator>(Length<TLengthType1st, TRatioType1st> const & lhs_, Length<TLengthType2nd, TRatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<TRatioType2nd, TRatioType1st>;
	return lhs_.value > (static_cast<TLengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den);
}

/// <summary>
/// Checks if lhs_ length is greater or equal than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is greater or equal; otherwise, <c>false</c>.
/// </returns>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd>
inline constexpr bool operator>=(Length<TLengthType1st, TRatioType1st> const &lhs_, Length<TLengthType2nd, TRatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<TRatioType2nd, TRatioType1st>;
	return lhs_.value >= (static_cast<TLengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den);
}

/// <summary>
/// Checks if lhs_ length is less than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is less; otherwise, <c>false</c>.
/// </returns>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd>
inline constexpr bool operator<(Length<TLengthType1st, TRatioType1st> const & lhs_, Length<TLengthType2nd, TRatioType2nd> const &rhs_)
{
	return !(lhs_ >= rhs_);
}

/// <summary>
/// Checks if lhs_ length is less or equal than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is less or equal; otherwise, <c>false</c>.
/// </returns>
template <	typename TLengthType1st, typename TRatioType1st,
			typename TLengthType2nd, typename TRatioType2nd>
inline constexpr bool operator<=(Length<TLengthType1st, TRatioType1st> const & lhs_, Length<TLengthType2nd, TRatioType2nd> const &rhs_)
{
	return !(lhs_ > rhs_);
}


using Nanometers	= Length<double, std::nano>;		// 0.000'000'001m
using Micrometers	= Length<double, std::micro>;		// 0.000'001m
using Millimeters	= Length<double, std::milli>;		// 0.001m
using Centimeters	= Length<double, std::centi>;		// 0.01m
using Decimeters	= Length<double, std::deci>;		// 0.1m
using Meters		= Length<double>;					// 1m
using Decameters	= Length<double, std::deca>;		// 10m
using Hectometers	= Length<double, std::hecto>;		// 100m
using Kilometers	= Length<double, std::kilo>;		// 1'000m
using Megameters	= Length<double, std::mega>;		// 1'000'000m
using Gigameters	= Length<double, std::giga>;		// 1'000'000'000m
using Miles			= Length<double, std::ratio_multiply<std::kilo, std::ratio<1609, 1000>>>; // 1609m
using Yards			= Length<double, std::ratio<9144, 10000>>;		// 0.9144m
using LightYears	= Length<double, std::ratio<9460730472580800>>;	// 9460730472580800m
}
