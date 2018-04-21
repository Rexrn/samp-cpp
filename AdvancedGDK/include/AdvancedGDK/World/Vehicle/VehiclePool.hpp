#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/Core/Events.hpp>
#include <AdvancedGDK/Server/Player/Player.hpp>
#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>

namespace agdk
{

class VehiclePool final
	: public IEventReceiver
{
public:

	bool destroy(Vehicle & vehicle_);

	bool exists(Vehicle & vehicle_) const;

	Vehicle* findVehicle(std::int32_t const vehicleHandle_);

	friend class Vehicle;
	friend class StaticVehicle;
private:

	bool add(std::unique_ptr<Vehicle> && vehicle_);

	void whenPlayerDisconnects(Player & player_);

	void whenPlayerChangesState(Player & player_, std::int32_t const newState_, std::int32_t const oldState_);

	void whenVehicleConstructed(Vehicle & vehicle_);

	std::vector< std::unique_ptr<Vehicle> >		m_vehicles;
	std::vector< Vehicle * >					m_spawnedVehicles;
	std::vector< Vehicle * >					m_occupiedVehicles;
};
}