#include "EnginePCH.hpp"

#include <SAMP-EDGEngine/World/Checkpoint.hpp>

namespace samp_edgengine
{

//////////////////////////////////////////////////////////////////////////////////////////////////////
Checkpoint::Checkpoint()
	:
	m_size{ 3 },
	m_intersectionRadius{ 3 },// a default size is 3m radius
	m_intersectionHeight{ 7 } // a default height is 7m radius
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Checkpoint::Checkpoint(math::Vector3f const& location_, float size_, float intersectionRadius_, float intersectionHeight_)
	:
	m_size{ size_ },
	m_intersectionRadius{ (intersectionRadius_ <= 0 ? m_size : intersectionRadius_) },
	m_intersectionHeight{ (intersectionHeight_ <= 0 ? 7.f : intersectionHeight_) }
{
	// Note: statically resolved virtual method does not matter here.
	this->setLocation(location_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Checkpoint::Checkpoint(Checkpoint const& other_)
	: Checkpoint{ other_.getLocation(), other_.getSize(), other_.getIntersectionRadius(), other_.getIntersectionHeight() }
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Checkpoint& Checkpoint::operator=(Checkpoint const& other_)
{
	this->setSize(other_.getSize());
	this->setLocation(other_.getLocation());
	this->setIntersectionHeight(other_.getIntersectionHeight());
	this->setIntersectionRadius(other_.getIntersectionRadius());
	this->setWorldAndMode(other_.getWorld(), other_.getWorldMode());
	this->setInteriorAndMode(other_.getInterior(), other_.getInteriorMode());
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Checkpoint::setPlacementTracker(I3DNodePlacementTracker* tracker_)
{
	m_placementTracker = tracker_;
	this->sendPlacementUpdate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
I3DNodePlacementTracker* Checkpoint::getPlacementTracker() const
{
	return m_placementTracker;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Checkpoint::sendPlacementUpdate()
{
	if (m_placementTracker)
		m_placementTracker->whenPlacementUpdateReceived( this->getPlacement() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
ActorPlacement Checkpoint::getPlacement() const
{
	return { this->getLocation(), this->getWorld(), this->getInterior() };
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Checkpoint::setSize(float size_)
{
	m_size = size_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Checkpoint::setIntersectionRadius(float intersectionRadius_)
{
	m_intersectionRadius = intersectionRadius_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Checkpoint::setIntersectionHeight(float intersectionHeight_)
{
	m_intersectionHeight = intersectionHeight_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
float Checkpoint::getSize() const
{
	return m_size;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
float Checkpoint::getIntersectionRadius() const
{
	return m_intersectionRadius;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
float Checkpoint::getIntersectionHeight() const
{
	return m_intersectionHeight;
}

////////////////////////////////////////////////////////////////////////////////////
bool operator==(Checkpoint const& lhs_, Checkpoint const& rhs_)
{
	return
		lhs_.getLocation()			== rhs_.getLocation()
		&& math::nearlyEqual(lhs_.getSize(), rhs_.getSize(), math::constants::MediumTolerance<float>)
		&& math::nearlyEqual(lhs_.getIntersectionHeight(), rhs_.getIntersectionHeight(), math::constants::MediumTolerance<float>)
		&& math::nearlyEqual(lhs_.getIntersectionRadius(), rhs_.getIntersectionRadius(), math::constants::MediumTolerance<float>)
		&& lhs_.getWorld()			== rhs_.getWorld()
		&& lhs_.getWorldMode()		== rhs_.getWorldMode()
		&& lhs_.getInterior()		== rhs_.getInterior()
		&& lhs_.getInteriorMode()	== rhs_.getInteriorMode();
		
}

////////////////////////////////////////////////////////////////////////////////////
bool operator!=(Checkpoint const& lhs_, Checkpoint const& rhs_)
{
	return !(lhs_ == rhs_);
}

}
