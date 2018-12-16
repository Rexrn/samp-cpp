#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/World/WI3DNode.hpp>

namespace samp_edgengine
{
class Player;

/// <summary>
/// An interface of every object that can be streamed.
/// </summary>
/// <seealso cref="IMapObject" />
class IWI3DStreamableNode
	:
	public IWI3DNode
{
public:
	/// <summary>
	/// Enumeration of all possible ways the node can be streamed.
	/// </summary>
	enum class VisibilityMode : Uint8
	{
		Everywhere = 0,		// Node will be seen everywhere
		Specified,			// Node will be seen only on specified world/interior
		AllButSpecified		// Node will be seen in every world/interior but specified
	};
	
	/// <summary>
	/// Initializes a new instance of the <see cref="IWI3DStreamableNode"/> class.
	/// </summary>
	IWI3DStreamableNode();

	/// <summary>
	/// Sets the node world and changes the visibility mode.
	/// </summary>
	/// <param name="world_">The world.</param>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setWorldAndMode(Int32 world_, VisibilityMode visibilityMode_);

	/// <summary>
	/// Sets the world visibility mode.
	/// </summary>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setWorldMode(VisibilityMode visibilityMode_);

	/// <summary>
	/// Sets the node interior and changes the visibility mode.
	/// </summary>
	/// <param name="interior_">The interior.</param>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setInteriorAndMode(Int32 interior_, VisibilityMode visibilityMode_);
	
	/// <summary>
	/// Sets the interior visibility mode.
	/// </summary>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setInteriorMode(VisibilityMode visibilityMode_);
	
	/// <summary>
	/// Returns whether node should be visible in specified world and interior.
	/// </summary>
	/// <param name="world_">The world.</param>
	/// <param name="interior_">The interior.</param>
	/// <returns>
	///		<c>true</c> if node should be visible; otherwise, <c>false</c>.
	/// </returns>
	bool shouldBeVisibleIn(Int32 world_, Int32 interior_) const;

	/// <summary>
	/// Returns the world visibility mode.
	/// </summary>
	/// <returns>
	///		The world visibility mode.
	/// </returns>
	VisibilityMode getWorldMode() const;

	/// <summary>
	/// Returns the interior visibility mode.
	/// </summary>
	/// <returns>
	///		The interior visibility mode.
	/// </returns>
	VisibilityMode getInteriorMode() const;

protected:
	VisibilityMode				m_worldMode,
								m_interiorMode;
};

}
