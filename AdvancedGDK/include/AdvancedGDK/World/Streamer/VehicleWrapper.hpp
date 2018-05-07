#pragma once

// PCH:
#include ADVANCEDGDK_PCH

// Base class:
#include <AdvancedGDK/World/Streamer/GlobalActorWrapper.hpp>
#include <AdvancedGDK/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>

namespace agdk
{
namespace default_streamer
{

class VehicleWrapper
	:
	public IGlobalActorWrapper,
	public IActorPlacementTracker
{
public:	

	/// <summary>
	/// Initializes a new instance of the <see cref="VehicleWrapper"/> class.
	/// </summary>
	VehicleWrapper();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="VehicleWrapper"/> class.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	VehicleWrapper(Vehicle & vehicle_);
	
	/// <summary>
	/// Sets pointer to the underlying vehicle.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	void setVehicle(Vehicle & vehicle_);
	
	/// <summary>
	/// Returns pointer to the underlying vehicle.
	/// </summary>
	/// <returns>Pointer to the underlying vehicle.</returns>
	Vehicle* getVehicle() const {
		return m_vehicle;
	}

	// Overridden methods from IGlobalActorWrapper:
	
	/// <summary>
	/// Changes vehicle visibility which depends on its visibility index.
	/// </summary>
	virtual void applyVisibility() override;

	/// <summary>
	/// Determines whether the specified player is in the visibility zone.
	/// </summary>
	/// <param name="placement_">The player's placement.</param>
	/// <returns>
	///		<c>true</c> if is in visibility zone; otherwise, <c>false</c>.
	/// </returns>
	virtual bool isPlayerInVisibilityZone(PlayerPlacement const& placement_) const override;
	
	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	virtual void whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_) override;

private:
	Vehicle* m_vehicle; // The underlying vehicle.
};


} // namespace default_streamer

} // namespace agdk
