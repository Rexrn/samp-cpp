#pragma once

#include ADVANCEDGDK_PCH

// Wrappers:
#include <AdvancedGDK/World/Streamer/GlobalObjectWrapper.hpp>
#include <AdvancedGDK/World/Streamer/VehicleWrapper.hpp>
#include <AdvancedGDK/World/Streamer/PlayerWrapper.hpp>

// Wrappers' underlying object types:
#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>
#include <AdvancedGDK/World/MapObject/GlobalObject.hpp>


// Additional includes:
#include <AdvancedGDK/Core/MathInc.hpp>
#include <AdvancedGDK/Core/BasicInterfaces/NonCopyable.hpp>

namespace agdk
{

namespace default_streamer
{

/// <summary>
/// A container which collects every player, vehicle, object located inside its area.
/// </summary>
/// <seealso cref="INonCopyable" />
class Chunk
	: public INonCopyable
{
public:
	template <typename TType>
	using ActorContainer = std::vector< std::unique_ptr<TType> >;
	
	/// <summary>
	/// Intercepts the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void intercept(Player & player_);
	
	/// <summary>
	/// Intercepts the specified vehicle.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	void intercept(Vehicle & vehicle_);
	
	/// <summary>
	/// Intercepts the specified global object.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	void intercept(GlobalObject & globalObject_);
	
	/// <summary>
	/// Releases the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void release(Player & player_);
	
	/// <summary>
	/// Releases the specified vehicle.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	void release(Vehicle & vehicle_);
	
	/// <summary>
	/// Releases the specified global object.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	void release(GlobalObject & globalObject_);
			
	/// <summary>
	/// Adds the score around specified player.
	/// </summary>
	/// <param name="placement_">The player's placement.</param>
	void addScoreAroundPlayer(PlayerPlacement const & placement_);
		
	/// <summary>
	/// Subtracts the score around player.
	/// </summary>
	/// <param name="player_">The player's placement.</param>
	void subtractScoreAroundPlayer(PlayerPlacement const & placement_);
	
	/// <summary>
	/// Applies the global actors visibility.
	/// </summary>
	void applyGlobalActorsVisibility();

	/// <summary>
	/// Returns cref to contained list of the players.
	/// </summary>
	/// <returns>cref to contained list of the players.</returns>
	auto const& getPlayers() const {
		return m_players;
	}
	
	/// <summary>
	/// Returns cref to contained list of the vehicles.
	/// </summary>
	/// <returns>cref to contained list of the vehicles.</returns>
	auto const& getVehicles() const {
		return m_vehicles;
	}

	/// <summary>
	/// Returns cref to contained list of the global objects.
	/// </summary>
	/// <returns>cref to contained list of the global objects.</returns>
	auto const& getGlobalObjects() const {
		return m_globalObjects;
	}

private:
	ActorContainer< PlayerWrapper >				m_players;			// Player wrapper container.
	ActorContainer< VehicleWrapper >			m_vehicles;			// Vehicle wrapper container.
	ActorContainer< GlobalObjectWrapper >		m_globalObjects;	// Global object wrapper container.
};

}

} // namespace agdk