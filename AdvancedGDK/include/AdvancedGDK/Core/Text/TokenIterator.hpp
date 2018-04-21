#pragma once

#include ADVANCEDGDK_PCH

namespace agdk::text
{

/// <summary>
/// Iterates through tokens inside strings separated by vector of separators.
/// </summary>
template <typename TStringType, typename TSeparatorType>
class TokenIterator
{
public:
	// Aliases
	using SeparatorType		= TSeparatorType;
	using StringType		= TStringType;
	using SeparatorsType	= std::vector<SeparatorType>;
	using SeparatorsPtrType	= std::shared_ptr<SeparatorsType>;
	using StringPtrType		= std::shared_ptr<StringType>;
	using IteratorType		= typename StringType::const_iterator;
	using DiffType			= typename StringType::difference_type;
	
	// Aliases for standard iterator traits:
	using difference_type	= DiffType;
	using value_type		= typename StringType::value_type;
	using pointer			= typename StringType::pointer;
	using reference			= typename StringType::reference;
	using iterator_category = std::forward_iterator_tag;
		
	// Methods:

	/// <summary>
	/// Initializes a new instance of the <see cref="TokenIterator"/> class.
	/// </summary>
	TokenIterator() = default;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="TokenIterator"/> class.
	/// </summary>
	/// <param name="separators_">Vector of separators.</param>
	/// <param name="string_">The string.</param>
	TokenIterator(StringType const & string_, SeparatorsType const & separators_);
	
	/// <summary>
	/// Increments the iterator (goes to the next token).
	/// </summary>
	/// <param name="unused_">Unused.</param>
	/// <returns>Reference to incremented iterator.</returns>
	TokenIterator& operator++();
	
	/// <summary>
	/// Increments the iterator (goes to the next token).
	/// </summary>
	/// <param name="unused_">Unused.</param>
	/// <returns>Copy of the iterator before incrementation.</returns>
	TokenIterator operator++(int unused_);
	
	/// <summary>
	/// Dereferences this operator returning current token.
	/// </summary>
	/// <returns>Current token.</returns>
	StringType operator*();

	/// <summary>
	/// Returns the underlying string iterator.
	/// </summary>
	/// <returns>Underlying string iterator</returns>
	IteratorType getStringIterator() const;

	/// <summary>
	/// Determines whether this iterator is on end of the string.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this iterator is on end of the string; otherwise, <c>false</c>.
	/// </returns>
	bool isOnEnd() const;


	/// <summary>
	/// Compares two token iterators, check if they are equal.
	/// </summary>
	/// <param name="lhs_">The LHS iterator.</param>
	/// <param name="rhs_">The RHS iterator.</param>
	/// <returns>
	///		<c>true</c> if iterators are equal; otherwise, <c>false</c>.
	/// </returns>
	template<typename T, typename U>
	friend bool operator==(TokenIterator<T, U> const & lhs_, TokenIterator<T, U> const & rhs_);

	/// <summary>
	///	Compares two token iterators, checks if they are different.
	/// </summary>
	/// <param name="lhs_">The LHS iterator.</param>
	/// <param name="rhs_">The RHS iterator.</param>
	/// <returns>
	///		<c>true</c> if iterators are different; otherwise, <c>false</c>.
	/// </returns>
	template<typename T, typename U>
	friend bool operator!=(TokenIterator<T, U> const & lhs_, TokenIterator<T, U> const & rhs_);

private:
		
	/// <summary>
	/// Calculates the current token.
	/// </summary>
	/// <returns>
	///		Pair containing complete token and distance is need to be done to get to next token.
	/// </returns>
	std::pair<StringType, DiffType> calculateToken() const;

	StringPtrType 			m_string;		// Copy of the string to tokenize.
	SeparatorsPtrType		m_separators;	// Copy of separator vector.
	IteratorType			m_iterator;		// Internal const iterator of the StringType.
	std::optional<DiffType> m_nextHop;		// Pre-calculated value of distance iterator must advance to get to another token.
};

/// <summary>
/// Returns its parameter without changes.
/// </summary>
template <typename T, typename U>
TokenIterator<T, U> begin(TokenIterator<T, U> iterator_);

/// <summary>
/// Returns empty iterator.
/// </summary>
template <typename T, typename U>
TokenIterator<T, U> end(TokenIterator<T, U> const & iterator_);

}

#include "TokenIterator.inl"
