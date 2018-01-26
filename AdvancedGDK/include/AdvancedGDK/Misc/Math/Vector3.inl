// File description:
// Implements base class for 3D vector manipulation.

// NOTE / WARNING:
// This can't be included separately, because it is included by "Math.hpp" header.
// Error will occur when separated, uses agdk::Math::Tolerance class.
#pragma once

// Precompiled header:
#include "../../../../stdafx.h"

// Custom includes:
#include "VectorStringBuilder.hpp"


namespace agdk
{
namespace impl
{
template <typename _Ty>
class BaseVector3;

/// <summary>
/// Adds two vectors together.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Sum of two vectors.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator + (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Subtracts rhs vector from lhs one.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Difference of two vectors.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator - (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Multiplies two vectors.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Product of two vectors.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator * (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Divides lhs vector by rhs vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Quotient of two vectors.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator / (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_);


////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs vector <op> rhs scalar).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds scalar to a vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector plus a scalar.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator + (BaseVector3<_Ty> const & lhs_, _Ty const rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Substracts scalar from a vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector minus a scalar.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator - (BaseVector3<_Ty> const & lhs_, _Ty const rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Multiplies vector by a scalar.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector times a scalar.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator * (BaseVector3<_Ty> const & lhs_, _Ty const rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Divides vector by a scalar.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector divided by a scalar.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator / (BaseVector3<_Ty> const & lhs_, _Ty const rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs scalar <op> rhs vector).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds scalar to a vector.
/// </summary>
/// <param name="lhs_">The scalar.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Vector plus a scalar.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator + (_Ty const lhs_, BaseVector3<_Ty> const & rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Multiplies vector by a scalar.
/// </summary>
/// <param name="lhs_">The scalar.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Vector times a scalar.</returns>
template <typename _Ty>
constexpr BaseVector3<_Ty> operator * (_Ty const lhs_, BaseVector3<_Ty> const & rhs_);

/// <summary>
/// Implements templated three dimensional vector arithmetic class.
/// </summary>
template <typename _Ty>
class BaseVector3
{
	// Performs a type check:
	// Is only set to true when T is not cv-qualified and is non-boolean arithmetic type.
	template <typename T>
	constexpr static bool is_noncvref_mathscalar_v =
		std::is_same_v<T, std::remove_cv_t< std::remove_reference_t<T> > > &&
		std::is_arithmetic_v<T> &&
		!std::is_same_v<T, bool>;

public:
	using ValueType = _Ty;

	// Allow every non-cv qualified arithmetic type but bool.
	static_assert(
		is_noncvref_mathscalar_v<ValueType>,
		"ValueType of a vector must be a non-cv qualified scalar type."
	);

		// This is basic component of a Vector3.
	ValueType x, y, z;

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector3"/> class.
	/// </summary>
	constexpr BaseVector3()
		: x{ 0 }, y{ 0 }, z{ 0 }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector3"/> class.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	/// <param name="z_">The z value.</param>
	constexpr BaseVector3(ValueType const x_, ValueType const y_, ValueType const z_)
		: x{ x_ }, y{ y_ }, z{ z_ }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector3"/> class.
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	constexpr BaseVector3(BaseVector3<ValueType> const &rhs_)
		: x{ rhs_.x },
		y{ rhs_.y },
		z{ rhs_.z }
	{
	}

	/// <summary>
	/// Sets values of the vector.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	/// <param name="z_">The z value.</param>
	constexpr void set(ValueType const x_, ValueType const y_, ValueType const z_)
	{
		x = static_cast<ValueType>(x_);
		y = static_cast<ValueType>(y_);
		z = static_cast<ValueType>(z_);
	}

	/// <summary>
	/// Returns length of the vector.
	/// </summary>
	/// <returns>Length of the vector.</returns>
	template <typename _LenTy = ValueType,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_LenTy> > >
	_LenTy length() const
	{
		if constexpr(std::is_same_v<_LenTy, ValueType>)
			return std::sqrt(x * x + y * y + z * z);
		else
		{
			auto conv = this->template convert<_LenTy>();
			return std::sqrt(conv.x * conv.x + conv.y * conv.y + conv.z * conv.z);
		}
	}

	/// <summary>
	/// Returns squared length of the vector.
	/// </summary>
	/// <returns>Squared length of the vector.</returns>
	template <typename _LenTy = ValueType,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_LenTy> > >
	constexpr _LenTy lengthSquared() const
	{
		if constexpr(std::is_same_v<_LenTy, ValueType>)
			return x * x + y * y + z * z;
		else
		{
			auto conv = this->template convert<_LenTy>();
			return static_cast<_LenTy>(conv.x * conv.x + conv.y * conv.y + conv.z * conv.z);
		}
	}

	/// <summary>
	/// Computes distance between two instances.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Distance between two instances.</returns>
	template <typename _DistTy = ValueType,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_DistTy> > >
	_DistTy distance(BaseVector3<ValueType> const & other_) const
	{
		return (*this - other_).template length<_DistTy>();
	}

	/// <summary>
	/// Computes squared distance between two instances.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Squared distance between two instances.</returns>
	template <typename _DistTy = ValueType,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_DistTy> > >
	constexpr _DistTy distanceSquared(BaseVector3<ValueType> const & other_) const
	{
		return (*this - other_).template lengthSquared<_DistTy>();
	}

	/// <summary>
	/// Computes dot product of two vectors (this and other).
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Dot product of two vectors.</returns>
	template <typename _DotTy = ValueType,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_DotTy> > >
	constexpr _DotTy dot(BaseVector3<ValueType> const & other_) const
	{
		if constexpr(std::is_same_v<_DotTy, ValueType>)
			return x * other_.x + y * other_.y + z * other_.z;
		else
		{
			auto convThis = this->template convert<_DotTy>();
			auto convOther = other_->template convert<_DotTy>();

			return static_cast<_DotTy>(
				convThis.x * convOther.x +
				convThis.y * convOther.y +
				convThis.z * convOther.z
				);
		}
	}

	/// <summary>
	/// Computes cross product of two vectors (this and other_).
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Cross product of two vectors.</returns>
	constexpr BaseVector3<ValueType> cross(BaseVector3<ValueType> const & other_) const
	{
		return BaseVector3<ValueType>{
			y * other_.z - z * other_.y,
				z * other_.x - x * other_.z,
				x * other_.y - y * other_.x
		};
	}

	/// <summary>
	/// Computes reflection vector of specified normal.
	/// </summary>
	/// <param name="normal_">The surface normal.</param>
	/// <returns>Reflection vector of specified normal</returns>
	constexpr BaseVector3<ValueType> reflect(BaseVector3<ValueType> const & normal_) const
	{
		auto normal = normal_.normalize();
		return (*this) - (normal * normal.dot(*this) * ValueType { 2 });
	}

	/// <summary>
	/// Computes reflection vector of specified normal and assigns it to self.
	/// </summary>
	/// <param name="normal_">The normal.</param>
	/// <returns>Reference to self after computing reflection of specified normal.</returns>
	constexpr BaseVector3<ValueType>& reflectSelf(BaseVector3<ValueType> const & normal_)
	{
		auto normal = normal_.normalize();
		*this -= normal * normal.dot(*this) * ValueType { 2 };
		return *this;
	}

	/// <summary>
	/// Computes normalized vector.
	/// </summary>
	/// <returns>Normalized vector</returns>
	constexpr BaseVector3<ValueType> normalize() const
	{
		auto len = this->length<ValueType>();
		if (len != 0)
		{
			return  BaseVector3<ValueType>{ x / len, y / len, z / len };
		}
		return *this;
	}

	/// <summary>
	/// Normalizes self and returns reference.
	/// </summary>
	/// <returns>Reference to normalized self.</returns>
	constexpr BaseVector3<ValueType>& normalizeSelf()
	{
		auto len = this->length<ValueType>();
		if (len != 0)
		{
			x /= len; y /= len; z /= len;
		}
		return *this;
	}

	// yet non-constexpr
	/// <summary>
	/// Converts vector to string.
	/// </summary>
	/// <param name="setup_">The string building setup.</param>
	/// <returns>Vector converted to std::string.</returns>
	std::string toString(VectorStringBuilder const & setup_ = VectorStringBuilder{}) const
	{
		std::stringstream stream;
		switch (setup_.wrap)
		{
		case VectorStringBuilder::Wrap::Round: { stream << "( "; break; }
		case VectorStringBuilder::Wrap::Square: { stream << "[ "; break; }
		case VectorStringBuilder::Wrap::Curly: { stream << "{ "; break; }
		default: break;
		}

		if (setup_.mantissaFixed)
			stream << std::fixed;

		stream.precision(setup_.precision);

		switch (setup_.compVisibility)
		{
		case VectorStringBuilder::CompVisibility::WithColon: {
			stream << "x: " << x << setup_.separator << ' '
				<< "y: " << y << setup_.separator << ' '
				<< "z: " << z;
			break;
		}
		case VectorStringBuilder::CompVisibility::WithEqual: {
			stream << "x = " << x << setup_.separator << ' '
				<< "y = " << y << setup_.separator << ' '
				<< "z = " << z;
			break;
		}
		default: {
			stream << x << setup_.separator << ' ' << y << setup_.separator << ' ' << z;
			break;
		}
		}

		switch (setup_.wrap)
		{
		case VectorStringBuilder::Wrap::Round: { stream << " )"; break; }
		case VectorStringBuilder::Wrap::Square: { stream << " ]"; break; }
		case VectorStringBuilder::Wrap::Curly: { stream << " }"; break; }
		default: break;
		}
		return stream.str();
	}

	/// <summary>
	/// Checks if two vectors are equal.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <param name="EqualityTolerance">The equality tolerance.</param>
	/// <returns>
	///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename _Ty2, typename _EqTy,
		typename = std::enable_if_t< std::is_floating_point_v<_EqTy> > >
		constexpr bool equals(BaseVector3<_Ty2> const & other_, _EqTy const equalityTolerance_ = Math::Tolerance<_EqTy>::Low) const
	{
		return (
			std::abs(static_cast<_EqTy>(x) - static_cast<_EqTy>(other_.x)) <= equalityTolerance_ &&
			std::abs(static_cast<_EqTy>(y) - static_cast<_EqTy>(other_.y)) <= equalityTolerance_ &&
			std::abs(static_cast<_EqTy>(z) - static_cast<_EqTy>(other_.z)) <= equalityTolerance_
			);
	}

	/// <summary>
	/// Computes lower bound vector of the two specified.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Vector with components:
	/// { x = min(lhs_.x, rhs_.x), y = min(lhs_.y, rhs_.y), z = min(lhs_.z, rhs_.z)  }
	/// </returns>
	constexpr static BaseVector3<ValueType> lowerBounds(BaseVector3<ValueType> const &lhs_, BaseVector3<ValueType> const & rhs_)
	{
		return BaseVector3<ValueType>{
			std::min(lhs_.x, rhs_.x),
				std::min(lhs_.y, rhs_.y),
				std::min(lhs_.z, rhs_.z)
		};
	}

	/// <summary>
	/// Computes upper bound vector of the two specified.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Vector with components:
	/// { x = max(lhs_.x, rhs_.x), y = max(lhs_.y, rhs_.y), z = max(lhs_.z, rhs_.z)  }
	/// </returns>
	constexpr static BaseVector3<ValueType> upperBounds(BaseVector3<ValueType> const & lhs_, BaseVector3<ValueType> const & rhs_)
	{
		return BaseVector3<ValueType>{
			std::max(lhs_.x, rhs_.x),
				std::max(lhs_.y, rhs_.y),
				std::min(lhs_.z, rhs_.z)
		};
	}

	/// <summary>
	/// Computes lower and upper bounds for two specified vectors.
	/// </summary>
	/// <param name="lower_">The lower bound vector.</param>
	/// <param name="upper_">The upper bound vecor.</param>
	/// <remarks>
	/// <para>Uses arguments as output, changes its values.</para>
	/// </remarks>
	constexpr static void bounds(BaseVector3<ValueType> & lower_, BaseVector3<ValueType> & upper_)
	{
		BaseVector3<ValueType> tempMin = lower_;
		lower_ = BaseVector3<ValueType>::lowerBounds(lower_, upper_);
		upper_ = BaseVector3<ValueType>::upperBounds(tempMin, upper_);
	}

	/// <summary>
	/// Converts vector to other type.
	/// </summary>
	/// <returns>Vector of other value type.</returns>
	template <typename _Ty2>
	constexpr BaseVector3<_Ty2> convert() const {
		return BaseVector3<_Ty2>{
			static_cast<_Ty2>(x),
			static_cast<_Ty2>(y),
			static_cast<_Ty2>(z)
		};
	}

	//////////////////////////////////////
	// Operators:
	//////////////////////////////////////

	/// <summary>
	/// Assigns vector to self.
	/// </summary>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self.</returns>
	constexpr BaseVector3<ValueType> & operator = (BaseVector3<ValueType> const & rhs_) {
		x = rhs_.x;
		y = rhs_.y;
		z = rhs_.z;
		return *this;
	}

	/// <summary>
	/// Negates vector.
	/// </summary>
	/// <returns>Negated vector.</returns>
	constexpr BaseVector3<ValueType> operator - () const {
		return BaseVector3<ValueType>{-x, -y, -z};
	}

	/// <summary>
	/// Checks if lhs vector is equal to rhs vector (with low tolerance).
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	/// <returns>
	///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename _Ty2>
	constexpr bool operator == (BaseVector3<_Ty2> const & rhs_) const {
		return equals(rhs_);
	}

	/// <summary>
	/// Checks if lhs vector is not equal to rhs vector (with low tolerance).
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	/// <returns>
	///  <c>true</c> if vectors are not equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename _Ty2>
	constexpr bool operator != (BaseVector3<_Ty2> const & rhs_) const {
		return !equals(rhs_);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr BaseVector3<ValueType>& operator += (BaseVector3<ValueType> const & rhs_)
	{
		x += rhs_.x;
		y += rhs_.y;
		z += rhs_.z;
		return *this;
	}

	/// <summary>
	/// Subtracts rhs vector from lhs one.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self after operation.</returns>
	template <typename _Ty2>
	constexpr BaseVector3<ValueType>& operator -= (BaseVector3<ValueType> const & rhs_) {
		x -= rhs_.x;
		y -= rhs_.y;
		z -= rhs_.z;
		return *this;
	}

	/// <summary>
	/// Multiplies two vectors.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	template <typename _Ty2>
	constexpr BaseVector3<ValueType>& operator *= (BaseVector3<ValueType> const & rhs_) {
		x *= rhs_.x;
		y *= rhs_.y;
		z *= rhs_.z;
		return *this;
	}

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr BaseVector3<ValueType>& operator /= (BaseVector3<ValueType> const & rhs_) {
		x /= rhs_.x;
		y /= rhs_.y;
		z /= rhs_.z;
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds scalar to a vector.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector plus a scalar.</returns>
	constexpr BaseVector3<ValueType>& operator += (ValueType const rhs_) {
		x += rhs_;
		y += rhs_;
		z += rhs_;
		return *this;
	}

	/// <summary>
	/// Substracts scalar from a vector.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector minus a scalar.</returns>
	constexpr BaseVector3<ValueType>& operator -= (ValueType const rhs_) {
		x -= rhs_;
		y -= rhs_;
		z -= rhs_;
		return *this;
	}

	/// <summary>
	/// Multiplies vector by a scalar.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector times a scalar.</returns>
	constexpr BaseVector3<ValueType>& operator *= (ValueType const rhs_) {
		x *= rhs_;
		y *= rhs_;
		z *= rhs_;
		return *this;
	}

	/// <summary>
	/// Divides vector by a scalar.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector divided by a scalar.</returns>
	constexpr BaseVector3<ValueType>& operator /= (ValueType const rhs_) {
		x /= rhs_;
		y /= rhs_;
		z /= rhs_;
		return *this;
	}

};

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator + (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_)
{
	return {
		lhs_.x + rhs_.x,
		lhs_.y + rhs_.y,
		lhs_.z + rhs_.z
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator - (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_)
{
	return {
		lhs_.x - rhs_.x,
		lhs_.y - rhs_.y,
		lhs_.z - rhs_.z
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator * (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_)
{
	return {
		lhs_.x * rhs_.x,
		lhs_.y * rhs_.y,
		lhs_.z * rhs_.z
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator / (BaseVector3<_Ty> const & lhs_, BaseVector3<_Ty> const & rhs_)
{
	return {
		lhs_.x / rhs_.x,
		lhs_.y / rhs_.y,
		lhs_.z / rhs_.z
	};
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs vector <op> rhs scalar).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator + (BaseVector3<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x + rhs_,
		lhs_.y + rhs_,
		lhs_.z + rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator - (BaseVector3<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x - rhs_,
		lhs_.y - rhs_,
		lhs_.z - rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator * (BaseVector3<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x * rhs_,
		lhs_.y * rhs_,
		lhs_.z * rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator / (BaseVector3<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x / rhs_,
		lhs_.y / rhs_,
		lhs_.z / rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs scalar <op> rhs vector).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator + (_Ty const lhs_, BaseVector3<_Ty> const & rhs_)
{
	return {
		rhs_.x + lhs_,
		rhs_.y + lhs_,
		rhs_.z + lhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr BaseVector3<_Ty> operator * (_Ty const lhs_, BaseVector3<_Ty> const & rhs_)
{
	return {
		rhs_.x * lhs_,
		rhs_.y * lhs_,
		rhs_.z * lhs_
	};
}

} // namespace impl

// 3D Vector class templated with float
using Vector3f		= impl::BaseVector3<float>;
// 3D Vector class templated with float
using Vector3		= impl::BaseVector3<float>;
// 3D Vector class templated with double
using Vector3d		= impl::BaseVector3<double>;
// 3D Vector class templated with std::int16_t
using Vector3i16	= impl::BaseVector3<std::int16_t>;
// 3D Vector class templated with std::int32_t
using Vector3i32	= impl::BaseVector3<std::int32_t>;
// 3D Vector class templated with std::int64_t
using Vector3i64	= impl::BaseVector3<std::int64_t>;
// 3D Vector class templated with std::uint16_t
using Vector3u16	= impl::BaseVector3<std::uint16_t>;
// 3D Vector class templated with std::uint32_t
using Vector3u32	= impl::BaseVector3<std::uint32_t>;
// 3D Vector class templated with std::uint64_t
using Vector3u64	= impl::BaseVector3<std::uint64_t>;

} // namespace agdk
