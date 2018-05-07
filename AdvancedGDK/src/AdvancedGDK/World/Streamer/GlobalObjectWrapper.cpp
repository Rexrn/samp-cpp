#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/GlobalObjectWrapper.hpp>

// Additional includes:
#include <AdvancedGDK/Server/Player/Player.hpp>
#include <AdvancedGDK/World/Streamer/StreamerSettings.hpp>

namespace agdk::default_streamer
{

////////////////////////////////////////////////////////////////////////
GlobalObjectWrapper::GlobalObjectWrapper()
	: m_object{ nullptr }
{
}

////////////////////////////////////////////////////////////////////////
GlobalObjectWrapper::GlobalObjectWrapper(GlobalObject& object_)
	: m_object{ &object_ }
{
}

////////////////////////////////////////////////////////////////////////
void GlobalObjectWrapper::setObject(GlobalObject& object_)
{
	m_object = &object_;
}

////////////////////////////////////////////////////////////////////////
void GlobalObjectWrapper::applyVisibility()
{
	if (this->shouldBeVisible() && !m_object->isSpawned())
	{
		m_object->spawn();
	}
	else if (!this->shouldBeVisible() && m_object->isSpawned())
	{
		m_object->despawn();
	}
}

////////////////////////////////////////////////////////////////////////
bool GlobalObjectWrapper::isPlayerInVisibilityZone(PlayerPlacement const& placement_) const
{
	return (m_object->getLocation().distanceSquared(placement_.location) <= StreamerSettings.getVisibilityDistanceSquared().value);
}

////////////////////////////////////////////////////////////////////////
void GlobalObjectWrapper::whenPlacementChanges(GlobalObjectPlacement const& prevPlacement_, GlobalObjectPlacement const& newPlacement_)
{
	// TODO: implement this:
	// Find a way to notify streamer without breaking SOLID.
	// Possibly by interface (like the abstraction layers work).
}

}
