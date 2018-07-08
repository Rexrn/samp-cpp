#include "EnginePCH.hpp"

#include <SAMP-EDGEngine/World/RaceCheckpoint.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////////////////
RaceCheckpoint::RaceCheckpoint()
	:
	m_type{ Type::Land }
{
}

////////////////////////////////////////////////////////////////////////////////////
RaceCheckpoint::RaceCheckpoint(math::Vector3f const& location_, math::Vector3f const& lookAt_, Type type_, float size_, float intersectionRadius_, float intersectionHeight_)
	:
	Checkpoint{ location_, size_, intersectionRadius_, intersectionHeight_ },
	m_lookAt{ lookAt_ },
	m_type{ type_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
void RaceCheckpoint::setLookAt(math::Vector3f const& lookAt_)
{
	m_lookAt = lookAt_;
}

////////////////////////////////////////////////////////////////////////////////////
void RaceCheckpoint::setType(Type type_)
{
	m_type = type_;
}

////////////////////////////////////////////////////////////////////////////////////
math::Vector3f RaceCheckpoint::getLookAt() const
{
	return m_lookAt;
}

////////////////////////////////////////////////////////////////////////////////////
RaceCheckpoint::Type RaceCheckpoint::getType() const
{
	return m_type;
}

}
