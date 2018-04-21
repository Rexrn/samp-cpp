#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/World/MapObject.hpp>
#include <AdvancedGDK/World/Actor.hpp>

namespace agdk
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
	public IWIActor
{
public:
	/// <summary>
	/// Enumeration of all possible ways the object can be streamed.
	/// </summary>
	enum class VisibilityMode : std::int8_t
	{
		Everywhere = 0,		// Object will be seen everywhere
		Specified,			// Object will be seen only on specified world/interior
		AllButSpecified		// Object will be seen in every world/interior but specified
	};
	
	/// <summary>
	/// Initializes a new instance of the <see cref="PerPlayerObject"/> class.
	/// </summary>
	PerPlayerObject();
	
	/// <summary>
	/// Sets the object world and changes the visibility mode.
	/// </summary>
	/// <param name="world_">The world.</param>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setWorld(std::int32_t const world_, VisibilityMode const visibilityMode_);

	/// <summary>
	/// Sets the world visibility mode.
	/// </summary>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setWorldVisibility(VisibilityMode const visibilityMode_);

	/// <summary>
	/// Sets the object interior and changes the visibility mode.
	/// </summary>
	/// <param name="interior_">The interior.</param>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setInterior(std::int32_t const interior_, VisibilityMode const visibilityMode_);
	
	/// <summary>
	/// Sets the interior visibility mode.
	/// </summary>
	/// <param name="visibilityMode_">The visibility mode.</param>
	virtual void setInteriorVisibility(VisibilityMode const visibilityMode_);

	/// <summary>
	/// Returns the distance squared to specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual math::Meters getDistanceSquaredTo(Player const & player_) const = 0;
	
	/// <summary>
	/// Returns whether object should be visible in specified world and interior.
	/// </summary>
	/// <param name="world_">The world.</param>
	/// <param name="interior_">The interior.</param>
	/// <returns>
	///		<c>true</c> if object should be visible; otherwise, <c>false</c>.
	/// </returns>
	bool shouldBeVisibleIn(std::int32_t const world_, std::int32_t const interior_) const;

	friend class MapStreamChunk;
	friend class WorldMap;
protected:	
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

	VisibilityMode				m_worldVisibility,
								m_interiorVisibility;
};

} // namespace agdk
