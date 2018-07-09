#include "EnginePCH.hpp"

#include <SAMP-EDGEngine/Server/PlayerTextDraw.hpp>

#include <SAMP-EDGEngine/Server/Player.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////////////////
PlayerTextDraw::PlayerTextDraw(Player& player_)
	:
	m_owner{ player_ },
	m_shown{ false }
{
}

////////////////////////////////////////////////////////////////////////////////////
PlayerTextDraw::~PlayerTextDraw()
{
	this->destroy();
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::create(bool show_)
{
	if (!(this->isCreated()))
	{
		m_handle = sampgdk::CreatePlayerTextDraw(m_owner.getIndex(), m_location.x, m_location.y, m_text.c_str());

		if (m_handle != InvalidHandle)
		{
			m_owner.bindTextDraw(m_handle, *this);

			sampgdk::PlayerTextDrawFont(m_owner.getIndex(), m_handle, static_cast<Int32>(m_font));
			sampgdk::PlayerTextDrawColor(m_owner.getIndex(), m_handle, m_textColor.toInt32());
			sampgdk::PlayerTextDrawBoxColor(m_owner.getIndex(), m_handle, m_boxColor.toInt32());
			sampgdk::PlayerTextDrawBackgroundColor(m_owner.getIndex(), m_handle, m_bgColor.toInt32());
			sampgdk::PlayerTextDrawAlignment(m_owner.getIndex(), m_handle, static_cast<Int32>(m_textAlign));
			sampgdk::PlayerTextDrawLetterSize(m_owner.getIndex(), m_handle, m_letterSize.x, m_letterSize.y);
			sampgdk::PlayerTextDrawSetOutline(m_owner.getIndex(), m_handle, static_cast<Int32>(m_outlineSize));
			sampgdk::PlayerTextDrawSetShadow(m_owner.getIndex(), m_handle, static_cast<Int32>(m_shadowSize));
			sampgdk::PlayerTextDrawUseBox(m_owner.getIndex(), m_handle, m_useBox);
			sampgdk::PlayerTextDrawSetProportional(m_owner.getIndex(), m_handle, m_proportional);
			sampgdk::PlayerTextDrawSetSelectable(m_owner.getIndex(), m_handle, m_selectable);
			sampgdk::PlayerTextDrawTextSize(m_owner.getIndex(), m_handle, m_textSize.x, m_textSize.y);

			if (m_previewModelIndex != -1)
			{
				sampgdk::PlayerTextDrawSetPreviewModel(m_owner.getIndex(), m_handle, m_previewModelIndex);
				sampgdk::PlayerTextDrawSetPreviewRot(m_owner.getIndex(), m_handle, m_previewRotation.x, m_previewRotation.y, m_previewRotation.z, m_previewZoom);
				if (m_previewVehicleColors[0] != -1)
					sampgdk::PlayerTextDrawSetPreviewVehCol(m_owner.getIndex(), m_handle, m_previewVehicleColors[0], m_previewVehicleColors[1]);
			}
			if (show_)
			{
				sampgdk::PlayerTextDrawShow(m_owner.getIndex(), m_handle);
			}
			m_shown = show_;
		}
		
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::destroy()
{
	if (this->isCreated())
	{
		m_owner.unbindTextDraw(m_handle);
		sampgdk::PlayerTextDrawDestroy(m_owner.getIndex(), m_handle);
		m_handle = InvalidHandle;
		m_shown = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::recreate()
{
	const_a shown = m_shown;
	this->destroy();
	this->create(shown);
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::show()
{
	if (this->isCreated())
	{
		sampgdk::PlayerTextDrawShow(m_owner.getIndex(), m_handle);
		m_shown = true;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::hide()
{
	if (this->isCreated())
	{
		sampgdk::PlayerTextDrawHide(m_owner.getIndex(), m_handle);
		m_shown = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////
bool PlayerTextDraw::isShown() const
{
	return m_shown;
}

}
