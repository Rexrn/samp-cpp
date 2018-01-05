/**
 * Header: Math.hpp
 * Author: Pawe³ Syska aka RazzorFlame.
 * Description:
 * Defines constants and includes other parts of Math module.
**/

#pragma once

#include <cmath>
#include <cinttypes>
#include <type_traits>

namespace agdk
{
	namespace Math
	{
		
		template <typename T>
		constexpr T Pi = static_cast<T>(3.14159265358979323846L);
		template <>
		constexpr const char* Pi<const char*> = "Pi";
		

		template <typename T>
		struct Tolerance final
		{
			Tolerance() = delete;

			static constexpr T Low			= T(0.000001L);
			static constexpr T Medium		= T(0.00001L);
			static constexpr T High			= T(0.0001L);
			static constexpr T VeryHigh		= T(0.001L);
		};

		template <typename T>
		inline bool nearlyEqual(const T lhs, const T rhs, const T equalityTolerance = Tolerance<T>::Medium)
		{
			return std::abs(lhs - rhs) <= equalityTolerance;
		}

		template <typename T>
		inline T clamp(const T current, const T a, const T b)
		{
			return max<T>(min<T>(current, b), a);
		}
	}

	namespace impl
	{
		template <typename T> class BaseVector2;
		template <typename T> class BaseVector3;
	}

	// 2D Vector class templated with float
	using Vector2f			= impl::BaseVector2<float>;
	// 2D Vector class templated with float
	using Vector2			= impl::BaseVector2<float>;
	// 2D Vector class templated with double
	using Vector2d			= impl::BaseVector2<double>;
	// 2D Vector class templated with std::int16_t
	using Vector2i16		= impl::BaseVector2<std::int16_t>;
	// 2D Vector class templated with std::int32_t
	using Vector2i32		= impl::BaseVector2<std::int32_t>;
	// 2D Vector class templated with std::int64_t
	using Vector2i64		= impl::BaseVector2<std::int64_t>;
	// 2D Vector class templated with std::uint16_t
	using Vector2ui16		= impl::BaseVector2<std::uint16_t>;
	// 2D Vector class templated with std::uint32_t
	using Vector2ui32		= impl::BaseVector2<std::uint32_t>;
	// 2D Vector class templated with std::uint64_t
	using Vector2ui64		= impl::BaseVector2<std::uint64_t>;

	// 3D Vector class templated with float
	using Vector3f			= impl::BaseVector3<float>;
	// 3D Vector class templated with float
	using Vector3			= impl::BaseVector3<float>;
	// 3D Vector class templated with double
	using Vector3d			= impl::BaseVector3<double>;
	// 3D Vector class templated with std::int16_t
	using Vector3i16		= impl::BaseVector3<std::int16_t>;
	// 3D Vector class templated with std::int32_t
	using Vector3i32		= impl::BaseVector3<std::int32_t>;
	// 3D Vector class templated with std::int64_t
	using Vector3i64		= impl::BaseVector3<std::int64_t>;
	// 3D Vector class templated with std::uint16_t
	using Vector3ui16		= impl::BaseVector3<std::uint16_t>;
	// 3D Vector class templated with std::uint32_t
	using Vector3ui32		= impl::BaseVector3<std::uint32_t>;
	// 3D Vector class templated with std::uint64_t
	using Vector3ui64		= impl::BaseVector3<std::uint64_t>;
}

#include "Math/Vector2.inl"
#include "Math/Vector3.inl"
#include "Math/Length.inl"
