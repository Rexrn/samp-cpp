#pragma once

// Base class headers:
#include <SAMP-EDGEngine/World/MapObject.hpp>
#include <SAMP-EDGEngine/World/WI3DStreamableNode.hpp>

// Other headers:
#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

namespace samp_edgengine
{
class MapStreamChunk;
class Player;

/// <summary>
/// An interface of every object that can be streamed.
/// </summary>
/// <seealso cref="IMapObject" />
class PerPlayerObject
	:
	public IMapObject,
	public IWI3DStreamableNode
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="PerPlayerObject"/> class.
	/// </summary>
	PerPlayerObject();
	
	// Tracking:	
	/// <summary>
	/// Sets the placement tracker.
	/// </summary>
	/// <param name="tracker_">The tracker.</param>
	void setPlacementTracker(I3DNodePlacementTracker *tracker_);

	/// <summary>
	/// Returns the placement tracker.
	/// </summary>
	/// <returns>Pointer to placement tracker.</returns>
	I3DNodePlacementTracker* getPlacementTracker() const;

	/// <summary>
	/// Sends the placement update to the tracker.
	/// </summary>
	void sendPlacementUpdate();
	
	/// <summary>
	/// Returns object's placement.
	/// </summary>
	/// <returns>Placement of the object.</returns>
	ActorPlacement getPlacement() const;

	/// <summary>
	/// Sets the object world and changes the visibility mode.
	/// </summary>
	/// <param name="world_">The world.</param>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setWorldAndMode(Int32 world_, VisibilityMode visibilityMode_) override;

	/// <summary>
	/// Sets the world visibility mode.
	/// </summary>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setWorldMode(VisibilityMode const visibilityMode_) override;

	/// <summary>
	/// Sets the object interior and changes the visibility mode.
	/// </summary>
	/// <param name="interior_">The interior.</param>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setInteriorAndMode(Int32 interior_, VisibilityMode visibilityMode_) override;
	
	/// <summary>
	/// Sets the interior visibility mode.
	/// </summary>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setInteriorMode(VisibilityMode visibilityMode_) override;

	/// <summary>
	/// Returns the distance squared to specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual math::Meters getDistanceSquaredTo(Player const & player_) const = 0;

	/// <summary>
	/// Spawns the object to the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>
	///		<c>true</c> if successfully spawned; otherwise <c>false</c>.
	/// </returns>
	virtual bool spawn(Player const & player_) = 0;

	/// <summary>
	/// Despawns the object of the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void despawn(Player const & player_) = 0;

	/// <summary>
	/// Returns the object location for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>The object location for specified player.</returns>
	virtual math::Vector3f getLocationFor(Player const & player_) const = 0;
	
	/// <summary>
	/// Returns the object rotation for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>The object rotation for specified player.</returns>
	virtual math::Vector3f getRotationFor(Player const & player_) const = 0;

protected:

	I3DNodePlacementTracker*	m_placementTracker;
};

} // namespace agdk
