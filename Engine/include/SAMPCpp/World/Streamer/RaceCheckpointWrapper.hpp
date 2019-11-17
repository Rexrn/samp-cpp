#pragma once
#include SAMPCPP_PCH



// Base class:
#include <SAMPCpp/World/Streamer/ChunkActor.hpp>
#include <SAMPCpp/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <SAMPCpp/World/Streamer/CheckpointWrapper.hpp>

namespace samp_cpp::default_streamer
{

class RaceCheckpointWrapper
	:
	public CheckpointWrapper
{
	using CheckpointWrapper::CheckpointWrapper;
};

}
