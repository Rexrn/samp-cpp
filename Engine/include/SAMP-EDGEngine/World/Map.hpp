#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/World/Vehicle.hpp>
#include <SAMP-EDGEngine/World/Scene.hpp>
#include <SAMP-EDGEngine/World/RemovedBuilding.hpp>

#include <SAMP-EDGEngine/Core/Pointers.hpp>
#include <SAMP-EDGEngine/Core/Events.hpp>
#include <SAMP-EDGEngine/World/GangZone.hpp>

namespace samp_edgengine
{

/// <summary>
/// 
/// </summary>
class MapClass
	:
	public IEventReceiver
{
public:
	template <typename TType>
	using ActorPtrType			= SharedPtr<TType>;
	template <typename TType>
	using ActorContainerType	= std::vector< ActorPtrType<TType> >;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="MapClass"/> class.
	/// </summary>
	MapClass();

	/// <summary>
	/// Constructs specified thing on the map (either vehicle, static vehicle or scene).
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>Reference to the constructed thing.</returns>
	template <typename TType, typename... TArgTypes>
	TType& construct(TArgTypes&&...args_)
	{
		return this->finalizeConstruction( this->beginConstruction<TType>( std::forward<TArgTypes>( args_)... ) );
	}

	/// <summary>
	/// Begins construction of the specified thing (either vehicle, static vehicle or scene; it is not added yet to the map).
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>The only owning pointer to the constructed thing.</returns>
	template <typename TType, typename... TArgTypes>
	ActorPtrType<TType> beginConstruction(TArgTypes&&...args_)
	{
		return std::make_shared<TType>( std::forward<TArgTypes>( args_)... );
	}

	/// <summary>
	/// Finalizes the vehicle construction - adds it to the pool.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	/// <returns>Reference to created vehicle.</returns>
	Vehicle& finalizeConstruction(ActorPtrType< Vehicle > const& vehicle_);

	/// <summary>
	/// Finalizes the static vehicle construction - adds it to the pool.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	/// <returns>Reference to created static vehicle.</returns>
	Vehicle& finalizeConstruction(ActorPtrType< StaticVehicle > const& staticVehicle_);

	/// <summary>
	/// Finalizes the scene construction - adds it to the pool.
	/// </summary>
	/// <param name="scene_">The scene.</param>
	/// <returns>Reference to created scene vehicle.</returns>
	Scene& finalizeConstruction(ActorPtrType< Scene > const& scene_);

	/// <summary>
	/// Finalizes the gang zone construction - adds it to the pool.
	/// </summary>
	/// <param name="gangZone_">The gang zone.</param>
	/// <returns>Reference to created gang zone.</returns>
	GangZone& finalizeConstruction(ActorPtrType< GangZone > const& gangZone_);
	
	/// <summary>
	/// Removes the specified gang zone.
	/// </summary>
	/// <param name="gangZone_">The gang zone.</param>
	/// <returns>
	///		<c>true</c> if gang zone existed and was removed; otherwise, <c>false</c>.
	/// </returns>
	bool remove(GangZone const & gangZone_);

	/// <summary>
	/// Finds the vehicle using SAMP handle.
	/// </summary>
	/// <param name="handle_">The handle.</param>
	/// <returns>Pointer to found vehicle or nullptr if vehicle with this handle does not exist.</returns>
	Vehicle* findVehicleByHandle(std::int32_t const vehicleHandle_);
		
	/// <summary>
	/// Removes specified building (an original map object).
	/// </summary>
	/// <param name="removedBuilding_">The removed building.</param>
	void removeBuilding(RemovedBuilding const & removedBuilding_);

	/// <summary>
	/// Returns cref to vehicle pool.
	/// </summary>
	/// <returns>cref to vehicle pool.</returns>
	auto const& getVehicles() const {
		return m_vehicles;
	}
	
	/// <summary>
	/// Returns cref to static vehicle pool.
	/// </summary>
	/// <returns>cref to static vehicle pool.</returns>
	auto const& getStaticVehicles() const {
		return m_staticVehicles;
	}
	
	/// <summary>
	/// Returns cref to scene pool.
	/// </summary>
	/// <returns>cref to scene pool.</returns>
	auto const& getScenes() const {
		return m_scenes;
	}

private:	
	
	/// <summary>
	/// Whens the player connects.
	/// </summary>
	/// <param name="player_">The player.</param>
	void whenPlayerConnects(Player & player_);

	/// <summary>
	/// Applies the removed building to the player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="building_">The building.</param>
	void applyRemovedBuilding(Player& player_, RemovedBuilding const& building_);

	/// <summary>
	/// Removes buildings for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void applyRemovedBuildings(Player & player_);

	ActorContainerType< Vehicle >		m_vehicles;
	ActorContainerType< StaticVehicle >	m_staticVehicles;
	ActorContainerType< Scene >			m_scenes;
	ActorContainerType< GangZone >		m_gangZones;

	std::vector< RemovedBuilding >		m_removedBuildings;
};

}
