#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/MapObject/PerPlayerObject.hpp>
#include <AdvancedGDK/World/Streaming/Chunk.hpp>

#include <AdvancedGDK/Server/Server.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>

namespace agdk
{

////////////////////////////////////////////////////////////////////////
PerPlayerObject::PerPlayerObject()
	:
	m_worldVisibility{ VisibilityMode::Everywhere },
	m_interiorVisibility{ VisibilityMode::Everywhere }
{
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setWorld(std::int32_t const world_, VisibilityMode const visibilityMode_)
{
	IWIActor::setWorld(world_);
	m_worldVisibility = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setWorldVisibility(VisibilityMode const visibilityMode_)
{
	m_worldVisibility = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setInterior(std::int32_t const interior_, VisibilityMode const visibilityMode_)
{
	IWIActor::setInterior(interior_);
	m_interiorVisibility = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void PerPlayerObject::setInteriorVisibility(VisibilityMode const visibilityMode_)
{
	m_interiorVisibility = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
bool PerPlayerObject::shouldBeVisibleIn(std::int32_t const world_, std::int32_t const interior_) const
{
	return ((	(m_worldVisibility		== VisibilityMode::Everywhere)									||
				(m_worldVisibility		== VisibilityMode::Specified		&& m_world == world_)		||
				(m_worldVisibility		== VisibilityMode::AllButSpecified	&& m_world != world_))		&&
			(	(m_interiorVisibility	== VisibilityMode::Everywhere)									||
				(m_interiorVisibility	== VisibilityMode::Specified		&& m_interior == interior_)	||
				(m_interiorVisibility	== VisibilityMode::AllButSpecified	&& m_interior != interior_)));
}


}