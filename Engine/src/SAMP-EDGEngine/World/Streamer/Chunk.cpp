#include "EnginePCH.hpp"

#include <SAMP-EDGEngine/World/Streamer/Chunk.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine::default_streamer
{

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(UniquePtr<PlayerWrapper> && player_)
{
	player_->setChunk(*this);
	m_players.push_back( std::forward< UniquePtr<PlayerWrapper> >( player_ ) );

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingIntercepted();
#endif
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(UniquePtr<VehicleWrapper> && vehicle_)
{
	vehicle_->setChunk(*this);
	m_vehicles.push_back( std::forward< UniquePtr<VehicleWrapper> >( vehicle_ ) );

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingIntercepted();
#endif
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(UniquePtr<GlobalObjectWrapper> && globalObject_)
{
	globalObject_->setChunk(*this);
	m_globalObjects.push_back( std::forward< UniquePtr<GlobalObjectWrapper> >( globalObject_ ) );

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingIntercepted();
#endif
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(UniquePtr<UniversalObjectWrapper>&& universalObject_)
{
	universalObject_->setChunk(*this);
	m_universalObjects.push_back(std::forward< UniquePtr<UniversalObjectWrapper> >(universalObject_));
	
#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingIntercepted();
#endif
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::intercept(UniquePtr<PersonalObjectWrapper>&& personalObject_)
{
	personalObject_->setChunk(*this);
	m_personalObjects.push_back(std::forward< UniquePtr<PersonalObjectWrapper> >(personalObject_));

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingIntercepted();
#endif
}

//////////////////////////////////////////////////////////////////////////////
UniquePtr<PlayerWrapper> Chunk::release(Player const& player_)
{
	auto const it = std::find_if(m_players.begin(), m_players.end(),
		[&player_](UniquePtr<PlayerWrapper> const& element_)
		{
			return element_->getPlayer() == &player_;
		});

#ifdef SAMP_EDGENGINE_DEBUG
	// # Assertion note:
	// You tried to release player that does not belong to this chunk. Fix your code.
	assert(it != m_players.end());
#endif

	auto result = std::move(*it);
	result->setChunk(nullptr);
	m_players.erase(it);

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingReleased();
#endif

	return result;
}

//////////////////////////////////////////////////////////////////////////////
UniquePtr<VehicleWrapper> Chunk::release(Vehicle const & vehicle_)
{
	auto const it = std::find_if(m_vehicles.begin(), m_vehicles.end(),
		[&vehicle_](UniquePtr<VehicleWrapper> const& element_)
		{
			return element_->getVehicle() == &vehicle_;
		});

#ifdef SAMP_EDGENGINE_DEBUG
	// # Assertion note:
	// You tried to release vehicle that does not belong to this chunk. Fix your code.
	assert(it != m_vehicles.end());
#endif

	auto result = std::move(*it);
	result->setChunk(nullptr);
	m_vehicles.erase(it);

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingReleased();
#endif

	return result;
}

//////////////////////////////////////////////////////////////////////////////
UniquePtr<GlobalObjectWrapper> Chunk::release(GlobalObject const & globalObject_)
{
	auto const it = std::find_if(m_globalObjects.begin(), m_globalObjects.end(),
		[&globalObject_](UniquePtr<GlobalObjectWrapper> const& element_)
		{
			return element_->getObject() == &globalObject_;
		});

#ifdef SAMP_EDGENGINE_DEBUG
	// # Assertion note:
	// You tried to release global object that does not belong to this chunk. Fix your code.
	assert(it != m_globalObjects.end());
#endif

	auto result = std::move(*it);
	result->setChunk(nullptr);
	m_globalObjects.erase(it);

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingReleased();
#endif

	return result;
}

//////////////////////////////////////////////////////////////////////////////
UniquePtr<UniversalObjectWrapper> Chunk::release(UniversalObject const & universalObject_)
{
	auto const it = std::find_if(m_universalObjects.begin(), m_universalObjects.end(),
		[&universalObject_](UniquePtr<UniversalObjectWrapper> const& element_)
		{
			return element_->getObject() == &universalObject_;
		});

#ifdef SAMP_EDGENGINE_DEBUG
	// # Assertion note:
	// You tried to release personal object that does not belong to this chunk. Fix your code.
	assert(it != m_universalObjects.end());
#endif

	auto result = std::move(*it);
	result->setChunk(nullptr);
	m_universalObjects.erase(it);

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingReleased();
#endif

	return result;
}

//////////////////////////////////////////////////////////////////////////////
UniquePtr<PersonalObjectWrapper> Chunk::release(PersonalObject const & personalObject_)
{
	auto const it = std::find_if(m_personalObjects.begin(), m_personalObjects.end(),
		[&personalObject_](UniquePtr<PersonalObjectWrapper> const& element_)
		{
			return element_->getObject() == &personalObject_;
		});

#ifdef SAMP_EDGENGINE_DEBUG
	// # Assertion note:
	// You tried to release personal object that does not belong to this chunk. Fix your code.
	assert(it != m_personalObjects.end());
#endif

	auto result = std::move(*it);
	result->setChunk(nullptr);
	m_personalObjects.erase(it);

#ifdef SAMP_EDGENGINE_DEBUG
	this->GZThingReleased();
#endif

	return result;
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
			globalObject->whenPlayerLeavesVisibilityZone();
	}
	for (auto &vehicle : m_vehicles)
	{
		if (vehicle->isPlayerInVisibilityZone(placement_))
			vehicle->whenPlayerLeavesVisibilityZone();
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

#ifdef SAMP_EDGENGINE_DEBUG

//////////////////////////////////////////////////////////////////////////////
void Chunk::GZThingIntercepted()
{
	if (!this->isEmpty() && !m_gangZone)
	{
		auto gangZone = GameMode->Map.beginConstruction<samp_edgengine::GangZone>();

		auto start = m_debugInfo.center - m_debugInfo.halfExtent;
		auto end = start + (m_debugInfo.halfExtent * 2.f);
		gangZone->create({ start.x, start.y }, { end.x, end.y });
	
		m_gangZone = &GameMode->Map.finalizeConstruction(gangZone);
	}

	m_gangZone->hide();
	m_gangZone->show(this->GZCalculateColor());

	if (!m_players.empty())
		m_gangZone->flash(this->GZCalculateFlashingColor());
}

//////////////////////////////////////////////////////////////////////////////
void Chunk::GZThingReleased()
{
	if (this->isEmpty() && m_gangZone)
	{
		GameMode->Map.remove(*m_gangZone);
		m_gangZone = nullptr;
	}
	else
	{
		m_gangZone->hide();
		m_gangZone->show(this->GZCalculateColor());

		if (m_players.empty())
			m_gangZone->stopFlashing();
	}
}

//////////////////////////////////////////////////////////////////////////////
Color Chunk::GZCalculateColor()
{
	const std::size_t countOfObjects	= m_globalObjects.size() + m_universalObjects.size() + m_personalObjects.size() + m_vehicles.size();
	const std::uint8_t colorValue		= std::min(std::size_t(255), countOfObjects);
	return Color{ colorValue, colorValue, 0, 128 };
}

//////////////////////////////////////////////////////////////////////////////
Color Chunk::GZCalculateFlashingColor()
{
	auto c = colors::Blue;
	c.a = 128;
	return c;
}

#endif
}
