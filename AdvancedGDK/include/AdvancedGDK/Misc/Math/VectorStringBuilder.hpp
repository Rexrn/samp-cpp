// File description:
// Provides basic StringBuilder setup for Vector classes.
#pragma once

// Precompiled header:
#include "../../../../stdafx.h"

namespace agdk
{

/// <summary>
/// Contains setup for a string conversion: <see cref="BaseVector2::toString">, and <see cref="BaseVector3::toString">.
/// </summary>
struct VectorStringBuilder final {
	enum class Wrap {
		None,
		Round,
		Square,
		Curly
	} wrap = Wrap::Round;

	enum class CompVisibility {
		None,
		WithColon,
		WithEqual
	} compVisibility = CompVisibility::None;

	unsigned char	separator = ',';

	std::uint8_t	precision = 3;
	const bool		mantissaFixed = true;

	/// <summary>
	/// Initializes a new instance of the <see cref="VectorStringBuilder"/> struct.
	/// </summary>
	constexpr VectorStringBuilder() {}

	/// <summary>
	/// Initializes a new instance of the <see cref="VectorStringBuilder"/> struct.
	/// </summary>
	/// <param name="wrap_">The wrap setting.</param>
	/// <param name="comp_">The component setting.</param>
	/// <param name="separator_">The separator.</param>
	/// <param name="precision_">The precision.</param>
	/// <param name="mantissaFixed_">The mantissa fixed.</param>
	constexpr VectorStringBuilder(Wrap const wrap_, CompVisibility const comp_, unsigned char const separator_, std::uint8_t const precision_, bool const mantissaFixed_)
		: wrap{ wrap_ }, compVisibility{ comp_ }, separator{ separator_ }, precision{ precision_ }, mantissaFixed{ mantissaFixed_ }
	{
	}

	/// <summary>
	/// Returns one of predefined styles.
	/// </summary>
	/// <param name="index_">The style index.</param>
	/// <returns>Predefined style.</returns>
	static constexpr VectorStringBuilder Style(std::size_t const index_) {
		VectorStringBuilder style[]{
			{ Wrap::Curly, CompVisibility::WithColon, ',', 3, false },	// example: { x: 10.245, y: 20 }
			{ Wrap::Curly, CompVisibility::WithEqual, ',', 3, false },	// example: { x = 10.245, y = 20 }
			{ Wrap::Round, CompVisibility::WithColon, ',', 3, false },	// example: ( x: 10.245, y: 20 )
			{ Wrap::Round, CompVisibility::WithEqual, ',', 3, false }	// example: ( x = 10.245, y = 20 )
		};
		return style[index_];
	};
};

} // namespace agdk
