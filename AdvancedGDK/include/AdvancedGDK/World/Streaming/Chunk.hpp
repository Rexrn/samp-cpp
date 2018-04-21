#pragma once

#include ADVANCEDGDK_PCH

#include "ChunkActor.hpp"
#include "VehicleChunkActor.hpp"
#include "GlobalObjectChunkActor.hpp"

#include <AdvancedGDK/Core/MathInc.hpp>
#include <AdvancedGDK/Core/BasicInterfaces/NonCopyable.hpp>


namespace agdk
{
class IMapObject;
class Vehicle;
class Player;
class GlobalObject;

class Chunk
	: public INonCopyable
{
public:
	template <typename TType>
	using ActorContainer = std::vector< std::unique_ptr<TType> >;
	
	void intercept(Player & player_);
	void intercept(Vehicle & vehicle_);
	void intercept(GlobalObject & globalObject_);

	void release(Player & player_);
	void release(Vehicle & vehicle_);
	void release(GlobalObject & globalObject_);

	auto const& getPlayers() const {
		return m_players;
	}

	auto const& getVehicles() const {
		return m_vehicles;
	}

	auto const& getGlobalObjects() const {
		return m_globalObjects;
	}
private:
	std::vector< Player* >						m_players;
	ActorContainer< VehicleChunkActor >			m_vehicles;
	ActorContainer< GlobalObjectChunkActor >	m_globalObjects;
};

}
