#pragma once
#include SAMPCPP_PCH




namespace samp_cpp::type_traits
{

template <typename TType>
struct removeCVRef {
	using type = std::remove_reference_t < std::remove_cv_t<TType> >;
};
template <typename TType>
using removeCVRefT = typename removeCVRef<TType>::type;

template <typename TType>
struct isCVRef {
	static constexpr bool value = std::is_same_v<TType, removeCVRefT<TType> >;
};
template <typename TType>
constexpr bool isCVRefV = isCVRef<TType>::value;

template <typename TChar>
struct isCharacter {
	static constexpr bool value = std::is_same_v<TChar, char> || std::is_same_v<TChar, unsigned char> || std::is_same_v<TChar, signed char>;
};
template <typename TChar>
static constexpr bool isCharacterV = isCharacter<TChar>::value;

template<class TNonRatioType>
struct isRatio {
	static constexpr bool value = false;
};

template<intmax_t _ratioNumerator, intmax_t _ratioDenumerator>
struct isRatio<std::ratio<_ratioNumerator, _ratioDenumerator> > {
	static constexpr bool value = true;
};

template<class TNonRatioType>
constexpr bool isRatioV = false;

template<intmax_t _ratioNumerator, intmax_t _ratioDenumerator>
constexpr bool isRatioV<std::ratio<_ratioNumerator, _ratioDenumerator> > = true;

template <typename TType>
struct isMathScalar {
	static constexpr bool value = isCVRefV<TType> && std::is_arithmetic_v<TType> && !std::is_same_v<TType, bool>;
};

template <typename TType>
constexpr bool isMathScalarV = isMathScalar<TType>::value;

}