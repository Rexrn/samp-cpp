#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/Core/BasicInterfaces/PlacementTracker.hpp>

namespace agdk
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IActorPlacementTracker::whenPlacementUpdateReceived(ActorPlacement const& newPlacement_)
{
	if (this->isSignificantChange(newPlacement_))
	{
		this->whenPlacementChanges(m_lastPlacement, newPlacement_);
		m_lastPlacement = newPlacement_;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IActorPlacementTracker::isSignificantChange(ActorPlacement const& newPlacement_) const
{
	return	newPlacement_.world != m_lastPlacement.world ||
			newPlacement_.interior != m_lastPlacement.interior ||
			newPlacement_.location.distanceSquared(m_lastPlacement.location) >= default_streamer::StreamerSettings.getMaxDisplacementDistanceSquared().value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IGlobalObjectPlacementTracker::whenPlacementUpdateReceived(GlobalObjectPlacement const& newPlacement_)
{
	if (this->isSignificantChange(newPlacement_))
	{
		this->whenPlacementChanges(m_lastPlacement, newPlacement_);
		m_lastPlacement = newPlacement_;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IGlobalObjectPlacementTracker::isSignificantChange(GlobalObjectPlacement const& newPlacement_) const
{
	return newPlacement_.location.distanceSquared(m_lastPlacement.location) >= default_streamer::StreamerSettings.getMaxDisplacementDistanceSquared().value;
}

}
