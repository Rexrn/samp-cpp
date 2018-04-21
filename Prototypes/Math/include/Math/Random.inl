// Note: this file is not meant to be included on its own.
// Include "Random.hpp" instead.

namespace agdk::math::random
{

//////////////////////////////////////////////////////////////////////////////
template <typename TType>
inline TType generate(TType const & from_, TType const & to_)
{
	// Check at compile time if the type is an integer.
	constexpr bool cxIsIntegerType = std::is_same_v<TType, short> || std::is_same_v<TType, unsigned short>
		|| std::is_same_v<TType, int> || std::is_same_v<TType, unsigned int>
		|| std::is_same_v<TType, long> || std::is_same_v<TType, unsigned long>
		|| std::is_same_v<TType, long long> || std::is_same_v<TType, unsigned long long>;

	// Check at compile time if the type is a floating point number.
	constexpr bool cxIsFloatType = std::is_same_v<TType, float> || std::is_same_v<TType, double> || std::is_same_v< TType, long double>;

	// Check if the type require 64 bit engine or not.
	constexpr bool cxCanUse32BitEngine = sizeof(TType) <= 4;

	// Assert compilation, when type is not supported.
	static_assert(cxIsIntegerType || cxIsFloatType, "agdk::math::random does not support this type.");

	// Calculate min and max value:
	auto[minValue, maxValue] = std::minmax(static_cast<TType>(from_), static_cast<TType>(to_));


	// For every integer type:
	if constexpr(cxIsIntegerType)
	{
		if constexpr(cxCanUse32BitEngine)
			return std::uniform_int_distribution<TType>(minValue, maxValue)(detail::getGenerator());
		else
			return std::uniform_int_distribution<TType>(minValue, maxValue)(detail::getGenerator64());
	}
	else // For every real (floating point) type:
	{
		if constexpr(cxCanUse32BitEngine)
			return std::uniform_real_distribution<TType>(minValue, maxValue)(detail::getGenerator());
		else
			return std::uniform_real_distribution<TType>(minValue, maxValue)(detail::getGenerator64());
	}
}

}