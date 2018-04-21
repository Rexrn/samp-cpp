#pragma once

#include "Box.hpp"
#include "Ball.hpp"

namespace agdk::math
{

/// <summary>
/// Checks whether two boxes intersect.
/// </summary>
/// <param name="left_">The first box.</param>
/// <param name="right_">The second box.</param>
/// <returns>
///		<c>true</c> if boxes intersect; otherwise <c>false</c>
/// </returns>
template <template <typename> typename T, typename V>
bool areIntersecting(Box<T, V> const & left_, Box<T, V> const & right_);

/// <summary>
/// Checks whether two balls intersect.
/// </summary>
/// <param name="left_">The first ball.</param>
/// <param name="right_">The second ball.</param>
/// <returns>
///		<c>true</c> if balls intersect; otherwise <c>false</c>
/// </returns>
template <template <typename> typename T, typename V>
bool areIntersecting(Ball<T, V> const & left_, Ball<T, V> const & right_);

}

#include "Algorithm.inl"
