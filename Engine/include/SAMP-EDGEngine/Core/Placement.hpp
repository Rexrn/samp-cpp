#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/Dependencies/QuickMaffs.hpp>
#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>

namespace samp_cpp
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