#pragma once
#include SAMPCPP_PCH



#include <SAMPCpp/Core/Placement.hpp>
#include <SAMPCpp/World/Streamer/StreamerSettings.hpp>

namespace samp_cpp
{

/// <summary>
/// An interface for object that tracks actor's placement.
/// </summary>
struct I3DNodePlacementTracker
{		
	/// <summary>
	/// Initializes a new instance of the <see cref="I3DNodePlacementTracker"/> struct.
	/// </summary>
	/// <param name="initialPlacement_">The initial placement.</param>
	explicit I3DNodePlacementTracker(ActorPlacement const & initialPlacement_);

	/// <summary>
	/// Event reaction designed to be called on every placement update.
	/// </summary>
	/// <param name="newPlacement_">The new placement.</param>
	void whenPlacementUpdateReceived(ActorPlacement const& newPlacement_);

	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	virtual void whenPlacementChanges(ActorPlacement const & prevPlacement_, ActorPlacement const & newPlacement_) = 0;
	
	/// <summary>
	/// Returns the last placement.
	/// </summary>
	/// <returns>Last placement.</returns>
	ActorPlacement getLastPlacement() const {
		return m_lastPlacement;
	}
private:
	
	/// <summary>
	/// Determines whether the placement significantly changed from last update.
	/// </summary>
	/// <param name="newPlacement_">The new placement.</param>
	/// <returns>
	///   <c>true</c> if the placement significantly changed from last update; otherwise, <c>false</c>.
	/// </returns>
	bool isSignificantChange(ActorPlacement const& newPlacement_) const;

	ActorPlacement m_lastPlacement;
};
	
/// <summary>
/// An interface for object that tracks global object's placement.
/// </summary>
struct IGlobalObjectPlacementTracker
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IGlobalObjectPlacementTracker"/> struct.
	/// </summary>
	/// <param name="initialPlacement_">The initial placement.</param>
	explicit IGlobalObjectPlacementTracker(GlobalObjectPlacement const & initialPlacement_);

	/// <summary>
	/// Event reaction designed to be called on every placement update.
	/// </summary>
	/// <param name="newPlacement_">The new placement.</param>
	void whenPlacementUpdateReceived(GlobalObjectPlacement const& newPlacement_);

	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	virtual void whenPlacementChanges(GlobalObjectPlacement const & prevPlacement_, GlobalObjectPlacement const & newPlacement_) = 0;

	/// <summary>
	/// Returns the last placement.
	/// </summary>
	/// <returns>Last placement.</returns>
	GlobalObjectPlacement getLastPlacement() const {
		return m_lastPlacement;
	}
private:

	/// <summary>
	/// Determines whether the placement significantly changed from last update.
	/// </summary>
	/// <param name="newPlacement_">The new placement.</param>
	/// <returns>
	///   <c>true</c> if the placement significantly changed from last update; otherwise, <c>false</c>.
	/// </returns>
	bool isSignificantChange(GlobalObjectPlacement const& newPlacement_) const;

	GlobalObjectPlacement m_lastPlacement;
};

}
