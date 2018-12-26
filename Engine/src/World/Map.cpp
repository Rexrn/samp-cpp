#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/World/Map.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>
#include <SAMP-EDGEngine/Server/Server.hpp>

namespace samp_edgengine
{

///////////////////////////////////////////////////////////////////////////////////////
MapClass::MapClass()
{
	Server->onPlayerConnect += { *this, &MapClass::whenPlayerConnects };
}

///////////////////////////////////////////////////////////////////////////////////////
Vehicle& MapClass::finalizeConstruction(ActorPtrType< Vehicle > const& vehicle_)
{
	m_vehicles.push_back(vehicle_);
	GameMode->streamer->whenVehicleJoinsMap(*vehicle_);
	return *vehicle_;
}

///////////////////////////////////////////////////////////////////////////////////////
StaticVehicle& MapClass::finalizeConstruction(ActorPtrType< StaticVehicle > const& staticVehicle_)
{
	m_staticVehicles.push_back(staticVehicle_);
	GameMode->streamer->whenStaticVehicleJoinsMap(*staticVehicle_);
	return *staticVehicle_;
}

///////////////////////////////////////////////////////////////////////////////////////
Scene& MapClass::finalizeConstruction(ActorPtrType< Scene > const& scene_)
{
	m_scenes.push_back(scene_);
	scene_->whenSceneIsAddedToMap();

	if (scene_->getRemovedBuildings().size() > 0)
	{
		auto const& removed = scene_->getRemovedBuildings();

		m_removedBuildings.shrink_to_fit();
		m_removedBuildings.reserve(removed.size());

		for (auto const & building : removed)
			this->removeBuilding(building);
	}

	return *scene_;
}

///////////////////////////////////////////////////////////////////////////////////////
GangZone& MapClass::finalizeConstruction(ActorPtrType< GangZone > const& gangZone_)
{
	m_gangZones.push_back(gangZone_);
	return *gangZone_;
}

///////////////////////////////////////////////////////////////////////////////////////
Checkpoint& MapClass::finalizeConstruction(ActorPtrType< Checkpoint > const& checkpoint_)
{
	m_checkpoints.push_back(checkpoint_);
	GameMode->streamer->whenCheckpointJoinsMap(*checkpoint_);
	return *checkpoint_;
}

///////////////////////////////////////////////////////////////////////////////////////
RaceCheckpoint& MapClass::finalizeConstruction(ActorPtrType< RaceCheckpoint > const& raceCheckpoint_)
{
	m_raceCheckpoints.push_back(raceCheckpoint_);
	GameMode->streamer->whenCheckpointJoinsMap(*raceCheckpoint_);
	return *raceCheckpoint_;
}

///////////////////////////////////////////////////////////////////////////////////////
bool MapClass::remove(Vehicle & vehicle_)
{
	auto it = std::find_if(m_vehicles.begin(), m_vehicles.end(),
			[&vehicle_](auto const& vehPtr_) {
				return vehPtr_.get() == &vehicle_;
			}
		);
	
	if (it != m_vehicles.end())
	{
		GameMode->streamer->whenVehicleLeavesMap(vehicle_);
		m_vehicles.erase(it);
		return true;
	}
	return this->remove(dynamic_cast<StaticVehicle&>(vehicle_));
}

///////////////////////////////////////////////////////////////////////////////////////
bool MapClass::remove(StaticVehicle & vehicle_)
{
	auto it = std::find_if(m_staticVehicles.begin(), m_staticVehicles.end(),
			[&vehicle_](auto const& vehPtr_) {
				return vehPtr_.get() == &vehicle_;
			}
		);
	
	if (it != m_staticVehicles.end())
	{
		GameMode->streamer->whenStaticVehicleLeavesMap(vehicle_);
		m_staticVehicles.erase(it);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
bool MapClass::remove(GangZone const & gangZone_)
{
	const_a it = std::find_if(m_gangZones.begin(), m_gangZones.end(),
		[&](auto const & e)
		{
			return &gangZone_ == e.get();
		});

	if (it != m_gangZones.end())
	{
		m_gangZones.erase(it);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
Vehicle* MapClass::findVehicleByHandle(Int32 const vehicleHandle_)
{
	// Do not allow for such "hacks" (getting first not-spawned vehicle).
	if (vehicleHandle_ == Vehicle::InvalidHandle)
		return nullptr;

	Vehicle* result = nullptr;
	// Find inside normal vehicles:
	{
		const_a it = std::find_if(m_vehicles.begin(), m_vehicles.end(),
			[vehicleHandle_]
			(ActorPtrType<Vehicle> const& veh_)
			{
				return veh_->getHandle() == vehicleHandle_;
			});

		result = (it != m_vehicles.end() ? it->get() : nullptr);
	}
	// If not found, try to find it inside static vehicles:
	if (!result)
	{
		const_a it = std::find_if(m_staticVehicles.begin(), m_staticVehicles.end(),
			[vehicleHandle_]
			(ActorPtrType<StaticVehicle> const& veh_)
			{
				return veh_->getHandle() == vehicleHandle_;
			});

		result = (it != m_staticVehicles.end() ? it->get() : nullptr);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////
void MapClass::removeBuilding(RemovedBuilding const& removedBuilding_)
{
	auto const it = std::find_if(m_removedBuildings.begin(), m_removedBuildings.end(),
		[&removedBuilding_](RemovedBuilding const &element_)
		{
			return element_ == removedBuilding_;
		});

	if (it == m_removedBuildings.end())
	{
		m_removedBuildings.emplace_back(removedBuilding_);

		for(auto & player : GameMode->players.getPool())
		{
			this->applyRemovedBuilding(*player, removedBuilding_);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void MapClass::whenPlayerConnects(Player& player_)
{
	this->applyRemovedBuildings(player_);
}

///////////////////////////////////////////////////////////////////////////////////////
void MapClass::applyRemovedBuilding(Player& player_, RemovedBuilding const & building_)
{
	sampgdk_RemoveBuildingForPlayer(player_.getIndex(),
		building_.model,
		building_.origin.x, building_.origin.y, building_.origin.z,
		static_cast<float>(building_.radius.value)
	);
}

///////////////////////////////////////////////////////////////////////////////////////
void MapClass::applyRemovedBuildings(Player& player_)
{
	for (auto const & building : m_removedBuildings)
		this->applyRemovedBuilding(player_, building);
}

} // namespace agdk
