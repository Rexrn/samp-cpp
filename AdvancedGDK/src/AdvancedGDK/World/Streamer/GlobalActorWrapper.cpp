#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/GlobalActorWrapper.hpp>

namespace agdk::default_streamer
{

/////////////////////////////////////////////////////////////////////////////////
IGlobalActorWrapper::IGlobalActorWrapper()
	: m_visibilityIndex{ 0 }
{
}

/////////////////////////////////////////////////////////////////////////////////
void IGlobalActorWrapper::whenPlayerEntersVisibilityZone()
{
	m_visibilityIndex++;
}

/////////////////////////////////////////////////////////////////////////////////
void IGlobalActorWrapper::whenPlayerLeavesVisibilityZone()
{
	if (m_visibilityIndex > 0)
		m_visibilityIndex--;
	else
		throw ReferenceCountingError("More players exited area than entered - counting mismatch.");
}

/////////////////////////////////////////////////////////////////////////////////
std::uint16_t IGlobalActorWrapper::getVisibilityIndex() const
{
	return m_visibilityIndex;
}

}
