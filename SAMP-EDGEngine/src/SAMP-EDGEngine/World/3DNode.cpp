#include "SAMP-EDGEnginePCH.hpp"

#include <SAMP-EDGEngine/World/3DNode.hpp>

namespace agdk
{

/////////////////////////////////////////////////////////////////////
void I3DNode::setLocation(math::Vector3f const& location_)
{
	this->syncLocation(location_);
}

/////////////////////////////////////////////////////////////////////
void I3DNode::move(math::Vector3f const& delta_)
{
	this->setLocation(this->getLocation() + delta_);
}

/////////////////////////////////////////////////////////////////////
math::Vector3f I3DNode::getLocation() const
{
	return m_storedLocation;
}

/////////////////////////////////////////////////////////////////////
void I3DNode::syncLocation(math::Vector3f const& location_)
{
	m_storedLocation = location_;
}

} // namespace agdk
