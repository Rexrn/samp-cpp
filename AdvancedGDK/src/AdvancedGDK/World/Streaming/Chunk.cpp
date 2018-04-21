#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streaming/Chunk.hpp>
#include <AdvancedGDK/World/Vehicle/Vehicle.hpp>

namespace agdk
{

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(Player& player_)
{
	m_players.emplace_back( &player_ );
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(Vehicle& vehicle_)
{
	m_vehicles.emplace_back( std::make_unique<VehicleChunkActor>(vehicle_) );
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(GlobalObject& globalObject_)
{
	m_globalObjects.emplace_back( std::make_unique<GlobalObjectChunkActor>(globalObject_) );
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::release(Player& player_)
{
	auto const it = std::find(m_players.begin(), m_players.end(), &player_);

#ifdef ADVANCEDGDK_DEBUG
		// # Assertion note:
		// You tried to release player that does not belong to this chunk. Fix your code.
		assert(it != m_players.end());
#endif

	m_players.erase(it);
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::release(Vehicle& vehicle_)
{
	auto const it = std::find_if(m_vehicles.begin(), m_vehicles.end(),
		[&vehicle_](std::unique_ptr<VehicleChunkActor> const& element_)
		{
			return element_->getActor() == &vehicle_;
		});

#ifdef ADVANCEDGDK_DEBUG
	// # Assertion note:
	// You tried to release vehicle that does not belong to this chunk. Fix your code.
	assert(it != m_vehicles.end());
#endif

	// STREAMER P-TODO: consider IChunkActor::setChunk.
	m_vehicles.erase(it);
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::release(GlobalObject& globalObject_)
{
	auto const it = std::find_if(m_globalObjects.begin(), m_globalObjects.end(),
		[&globalObject_](std::unique_ptr<GlobalObjectChunkActor> const& element_)
		{
			return element_->getActor() == &globalObject_;
		});

#ifdef ADVANCEDGDK_DEBUG
	// # Assertion note:
	// You tried to release vehicle that does not belong to this chunk. Fix your code.
	assert(it != m_globalObjects.end());
#endif

	// STREAMER P-TODO: consider IChunkActor::setChunk.
	m_globalObjects.erase(it);
}

}
