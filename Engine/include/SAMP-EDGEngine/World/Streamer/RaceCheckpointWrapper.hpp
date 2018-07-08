#pragma once

#include SAMP_EDGENGINE_PCH

// Base class:
#include <SAMP-EDGEngine/World/Streamer/ChunkActor.hpp>
#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <SAMP-EDGEngine/World/Streamer/CheckpointWrapper.hpp>

namespace samp_edgengine::default_streamer
{

class RaceCheckpointWrapper
	:
	public CheckpointWrapper
{
	using CheckpointWrapper::CheckpointWrapper;
};

}
