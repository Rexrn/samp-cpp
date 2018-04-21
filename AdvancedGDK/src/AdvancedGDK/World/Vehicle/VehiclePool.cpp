#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Vehicle/VehiclePool.hpp>
#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>

namespace agdk
{

/////////////////////////////////////////////////////////////////////////////////////////////
bool VehiclePool::destroy(Vehicle & vehicle_)
{
	// Check whether vehicle exists in whole pool:
	auto itInWholePool = std::find_if(m_vehicles.begin(), m_vehicles.end(),
		[&vehicle_](auto const &e_) { return e_.get() == &vehicle_; });

	// Proceed only if exists
	if (itInWholePool != m_vehicles.end())
	{
		// Check if vehicle is occupied, if so - remove it:
		{
			auto it = std::find_if(m_occupiedVehicles.begin(), m_occupiedVehicles.end(),
				[&vehicle_](auto const &e_) { return e_ == &vehicle_; });
			if (it != m_occupiedVehicles.end())
				m_occupiedVehicles.erase(it);
		}

		// Check if vehicle is spawned, if so - remove it:
		{
			auto it = std::find_if(m_spawnedVehicles.begin(), m_spawnedVehicles.end(),
				[&vehicle_](auto const &e_) { return e_ == &vehicle_; });
			if (it != m_spawnedVehicles.end())
				m_spawnedVehicles.erase(it);
		}

		// Erase vehicle from the whole pool
		m_vehicles.erase(itInWholePool);
		// Vehicle gets automatically despawned here.
		return true;
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool VehiclePool::exists(Vehicle & vehicle_) const
{
	return std::find_if(m_vehicles.begin(), m_vehicles.end(), [&vehicle_](auto const &e_) { return e_.get() == &vehicle_; }) != m_vehicles.end();
}

/////////////////////////////////////////////////////////////////////////////////////////////
Vehicle* VehiclePool::findVehicle(std::int32_t const vehicleHandle_)
{
	auto it = std::find_if(m_spawnedVehicles.begin(), m_spawnedVehicles.end(),
		[vehicleHandle_](Vehicle * veh_) {
			return veh_->getHandle() == vehicleHandle_;
		});
	return (it != m_spawnedVehicles.end() ? *it : nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool VehiclePool::add(std::unique_ptr<Vehicle>&& vehicle_)
{
	if ( !this->exists(*vehicle_) ) {
		m_vehicles.push_back(std::forward< std::unique_ptr<Vehicle> >(vehicle_));
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void VehiclePool::whenPlayerDisconnects(Player & player_)
{
	if (auto vehicle = player_.getVehicle())
		vehicle->whenPlayerExits(player_);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void VehiclePool::whenPlayerChangesState(Player & player_, std::int32_t const newState_, std::int32_t const oldState_)
{
	if (oldState_ == PLAYER_STATE_DRIVER && newState_ != PLAYER_STATE_DRIVER)
	{
		// For a single moment player have still saved pointer to the vehicle.
		if (auto vehicle = player_.getVehicle())
			vehicle->whenPlayerExits(player_);
		// player_.getVehicle() becomes nullptr at the end of the Server::SampEvents::sampEventOnPlayerChangedState (TODO)
	}
	else if (oldState_ == PLAYER_STATE_PASSENGER && newState_ != PLAYER_STATE_PASSENGER)
	{
		// For a single moment player have still saved pointer to the vehicle.
		if (auto vehicle = player_.getVehicle())
			vehicle->whenPlayerExits(player_);
		// player_.getVehicle() becomes nullptr at the end of the Server::SampEvents::sampEventOnPlayerChangedState (TODO).
	}
	else if (oldState_ != PLAYER_STATE_DRIVER && newState_ == PLAYER_STATE_DRIVER)
	{
		auto vehicle = this->findVehicle(player_.getClientVehicle());
		if (vehicle)
			vehicle->whenPlayerEnters(player_, 0);
	}
	else if (oldState_ != PLAYER_STATE_DRIVER && newState_ == PLAYER_STATE_PASSENGER)
	{
		auto vehicle = this->findVehicle(player_.getClientVehicle());
		if (vehicle)
			vehicle->whenPlayerEnters(player_, player_.getVehicleSeat());
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
void VehiclePool::whenVehicleConstructed(Vehicle & vehicle_)
{
	// TODO: implement this and the streamer.
}

}