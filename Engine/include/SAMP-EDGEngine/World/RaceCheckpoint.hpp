#pragma once

#include <SAMP-EDGEngine/World/Checkpoint.hpp>

namespace samp_edgengine
{

class Player;

/// <summary>
/// A in-game race checkpoint.
/// </summary>
/// <seealso cref="Checkpoint" />
class RaceCheckpoint
	: public Checkpoint
{
public:

	enum Type
	{
		Land		= 0,
		LandFinish	= 1,
		None		= 2,
		Air			= 3,
		AirFinish	= 4
	};
	
	/// <summary>
	/// Initializes a new instance of the <see cref="RaceCheckpoint"/> class.
	/// </summary>
	RaceCheckpoint();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="RaceCheckpoint"/> class.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <param name="lookAt_">The look-at location.</param>
	/// <param name="type_">The type.</param>
	/// <param name="size_">The size.</param>
	/// <param name="intersectionRadius_">The intersection radius.</param>
	/// <param name="intersectionHeight_">Height of the intersection.</param>
	RaceCheckpoint(math::Vector3f const &location_, math::Vector3f const &lookAt_, Type type_, float size_, float intersectionRadius_ = -1, float intersectionHeight_ = -1);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="RaceCheckpoint"/> class.
	/// </summary>
	/// <param name="other_">The other.</param>
	RaceCheckpoint(RaceCheckpoint const& other_);
	
	/// <summary>
	/// Copy-assignment operator.
	/// </summary>
	/// <param name="other_">The other.</param>
	/// <returns>Reference to self.</returns>
	RaceCheckpoint& operator=(RaceCheckpoint const& other_);

	/// <summary>
	/// Sets the look-at location.
	/// </summary>
	/// <param name="lookAt_">The look-at.</param>
	void setLookAt(math::Vector3f const &lookAt_);
	
	/// <summary>
	/// Sets the race checkpoint type.
	/// </summary>
	/// <param name="type_">The type.</param>
	void setType(Type type_);

	/// <summary>
	/// Returns the look-at location.
	/// </summary>
	/// <returns>The look-at location.</returns>
	math::Vector3f getLookAt() const;

	/// <summary>
	/// Returns the race checkpoint type.
	/// </summary>
	/// <returns>The race checkpoint type.</returns>
	Type getType() const;

private:

	// A look-at target location.
	math::Vector3f m_lookAt;
	// Race checkpoint type.
	Type m_type;
};


bool operator==(RaceCheckpoint const &lhs_, RaceCheckpoint const &rhs_);

bool operator!=(RaceCheckpoint const &lhs_, RaceCheckpoint const &rhs_);

}
