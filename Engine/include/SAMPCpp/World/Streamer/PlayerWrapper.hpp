#pragma once
#include SAMPCPP_PCH



// Base class:
#include <SAMPCpp/World/Streamer/ChunkActor.hpp>
#include <SAMPCpp/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <SAMPCpp/Server/Player.hpp>
#include <SAMPCpp/World/PerPlayerObject.hpp>

namespace samp_cpp::default_streamer
{

class PlayerWrapper
	:
	public IChunkActor,
	public I3DNodePlacementTracker
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="PlayerWrapper"/> class.
	/// </summary>
	/// <param name="player_">The player.</param>
	PlayerWrapper(Player & player_);

	/// <summary>
	/// Returns pointer to the underlying player.
	/// </summary>
	/// <returns>Pointer to the underlying player.</returns>
	Player * getPlayer() const {
		return m_player;
	}
	
	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	virtual void whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_) override;

	std::vector<PerPlayerObject*> spawnedObjects; // List of per-player objects spawned.
private:
	Player * m_player; // The underlying player.
};

}
