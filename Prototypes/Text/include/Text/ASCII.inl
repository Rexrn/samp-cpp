// Note: this file is not meant to be included on its own.
// Include "ASCII.hpp" instead.

namespace agdk::proto::text::ascii
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

}