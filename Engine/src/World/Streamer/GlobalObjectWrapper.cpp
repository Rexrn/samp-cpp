#include SAMPCPP_PCH

#include <SAMPCpp/World/Streamer/GlobalObjectWrapper.hpp>

// Additional includes:
#include <SAMPCpp/Server/Player.hpp>
#include <SAMPCpp/World/Streamer/StreamerSettings.hpp>
#include <SAMPCpp/Server/GameMode.hpp>

namespace samp_cpp::default_streamer
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
	return (this->getLastPlacement().location.distanceSquared(placement_.location) <= StreamerSettings.getVisibilityDistanceSquared().value);
}

////////////////////////////////////////////////////////////////////////
void GlobalObjectWrapper::whenPlacementChanges(GlobalObjectPlacement const& prevPlacement_, GlobalObjectPlacement const& newPlacement_)
{
	GameMode->streamer->whenObjectPlacementChanges(*m_object, prevPlacement_, newPlacement_);
}

///////////////////////////////////////////////////////////////////////////
math::Vector3f GlobalObjectWrapper::getLocation() const
{
	return this->getLastPlacement().location;
}

}
