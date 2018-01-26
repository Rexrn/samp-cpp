// File description:
// Implements helper class for String manipulation.
#pragma once

// Precompiled header:
#include "../../../stdafx.h"

namespace agdk
{
	/// <summary>
	/// If character in std::istream is what expected skip this character else set fail flag.
	/// </summary>
	template <char C>
	std::istream& expect(std::istream& in)		// TODO: move this function to other file.
	{
		if ((in >> std::ws).peek() == C) {
			in.ignore();
		}
		else {
			in.setstate(std::ios_base::failbit);
		}
		return in;
	}
	
	/// <summary>
	/// Creates string from passed parameters.
	/// </summary>
	/// <returns>String created from passed parameters.</returns>
	/// <remarks>
	/// <para>This function is equivalent to:
	///		<code>
	///		std::stringstream stream;
	///		stream << param_1 << param_2 << param_3 << ... << param_n;
	///		std::string result = stream.str();
	///		</code>
	/// </para>
	/// </remarks>
	template <typename TFirst, typename... TRest>
	inline std::string make_string(TFirst &&first_, TRest&&... rest_)
	{
		std::stringstream stream;
		stream << std::forward<TFirst>(first_);
		(stream << ... << std::forward<TRest>(rest_));
		return stream.str();
	}

	/// <summary>
	/// Helper static class for manipulating strings.
	/// </summary>
	class StringHelper
	{		
		/// <summary>
		/// Prevents instance of the <see cref="StringHelper"/> class from being created.
		/// </summary>
		StringHelper() = delete;
	public:
		
		/// <summary>
		/// Compares two strings.
		/// </summary>
		/// <param name="lhs">The left hand side string.</param>
		/// <param name="rhs">The right hand side string.</param>
		/// <param name="caseSensitive_">Case sensitive.</param>
		/// <returns>True if lhs string is equal to rhs string.</returns>
		static bool equals(const std::string_view lhs, const std::string_view rhs, const bool caseSensitive_ = true);

		/// <summary>
		/// Trims std::string whitespaces from the front side.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns>Trimmed string.</returns>
		static std::string	trimLeft(std::string string_);

		/// <summary>
		/// Trims std::string whitespaces from the back side.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns>Trimmed string.</returns>
		static std::string	trimRight(std::string string_);

		/// <summary>
		/// Trims std::string whitespaces.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns>Trimmed string.</returns>
		static std::string	trim(std::string string_);

		/// <summary>
		/// Converts std::string to lowercase.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns>Lowercased string.</returns>
		static std::string	toLower(std::string string_);

		/// <summary>
		/// Converts std::string to UPPERCASE.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns>UPPERCASED string.</returns>
		static std::string	toUpper(std::string string_);
		
		/// <summary>
		/// Removes whitespaces from std::string.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns>String without whitespaces.</returns>
		static std::string	removeSpaces(std::string string_);

		/// <summary>
		/// Replaces every `from_` to `to_` in `subject`
		/// </summary>
		/// <param name="subject">The subject.</param>
		/// <param name="from">String to replace.</param>
		/// <param name="to">String to insert.</param>
		/// <returns>
		/// Subject with replaced every `from_` to `to_`.
		/// </returns>	
		static std::string	replace(std::string subject_, const std::string& from_, const std::string& to_);
		
		/// <summary>
		/// Counts all occurences of `sequence_` in `subject_`.
		/// </summary>
		/// <param name="subject_">The subject.</param>
		/// <param name="sequence_">The sequence.</param>
		/// <returns>Number of occurences.</returns>
		static std::size_t	count(const std::string_view subject_, const std::string &sequence_);
		
		/// <summary>
		/// Converts string to boolean.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns>String converted to boolean.</returns>
		static bool			toBoolean(const std::string_view string_, const bool valueIfNotValid = false);

		/// <summary>
		/// Checks if string stores integer inside.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <param name="unsigned_">If set to <c>true</c> only unsigned values will be taken into consideration.</param>
		/// <returns>
		/// <c>true</c> if string stores integer, otherwise <c>false</c>.
		/// </returns>
		static bool			storesInteger(const std::string_view string_, const bool unsigned_ = false);

		/// <summary>
		/// Checks if string stores floating point inside.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <param name="separator_">The floating point separator.</param>
		/// <returns><c>true</c> if string stores float, otherwise <c>false</c>.</returns>
		/// <remarks>
		/// <para>This function does exactly the same as <see cref="storesNumber"/>.</para>
		/// </remarks>
		static bool			storesFloat(const std::string_view string_, const std::string::value_type separator_ = '.');

		/// <summary>
		/// Checks if string stores boolean inside.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <returns><c>true</c> if string stores boolean, otherwise <c>false</c>.</returns>
		static bool			storesBoolean(const std::string_view string_);
		
		/// <summary>
		/// Checks if string stores number inside.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <param name="separator_">The floating point separator.</param>
		/// <returns><c>true</c> if string stores number, otherwise <c>false</c>.</returns>
		static bool			storesNumber(const std::string_view string_, const std::string::value_type separator_ = '.');

		template <typename _Ty>
		using remove_cvref_t = std::remove_reference_t< std::remove_cv_t<_Ty> >;

#ifdef _AGDK_FS_STRINGHELPER_TO_CXX17FROMCHARS
		/// <summary>
		/// Returns string converted to specified type (as template).
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <param name="valueIfNotValid_">The value if cast is not valid.</param>
		/// <returns>String converted to specified type (as template).</returns>
		template <typename _Ty>
		static remove_cvref_t<_Ty> to(const std::string_view string_, remove_cvref_t<_Ty> valueIfNotValid_ = _Ty{})
		{
			using RawT = remove_cvref_t<_Ty>;	// remove references and constness/volatility
			if constexpr(std::is_same_v<RawT,	bool>)
			{
				return static_cast<RawT>(StringHelper::storesBoolean(string_) ? StringHelper::toBoolean(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		std::int16_t>)
			{
				std::int16_t resultValue;
				return static_cast<RawT>(StringHelper::storesInteger(string_) ? std::from_chars(string_.data(), string_.data() + string_.size(), resultValue) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		std::int32_t>)
			{
				std::int32_t resultValue;
				return static_cast<RawT>(StringHelper::storesInteger(string_) ? std::from_chars(string_.data(), string_.data() + string_.size(), resultValue) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		std::int64_t>)
			{
				std::int64_t resultValue;
				return (StringHelper::storesInteger(string_) ? std::stoll(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		std::uint16_t>)
			{
				std::uint16_t resultValue;
				return (StringHelper::storesInteger(string_) ? std::from_chars(string_.data(), string_.data() + string_.size(), resultValue) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		std::uint32_t>)
			{
				std::uint32_t resultValue;
				return (StringHelper::storesInteger(string_) ? std::from_chars(string_.data(), string_.data() + string_.size(), resultValue) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		std::uint64_t>)
			{
				std::uint64_t resultValue;
				return (StringHelper::storesInteger(string_) ? std::from_chars(string_.data(), string_.data() + string_.size(), resultValue) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		char>
							|| std::is_same_v<RawT,		unsigned char>
							|| std::is_same_v<RawT,		signed char>)
			{
				return static_cast<RawT>(!string_.empty() ? string_[0] : valueIfNotValid_);
			}
			else if constexpr(std::is_same_v<RawT,		float>)
			{
				return (StringHelper::storesFloat(string_) ? std::stof(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		double>)
			{
				return (StringHelper::storesFloat(string_) ? std::stod(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT,		long double>)
			{
				return (StringHelper::storesFloat(string_) ? std::stold(string_) : valueIfNotValid_);
			}
			else
				return valueIfNotValid_;
		}
#else
		/// <summary>
		/// Returns string converted to specified type (as template).
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <param name="valueIfNotValid_">The value if cast is not valid.</param>
		/// <returns>String converted to specified type (as template).</returns>
		template <typename _Ty>
		static remove_cvref_t<_Ty> to(const std::string & string_, remove_cvref_t<_Ty> valueIfNotValid_ = _Ty{})
		{
			using RawT = remove_cvref_t<_Ty>;	// remove references and constness/volatility
			if constexpr(std::is_same_v<RawT, bool>)
			{
				return static_cast<RawT>(StringHelper::storesBoolean(string_) ? StringHelper::toBoolean(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, std::int16_t>)
			{
				return static_cast<RawT>(StringHelper::storesInteger(string_) ? std::stoi(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, std::int32_t>)
			{
				return static_cast<RawT>(StringHelper::storesInteger(string_) ? std::stol(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, std::int64_t>)
			{
				return (StringHelper::storesInteger(string_) ? std::stoll(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, std::uint16_t>)
			{
				return static_cast<RawT>(StringHelper::storesInteger(string_) ? std::stoul(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, std::uint32_t>)
			{
				return static_cast<RawT>(StringHelper::storesInteger(string_) ? std::stoul(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, std::uint64_t>)
			{
				return (StringHelper::storesInteger(string_) ? std::stoull(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, char>
							|| std::is_same_v<RawT, unsigned char>
							|| std::is_same_v<RawT, signed char>)
			{
				return static_cast<RawT>(!string_.empty() ? string_[0] : valueIfNotValid_);
			}
			else if constexpr(std::is_same_v<RawT, float>)
			{
				return (StringHelper::storesFloat(string_) ? std::stof(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, double>)
			{
				return (StringHelper::storesFloat(string_) ? std::stod(string_) : valueIfNotValid_);
			}
			else if constexpr (std::is_same_v<RawT, long double>)
			{
				return (StringHelper::storesFloat(string_) ? std::stold(string_) : valueIfNotValid_);
			}
			else
				return valueIfNotValid_;
		}
#endif
		
		/// <summary>
		/// Checks length of maximum sequence length from `sequence_` in `string_`.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <param name="sequence_">The sequence.</param>
		/// <param name="caseSensitive">Case sensitive.</param>
		/// <returns>
		/// Maximum sequence length found in `string_`.
		/// </returns>
		static std::size_t	maxSequenceLength(const std::string_view string_, const std::string_view sequence_, const bool caseSensitive = true);
		
		/// <summary>
		/// Explodes std::string into array of std::string using a separator.
		/// </summary>
		/// <param name="string_">The string.</param>
		/// <param name="delimiter_">The delimiter.</param>
		/// <returns>Dynamic array (std::vector) containing parts of splitted string.</returns>
		static std::vector<std::string> explode(const std::string_view string_, const std::string::value_type delimiter_);
		
		/* This code is deprecated, C++17 includes <filesystem> library.
			/// <summary>
			/// Splits the path.
			/// </summary>
			/// <param name="fullPath">The full path.</param>
			/// <returns>Pair of paths: pair.first = directory, pair.second = filename.</returns>
			static std::pair<std::string, std::string> splitPath(const std::string &fullPath);
		*/
	};
}