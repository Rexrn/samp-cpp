#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Core/Pointers.hpp>

namespace agdk
{

#ifdef SAMP_EDGENGINE_DEBUG
struct DivisibleGrid3ElementDebugInfo
{
	math::Vector3f center, halfExtent;
};
struct IDivisibleGrid3ElementBase
{
public:
	/// <summary>
	/// Returns the debug information.
	/// </summary>
	/// <returns>
	///		The debug information.
	/// </returns>
	auto const & getDebugInfo() const
	{
		return m_debugInfo;
	}

	/// <summary>
	/// Sets the debug information.
	/// </summary>
	/// <param name="debugInfo_">The debug information.</param>
	void setDebugInfo(DivisibleGrid3ElementDebugInfo debugInfo_)
	{
		m_debugInfo = debugInfo_;
	}
protected:	
	
	DivisibleGrid3ElementDebugInfo m_debugInfo;
};
#endif

/// <summary>
/// Interface for every grid node.
/// </summary>
template <typename TRatioType>
class IDivisibleGrid3Node
{	
	/// <summary>
	/// Store extents as constexpr static constant to save memory.
	/// </summary>
	static constexpr math::Vector3f cxHalfExtent{
		static_cast<float>(TRatioType::num) / TRatioType::den,
		static_cast<float>(TRatioType::num) / TRatioType::den,
		static_cast<float>(TRatioType::num) / TRatioType::den,
	};
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="IDivisibleGrid3Node"/> class.
	/// </summary>
	/// <param name="center_">The center.</param>
	IDivisibleGrid3Node(math::Vector3f const center_)
		: m_center{ center_ }
	{
	}

	/// <summary>
	/// Returns the center point.
	/// </summary>
	/// <returns>Center point.</returns>
	math::Vector3f getCenter() const {
		return m_center;
	}

	/// <summary>
	/// Returns an axis aligned bounding box of size exactly 2 * getHalfExtent().
	/// </summary>
	/// <returns>Axis aligned bounding box ( std::pair(min, max) ).</returns>
	std::pair<math::Vector3f, math::Vector3f> getAABB() const
	{
		math::Vector3f min = this->getCenter() - getHalfExtent();
		math::Vector3f max = this->getCenter() + getHalfExtent();
		return std::make_pair(min, max);
	}

	/// <summary>
	/// Determines whether this instance contains specified point.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <returns>
	///   <c>true</c> if this instance contains specified point; otherwise, <c>false</c>.
	/// </returns>
	bool containsPoint(math::Vector3f const & location_) const {
		auto[min, max] = this->getAABB();
		return (location_.x >= min.x && location_.x < max.x &&
				location_.y >= min.y && location_.y < max.y &&
				location_.z >= min.z && location_.z < max.z);
	}

	/// <summary>
	/// Returns half extent of the node.
	/// </summary>
	/// <returns>Half extent of the node.</returns>
	constexpr static math::Vector3f getHalfExtent() {
		return cxHalfExtent;
	}

protected:
	math::Vector3f m_center;
};

/// <summary>
/// Stores every non-zero level node grid inside.
/// </summary>
template <typename TElementType, typename TRatioType, std::uint32_t _numDivisions, std::uint32_t _levelsLeft>
class DivisibleGrid3Node
	: public IDivisibleGrid3Node<TRatioType>
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

	static constexpr std::uint32_t cxLevel = _levelsLeft;
public:
	// Parent class:
	using Super = IDivisibleGrid3Node<TRatioType>;

	// Some helper typedefs:

	// The type of ratio that zero-level node uses.
	using ZeroLevelRatio	= std::ratio_divide< TRatioType, std::ratio< calculateRatioNumeratorPower(_numDivisions, cxLevel) > >;
	// The type of ratio that is used in one level lower nodes.
	using LowerLevelRatio	= std::ratio_divide< TRatioType, std::ratio< _numDivisions > >;
	
	// The type of node with zero level.
	using ZeroLevelType		= DivisibleGrid3Node<TElementType, ZeroLevelRatio, _numDivisions, 0>;
	// The type of node with one level lower.
	using LowerLevelType	= DivisibleGrid3Node<TElementType, LowerLevelRatio, _numDivisions, _levelsLeft - 1>;

	// Pointer to contained nodes.
	using NodePointer		= UniquePtr< LowerLevelType >;
	// Raw pointer to contained nodes.
	using RawNodePointer	= LowerLevelType* ;
	

	/// <summary>
	/// Initializes a new instance of the <see cref="DivisibleGrid3Node"/> class.
	/// </summary>
	/// <param name="center_">The center.</param>
	DivisibleGrid3Node(math::Vector3f const center_)
		: Super(center_), m_childCount{ 0 }
	{
	}

	/// <summary>
	/// Returns reference to element stored inside node containing specified location. If the node does not exist it creates it.
	/// </summary>
	/// <returns>Reference to stored element.</returns>
	TElementType& require(math::Vector3f const & location_)
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
			auto nodeBaseLocation = baseLocation + (arrayIndices.template convert<float>() * childHalfExtent * 2.f);

			node = std::make_unique<LowerLevelType>(nodeBaseLocation + childHalfExtent);

			return node->require(location_);
		}
	}

	/// <summary>
	/// Returns reference to node of deepest level containing specified location. If it does not exist it creates it.
	/// </summary>
	/// <returns>Reference to deepest node containing the location.</returns>
	ZeroLevelType& requireNode(math::Vector3f const & location_)
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
	TElementType* get(math::Vector3f const & location_)
	{
		auto arrayIndices = this->computeArrayIndices(location_);

		if (auto & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z])
		{
			return node->get(location_);
		}
		return nullptr;
	}

	/// <summary>
	/// Returns pointer to constant element stored inside node containing specified location.
	/// </summary>
	/// <returns>Pointer to constant stored element.</returns>
	TElementType const* get(math::Vector3f const & location_) const
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
	ZeroLevelType* getNode(math::Vector3f const & location_)
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
	/// <returns>Pointer to const deepest node containing the location.</returns>
	ZeroLevelType const* getNode(math::Vector3f const & location_) const
	{
		auto arrayIndices = this->computeArrayIndices(location_);

		if (auto const & node = m_content[arrayIndices.x][arrayIndices.y][arrayIndices.z])
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
	void removeNode(math::Vector3f const & location_)
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
	/// Returns the content.
	/// </summary>
	/// <returns></returns>
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
	auto computeArrayIndices(math::Vector3f const & location_) const
	{
		constexpr auto halfExtent		= Super::getHalfExtent().template convert<double>();
		constexpr auto childHalfExtent	= LowerLevelType::getHalfExtent().template convert<double>();

		math::Vector3d relativeLocation = location_.convert<double>() - (this->getCenter().template convert<double>() - halfExtent);

		// Assertion note:
		// You tried to get instance of a chunk that does not exist in this node (or entire grid if Level is the one you set as the highest).
		assert(	relativeLocation.x >= 0.0 &&
				relativeLocation.y >= 0.0 &&
				relativeLocation.z >= 0.0);

#ifdef SAMP_EDGENGINE_DEBUG
		using VectorType = math::Vector3i64;
#else
		using VectorType = math::Vector3size;
#endif
		
		return VectorType {
			static_cast<VectorType::ValueType>(std::floor(relativeLocation.x / (childHalfExtent.x * 2.0))),
			static_cast<VectorType::ValueType>(std::floor(relativeLocation.y / (childHalfExtent.y * 2.0))),
			static_cast<VectorType::ValueType>(std::floor(relativeLocation.z / (childHalfExtent.z * 2.0)))
		};
	}

	// Number of currently stored children inside arrays.
	std::size_t m_childCount;
	// Array of nodes.
	std::array< std::array< std::array<NodePointer, _numDivisions>, _numDivisions>, _numDivisions> m_content;
};


/// <summary>
/// Stores every zero-level node.
/// </summary>
template <typename TElementType, typename TRatioType, std::uint32_t _numDivisions>
class DivisibleGrid3Node<TElementType, TRatioType, _numDivisions, 0>
	: public IDivisibleGrid3Node<TRatioType>
{

	// Level of the node.
	static constexpr std::uint32_t cxLevel = 0;
public:
	using Super = IDivisibleGrid3Node<TRatioType>;

	/// <summary>
	/// Initializes a new instance of the <see cref="DivisibleGrid3Node"/> class.
	/// </summary>
	/// <param name="center_">The center.</param>
	DivisibleGrid3Node(math::Vector3f const center_)
		: Super(center_)
	{
#ifdef SAMP_EDGENGINE_DEBUG
		m_element.setDebugInfo( { center_, Super::getHalfExtent() });
#endif
	}

	/// <summary>
	/// Returns reference to stored element.
	/// </summary>
	/// <returns>Reference to stored thing.</returns>
	TElementType& require(math::Vector3f const & location_) {
		return m_element;
	}

	/// <summary>
	/// Returns pointer to stored thing.
	/// </summary>
	/// <returns>Pointer to stored thing.</returns>
	TElementType* get(math::Vector3f const & location_) {
		return &m_element;
	}

	/// <summary>
	/// Returns pointer to const stored thing.
	/// </summary>
	/// <returns>Pointer to const stored thing.</returns>
	TElementType const* get(math::Vector3f const & location_) const {
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
	TElementType m_element;
};

}
