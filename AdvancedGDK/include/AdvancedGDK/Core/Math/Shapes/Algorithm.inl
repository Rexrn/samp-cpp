// Note: this file is not meant to be included on its own.
// Include "Algorithm.hpp" instead.

namespace agdk::math
{

///////////////////////////////////////////////////////////////////////////////////////
template <template <typename> typename T, typename V>
bool areIntersecting(Box<T, V> const & left_, Box<T, V> const & right_)
{
	auto intersectDist = left_.getHalfExtent() + right_.getHalfExtent();
	auto diff = (left_.center - right_.center).absolute();

	for (std::size_t i = 0; i < diff.size(); i++) {
		if (diff[i] >= intersectDist[i])
			return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////
template <template <typename> typename T, typename V>
bool areIntersecting(Ball<T, V> const & left_, Ball<T, V> const & right_)
{
	auto distanceSq = left_.center.distanceSquared(right_.center);
	auto radiiSum = left_.getRadius() + right_.getRadius();

	return (distanceSq < radiiSum * radiiSum);
}

}
