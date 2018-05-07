#pragma once

#include ADVANCEDGDK_PCH

// Base class:
#include <AdvancedGDK/World/Streamer/ChunkActor.hpp>
#include <AdvancedGDK/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <AdvancedGDK/Server/Player/Player.hpp>

namespace agdk::default_streamer
{

class PlayerWrapper
	:
	public IChunkActor,
	public IActorPlacementTracker
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="PlayerWrapper"/> class.
	/// </summary>
	PlayerWrapper();

	/// <summary>
	/// Initializes a new instance of the <see cref="PlayerWrapper"/> class.
	/// </summary>
	/// <param name="player_">The player.</param>
	PlayerWrapper(Player & player_);

	/// <summary>
	/// Sets pointer to the underlying player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void setPlayer(Player & player_);

	/// <summary>
	/// Returns pointer to the underlying player.
	/// </summary>
	/// <returns>Pointer to the underlying player.</returns>
	Player* getPlayer() const {
		return m_player;
	}
	
	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	virtual void whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_) override;

private:
	Player * m_player; // The underlying player.
};

}
