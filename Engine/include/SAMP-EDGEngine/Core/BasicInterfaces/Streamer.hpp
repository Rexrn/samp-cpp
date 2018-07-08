#pragma once

#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

namespace samp_edgengine
{
class Player;
class Vehicle;
class StaticVehicle;
class GlobalObject;
class PersonalObject;
class UniversalObject;

class IStreamer
{
public:	
	
	/// <summary>
	/// Event reaction designed to be called when player joins the server.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void whenPlayerJoinsServer(Player & player_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when vehicle joins map.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	virtual void whenVehicleJoinsMap(Vehicle & vehicle_) = 0;

	/// <summary>
	/// Event reaction designed to be called when static vehicle joins map.
	/// </summary>
	/// <param name="staticVehicle_">The static vehicle.</param>
	virtual void whenStaticVehicleJoinsMap(StaticVehicle & staticVehicle_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when global object joins map.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	virtual void whenObjectJoinsMap(GlobalObject & globalObject_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when personal object joins map.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	virtual void whenObjectJoinsMap(PersonalObject & personalObject_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when universal object joins map.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	virtual void whenObjectJoinsMap(UniversalObject & universalObject_) = 0;

	/// <summary>
	/// Event reaction designed to be called when checkpoint joins map.
	/// </summary>
	/// <param name="checkpoint_">The checkpoint.</param>
	virtual void whenCheckpointJoinsMap(Checkpoint & checkpoint_) = 0;

	/// <summary>
	/// Event reaction designed to be called when race checkpoint joins map.
	/// </summary>
	/// <param name="raceCheckpoint_">The race checkpoint.</param>
	virtual void whenCheckpointJoinsMap(RaceCheckpoint & raceCheckpoint_) = 0;




	/// <summary>
	/// Event reaction designed to be called when player leaves the server.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void whenPlayerLeavesServer(Player & player_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when vehicle leaves map.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	virtual void whenVehicleLeavesMap(Vehicle & vehicle_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when static vehicle leaves map.
	/// </summary>
	/// <param name="staticVehicle_">The static vehicle.</param>
	virtual void whenStaticVehicleLeavesMap(StaticVehicle & staticVehicle_) = 0;

	/// <summary>
	/// Event reaction designed to be called when global object leaves the map.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	virtual void whenObjectLeavesMap(GlobalObject & globalObject_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when personal object leaves map.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	virtual void whenObjectLeavesMap(PersonalObject & personalObject_) = 0;
	
	/// <summary>
	/// Event reaction designed to be called when universal object leaves map.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	virtual void whenObjectLeavesMap(UniversalObject & universalObject_) = 0;

	/// <summary>
	/// Event reaction designed to be called when checkpoint leaves map.
	/// </summary>
	/// <param name="checkpoint_">The checkpoint.</param>
	virtual void whenCheckpointLeavesMap(Checkpoint & checkpoint_) = 0;

	/// <summary>
	/// Event reaction designed to be called when race checkpoint leaves map.
	/// </summary>
	/// <param name="raceCheckpoint_">The race checkpoint.</param>
	virtual void whenRaceCheckpointLeavesMap(RaceCheckpoint & raceCheckpoint_) = 0;




	/// <summary>
	/// Event reaction designed to be called when the player changes location significantly.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenPlayerPlacementChanges(Player & player_, PlayerPlacement const& previousPlacement_, PlayerPlacement const& currentPlacement_) = 0;

	/// <summary>
	/// Event reaction designed to be called when the vehicle changes location significantly.
	/// </summary>
	/// <param name="vehicle_">The vehicle_.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenVehiclePlacementChanges(Vehicle & vehicle_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) = 0;

	/// <summary>
	/// Event reaction designed to be called when the static vehicle changes location significantly.
	/// </summary>
	/// <param name="staticVehicle_">The static vehicle_.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenStaticVehiclePlacementChanges(StaticVehicle & staticVehicle_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) = 0;

	/// <summary>
	/// Event reaction designed to be called when the global object changes location significantly.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenObjectPlacementChanges(GlobalObject & globalObject_, GlobalObjectPlacement const& previousPlacement_, GlobalObjectPlacement const& currentPlacement_) = 0;

	/// <summary>
	/// Event reaction designed to be called when the universal object changes location significantly.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenObjectPlacementChanges(UniversalObject & universalObject_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) = 0;

	/// <summary>
	/// Event reaction designed to be called when the personal object changes location significantly.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenObjectPlacementChanges(PersonalObject & personalObject_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) = 0;
};

}