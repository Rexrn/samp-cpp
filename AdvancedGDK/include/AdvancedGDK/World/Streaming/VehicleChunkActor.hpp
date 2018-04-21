#pragma once

#include "ChunkActor.hpp"
#include "GloballyVisibleActor.hpp"

#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>

namespace agdk
{

class VehicleChunkActor
	:
	public GloballyVisibleActor,
	public IChunkActor<Vehicle>
{
public:
	using IChunkActor::IChunkActor;
};

}
