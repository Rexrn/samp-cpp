#include <SAMP-EDGEngine/World/PerPlayerObject.hpp>
#include <SAMP-EDGEngine/World/Streamer/Chunk.hpp>

#include <SAMP-EDGEngine/Server/Server.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////
PerPlayerObject::PerPlayerObject()
	:
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
void PerPlayerObject::setWorldAndMode(Int32 world_, VisibilityMode visibilityMode_)
{
	IWI3DStreamableNode::setWorldAndMode(world_, visibilityMode_);

	this->sendPlacementUpdate();
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setWorldMode(VisibilityMode visibilityMode_)
{
	IWI3DStreamableNode::setWorldMode(visibilityMode_);

	this->sendPlacementUpdate();
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setInteriorAndMode(Int32 interior_, VisibilityMode visibilityMode_)
{
	IWI3DStreamableNode::setInteriorAndMode(interior_, visibilityMode_);

	this->sendPlacementUpdate();
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setInteriorMode(VisibilityMode visibilityMode_)
{
	IWI3DStreamableNode::setInteriorMode(visibilityMode_);

	this->sendPlacementUpdate();
}

}