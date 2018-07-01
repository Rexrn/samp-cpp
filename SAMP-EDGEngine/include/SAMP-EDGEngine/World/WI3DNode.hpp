#pragma once

// Precompiled header:
#include SAMP_EDGENGINE_PCH

// Header with base class:
#include <SAMP-EDGEngine/World/3DNode.hpp>

namespace agdk
{
	
/// <summary>
/// Basic interface for every in-game object that has its world, interior and location specified.
/// </summary>
/// <seealso cref="I3DNode" />
class IWI3DNode
	: public virtual I3DNode
{
public:
	// The base class:
	using Super = I3DNode;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="IWI3DNode"/> class.
	/// </summary>
	IWI3DNode();

	/// <summary>
	/// Sets the virtual world.
	/// </summary>
	/// <param name="world_">The world.</param>
	virtual void setWorld(Int32 world_);

	/// <summary>
	/// Sets the interior.
	/// </summary>
	/// <param name="interior_">The interior.</param>
	virtual void setInterior(Int32 interior_);

	/// <summary>
	/// Returns nodes virtual world.
	/// </summary>
	/// <returns>The virtual world.</returns>
	virtual Int32 getWorld() const;

	/// <summary>
	/// Returns nodes interior.
	/// </summary>
	/// <returns>The interior.</returns>
	virtual Int32 getInterior() const;

protected:
	/// <summary>
	/// Synchronises its actual virtual world with the stored one.
	/// </summary>
	/// <param name="world_">The world.</param>
	virtual void syncWorld(Int32 world_);

	/// <summary>
	/// Synchronises its actual interior with the stored one.
	/// </summary>
	/// <param name="world_">The interior.</param>
	virtual void syncInterior(Int32 interior_);

	Int32 m_world;		// Last saved world.
	Int32 m_interior;	// Last saved interior.
};

} // namespace agdk