#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/Chunk.hpp>

namespace agdk::default_streamer
{

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(Player& player_)
{
	m_players.emplace_back( std::make_unique<PlayerWrapper>(player_) );
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(Vehicle& vehicle_)
{
	m_vehicles.emplace_back( std::make_unique<VehicleWrapper>( vehicle_ ) );
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(GlobalObject& globalObject_)
{
	m_globalObjects.emplace_back( std::make_unique<GlobalObjectWrapper>( globalObject_ ) );
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::release(Player& player_)
{
	auto const it = std::find_if(m_players.begin(), m_players.end(),
		[&player_](std::unique_ptr<PlayerWrapper> const& element_)
		{
			return element_->getPlayer() == &player_;
		});

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
		[&vehicle_](std::unique_ptr<VehicleWrapper> const& element_)
		{
			return element_->getVehicle() == &vehicle_;
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
		[&globalObject_](std::unique_ptr<GlobalObjectWrapper> const& element_)
		{
			return element_->getObject() == &globalObject_;
		});

#ifdef ADVANCEDGDK_DEBUG
	// # Assertion note:
	// You tried to release vehicle that does not belong to this chunk. Fix your code.
	assert(it != m_globalObjects.end());
#endif

	// STREAMER P-TODO: consider IChunkActor::setChunk.
	m_globalObjects.erase(it);
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::addScoreAroundPlayer(PlayerPlacement const & placement_)
{
	for(auto &globalObject : m_globalObjects) 
	{
		if (globalObject->isPlayerInVisibilityZone(placement_))
			globalObject->whenPlayerEntersVisibilityZone();
	}
	for (auto &vehicle : m_vehicles)
	{
		if (vehicle->isPlayerInVisibilityZone(placement_))
			vehicle->whenPlayerEntersVisibilityZone();
	}
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::subtractScoreAroundPlayer(PlayerPlacement const & placement_)
{
	for (auto &globalObject : m_globalObjects)
	{
		if (globalObject->isPlayerInVisibilityZone(placement_))
			globalObject->whenPlayerEntersVisibilityZone();
	}
	for (auto &vehicle : m_vehicles)
	{
		if (vehicle->isPlayerInVisibilityZone(placement_))
			vehicle->whenPlayerEntersVisibilityZone();
	}
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::applyGlobalActorsVisibility()
{
	for (auto &globalObject : m_globalObjects)
		globalObject->applyVisibility();
	for (auto &vehicle : m_vehicles)
		vehicle->applyVisibility();
}

}
