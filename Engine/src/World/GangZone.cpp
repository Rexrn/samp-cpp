#include SAMPCPP_PCH

#include <SAMPCpp/World/GangZone.hpp>
#include <SAMPCpp/Server/Player.hpp>

namespace samp_cpp
{

////////////////////////////////////////////////////////////////////////////////////
GangZone::GangZone()
	:
	m_color{ DefaultColor },
	m_flashingColor{ DefaultFlashingColor },
	m_handle{ InvalidHandle }
{
}

////////////////////////////////////////////////////////////////////////////////////
GangZone::GangZone(math::Vector2f const& startLoc_, math::Vector2f const& endLoc_, Color const& color_, Color const & flashingColor_)
	:
	m_startLocation{ startLoc_ },
	m_endLocation{ endLoc_ },
	m_color{ color_ },
	m_flashingColor{ DefaultFlashingColor },
	m_handle{ InvalidHandle }
{
	this->fixBounds();
}

////////////////////////////////////////////////////////////////////////////////////
GangZone::GangZone(GangZone&& movedZone_)
{
	*this = std::forward<GangZone>(movedZone_);
}

////////////////////////////////////////////////////////////////////////////////////
GangZone::GangZone(GangZone const& otherZone_)
{
	*this = otherZone_;
}

////////////////////////////////////////////////////////////////////////////////////
GangZone& GangZone::operator=(GangZone&& movedZone_)
{
	std::swap(m_startLocation, movedZone_.m_startLocation);
	std::swap(m_endLocation, movedZone_.m_endLocation);
	std::swap(m_color, movedZone_.m_color);
	std::swap(m_flashingColor, movedZone_.m_flashingColor);
	std::swap(m_handle, movedZone_.m_handle);

	return *this;
}

////////////////////////////////////////////////////////////////////////////////////
GangZone& GangZone::operator=(GangZone const& otherZone_)
{
	this->destroy();

	m_startLocation		= otherZone_.m_startLocation;
	m_endLocation		= otherZone_.m_endLocation;
	m_color				= otherZone_.m_color;
	m_flashingColor		= otherZone_.m_flashingColor;

	return *this;
}

////////////////////////////////////////////////////////////////////////////////////
GangZone::~GangZone()
{
	if (m_handle != InvalidHandle)
	{
		m_handle = sampgdk_GangZoneDestroy(m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
bool GangZone::create()
{
	if (m_handle == InvalidHandle)
	{
		m_handle = sampgdk_GangZoneCreate(m_startLocation.x, m_startLocation.y, m_endLocation.x, m_endLocation.y);
		return m_handle != InvalidHandle;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////
bool GangZone::create(math::Vector2f const& startLoc_, math::Vector2f const& endLoc_)
{
	if (m_handle == InvalidHandle)
	{
		m_startLocation = startLoc_;
		m_endLocation = endLoc_;
		this->fixBounds();

		m_handle = sampgdk_GangZoneCreate(m_startLocation.x, m_startLocation.y, m_endLocation.x, m_endLocation.y);
		return m_handle != InvalidHandle;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////
bool GangZone::destroy()
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneDestroy(m_handle);
		m_handle = InvalidHandle;
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::show()
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneShowForAll(m_handle, m_color.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::show(Color const& color_)
{
	this->setColor(color_);
	this->show();
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::show(Player& player_)
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneShowForPlayer(player_.getIndex(), m_handle, m_color.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::show(Player& player_, Color const& color_)
{
	this->setColor(color_);
	this->show(player_);
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::flash()
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneFlashForAll(m_handle, m_flashingColor.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::flash(Color const& flashingColor_)
{
	this->setFlashingColor(flashingColor_);
	this->flash();
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::flash(Player& player_)
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneFlashForPlayer(player_.getIndex(), m_handle, m_flashingColor.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::flash(Player& player_, Color const& flashingColor_)
{
	this->setFlashingColor(flashingColor_);
	this->flash(player_);
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::hide()
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneHideForAll(m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::hide(Player& player_)
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneHideForPlayer(player_.getIndex(), m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::stopFlashing()
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneStopFlashForAll(m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::stopFlashing(Player& player_)
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_GangZoneStopFlashForPlayer(player_.getIndex(), m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::setColor(Color const& color_)
{
	m_color = color_;
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::setFlashingColor(Color const& flashingColor_)
{
	m_flashingColor = flashingColor_;
}

////////////////////////////////////////////////////////////////////////////////////
math::Vector2f GangZone::getStartLocation() const
{
	return m_startLocation;
}

////////////////////////////////////////////////////////////////////////////////////
math::Vector2f GangZone::getEndLocation() const
{
	return m_endLocation;
}

////////////////////////////////////////////////////////////////////////////////////
Color GangZone::getColor() const
{
	return m_color;
}

////////////////////////////////////////////////////////////////////////////////////
void GangZone::fixBounds()
{
	math::Vector2f::bounds(m_startLocation, m_endLocation);
}

}
