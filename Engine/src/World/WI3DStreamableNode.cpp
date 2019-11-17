#include SAMPCPP_PCH

// The header of this class:
#include <SAMPCpp/World/WI3DStreamableNode.hpp>

namespace samp_cpp
{

//////////////////////////////////////////////////////////////////////////////////////////
IWI3DStreamableNode::IWI3DStreamableNode()
	:
	m_worldMode{ VisibilityMode::Everywhere },
	m_interiorMode{ VisibilityMode::Everywhere }
{
}

////////////////////////////////////////////////////////////////////////
void IWI3DStreamableNode::setWorldAndMode(Int32 world_, VisibilityMode visibilityMode_)
{
	IWI3DNode::setWorld(world_);
	m_worldMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void IWI3DStreamableNode::setWorldMode(VisibilityMode visibilityMode_)
{
	m_worldMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void IWI3DStreamableNode::setInteriorAndMode(Int32 interior_, VisibilityMode visibilityMode_)
{
	IWI3DNode::setInterior(interior_);
	m_interiorMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
void IWI3DStreamableNode::setInteriorMode(VisibilityMode visibilityMode_)
{
	m_interiorMode = visibilityMode_;
}

////////////////////////////////////////////////////////////////////////
bool IWI3DStreamableNode::shouldBeVisibleIn(Int32 world_, Int32 interior_) const
{
	return ((	(m_worldMode		== VisibilityMode::Everywhere)									||
				(m_worldMode		== VisibilityMode::Specified		&& m_world == world_)		||
				(m_worldMode		== VisibilityMode::AllButSpecified	&& m_world != world_))		&&
			(	(m_interiorMode	== VisibilityMode::Everywhere)										||
				(m_interiorMode	== VisibilityMode::Specified			&& m_interior == interior_)	||
				(m_interiorMode	== VisibilityMode::AllButSpecified		&& m_interior != interior_)));
}

//////////////////////////////////////////////////////////////////////////////////////////
IWI3DStreamableNode::VisibilityMode IWI3DStreamableNode::getWorldMode() const
{
	return m_worldMode;
}

//////////////////////////////////////////////////////////////////////////////////////////
IWI3DStreamableNode::VisibilityMode IWI3DStreamableNode::getInteriorMode() const
{
	return m_interiorMode;
}

}
