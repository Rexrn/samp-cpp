#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>

namespace samp_edgengine
{

class Player;

/// <summary>
/// A in-game checkpoint.
/// </summary>
class Checkpoint
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Checkpoint"/> class.
	/// </summary>
	Checkpoint();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Checkpoint"/> class.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <param name="size_">The size.</param>
	/// <param name="intersectionRadius_">The intersection radius.</param>
	/// <param name="intersectionHeight_">Height of the intersection.</param>
	Checkpoint(math::Vector3f const &location_, float size_, float intersectionRadius_ = -1, float intersectionHeight_ = -1);
	
	/// <summary>
	/// Sets the location.
	/// </summary>
	/// <param name="location_">The location.</param>
	void setLocation(math::Vector3f const &location_);
	
	/// <summary>
	/// Sets the (visible) size.
	/// </summary>
	/// <param name="size_">The size.</param>
	void setSize(float size_);
	
	/// <summary>
	/// Sets the intersection radius.
	/// </summary>
	/// <param name="intersectionRadius_">The intersection radius.</param>
	void setIntersectionRadius(float intersectionRadius_);
	
	/// <summary>
	/// Sets the height of the intersection.
	/// </summary>
	/// <param name="intersectionHeight_">Height of the intersection.</param>
	void setIntersectionHeight(float intersectionHeight_);
	
	/// <summary>
	/// Moves checkpoint by the specified delta.
	/// </summary>
	/// <param name="delta_">The delta.</param>
	void move(math::Vector3f const& delta_);

	/// <summary>
	/// Returns the location.
	/// </summary>
	/// <returns>The location.</returns>
	math::Vector3f getLocation() const;

	/// <summary>
	/// Returns the visible size.
	/// </summary>
	/// <returns>The size.</returns>
	float getSize() const;

	/// <summary>
	/// Returns the intersection radius.
	/// </summary>
	/// <returns>The intersection radius.</returns>
	float getIntersectionRadius() const;

	/// <summary>
	/// Returns the height of the intersection.
	/// </summary>
	/// <returns>The height of the intersection.</returns>
	float getIntersectionHeight() const;
	
	/// <summary>
	/// Determines whether player is allowed to see or interact with the checkpoint.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>
	///   <c>true</c> if player is allowed to see or interact with the checkpoint; otherwise, <c>false</c>.
	/// </returns>
	virtual bool isAllowedForPlayer(Player const & player_) const;

protected:

	// Checkpoint location.
	math::Vector3f m_location;

	// Checkpoint size (visible radius).
	float m_size;
	float m_intersectionRadius;
	float m_intersectionHeight;
};

}
