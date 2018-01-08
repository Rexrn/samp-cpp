/**
 * Header: Vector2.inl
 * Author: Pawel Syska aka RazzorFlame.
 * Description:
 * Implements base class for 2D vector manipulation.
**/

// NOTE / WARNING:
// This can't be included separately, because it is included by "Math.hpp" header.
// Error will occur when separated, uses agdk::Math::Tolerance class.

// Standard includes:
#include <cmath>
#include <cinttypes>
#include <type_traits>
#include <string>
#include <sstream>
#include <iomanip>

// Custom includes:
#include "VectorStringBuilder.hpp"


namespace agdk::impl
{
template <typename _Ty>
class BaseVector3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds two vectors together.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Sum of two vectors.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator + (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_);

/// <summary>
/// Subtracts rhs vector from lhs one.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Difference of two vectors.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator - (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_);

/// <summary>
/// Multiplies two vectors.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Product of two vectors.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator * (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_);

/// <summary>
/// Divides lhs vector by rhs vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Quotient of two vectors.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator / (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs vector <op> rhs scalar).
////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds scalar to a vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector plus a scalar.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator + (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_);

/// <summary>
/// Substracts scalar from a vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector minus a scalar.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator - (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_);

/// <summary>
/// Multiplies vector by a scalar.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector times a scalar.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator * (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_);

/// <summary>
/// Divides vector by a scalar.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector divided by a scalar.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator / (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs scalar <op> rhs vector).
////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds scalar to a vector.
/// </summary>
/// <param name="lhs_">The scalar.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Vector plus a scalar.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator + (_Ty const lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_);

/// <summary>
/// Multiplies vector by a scalar.
/// </summary>
/// <param name="lhs_">The scalar.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Vector times a scalar.</returns>
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator * (_Ty const lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_);



namespace agdk
{

namespace impl
{

/// <summary>
/// Implements templated two dimensional vector arithmetic class.
/// </summary>
template <typename _Ty>
class BaseVector2
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

	// This is basic component of a Vector2.
	ValueType x, y;

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector2"/> class.
	/// </summary>
	constexpr BaseVector2()
		: x{ 0 }, y{ 0 }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector2"/> class.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	constexpr BaseVector2(ValueType const x_, ValueType const y_)
		: x{ x_ }, y{ y_ }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector2"/> class.
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	constexpr BaseVector2(BaseVector2<ValueType> const &rhs_)
		: x{ rhs_.x },
		y{ rhs_.y }
	{
	}
			
	/// <summary>
	/// Sets values of the vector.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	constexpr void set(ValueType const x_, ValueType const y_)
	{
		x = static_cast<ValueType>(x_);
		y = static_cast<ValueType>(y_);
	}
			
	/// <summary>
	/// Returns length of the vector.
	/// </summary>
	/// <returns>Length of the vector.</returns>
	template <typename _LenTy = ValueType,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_LenTy> > >
	constexpr _LenTy length() const
	{
		if constexpr(std::is_same_v<_LenTy, ValueType>)
			return std::sqrt(x * x + y * y);
		else
		{
			auto conv = this->template convert<_LenTy>();
			return std::sqrt(conv.x * conv.x + conv.y * conv.y);
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
			return x * x + y * y;
		else
		{
			auto conv = this->template convert<_LenTy>();
			return static_cast<_LenTy>(conv.x * conv.x + conv.y * conv.y);
		}
	}

	/// <summary>
	/// Computes distance between two instances.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Distance between two instances.</returns>
	template <typename _DistTy = ValueType,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_DistTy> > >
	constexpr _DistTy distance(BaseVector2<ValueType> const & other_) const
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
	constexpr _DistTy distanceSquared(BaseVector2<ValueType> const & other_) const
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
	constexpr _DotTy dot(BaseVector2<ValueType> const & other_) const
	{
		if constexpr(std::is_same_v<_DotTy, ValueType>)
			return x * other_.x + y * other_.y;
		else
		{
			auto convThis = this->template convert<_DotTy>();
			auto convOther = other_->template convert<_DotTy>();

			return static_cast<_DotTy>(
				convThis.x * convOther.x + convThis.y * convOther.y
			);
		}
	}

	/// <summary>
	/// Computes cross product of two vectors (this and rhs).
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Cross product of two vectors.</returns>
	template <typename _CrossTy,
		typename = std::enable_if_t< is_noncvref_mathscalar_v<_CrossTy> > >
	constexpr _CrossTy cross(BaseVector2<ValueType> const & other_) const
	{
		if constexpr(std::is_same_v<_CrossTy, ValueType>)
			return x * other_.y + y * other_.x;
		else
		{
			auto convThis = this->template convert<_CrossTy>();
			auto convOther = other_->template convert<_CrossTy>();

			return static_cast<_CrossTy>(
				convThis.x * convOther.y + convThis.y * convOther.x
			);
		}
	}

	/// <summary>
	/// Computes reflection vector of specified normal.
	/// </summary>
	/// <param name="normal_">The surface normal.</param>
	/// <returns>Reflection vector of specified normal</returns>
	constexpr BaseVector2<ValueType> reflect(BaseVector2<ValueType> const & normal_) const
	{
		auto normal = normal_.normalize();
		return (*this) - (normal * normal.dot(*this) * ValueType{ 2 });
	}
			
	/// <summary>
	/// Computes reflection vector of specified normal and assigns it to self.
	/// </summary>
	/// <param name="normal_">The normal.</param>
	/// <returns>Reference to self after computing reflection of specified normal.</returns>	
	constexpr BaseVector2<ValueType>& reflectSelf(BaseVector2<ValueType> const & normal_)
	{
		auto normal = normal_.normalize();
		*this -= normal * normal.dot(*this) * ValueType{ 2 };
		return *this;
	}
			
	/// <summary>
	/// Computes normalized vector.
	/// </summary>
	/// <returns>Normalized vector</returns>
	constexpr BaseVector2<ValueType> normalize() const
	{
		auto len = this->template length<ValueType>();
		if (len != 0)
		{
			return BaseVector2<ValueType>{ x / len, y / len };
		}
		return *this;
	}
			
	/// <summary>
	/// Normalizes self and returns reference.
	/// </summary>
	/// <returns>Reference to normalized self.</returns>
	constexpr BaseVector2<ValueType>& normalizeSelf()
	{
		auto len = this->template length<ValueType>();
		if (len != 0)
		{
			x /= len; y /= len;
		}
		return *this;
	}

	/* yet non-constexpr */	
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
		case VectorStringBuilder::Wrap::Round:		{ stream << "( "; break; }
		case VectorStringBuilder::Wrap::Square:	{ stream << "[ "; break; }
		case VectorStringBuilder::Wrap::Curly:		{ stream << "{ "; break; }
		default: break;
		}

		if (setup_.mantissaFixed)
			stream << std::fixed;
		
		stream.precision(setup_.precision);

		switch (setup_.compVisibility)
		{
		case VectorStringBuilder::CompVisibility::WithColon: {
			stream	<< "x: " << x << setup_.separator << ' '
					<< "y: " << y;
			break;
		}
		case VectorStringBuilder::CompVisibility::WithEqual: {
			stream	<< "x = " << x << setup_.separator << ' '
					<< "y = " << y;
			break;
		}
		default: {
			stream << x << setup_.separator << ' ' << y;
			break;
		}
		}

		switch (setup_.wrap)
		{
		case VectorStringBuilder::Wrap::Round:		{ stream << " )"; break; }
		case VectorStringBuilder::Wrap::Square:	{ stream << " ]"; break; }
		case VectorStringBuilder::Wrap::Curly:		{ stream << " }"; break; }
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
	template <typename _Ty2, typename _EqTy = ValueType,
				typename = std::enable_if_t< std::is_floating_point_v<_EqTy> > >
	constexpr bool equals(BaseVector2<_Ty2> const & other_, _EqTy const equalityTolerance_ = Math::Tolerance<_EqTy>::Low) const
	{
		return (
			std::abs(static_cast<_EqTy>(x) - static_cast<_EqTy>(other_.x)) <= equalityTolerance_ &&
			std::abs(static_cast<_EqTy>(y) - static_cast<_EqTy>(other_.y)) <= equalityTolerance_
		);
	}

	/// <summary>
	/// Computes lower bound vector of the two specified.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Vector with components { x = min(lhs_.x, rhs_.x), y = min(lhs_.y, rhs_.y) }</returns>
	constexpr static BaseVector2<ValueType> lowerBounds(BaseVector2<ValueType> const & lhs_, BaseVector2<ValueType> const & rhs_)
	{
		return BaseVector2<ValueType>{
			std::min(lhs_.x, rhs_.x),
			std::min(lhs_.y, rhs_.y)
		};
	}

	/// <summary>
	/// Computes upper bound vector of the two specified.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Vector with components { x = max(lhs_.x, rhs_.x), y = max(lhs_.y, rhs_.y) }</returns>
	constexpr static BaseVector2<_Ty> upperBounds(BaseVector2<ValueType> const & lhs_, BaseVector2<ValueType> const & rhs_)
	{
		return BaseVector2<ValueType>{
			std::max(lhs_.x, rhs_.x),
			std::max(lhs_.y, rhs_.y)
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
	constexpr static void bounds(BaseVector2<ValueType> & lower_, BaseVector2<ValueType> & upper_)
	{
		BaseVector2<ValueType> tempMin = lower_;
		lower_ = BaseVector2<ValueType>::lowerBounds(lower_, upper_);
		upper_ = BaseVector2<ValueType>::upperBounds(tempMin, upper_);
	}
			
	/// <summary>
	/// Converts vector to other type.
	/// </summary>
	/// <returns>Vector of other value type.</returns>
	template <typename _Ty2>
	constexpr BaseVector2<_Ty2> convert() const {
		return BaseVector2<_Ty2>{
			static_cast<_Ty2>(x),
			static_cast<_Ty2>(y)
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
	constexpr BaseVector2<ValueType> & operator = (BaseVector2<ValueType> const & rhs_) {
		x = rhs_.x;
		y = rhs_.y;
		return *this;
	}
			
	/// <summary>
	/// Negates vector.
	/// </summary>
	/// <returns>Negated vector.</returns>
	constexpr BaseVector2<ValueType> operator - () const {
		return BaseVector2<ValueType>{-x, -y};
	}

	/// <summary>
	/// Checks if lhs vector is equal to rhs vector (with low tolerance).
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	/// <returns>
	///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename _Ty2>
	constexpr bool operator == (BaseVector2<_Ty2> const & rhs_) const {
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
	constexpr bool operator != (BaseVector2<_Ty2> const & rhs_) const {
		return !equals(rhs_);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr BaseVector2<ValueType>& operator += (BaseVector2<ValueType> const & rhs_)
	{
		x += rhs_.x;
		y += rhs_.y;
		return *this;
	}

	/// <summary>
	/// Subtracts rhs vector from lhs one.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self after operation.</returns>
	template <typename _Ty2>
	constexpr BaseVector2<ValueType>& operator -= (BaseVector2<ValueType> const & rhs_) {
		x -= rhs_.x;
		y -= rhs_.y;
		return *this;
	}

	/// <summary>
	/// Multiplies two vectors.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	template <typename _Ty2>
	constexpr BaseVector2<ValueType>& operator *= (BaseVector2<ValueType> const & rhs_) {
		x *= rhs_.x;
		y *= rhs_.y;
		return *this;
	}

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr BaseVector2<ValueType>& operator /= (BaseVector2<ValueType> const & rhs_) {
		x /= rhs_.x;
		y /= rhs_.y;
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds scalar to a vector.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector plus a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator += (ValueType const rhs_) {
		x += rhs_;
		y += rhs_;
		return *this;
	}

	/// <summary>
	/// Substracts scalar from a vector.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector minus a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator -= (ValueType const rhs_) {
		x -= rhs_;
		y -= rhs_;
		return *this;
	}

	/// <summary>
	/// Multiplies vector by a scalar.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector times a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator *= (ValueType const rhs_) {
		x *= rhs_;
		y *= rhs_;
		return *this;
	}

	/// <summary>
	/// Divides vector by a scalar.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector divided by a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator /= (ValueType const rhs_) {
		x /= rhs_;
		y /= rhs_;
		return *this;
	}
};

} // namespace impl

} // namespace agdk

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator + (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_)
{
	return {
		lhs_.x + rhs_.x,
		lhs_.y + rhs_.y
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator - (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_)
{
	return {
		lhs_.x - rhs_.x,
		lhs_.y - rhs_.y
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator * (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_)
{
	return {
		lhs_.x * rhs_.x,
		lhs_.y * rhs_.y
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator / (agdk::impl::BaseVector2<_Ty> const & lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_)
{
	return {
		lhs_.x / rhs_.x,
		lhs_.y / rhs_.y
	};
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs vector <op> rhs scalar).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator + (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x + rhs_,
		lhs_.y + rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator - (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x - rhs_,
		lhs_.y - rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator * (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x * rhs_,
		lhs_.y * rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator / (agdk::impl::BaseVector2<_Ty> const & lhs_, _Ty const rhs_)
{
	return {
		lhs_.x / rhs_,
		lhs_.y / rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs scalar <op> rhs vector).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator + (_Ty const lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_)
{
	return {
		rhs_.x + lhs_,
		rhs_.y + lhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename _Ty>
constexpr agdk::impl::BaseVector2<_Ty> operator * (_Ty const lhs_, agdk::impl::BaseVector2<_Ty> const & rhs_)
{
	return {
		rhs_.x * lhs_,
		rhs_.y * lhs_
	};
}
