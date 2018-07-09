#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>

namespace samp_edgengine
{

struct ActorPlacement
{
	math::Vector3f	location;
	Int32			world;
	Int32			interior;
};

using PlayerPlacement			= ActorPlacement;
using VehiclePlacement			= ActorPlacement;
using PerPlayerObjectPlacement	= ActorPlacement;

/// <summary>
/// A special case: global object is visible in any world and any interior.
/// </summary>
struct GlobalObjectPlacement
{
	math::Vector3f	location;
};



}