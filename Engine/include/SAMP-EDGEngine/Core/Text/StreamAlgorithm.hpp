#pragma once
#include SAMPEDGENGINE_PCH



namespace samp_cpp::text
{


/// <summary>
/// Check whether next character in std::basic_istream is what expected. Skip it if so; otherwise, set fail flag.
/// </summary>
template <auto _char, typename TCharType = decltype(_char)>
std::basic_istream<TCharType>& skipIf(std::basic_istream<TCharType>& istream_);

/// <summary>
/// Check whether next character in std::basic_istream is what expected. Skip it if so; otherwise, set fail flag.
/// </summary>
template <typename TCharType, TCharType _char>
std::basic_istream<TCharType>& skipIf(std::basic_istream<TCharType>& istream_);


} // namespace

#include "StreamAlgorithm.inl"