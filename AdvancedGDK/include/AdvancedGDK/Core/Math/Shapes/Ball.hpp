#pragma once

#include "../Vector2.hpp"
#include "../Vector3.hpp"

namespace agdk::math
{

/// <summary>
/// A ball shape (a circle or sphere).
/// </summary>
template <template <typename> typename TVectorType, typename TValueType>
struct Ball
{	
	// Aliases:
	using ValueType		= TValueType;
	using VectorType	= TVectorType<ValueType>;

	// Methods:
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	Ball() = default;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	/// <param name="center_">The center.</param>
	/// <param name="radius_">The radius.</param>
	Ball(VectorType const & center_, ValueType const radius_)
		: center{ center_ }, m_radius{ radius_ }
	{
	}
	
	/// <summary>
	/// Sets the ball diameter.
	/// </summary>
	/// <param name="extent_">The ball diameter.</param>
	void setDiameter(ValueType const diameter_)
	{
		m_radius = std::abs(diameter_) / static_cast<ValueType>( 2 );
	}
	
	/// <summary>
	/// Sets the ball radius.
	/// </summary>
	/// <param name="radius_">The ball radius.</param>
	void setRadius(ValueType const radius_)
	{
		m_radius = std::abs( radius_ );
	}
	
	/// <summary>
	/// Returns ball diameter.
	/// </summary>
	/// <returns>Ball diameter.</returns>
	VectorType getDiameter() const
	{
		return m_radius * static_cast<ValueType>( 2 );
	}

	/// <summary>
	/// Returns ball radius.
	/// </summary>
	/// <returns>Ball radius.</returns>
	VectorType getRadius() const
	{
		return m_radius;
	}

	VectorType center;
private:
	ValueType m_radius;
};

template <typename TValueType>
using Circle	= Ball<Vector2, TValueType>;

template <typename TValueType>
using Sphere	= Ball<Vector3, TValueType>;

using CircleF	= Circle<float>;
using CircleD	= Circle<double>;
using CircleI8	= Circle<std::int8_t>;
using CircleI16	= Circle<std::int16_t>;
using CircleI32	= Circle<std::int32_t>;
using CircleI64	= Circle<std::int64_t>;
using CircleU8	= Circle<std::uint8_t>;
using CircleU16	= Circle<std::uint16_t>;
using CircleU32	= Circle<std::uint32_t>;
using CircleU64	= Circle<std::uint64_t>;

using SphereF	= Sphere<float>;
using SphereD	= Sphere<double>;
using SphereI8	= Sphere<std::int8_t>;
using SphereI16	= Sphere<std::int16_t>;
using SphereI32	= Sphere<std::int32_t>;
using SphereI64	= Sphere<std::int64_t>;
using SphereU8	= Sphere<std::uint8_t>;
using SphereU16	= Sphere<std::uint16_t>;
using SphereU32	= Sphere<std::uint32_t>;
using SphereU64	= Sphere<std::uint64_t>;

}