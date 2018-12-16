#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/GlobalTextDraw.hpp>

#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////////////////
GlobalTextDraw::GlobalTextDraw()
{
}

////////////////////////////////////////////////////////////////////////////////////
GlobalTextDraw::~GlobalTextDraw()
{
	this->destroy();
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::create(bool show_)
{
	if (!(this->isCreated()))
	{
		m_handle = sampgdk::TextDrawCreate(m_location.x, m_location.y, m_text.c_str());

		if (m_handle)
		{
			GameMode->bindTextDraw(m_handle, *this);

			sampgdk::TextDrawFont				(m_handle, static_cast<Int32>(m_font));
			sampgdk::TextDrawColor				(m_handle, m_textColor.toInt32());
			sampgdk::TextDrawBoxColor			(m_handle, m_boxColor.toInt32());
			sampgdk::TextDrawBackgroundColor	(m_handle, m_bgColor.toInt32());
			sampgdk::TextDrawAlignment			(m_handle, static_cast<Int32>(m_textAlign));
			sampgdk::TextDrawLetterSize			(m_handle, m_letterSize.x, m_letterSize.y);
			sampgdk::TextDrawTextSize			(m_handle, m_textSize.x, m_textSize.y);
			sampgdk::TextDrawSetOutline			(m_handle, static_cast<Int32>(m_outlineSize));
			sampgdk::TextDrawSetShadow			(m_handle, static_cast<Int32>(m_shadowSize));
			sampgdk::TextDrawUseBox				(m_handle, m_useBox);
			sampgdk::TextDrawSetProportional	(m_handle, m_proportional);
			sampgdk::TextDrawSetSelectable		(m_handle, m_selectable);

			if (m_previewModelIndex != -1)
			{
				sampgdk::TextDrawSetPreviewModel(m_handle, m_previewModelIndex);
				sampgdk::TextDrawSetPreviewRot(m_handle, m_previewRotation.x, m_previewRotation.y, m_previewRotation.z, m_previewZoom);
				if (m_previewVehicleColors[0] != -1)
					sampgdk::TextDrawSetPreviewVehCol(m_handle, m_previewVehicleColors[0], m_previewVehicleColors[1]);
			}

			if (show_)
			{
				this->showToEveryone();
			}
		}
		
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::destroy()
{
	if (this->isCreated())
	{
		GameMode->unbindTextDraw(m_handle);
		sampgdk::TextDrawDestroy(m_handle);
		m_handle = InvalidHandle;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::recreate()
{
	this->destroy();
	this->create(true);
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::show(Player& player_)
{
	if (this->isCreated())
	{
		sampgdk::TextDrawShowForPlayer(player_.getIndex(), m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::hide(Player& player_)
{
	if (this->isCreated())
	{
		sampgdk::TextDrawHideForPlayer(player_.getIndex(), m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::showToEveryone()
{
	if (this->isCreated())
	{
		sampgdk::TextDrawShowForAll(m_handle);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::hideFromEveryone()
{
	if (this->isCreated())
	{
		sampgdk::TextDrawHideForAll(m_handle);
	}
}

}
