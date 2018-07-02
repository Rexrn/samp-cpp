#include "SAMP-EDGEnginePCH.hpp"

#include <SAMP-EDGEngine/World/Streamer/VehicleWrapper.hpp>

// Additional headers:
#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/World/Streamer/StreamerSettings.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine::default_streamer
{

///////////////////////////////////////////////////////////////////////////
VehicleWrapper::VehicleWrapper(Vehicle& vehicle_)
	:
	I3DNodePlacementTracker(vehicle_.getPlacement()),
	m_vehicle{ &vehicle_ }
{
	m_vehicle->setPlacementTracker(this);
}

///////////////////////////////////////////////////////////////////////////
void VehicleWrapper::setVehicle(Vehicle& vehicle_)
{
	if (m_vehicle)
		m_vehicle->setPlacementTracker(nullptr);

	m_vehicle = &vehicle_;
	m_vehicle->setPlacementTracker(this);
}

///////////////////////////////////////////////////////////////////////////
void VehicleWrapper::applyVisibility()
{
	if (this->shouldBeVisible() && !m_vehicle->isSpawned())
	{
		m_vehicle->spawn();
	}
	else if (!this->shouldBeVisible() && m_vehicle->isSpawned())
	{
		m_vehicle->despawn();
	}
}

///////////////////////////////////////////////////////////////////////////
bool VehicleWrapper::isPlayerInVisibilityZone(PlayerPlacement const& placement_) const
{
	return	placement_.world == m_vehicle->getWorld() &&
			placement_.interior == m_vehicle->getInterior() &&
			placement_.location.distanceSquared(m_vehicle->getLocation()) <= StreamerSettings.getVisibilityDistanceSquared().value;
}

///////////////////////////////////////////////////////////////////////////
void VehicleWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	GameMode->Streamer->whenVehiclePlacementChanges(*m_vehicle, prevPlacement_, newPlacement_);
}

}
