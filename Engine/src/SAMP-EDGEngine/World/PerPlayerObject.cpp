#include "EnginePCH.hpp"

#include <SAMP-EDGEngine/World/PerPlayerObject.hpp>
#include <SAMP-EDGEngine/World/Streamer/Chunk.hpp>

#include <SAMP-EDGEngine/Server/Server.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////
PerPlayerObject::PerPlayerObject()
	:
	m_worldMode{ VisibilityMode::Everywhere },
	m_interiorMode{ VisibilityMode::Everywhere },
	m_placementTracker{ nullptr }
{
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setPlacementTracker(I3DNodePlacementTracker* tracker_)
{
	m_placementTracker = tracker_;
	this->sendPlacementUpdate();
}

////////////////////////////////////////////////////////////////////////
I3DNodePlacementTracker* PerPlayerObject::getPlacementTracker() const
{
	return m_placementTracker;
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::sendPlacementUpdate()
{
	if (m_placementTracker) {
		m_placementTracker->whenPlacementUpdateReceived( this->getPlacement() );
	}
}

////////////////////////////////////////////////////////////////////////
ActorPlacement PerPlayerObject::getPlacement() const
{
	return { this->getLocation(), this->getWorld(), this->getInterior() };
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setWorldAndMode(std::int32_t const world_, VisibilityMode const visibilityMode_)
{
	IWI3DNode::setWorld(world_);
	m_worldMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setWorldMode(VisibilityMode const visibilityMode_)
{
	m_worldMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setInteriorAndMode(std::int32_t const interior_, VisibilityMode const visibilityMode_)
{
	IWI3DNode::setInterior(interior_);
	m_interiorMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setInteriorMode(VisibilityMode const visibilityMode_)
{
	m_interiorMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
bool PerPlayerObject::shouldBeVisibleIn(std::int32_t const world_, std::int32_t const interior_) const
{
	return ((	(m_worldMode		== VisibilityMode::Everywhere)									||
				(m_worldMode		== VisibilityMode::Specified		&& m_world == world_)		||
				(m_worldMode		== VisibilityMode::AllButSpecified	&& m_world != world_))		&&
			(	(m_interiorMode	== VisibilityMode::Everywhere)									||
				(m_interiorMode	== VisibilityMode::Specified		&& m_interior == interior_)	||
				(m_interiorMode	== VisibilityMode::AllButSpecified	&& m_interior != interior_)));
}


}