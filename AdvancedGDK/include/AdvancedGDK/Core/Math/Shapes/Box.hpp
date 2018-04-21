#pragma once

#include "../Vector2.hpp"
#include "../Vector3.hpp"

namespace agdk::math
{

/// <summary>
/// A box shape (a cuboid or rectangle).
/// </summary>
template <template <typename> typename TVectorType, typename TValueType>
struct Box
{	
	// Aliases:
	using ValueType		= TValueType;
	using VectorType	= TVectorType<ValueType>;

	// Methods:
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	Box() = default;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	/// <param name="center_">The center.</param>
	/// <param name="halfExtent_">The half extent.</param>
	Box(VectorType const & center_, VectorType const & halfExtent_)
		: center{ center_ }, m_halfExtent{ halfExtent_ }
	{
	}
	
	/// <summary>
	/// Sets the box full extent.
	/// </summary>
	/// <param name="extent_">The extent.</param>
	void setExtent(VectorType const & extent_)
	{
		m_halfExtent = extent_.absolute() / static_cast<ValueType>( 2 );
	}
	
	/// <summary>
	/// Sets the box half extent.
	/// </summary>
	/// <param name="halfExtent_">The half extent.</param>
	void setHalfExtent(VectorType const & halfExtent_)
	{
		m_halfExtent = halfExtent_.absolute();
	}
	
	/// <summary>
	/// Returns box full extent.
	/// </summary>
	/// <returns>Box full extent.</returns>
	VectorType getExtent() const
	{
		return m_halfExtent * static_cast<ValueType>( 2 );
	}

	/// <summary>
	/// Returns box half extent.
	/// </summary>
	/// <returns>Box half extent.</returns>
	VectorType getHalfExtent() const
	{
		return m_halfExtent;
	}

	VectorType center;
private:
	VectorType m_halfExtent;
};

template <typename TValueType>
using Rect		= Box<Vector2, TValueType>;

template <typename TValueType>
using Cuboid	= Box<Vector3, TValueType>;

using RectF		= Rect<float>;
using RectD		= Rect<double>;
using RectI8	= Rect<std::int8_t>;
using RectI16	= Rect<std::int16_t>;
using RectI32	= Rect<std::int32_t>;
using RectI64	= Rect<std::int64_t>;
using RectU8	= Rect<std::uint8_t>;
using RectU16	= Rect<std::uint16_t>;
using RectU32	= Rect<std::uint32_t>;
using RectU64	= Rect<std::uint64_t>;

using CuboidF	= Cuboid<float>;
using CuboidD	= Cuboid<double>;
using CuboidI8	= Cuboid<std::int8_t>;
using CuboidI16	= Cuboid<std::int16_t>;
using CuboidI32	= Cuboid<std::int32_t>;
using CuboidI64	= Cuboid<std::int64_t>;
using CuboidU8	= Cuboid<std::uint8_t>;
using CuboidU16	= Cuboid<std::uint16_t>;
using CuboidU32	= Cuboid<std::uint32_t>;
using CuboidU64	= Cuboid<std::uint64_t>;

}
