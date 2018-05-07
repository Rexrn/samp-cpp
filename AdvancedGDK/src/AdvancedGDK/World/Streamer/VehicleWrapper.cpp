#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/VehicleWrapper.hpp>

// Additional headers:
#include <AdvancedGDK/Server/Player/Player.hpp>
#include <AdvancedGDK/World/Streamer/StreamerSettings.hpp>

namespace agdk::default_streamer
{

///////////////////////////////////////////////////////////////////////////
VehicleWrapper::VehicleWrapper()
	: m_vehicle{ nullptr }
{
}

///////////////////////////////////////////////////////////////////////////
VehicleWrapper::VehicleWrapper(Vehicle& vehicle_)
	: m_vehicle{ &vehicle_ }
{
}

///////////////////////////////////////////////////////////////////////////
void VehicleWrapper::setVehicle(Vehicle& vehicle_)
{
	m_vehicle = &vehicle_;
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
	return placement_.world == m_vehicle->getWorld() &&
		placement_.interior == m_vehicle->getInterior() &&
		placement_.location.distanceSquared(m_vehicle->getLocation()) <= StreamerSettings.getVisibilityDistanceSquared().value;
}

///////////////////////////////////////////////////////////////////////////
void VehicleWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	// TODO: implement this:
	// Find a way to notify streamer without breaking SOLID.
	// Possibly by interface (like the abstraction layers work).
}

}
