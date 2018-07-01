#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Map.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>
#include <AdvancedGDK/Core/TypesAndDefinitions.hpp>
#include <AdvancedGDK/Server/Server.hpp>

namespace agdk
{

///////////////////////////////////////////////////////////////////////////////////////
MapClass::MapClass()
{
	Server->Events.PlayerConnects += { *this, &MapClass::whenPlayerConnects };
}

///////////////////////////////////////////////////////////////////////////////////////
Vehicle& MapClass::finalizeConstruction(ActorPtrType< Vehicle > const& vehicle_)
{
	m_vehicles.push_back(vehicle_);
	GameMode->Streamer->whenVehicleJoinsMap(*vehicle_);
	return *vehicle_;
}

///////////////////////////////////////////////////////////////////////////////////////
Vehicle& MapClass::finalizeConstruction(ActorPtrType< StaticVehicle > const& staticVehicle_)
{
	m_staticVehicles.push_back(staticVehicle_);
	GameMode->Streamer->whenStaticVehicleJoinsMap(*staticVehicle_);
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
Vehicle* MapClass::findVehicleByHandle(std::int32_t const vehicleHandle_)
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

		for(auto & player : GameMode->Players.getPool())
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
