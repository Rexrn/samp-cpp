// Note: this file is not meant to be included on its own.
// Include "TokenIterator.hpp" instead.

namespace samp_edgengine::text
{

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline TokenIterator<T, U>::TokenIterator(StringType const & string_, SeparatorsType const & separators_)
{
	// Create one-time string and separators copy, shared between copied iterators.
	m_string = std::make_shared<StringType>(string_);
	m_iterator = m_string->begin();
	m_separators = std::make_shared<SeparatorsType>(separators_);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline TokenIterator<T, U>& TokenIterator<T, U>::operator++()
{
	// To advance iterator, we need to know how many characters it must jump.
	if (!m_nextHop.has_value()) {
		m_nextHop = this->calculateToken().second;
	}
	std::advance(m_iterator, m_nextHop.value());

	// Reset the hop, it must be recalculated once again.
	m_nextHop.reset();
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline TokenIterator<T, U> TokenIterator<T, U>::operator++(int unused_)
{
	// Store copy of previous state of the iterator.
	auto previous = *this;

	// To advance iterator, we need to know how many characters it must jump.
	if (!m_nextHop.has_value()) {
		m_nextHop = this->calculateToken().second;
	}
	std::advance(m_iterator, m_nextHop.value());

	// Reset the hop, it must be recalculated once again.
	m_nextHop.reset();
	return previous;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline typename TokenIterator<T, U>::StringType TokenIterator<T, U>::operator*()
{
	auto[token, hop] = this->calculateToken();
	// Save the distance of the next hop, because calculating this takes some time.
	m_nextHop = hop;
	return token;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline typename TokenIterator<T, U>::IteratorType TokenIterator<T, U>::getStringIterator() const
{
	return m_iterator;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline bool TokenIterator<T, U>::isOnEnd() const
{
	return !m_string || m_string->empty() || m_iterator == m_string->end();
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline std::pair<typename TokenIterator<T, U>::StringType, typename TokenIterator<T, U>::DiffType>
TokenIterator<T, U>::calculateToken() const
{
	// At first assume that next nearest separator is on the end.
	// Any closer than this will be considered as better match.
	IteratorType nearestSeparator = m_string->cend();
	// Calculate the current nearest distance to separator.
	DiffType minDist = std::distance(m_iterator, m_string->cend());
	// Store length of separator found to make proper "hop" next time (jump after the separator).
	DiffType sepLen = 0;

	// Check every separator:
	for (auto const & separator : *m_separators)
	{
		// Search for the first separator:
		auto sepFound = std::search(m_iterator, m_string->cend(), separator.cbegin(), separator.cend());
		if (sepFound != m_string->cend())
		{
			// How many characters "away" is the separator?
			auto currDist = std::distance(m_iterator, sepFound);
			if (currDist < minDist)
			{
				nearestSeparator = sepFound;
				sepLen = separator.size();
				minDist = currDist;
			}
		}
	}
	return { StringType{ m_iterator, nearestSeparator }, minDist + sepLen };
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline bool operator==(TokenIterator<T, U> const & lhs_, TokenIterator<T, U> const & rhs_)
{
	if (lhs_.isOnEnd() && rhs_.isOnEnd())
		return true;
	else
		return (lhs_.m_string == rhs_.m_string && lhs_.m_iterator == rhs_.m_iterator);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
inline bool operator!=(TokenIterator<T, U> const & lhs_, TokenIterator<T, U> const & rhs_)
{
	return !(lhs_ == rhs_);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
inline TokenIterator<T, U> begin(TokenIterator<T, U> iterator_) {
	return iterator_;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
inline TokenIterator<T, U> end(TokenIterator<T, U>  const & iterator_) {
	return {};
}

} // namespace