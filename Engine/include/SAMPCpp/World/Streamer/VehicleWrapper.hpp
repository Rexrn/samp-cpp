#pragma once
#include SAMPCPP_PCH



// Base class:
#include <SAMPCpp/World/Streamer/GlobalActorWrapper.hpp>
#include <SAMPCpp/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <SAMPCpp/World/Vehicle.hpp>

namespace samp_cpp
{
namespace default_streamer
{

class VehicleWrapper
	:
	public IGlobalActorWrapper,
	public I3DNodePlacementTracker
{
public:	

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

	/// <summary>Returns the location.</summary>
	/// <returns>math::Vector3f</returns>
	virtual math::Vector3f getLocation() const override;
private:
	Vehicle* m_vehicle; // The underlying vehicle.
};


} // namespace default_streamer

} // namespace agdk
