#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>
#include <AdvancedGDK/World/Scene.hpp>

namespace agdk
{
	
class Map
{
public:
	template <typename TType>
	using ActorPtrType			= std::shared_ptr<TType>;
	template <typename TType>
	using ActorContainerType	= std::vector< ActorPtrType<TType> >;

	/// <summary>
	/// Begins the vehicle construction (it is not added yet to the map).
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>Owning pointer to the constructed vehicle.</returns>
	template <typename TType, typename... TArgTypes>
	ActorPtrType<TType> beginConstruction(TArgTypes&&...args_)
	{
		return std::make_shared<TType>( std::forward<TArgTypes>( args_)... );
	}

	/// <summary>
	/// Finalizes the vehicle construction - adds it to the pool.
	/// </summary>
	/// <param name="vehicle_">The vegucke.</param>
	/// <returns>Reference to created vehicle.</returns>
	Vehicle &finalizeConstruction( ActorPtrType<Vehicle> const &vehicle_ )
	{
		m_vehicles.push_back(vehicle_);
		return *vehicle_;
	}

	/// <summary>
	/// Finalizes the static vehicle construction - adds it to the pool.
	/// </summary>
	/// <param name="vehicle_">The vegucke.</param>
	/// <returns>Reference to created static vehicle.</returns>
	Vehicle &finalizeConstruction(ActorPtrType<StaticVehicle> const &staticVehicle_)
	{
		m_staticVehicles.push_back(staticVehicle_);
		return *staticVehicle_;
	}

	/// <summary>
	/// Finalizes the static vehicle construction - adds it to the pool.
	/// </summary>
	/// <param name="vehicle_">The vegucke.</param>
	/// <returns>Reference to created static vehicle.</returns>
	Scene &finalizeConstruction(ActorPtrType<Scene> const &scene_)
	{
		m_scenes.push_back(scene_);
		return *scene_;
	}

private:
	ActorContainerType< Vehicle >		m_vehicles;
	ActorContainerType< StaticVehicle >	m_staticVehicles;
	ActorContainerType< Scene >			m_scenes;
};

}
