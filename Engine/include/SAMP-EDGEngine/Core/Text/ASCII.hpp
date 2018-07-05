#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Core/TypeTraits.hpp>
#include <SAMP-EDGEngine/Core/Text/Essentials.hpp>

namespace samp_edgengine::text::ascii
{

/// <summary>
/// Determines whether the specified character is a whitespace.
/// </summary>
/// <param name="character_">The character.</param>
/// <returns>
///		<c>true</c> if the specified character is whitespace; otherwise, <c>false</c>.
/// </returns>
template <typename TChar,
	typename = std::enable_if_t< type_traits::isCharacterV<TChar> > >
bool isSpace(TChar character_);

/// <summary>
/// Converts single ASCII character to lower case ('A' => 'a').
/// </summary>
/// <param name="character_">The character.</param>
/// <returns>Lower case representation of the character.</returns>
template <typename TChar,
	typename = std::enable_if_t< type_traits::isCharacterV<TChar> > >
char toLower(TChar character_);

/// <summary>
/// Converts ASCII std::string to lower case ("ABC" => "abc").
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>Lower case representation of the string.</returns>
std::string toLower(std::string_view const string_);

/// <summary>
/// Converts single ASCII character to upper case ('a' => 'A').
/// </summary>
/// <param name="character_">The character.</param>
/// <returns>Upper case representation of the character.</returns>
template <typename TChar,
	typename = std::enable_if_t< type_traits::isCharacterV<TChar> > >
char toUpper(TChar character_);

/// <summary>
/// Converts ASCII std::string to upper case ("abc" => "ABC").
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>Upper case representation of the string.</returns>
std::string toUpper(std::string_view const string_);

/// <summary>
/// Checks if specified characters are equal.
/// </summary>
/// <param name="lhs_">The left character.</param>
/// <param name="rhs_">The right character.</param>
/// <returns>
///		<c>true</c> if equal; otherwise, <c>false</c>.
/// </returns>
template <CaseSensitivity _caseSensitivity = CaseSensitive, typename TChar,
	typename = std::enable_if_t< type_traits::isCharacterV<TChar> > >
bool equal(TChar lhs_, TChar rhs_);

/// <summary>
/// Checks if specified ranges of characters are equal.
/// </summary>
/// <param name="begin1_">The start iterator of the first string.</param>
/// <param name="end1_">The end iterator of the first string.</param>
/// <param name="begin2_">The start iterator of the second string.</param>
/// <param name="end2_">The end iterator of the second string.</param>
/// <returns>
///		<c>true</c> if characters in range [begin1_, end1_) is equal to characters in range [begin2_, end2_); otherwise, <c>false</c>.
/// </returns>
template <CaseSensitivity _caseSensitivity = CaseSensitive, typename InputIt1, typename InputIt2>
bool equal(InputIt1 begin1_, InputIt1 end1_, InputIt2 begin2_, InputIt2 end2_);

/// <summary>
/// Checks if specified strings are equal.
/// </summary>
/// <param name="lhs">The left hand side string.</param>
/// <param name="rhs">The right hand side string.</param>
/// <returns>
///		<c>true</c> if lhs string is equal to rhs string; otherwise, <c>false</c>.
/// </returns>
template <CaseSensitivity _caseSensitivity = CaseSensitive>
bool equal(std::string_view const lhs_, std::string_view const rhs_);

/// <summary>
/// Trims std::string whitespaces from the front side.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>Trimmed string.</returns>
std::string trimLeft(std::string_view const string_);

/// <summary>
/// Trims std::string whitespaces from the front side.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>Trimmed string.</returns>
std::string trimRight(std::string_view const string_);

/// <summary>
/// Trims std::string whitespaces.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>Trimmed string.</returns>
std::string	trim(std::string_view const string_);

/// <summary>
/// Removes whitespaces from std::string.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>String without whitespaces.</returns>
std::string removeSpaces(std::string_view const string_);

/// <summary>
/// Replaces every `from_` to `to_` in `subject`
/// </summary>
/// <param name="subject">The subject.</param>
/// <param name="from">String to replace.</param>
/// <param name="to">String to insert.</param>
/// <returns>
/// Subject with replaced every `from_` to `to_`.
/// </returns>	
std::string replaceAll(std::string_view const target_, std::string_view const from_, std::string_view const to_);

/// <summary>
/// Counts all occurences of `sequence_` in `subject_`.
/// </summary>
/// <param name="subject_">The subject.</param>
/// <param name="sequence_">The sequence.</param>
/// <returns>Number of occurences.</returns>
std::string::size_type count(std::string_view const subject_, std::string_view const sequence_);

/// <summary>
/// Checks whether specified string contains value of TTestType inside.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>
///		<c>true</c> if string contains boolean; otherwise, <c>false</c>.
/// </returns>
template <typename TTestType>
bool stores(std::string_view const string_);

/// <summary>
/// Checks whether specified string contains boolean inside.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>
///		<c>true</c> if string contains boolean; otherwise, <c>false</c>.
/// </returns>
bool storesBoolean(std::string_view const string_);
/// <summary>
/// Checks whether specified string contains integer inside.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>
///		<c>true</c> if string contains integer; otherwise, <c>false</c>.
/// </returns>
template <typename TIntegerType = std::intmax_t,
	typename = std::enable_if_t< std::is_integral_v<TIntegerType> > >
bool storesInteger(std::string_view const string_);

/// <summary>
/// Checks whether specified string contains real number inside.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>
///		<c>true</c> if string contains real number; otherwise, <c>false</c>.
/// </returns>
template <typename TFloatType = long double,
	typename = std::enable_if_t< std::is_floating_point_v<TFloatType> > >
bool storesReal(std::string_view const string_);

/// <summary>
/// Returns string converted to specified type if conversion is valid and possible.
/// </summary>
/// <param name="string_">The string.</param>
/// <returns>
///		If possible, string converted to target type; otherwise, empty std::optional.
/// </returns>
template <typename TTargetType>
std::optional<TTargetType> convert(std::string_view const string_);

/// <summary>
/// Searches for maximal sequence [begin2_, end2_) packed inside [begin1_, end1_).
/// </summary>
/// <param name="begin1_">The begin of the first sequence.</param>
/// <param name="end1_">The end of the first sequence.</param>
/// <param name="begin2_">The begin of the searched sequence.</param>
/// <param name="end2_">The end of the searched sequence.</param>
/// <param name="comp_">Binary predicate comparing two elements.</param>
/// <returns>
///		Pair of iterators belonging to first container, pointing to the [begin, end) of the sequence (begin = pair::first, end = pair::second).
/// </returns>
template <typename InputIt1, typename InputIt2, typename TCompare>
std::pair<InputIt1, InputIt1> searchWithIncomplete(InputIt1 begin1_, InputIt1 end1_, InputIt2 begin2_, InputIt2 end2_, TCompare comp_);

/// <summary>
/// Searches for maximal sequence [begin2_, end2_) packed inside [begin1_, end1_).
/// </summary>
/// <param name="begin1_">The begin of the first sequence.</param>
/// <param name="end1_">The end of the first sequence.</param>
/// <param name="begin2_">The begin of the searched sequence.</param>
/// <param name="end2_">The end of the searched sequence.</param>
/// <returns>
///		Pair of iterators belonging to first container, pointing to the [begin, end) of the sequence (begin = pair::first, end = pair::second).
/// </returns>
/// <remarks>
///		<para>Uses default `operator==` to compare two values.</para>
/// </remarks>
template <CaseSensitivity _caseSensitivity = CaseSensitive, typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt1> searchWithIncomplete(InputIt1 begin1_, InputIt1 end1_, InputIt2 begin2_, InputIt2 end2_);

/// <summary>
/// Searches for maximal sequence stored in `searchFor_` inside `searchIn_`.
/// </summary>
/// <param name="searchIn_">Sequence algorithm will search in.</param>
/// <param name="searchFor_">Sequence algorithm will search for.</param>
/// <returns>
///		Pair of indices creating [begin, end) of the sequence (begin = pair::first, end = pair::second).
///		It guaranteed that begin <= end. Both indices are equal to `searchIn_.size()` if not found.
/// </returns>
template <CaseSensitivity _caseSensitivity = CaseSensitive>
std::pair<std::string_view::size_type, std::string_view::size_type> searchWithIncomplete(std::string_view const searchIn_, std::string_view const searchFor_);

/// <summary>
/// Searches for maximal sequence stored in `searchFor_` inside `searchIn_`.
/// </summary>
/// <param name="searchIn_">Sequence algorithm will search in.</param>
/// <param name="searchFor_">Sequence algorithm will search for.</param>
/// <returns>
///		Pair of iterators belonging to first container, pointing to the [begin, end) of the sequence (begin = pair::first, end = pair::second).
/// </returns>
template <CaseSensitivity _caseSensitivity = CaseSensitive>
std::pair<std::string::const_iterator, std::string::const_iterator> searchWithIncomplete(std::string const & searchIn_, std::string const & searchFor_);

/// <summary>
/// Composes string of passed parameters.
/// </summary>
/// <returns>String composed of passed parameters.</returns>
/// <remarks>
/// <para>This function is equivalent to:
///		<code>
///		std::stringstream stream;
///		stream << param_1 << param_2 << param_3 << ... << param_n;
///		std::string result = stream.str();
///		</code>
/// </para>
/// </remarks>
template <typename TFirstArg, typename... TRestArgs>
std::string compose(TFirstArg && first_, TRestArgs &&... rest_);

} // namespace


// Include file that contains definition.
#include "ASCII.inl"