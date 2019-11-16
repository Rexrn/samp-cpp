#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/World/RaceCheckpoint.hpp>

namespace samp_cpp
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
RaceCheckpoint::RaceCheckpoint(RaceCheckpoint const& other_)
	: RaceCheckpoint{ other_.getLocation(), other_.getLookAt(), other_.getType(), other_.getSize(), other_.getIntersectionRadius(), other_.getIntersectionHeight() }
{
}

////////////////////////////////////////////////////////////////////////////////////
RaceCheckpoint& RaceCheckpoint::operator=(RaceCheckpoint const& other_)
{
	this->setSize(other_.getSize());
	this->setLocation(other_.getLocation());
	this->setIntersectionHeight(other_.getIntersectionHeight());
	this->setIntersectionRadius(other_.getIntersectionRadius());
	this->setWorldAndMode(other_.getWorld(), other_.getWorldMode());
	this->setInteriorAndMode(other_.getInterior(), other_.getInteriorMode());
	this->setLookAt(other_.getLookAt());
	this->setType(other_.getType());
	return *this;
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

////////////////////////////////////////////////////////////////////////////////////
bool operator==(RaceCheckpoint const& lhs_, RaceCheckpoint const& rhs_)
{
	return
		lhs_.getLocation()			== rhs_.getLocation()
		&& math::nearlyEqual(lhs_.getSize(), rhs_.getSize(), math::constants::MediumTolerance<float>)
		&& math::nearlyEqual(lhs_.getIntersectionHeight(), rhs_.getIntersectionHeight(), math::constants::MediumTolerance<float>)
		&& math::nearlyEqual(lhs_.getIntersectionRadius(), rhs_.getIntersectionRadius(), math::constants::MediumTolerance<float>)
		&& lhs_.getWorld()			== rhs_.getWorld()
		&& lhs_.getWorldMode()		== rhs_.getWorldMode()
		&& lhs_.getInterior()		== rhs_.getInterior()
		&& lhs_.getInteriorMode()	== rhs_.getInteriorMode()
		&& lhs_.getLookAt()			== rhs_.getLookAt()
		&& lhs_.getType()			== rhs_.getType();
		
}

////////////////////////////////////////////////////////////////////////////////////
bool operator!=(RaceCheckpoint const& lhs_, RaceCheckpoint const& rhs_)
{
	return !(lhs_ == rhs_);
}
}
