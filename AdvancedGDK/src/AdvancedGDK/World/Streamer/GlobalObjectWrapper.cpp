#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/GlobalObjectWrapper.hpp>

// Additional includes:
#include <AdvancedGDK/Server/Player.hpp>
#include <AdvancedGDK/World/Streamer/StreamerSettings.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>

namespace agdk::default_streamer
{

////////////////////////////////////////////////////////////////////////
GlobalObjectWrapper::GlobalObjectWrapper(GlobalObject& object_)
	:
	IGlobalObjectPlacementTracker(object_.getPlacement()),
	m_object{ &object_ }
{
	m_object->setPlacementTracker(this);
}

////////////////////////////////////////////////////////////////////////
void GlobalObjectWrapper::setObject(GlobalObject& object_)
{
	if (m_object)
		m_object->setPlacementTracker(nullptr);

	m_object = &object_;
	m_object->setPlacementTracker(this);
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
	GameMode->Streamer->whenObjectPlacementChanges(*m_object, prevPlacement_, newPlacement_);
}

}
