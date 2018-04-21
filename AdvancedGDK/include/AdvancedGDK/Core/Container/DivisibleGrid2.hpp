#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/Core/MathInc.hpp>

namespace agdk
{

/// <summary>
/// Interface for every grid node.
/// </summary>
template <typename t_ratioType>
class IDivisibleGrid2Node
{	
	/// <summary>
	/// Store extents as constexpr static constant to save memory.
	/// </summary>
	static constexpr math::Vector2f cxHalfExtent{
		static_cast<float>(t_ratioType::num) / t_ratioType::den,
		static_cast<float>(t_ratioType::num) / t_ratioType::den,
	};
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="IDivisibleGrid2Node"/> class.
	/// </summary>
	/// <param name="center_">The center.</param>
	IDivisibleGrid2Node(math::Vector2f const center_)
		: m_center{ center_ }
	{
	}

	/// <summary>
	/// Returns the center point.
	/// </summary>
	/// <returns>Center point.</returns>
	math::Vector2f getCenter() const {
		return m_center;
	}

	/// <summary>
	/// Returns an axis aligned bounding box of size exactly 2 * getHalfExtent().
	/// </summary>
	/// <returns>Axis aligned bounding box ( std::pair(min, max) ).</returns>
	std::pair<math::Vector2f, math::Vector2f> getAABB() const
	{
		math::Vector2f min = this->getCenter() - getHalfExtent();
		math::Vector2f max = this->getCenter() + getHalfExtent();
		return std::make_pair(min, max);
	}

	/// <summary>
	/// Determines whether this instance contains specified point.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <returns>
	///   <c>true</c> if this instance contains specified point; otherwise, <c>false</c>.
	/// </returns>
	bool containsPoint(math::Vector2f const & location_) const {
		auto[min, max] = this->getAABB();
		return (location_.x >= min.x && location_.x < max.x &&
				location_.y >= min.y && location_.y < max.y);
	}

	/// <summary>
	/// Returns half extent of the node.
	/// </summary>
	/// <returns>Half extent of the node.</returns>
	constexpr static math::Vector2f getHalfExtent() {
		return cxHalfExtent;
	}

protected:
	math::Vector2f m_center;
};

/// <summary>
/// Stores every non-zero level node grid inside.
/// </summary>
template <typename t_elementType, typename t_ratioType, std::uint32_t t_numDivisions, std::uint32_t t_levelsLeft>
class DivisibleGrid2Node
	: public IDivisibleGrid2Node<t_ratioType>
{
	/// <summary>
	/// Calculates the ratio numerator power.
	/// </summary>
	/// <param name="base_">The base.</param>
	/// <param name="exponent_">The exponent.</param>
	/// <returns>
	/// base^exponent
	/// </returns>
	constexpr static std::intmax_t calculateRatioNumeratorPower(std::intmax_t base_, std::intmax_t exponent_)
	{
		std::intmax_t result = base_;
		while (exponent_-- > 1)
			result *= base_;
		return result;
	}

	static constexpr std::uint32_t cxLevel = t_levelsLeft;
public:
	// Parent class:
	using Super = IDivisibleGrid2Node<t_ratioType>;

	// Some helper typedefs:

	// The type of ratio that zero-level node uses.
	using ZeroLevelRatio	= std::ratio_divide< t_ratioType, std::ratio< calculateRatioNumeratorPower(t_numDivisions, cxLevel) > >;
	// The type of ratio that is used in one level lower nodes.
	using LowerLevelRatio	= std::ratio_divide< t_ratioType, std::ratio< t_numDivisions > >;
	
	// The type of node with zero level.
	using ZeroLevelType		= DivisibleGrid2Node<t_elementType, ZeroLevelRatio, t_numDivisions, 0>;
	// The type of node with one level lower.
	using LowerLevelType	= DivisibleGrid2Node<t_elementType, LowerLevelRatio, t_numDivisions, t_levelsLeft - 1>;

	// Pointer to contained nodes.
	using NodePointer		= std::unique_ptr< LowerLevelType >;
	// Raw pointer to contained nodes.
	using RawNodePointer	= LowerLevelType* ;
	

	/// <summary>
	/// Initializes a new instance of the <see cref="DivisibleGrid2Node"/> class.
	/// </summary>
	/// <param name="center_">The center.</param>
	DivisibleGrid2Node(math::Vector2f const center_)
		: Super(center_), m_childCount{ 0 }
	{
	}

	/// <summary>
	/// Returns reference to element stored inside node containing specified location. If the node does not exist it creates it.
	/// </summary>
	/// <returns>Reference to stored element.</returns>
	t_elementType& require(math::Vector2f const & location_)
	{
		constexpr auto halfExtent		= Super::getHalfExtent();
		constexpr auto childHalfExtent	= LowerLevelType::getHalfExtent();

		auto arrayIndices = this->computeArrayIndices(location_);

		auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z];
		if (node) {
			return node->require(location_);
		}
		else
		{
			// We are creating new child, count it.
			m_childCount++;
			
			auto baseLocation = this->getCenter() - halfExtent;
			auto nodeBaseLocation = baseLocation + (arrayIndices.convert<float>() * childHalfExtent * 2.f);

			node = std::make_unique<LowerLevelType>(nodeBaseLocation + childHalfExtent);

			return node->require(location_);
		}
	}

	/// <summary>
	/// Returns reference to node of deepest level containing specified location. If it does not exist it creates it.
	/// </summary>
	/// <returns>Reference to deepest node containing the location.</returns>
	ZeroLevelType& requireNode(math::Vector2f const & location_)
	{
		constexpr auto halfExtent		= Super::getHalfExtent();
		constexpr auto childHalfExtent	= LowerLevelType::getHalfExtent();

		auto arrayIndices = this->computeArrayIndices(location_);

		auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z];
		if (node) {
			if constexpr(cxLevel == 1)
				return *node;
			else
				return node->requireNode(location_);
		}
		else
		{
			// We are creating new child, count it.
			m_childCount++;

			auto baseLocation		= this->getCenter() - halfExtent;
			auto nodeBaseLocation	= baseLocation + (arrayIndices.convert<float>() * childHalfExtent * 2.f);

			node = std::make_unique<LowerLevelType>(nodeBaseLocation + childHalfExtent);

			if constexpr(cxLevel == 1)
				return *node;
			else
				return node->requireNode(location_);
		}
	}

	/// <summary>
	/// Returns pointer to element stored inside node containing specified location.
	/// </summary>
	/// <returns>Pointer to stored element.</returns>
	t_elementType* get(math::Vector2f const & location_)
	{
		auto arrayIndices = this->computeArrayIndices(location_);

		if (auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z])
		{
			return node->get(location_);
		}
		return nullptr;
	}

	/// <summary>
	/// Returns pointer to const element stored inside node containing specified location.
	/// </summary>
	/// <returns>Pointer to const stored element.</returns>
	t_elementType const* get(math::Vector2f const & location_) const
	{
		auto arrayIndices = this->computeArrayIndices(location_);

		if (auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z])
		{
			return node->get(location_);
		}
		return nullptr;
	}

	/// <summary>
	/// Returns pointer to node of deepest level containing specified location.
	/// </summary>
	/// <returns>Pointer to deepest node containing the location.</returns>
	ZeroLevelType* getNode(math::Vector2f const & location_)
	{
		auto arrayIndices = this->computeArrayIndices(location_);

		if (auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z])
		{
			if constexpr(cxLevel == 1)
				return node.get();
			else
				return node->get(location_);
		}
		else
			return nullptr;
	}

	/// <summary>
	/// Returns pointer to const node of deepest level containing specified location.
	/// </summary>
	/// <returns>Pointer to deepest const node containing the location.</returns>
	ZeroLevelType const* getNode(math::Vector2f const & location_) const
	{
		auto arrayIndices = this->computeArrayIndices(location_);

		if (auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z])
		{
			if constexpr(cxLevel == 1)
				return node.get();
			else
				return node->get(location_);
		}
		else
			return nullptr;
	}

	/// <summary>
	/// Returns pointer to stored thing.
	/// </summary>
	/// <returns>Pointer to stored thing.</returns>
	void removeNode(math::Vector2f const & location_)
	{
		auto arrayIndices = this->computeArrayIndices(location_);

		// Do lower node exist?
		if (auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z])
		{
			if constexpr(cxLevel == 1)
			{
				node.reset();
				m_childCount--;
			}
			else
			{
				node->removeNode(location_);
				if (auto childCount = node->getChildCount();
					childCount == 0)
				{
					node.reset();
					m_childCount--;
				}
			}
		}
	}
		
	/// <summary>
	/// Returns cref to the node content.
	/// </summary>
	/// <returns>cref to the node content.</returns>
	auto const& getContent() const {
		return m_content;
	}
	
	/// <summary>
	/// Returns the child count.
	/// </summary>
	/// <returns>The child count.</returns>
	std::size_t getChildCount() const {
		return m_childCount;
	}

	/// <summary>
	/// Returns node level.
	/// </summary>
	/// <returns>Node level.</returns>
	constexpr static std::uint32_t getLevel() {
		return cxLevel;
	}
private:
	
	/// <summary>
	/// Computes array indices for specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <returns>Vector of array indices that represents node containing specified location.</returns>
	auto computeArrayIndices(math::Vector2f const & location_) const
	{
		constexpr auto halfExtent		= Super::getHalfExtent();
		constexpr auto childHalfExtent	= LowerLevelType::getHalfExtent();

		auto relativeLocation = location_ - (this->getCenter() - halfExtent);

		// Assertion note:
		// You tried to get instance of a chunk that does not exist in this node (or entire grid if Level is the one you set as the highest).
		assert(	relativeLocation.x >= 0 &&
				relativeLocation.y >= 0);

#ifdef ADVANCEDGDK_DEBUG
		using VectorType = math::Vector2i64;
#else
		using VectorType = math::Vector2size;
#endif
		
		return VectorType {
			static_cast<VectorType::ValueType>(std::floor(relativeLocation.x / (childHalfExtent.x * 2))),
			static_cast<VectorType::ValueType>(std::floor(relativeLocation.y / (childHalfExtent.y * 2)))
		};
	}

	// Number of currently stored children inside arrays.
	std::size_t m_childCount;
	// Array of nodes.
	std::array< std::array< std::array<NodePointer, t_numDivisions>, t_numDivisions>, t_numDivisions> m_content;
};


/// <summary>
/// Stores every zero-level node.
/// </summary>
template <typename t_elementType, typename t_ratioType, std::uint32_t t_numDivisions>
class DivisibleGrid2Node<t_elementType, t_ratioType, t_numDivisions, 0>
	: public IDivisibleGrid2Node<t_ratioType>
{

	// Level of the node.
	static constexpr std::uint32_t cxLevel = 0;
public:
	using Super = IDivisibleGrid2Node<t_ratioType>;

	/// <summary>
	/// Initializes a new instance of the <see cref="DivisibleGrid2Node"/> class.
	/// </summary>
	/// <param name="center_">The center.</param>
	DivisibleGrid2Node(math::Vector2f const center_)
		: Super(center_)
	{
	}

	/// <summary>
	/// Returns reference to stored element.
	/// </summary>
	/// <returns>Reference to stored thing.</returns>
	t_elementType& require(math::Vector2f const & location_) {
		return m_element;
	}

	/// <summary>
	/// Returns pointer to stored thing.
	/// </summary>
	/// <returns>Pointer to stored thing.</returns>
	t_elementType* get(math::Vector2f const & location_) {
		return &m_element;
	}

	/// <summary>
	/// Returns pointer to const stored thing.
	/// </summary>
	/// <returns>Pointer to const stored thing.</returns>
	t_elementType const* get(math::Vector2f const & location_) const {
		return &m_element;
	}
	
	/// <summary>
	/// Returns node level.
	/// </summary>
	/// <returns>Node level.</returns>
	constexpr static std::uint32_t getLevel() {
		return cxLevel;
	}
private:
	// The stored element.
	// Needs to satisfy concept: DefaultConstructible.
	t_elementType m_element;
};

}
