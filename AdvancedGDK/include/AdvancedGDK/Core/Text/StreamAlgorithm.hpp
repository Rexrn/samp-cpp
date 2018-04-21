#pragma once

#include ADVANCEDGDK_PCH

namespace agdk::text
{

#ifdef __cpp_template_auto
/// <summary>
/// Check whether next character in std::basic_istream is what expected. Skip it if so; otherwise, set fail flag.
/// </summary>
template <auto _char, typename TCharType = decltype(_char)>
std::basic_istream<TCharType>& skipIf(std::basic_istream<TCharType>& istream_);

#else

#ifdef _MSC_VER
#pragma message("Your compiler does not support auto as non-type template parameter.")
#elif defined (__GNUC__) defined(__cplusplus)
#warning "Your compiler does not support auto as non-type template parameter."
#endif

template <typename TCharType, TCharType _char>
std::basic_istream<TCharType>& skipIf(std::basic_istream<TCharType>& istream_);

#endif

} // namespace

#include "StreamAlgorithm.inl"