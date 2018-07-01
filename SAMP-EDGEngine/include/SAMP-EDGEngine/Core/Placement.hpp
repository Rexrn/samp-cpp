#pragma once

#include SAMP_EDGENGINE_PCH

namespace agdk
{

struct ActorPlacement
{
	math::Vector3f	location;
	std::int32_t	world;
	std::int32_t	interior;
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