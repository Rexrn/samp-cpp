#include <SAMP-EDGEngine/World/Streamer/UniversalObjectWrapper.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine
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
		GameMode->Streamer->whenObjectPlacementChanges(*m_object, prevPlacement_, newPlacement_);
	}
}

}

}
