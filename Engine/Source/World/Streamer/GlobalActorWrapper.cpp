#include <SAMP-EDGEngine/World/Streamer/GlobalActorWrapper.hpp>

namespace samp_edgengine::default_streamer
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
void IGlobalActorWrapper::setVisibilityIndex(Uint16 visibilityIndex_)
{
	m_visibilityIndex = visibilityIndex_;
}

/////////////////////////////////////////////////////////////////////////////////
Uint16 IGlobalActorWrapper::getVisibilityIndex() const
{
	return m_visibilityIndex;
}

}
