#include "SAMP-EDGEnginePCH.hpp"

#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

namespace agdk
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////
I3DNodePlacementTracker::I3DNodePlacementTracker(ActorPlacement const & initialPlacement_)
	: m_lastPlacement{ initialPlacement_ }
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void I3DNodePlacementTracker::whenPlacementUpdateReceived(ActorPlacement const& newPlacement_)
{
	if (this->isSignificantChange(newPlacement_))
	{
		this->whenPlacementChanges(m_lastPlacement, newPlacement_);
		m_lastPlacement = newPlacement_;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool I3DNodePlacementTracker::isSignificantChange(ActorPlacement const& newPlacement_) const
{
	return	newPlacement_.world != m_lastPlacement.world ||
			newPlacement_.interior != m_lastPlacement.interior ||
			newPlacement_.location.distanceSquared(m_lastPlacement.location) >= default_streamer::StreamerSettings.getMaxDisplacementDistanceSquared().value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
IGlobalObjectPlacementTracker::IGlobalObjectPlacementTracker(GlobalObjectPlacement const & initialPlacement_)
	: m_lastPlacement{ initialPlacement_ }
{
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
