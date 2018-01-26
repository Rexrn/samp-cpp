// File description:
// Implements useful mathematic functions and classes such as 2D and 3D vectors and Length class.
#pragma once

// Precompiled header:
#include "../../../stdafx.h"

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
}

#include "Math/Vector2.inl"
#include "Math/Vector3.inl"
#include "Math/Length.inl"
