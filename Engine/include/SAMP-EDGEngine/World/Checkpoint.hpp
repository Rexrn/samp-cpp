#pragma once

#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>
#include <SAMP-EDGEngine/World/WI3DStreamableNode.hpp>
#include <SAMP-EDGEngine/Core/Placement.hpp>
#include "SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp"

namespace samp_edgengine
{

class Player;

/// <summary>
/// A in-game checkpoint.
/// </summary>
class Checkpoint
	: public IWI3DStreamableNode
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
	/// Initializes a new instance of the <see cref="Checkpoint"/> class.
	/// </summary>
	/// <param name="other_">The other.</param>
	Checkpoint(Checkpoint const& other_);
	
	/// <summary>
	/// Copy-assignment operator.
	/// </summary>
	/// <param name="other_">The other.</param>
	/// <returns>Reference to self.</returns>
	Checkpoint& operator=(Checkpoint const& other_);

	// Tracking:	
	/// <summary>
	/// Sets the placement tracker.
	/// </summary>
	/// <param name="tracker_">The tracker.</param>
	void setPlacementTracker(I3DNodePlacementTracker *tracker_);

	/// <summary>
	/// Returns the placement tracker.
	/// </summary>
	/// <returns>Placement tracker</returns>
	I3DNodePlacementTracker* getPlacementTracker() const;
	
	/// <summary>
	/// Sends the placement update.
	/// </summary>
	void sendPlacementUpdate();

	/// <summary>
	/// Returns player's placement.
	/// </summary>
	/// <returns>Player's placement.</returns>
	ActorPlacement getPlacement() const;

	// Checkpoint functions:

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

protected:

	// Checkpoint size (visible radius).
	float m_size;
	float m_intersectionRadius;
	float m_intersectionHeight;

	// Placement tracker:
	I3DNodePlacementTracker * m_placementTracker;
};

////////////////////////////////////////////////////////////////////////////////////
bool operator==(Checkpoint const& lhs_, Checkpoint const& rhs_);

////////////////////////////////////////////////////////////////////////////////////
bool operator!=(Checkpoint const& lhs_, Checkpoint const& rhs_);

}
