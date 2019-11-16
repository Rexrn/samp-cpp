#pragma once
#include SAMPEDGENGINE_PCH



// Base class:
#include <SAMP-EDGEngine/World/Streamer/ChunkActor.hpp>
#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <SAMP-EDGEngine/World/Checkpoint.hpp>

namespace samp_cpp::default_streamer
{

class CheckpointWrapper
	:
	public IChunkActor,
	public I3DNodePlacementTracker
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="CheckpointWrapper"/> class.
	/// </summary>
	/// <param name="checkpoint_">The checkpoint.</param>
	CheckpointWrapper(Checkpoint & checkpoint_);


	/// <summary>
	/// Returns pointer to the underlying checkpoint.
	/// </summary>
	/// <returns>Pointer to the underlying checkpoint.</returns>
	Checkpoint * getCheckpoint() const {
		return m_checkpoint;
	}

	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	virtual void whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_) override;

private:
	Checkpoint * m_checkpoint; // The underlying checkpoint.
};

}
