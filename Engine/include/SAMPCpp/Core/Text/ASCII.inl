// Note: this file is not meant to be included on its own.
// Include "ASCII.hpp" instead.

#include "ASCII.hpp"



namespace samp_cpp::text
{

///////////////////////////////////////////////////////////////////////
template <typename TChar, typename>
inline bool isSpace(TChar character_)
{
	return std::isspace(static_cast<unsigned char>(character_));
}

///////////////////////////////////////////////////////////////////////
template <typename TChar, typename>
inline char toLower(TChar character_)
{
	return static_cast<char>(std::tolower(static_cast<unsigned char>(character_)));
}

///////////////////////////////////////////////////////////////////////
template <typename TChar, typename>
inline char toUpper(TChar character_) {
	return static_cast<char>( std::toupper(static_cast<unsigned char>(character_)) );
}

///////////////////////////////////////////////////////////////////////
template <CaseSensitivity _caseSensitivity, typename TChar, typename>
inline bool equal(TChar lhs_, TChar rhs_)
{
	if constexpr (_caseSensitivity == CaseInsensitive)
		return toLower(lhs_) == toLower(rhs_);
	else
		return static_cast<unsigned char>(lhs_) == static_cast<unsigned char>(rhs_);
}

///////////////////////////////////////////////////////////////////////
template <CaseSensitivity _caseSensitivity, typename InputIt1, typename InputIt2>
inline bool equal(InputIt1 begin1_, InputIt1 end1_, InputIt2 begin2_, InputIt2 end2_)
{
	return std::equal(begin1_, end1_, begin2_, end2_,
		[](char const left_, char const right_)
		{
			return equal<_caseSensitivity>(left_, right_);
		});
}

///////////////////////////////////////////////////////////////////////
template <CaseSensitivity _caseSensitivity>
inline bool equal(std::string_view const lhs_, std::string_view const rhs_)
{
	return equal<_caseSensitivity>(lhs_.begin(), lhs_.end(), rhs_.begin(), rhs_.end());
}

///////////////////////////////////////////////////////////////////////
template <typename TOutputIt>
void split(TOutputIt outputIt_, std::string_view string_, std::string_view separator_)
{
    std::string_view::size_type prev_pos = 0, pos = 0;

    while((pos = string_.find(separator_, pos)) != std::string_view::npos)
    {
        std::string substring( string_.substr(prev_pos, pos-prev_pos) );

        *outputIt_ = substring;
		++outputIt_;

		pos += separator_.length();
        prev_pos = pos;
    }

    *outputIt_ = std::string(string_.substr(prev_pos, pos-prev_pos)); // Last word
}

///////////////////////////////////////////////////////////////////////
template <typename TTestType>
inline bool stores(std::string_view const string_) {
	// Prepare stream:
	std::istringstream stream{ toLower(trim(string_)) };
	if constexpr (std::is_same_v<TTestType, bool>)
		stream >> std::boolalpha;

	// Try read:
	TTestType temp;
	return static_cast<bool>(stream >> temp);
}

///////////////////////////////////////////////////////////////////////
template <typename TIntegerType, typename >
inline bool storesInteger(std::string_view const string_) {
	return stores<TIntegerType>(string_);
}

///////////////////////////////////////////////////////////////////////
template <typename TFloatType, typename >
inline bool storesReal(std::string_view const string_) {
	return stores<TFloatType>(string_);
}

///////////////////////////////////////////////////////////////////////
template <typename TTargetType>
inline std::optional<TTargetType> convert(std::string_view const string_)
{
	// Prepare stream:
	std::istringstream stream{ toLower(trim(string_)) };
	if constexpr (std::is_same_v<TTargetType, bool>)
		stream >> std::boolalpha;

	TTargetType result;
	if (stream >> result)
		return result;
	else
		return {}; // empty optional
}

///////////////////////////////////////////////////////////////////////
template <typename InputIt1, typename InputIt2, typename TCompare>
inline std::pair<InputIt1, InputIt1> searchWithIncomplete(InputIt1 begin1_, InputIt1 end1_, InputIt2 begin2_, InputIt2 end2_, TCompare comp_)
{
	using ItTraits = std::iterator_traits<InputIt1>;
	using DiffType = typename ItTraits::difference_type;

	// The iterator that contains begin of the max subsequence.
	InputIt1 maxIterator = end1_;
	// Number of characters in max sequence.
	DiffType maxLength = 0;

	// Length of the first sequence. Decreases as begin1_ goes towards end1_.
	DiffType len1 = end1_ - begin1_;
	// Length of the second sequence. 
	DiffType const len2 = end2_ - begin2_;

	// Search for the max sequence going from begin1_ => end1_.
	while (begin1_ != end1_)
	{
		// Pick lowest of the two lengths (mismatch requires two ranges to have same number of elements):
		auto minimalLength = std::min(len1, len2);
		// Calculate at which point two ranges differ:
		auto seqResult = std::mismatch(begin1_, begin1_ + minimalLength, begin2_, begin2_ + minimalLength, comp_);
		// Calculate length of this sequence:
		DiffType seqLength = seqResult.first - begin1_;

		// Update max sequence.
		if (seqLength > maxLength) {
			maxLength = seqLength;
			maxIterator = begin1_;
		}

		// Next step.
		++begin1_;
		--len1;

		// Stop when it will be not possible to find any wider sequence.
		if (maxLength >= len1)
			break;
	}
	return { maxIterator, maxIterator + maxLength };
}

///////////////////////////////////////////////////////////////////////
template <CaseSensitivity _caseSensitivity, typename InputIt1, typename InputIt2>
inline std::pair<InputIt1, InputIt1> searchWithIncomplete(InputIt1 begin1_, InputIt1 end1_, InputIt2 begin2_, InputIt2 end2_)
{
	return searchWithIncomplete(begin1_, end1_, begin2_, end2_,
		[](auto const & a, auto const & b)
	{
		if constexpr (_caseSensitivity == CaseSensitive)
			return a == b;
		else
			return toLower(a) == toLower(b);
	});
}

///////////////////////////////////////////////////////////////////////
template <CaseSensitivity _caseSensitivity>
inline std::pair<std::string_view::size_type, std::string_view::size_type> searchWithIncomplete(std::string_view const searchIn_, std::string_view const searchFor_)
{
	auto[first, second] = searchWithIncomplete<_caseSensitivity>(searchIn_.begin(), searchIn_.end(), searchFor_.begin(), searchFor_.end());

	using size_type = std::string_view::size_type;
	return std::make_pair(
		static_cast<size_type>(first - searchIn_.begin()),
		static_cast<size_type>(second - searchIn_.begin())
	);
}

///////////////////////////////////////////////////////////////////////
template <CaseSensitivity _caseSensitivity>
inline std::pair<std::string::const_iterator, std::string::const_iterator> searchWithIncomplete(std::string const & searchIn_, std::string const & searchFor_)
{
	auto[first, second] = searchWithIncomplete<_caseSensitivity>(searchIn_.begin(), searchIn_.end(), searchFor_.begin(), searchFor_.end());
	return { first, second };
}

///////////////////////////////////////////////////////////////////////
template <typename TFirstArg, typename... TRestArgs>
inline std::string compose(TFirstArg && first_, TRestArgs &&... rest_)
{
	std::stringstream stream;
	stream << std::forward<TFirstArg>(first_);
	(stream << ... << std::forward<TRestArgs>(rest_));
	return stream.str();
}

namespace priv
{

template <typename... TArgs>
std::vector<std::string> argsToStrings(TArgs&&... args_)
{
	return std::vector<std::string>{ compose(std::forward<TArgs>(args_))... };
}

}

///////////////////////////////////////////////////////////////////////
template<typename ...TArgs>
std::string format(std::string_view format_, TArgs && ...args_)
{
	// .first = format point, .second = argument id
	using FormatPoint = std::pair<std::size_t, std::size_t>;

	std::string result;
	result.reserve(result.size()*2);
	std::vector<std::string> argStrs = priv::argsToStrings(std::forward<TArgs>(args_)...);

	std::int64_t tokenStart = -1;
	std::int64_t resultOffset = 0;
	for (std::size_t i = 0; i < format_.size(); i++)
	{
		// Skip escape character:
		if (format_[i] == '\\' && i + 1 < format_.size())
		{
			i++;
			resultOffset--;
		}

		if (i >= format_.size())
			break;

		result.push_back(format_[i]);

		if (tokenStart == -1)
		{
			if (format_[i] == '{' && (i == 0 || format_[i - 1] != '\\'))
				tokenStart = i;
		}
		else
		{
			if (format_[i] != '}' && (format_[i] < '0' || format_[i] > '9'))
			{
				tokenStart = -1;
			}
			else if (format_[i] == '}')
			{
				// By this moment `result` can look like this:
				// Some text {3}
				// tokenStart: 10
				// i: 12
				// arg index: substr(tokenStart + 1, i - tokenStart - 1)
				// So...
				// We have to replace part <10; 12> with result.substr(tokenStart + 1, i - tokenStart - 1)
				std::int64_t argIdStart = tokenStart + 1;
				std::int64_t argLen = std::int64_t(i) - argIdStart;
				std::size_t replaceLength = static_cast<std::size_t>(i - tokenStart + 1);
				if (argLen > 0)
				{
					auto argId = convert<std::int32_t>(
							result.substr(
								std::size_t(argIdStart+resultOffset),
								std::size_t(argLen)
							)
						).value_or(-1);

					
					if (argId == -1 || std::int64_t(argStrs.size()) <= argId)
					{
						// Token id is invalid, remove the token from string:
						result.erase(
								std::size_t(tokenStart + resultOffset),
								replaceLength
							);
					}
					else
					{
						// Replace token template with token specified in arguments:
						result.replace(
								std::size_t(tokenStart + resultOffset),
								replaceLength,
								argStrs[argId]
							);
					}
				}
				else
				{
					// Remove invalid token, that looks like this: "{}", with no index in it.
					result.erase(
							std::size_t(tokenStart+resultOffset),
							replaceLength
						);
				}
				resultOffset = result.size() - i - 1;
				tokenStart = -1;
			}
		}
	}

	result.shrink_to_fit();
	return result;
}

}