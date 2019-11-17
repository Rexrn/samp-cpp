#include SAMPCPP_PCH

#include <SAMPCpp/World/Streamer/UniversalObjectWrapper.hpp>
#include <SAMPCpp/Server/GameMode.hpp>

namespace samp_cpp
{

namespace default_streamer
{

//////////////////////////////////////////////////////////////////////////////
UniversalObjectWrapper::UniversalObjectWrapper(UniversalObject& object_)
	:
	I3DNodePlacementTracker(object_.getPlacement()),
	m_object{ &object_ }
{
	m_object->setPlacementTracker(this);
}

//////////////////////////////////////////////////////////////////////////////
void UniversalObjectWrapper::setObject(UniversalObject& object_)
{
	m_object = &object_;
	m_object->setPlacementTracker(this);
}

//////////////////////////////////////////////////////////////////////////////
void UniversalObjectWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	if(m_object)
	{
		GameMode->streamer->whenObjectPlacementChanges(*m_object, prevPlacement_, newPlacement_);
	}
}

}

}
