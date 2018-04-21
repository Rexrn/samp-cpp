#pragma once

#include "ChunkActor.hpp"
#include "GloballyVisibleActor.hpp"

#include <AdvancedGDK/World/MapObject/GlobalObject.hpp>

namespace agdk
{

class GlobalObjectChunkActor
	:
	public GloballyVisibleActor,
	public IChunkActor<GlobalObject>
{
public:
	using IChunkActor::IChunkActor;
};

}
