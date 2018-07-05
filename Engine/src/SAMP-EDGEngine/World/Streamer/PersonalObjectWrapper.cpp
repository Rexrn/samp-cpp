#include "EnginePCH.hpp"

#include <SAMP-EDGEngine/World/Streamer/PersonalObjectWrapper.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine
{

namespace default_streamer
{

//////////////////////////////////////////////////////////////////////////////
PersonalObjectWrapper::PersonalObjectWrapper(PersonalObject& object_)
	:
	I3DNodePlacementTracker(object_.getPlacement()),
	m_object{ &object_ }
{
}

//////////////////////////////////////////////////////////////////////////////
void PersonalObjectWrapper::setObject(PersonalObject& object_)
{
	m_object = &object_;
}

//////////////////////////////////////////////////////////////////////////////
void PersonalObjectWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	if (m_object)
	{
		GameMode->Streamer->whenObjectPlacementChanges(*m_object, prevPlacement_, newPlacement_);
	}
}

}

}
