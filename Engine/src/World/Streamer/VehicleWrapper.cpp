#include SAMPEDGENGINE_PCH

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
	auto lp = this->getLastPlacement();

	return	placement_.world == lp.world &&
			placement_.interior == lp.interior &&
			placement_.location.distanceSquared(lp.location) <= StreamerSettings.getVisibilityDistanceSquared().value;
}

///////////////////////////////////////////////////////////////////////////
void VehicleWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	GameMode->streamer->whenVehiclePlacementChanges(*m_vehicle, prevPlacement_, newPlacement_);
}

}
