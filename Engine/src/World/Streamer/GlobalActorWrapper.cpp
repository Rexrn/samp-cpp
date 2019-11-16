#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/World/Streamer/GlobalActorWrapper.hpp>

namespace samp_cpp::default_streamer
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
	//if (m_visibilityIndex > 0)
	
	m_visibilityIndex--;
	
	// else
	// 		throw ReferenceCountingError("More players exited area than entered - counting mismatch.");
}

/////////////////////////////////////////////////////////////////////////////////
void IGlobalActorWrapper::setVisibilityIndex(Int16 visibilityIndex_)
{
	m_visibilityIndex = visibilityIndex_;
}

/////////////////////////////////////////////////////////////////////////////////
Int16 IGlobalActorWrapper::getVisibilityIndex() const
{
	return m_visibilityIndex;
}

}
