#include SAMPCPP_PCH

#include <SAMPCpp/Server/PlayerTextDraw.hpp>

#include <SAMPCpp/Server/Player.hpp>

#include <SAMPCpp/Server/ServerDebugLog.hpp>
#include <SAMPCpp/Server/GameMode.hpp>

namespace samp_cpp
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
void PlayerTextDraw::setText(std::string text_, bool update_)
{
	ITextDraw::setText(std::move(text_), update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetString(m_owner.getIndex(), this->getHandle(), m_text.c_str());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setFont(Font font_, bool update_)
{
	ITextDraw::setFont(font_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawFont(m_owner.getIndex(), this->getHandle(), static_cast<Int32>(font_));
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setLocation(math::Vector2f const &location_)
{
	ITextDraw::setLocation(location_);
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setTextColor(Color const &textColor_, bool update_)
{
	ITextDraw::setTextColor(textColor_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawColor(m_owner.getIndex(), this->getHandle(), textColor_.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setBoxColor(Color const &boxColor_, bool update_)
{
	ITextDraw::setBoxColor(boxColor_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawBoxColor(m_owner.getIndex(), this->getHandle(), boxColor_.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setBackgroundColor(Color const &bgColor_, bool update_)
{
	ITextDraw::setBackgroundColor(bgColor_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawBackgroundColor(m_owner.getIndex(), this->getHandle(), bgColor_.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setTextAlign(TextAlign align_, bool update_)
{
	ITextDraw::setTextAlign(align_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawAlignment(m_owner.getIndex(), this->getHandle(), static_cast<Int32>(align_));
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setLetterSize(math::Vector2f const &letterSize_, bool update_)
{
	ITextDraw::setLetterSize(letterSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawLetterSize(m_owner.getIndex(), this->getHandle(), letterSize_.x, letterSize_.y);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setTextSize(math::Vector2f const &textSize_, bool update_)
{
	ITextDraw::setTextSize(textSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawTextSize(m_owner.getIndex(), this->getHandle(), textSize_.x, textSize_.y);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setOutlineSize(Int32 outlineSize_, bool update_)
{
	ITextDraw::setOutlineSize(outlineSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetOutline(m_owner.getIndex(), this->getHandle(), outlineSize_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setShadowSize(Int32 shadowSize_, bool update_)
{
	ITextDraw::setShadowSize(shadowSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetShadow(m_owner.getIndex(), this->getHandle(), shadowSize_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setUseBox(bool useBox_, bool update_)
{
	ITextDraw::setUseBox(useBox_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawUseBox(m_owner.getIndex(), this->getHandle(), useBox_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setProportional(bool proportional_, bool update_)
{
	ITextDraw::setProportional(proportional_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetProportional(m_owner.getIndex(), this->getHandle(), proportional_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setSelectable(bool selectable_, bool update_)
{
	ITextDraw::setSelectable(selectable_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetSelectable(m_owner.getIndex(), this->getHandle(), selectable_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setPreview(Int32 modelIndex_, math::Vector3f const &rotation_, float zoom_, std::array<Int32, 2> vehColors_, bool update_)
{
	ITextDraw::setPreview(modelIndex_, rotation_, zoom_, vehColors_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetPreviewModel(m_owner.getIndex(), this->getHandle(), modelIndex_);
		sampgdk_PlayerTextDrawSetPreviewRot(m_owner.getIndex(), this->getHandle(), rotation_.x, rotation_.y, rotation_.z, zoom_);
		sampgdk_PlayerTextDrawSetPreviewVehCol(m_owner.getIndex(), this->getHandle(), vehColors_[0], vehColors_[1]);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setPreviewModel(Int32 modelIndex_, bool update_)
{
	ITextDraw::setPreviewModel(modelIndex_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetPreviewModel(m_owner.getIndex(), this->getHandle(), modelIndex_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setPreviewRotation(math::Vector3f const &rotation_, bool update_)
{
	ITextDraw::setPreviewRotation(rotation_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetPreviewRot(m_owner.getIndex(), this->getHandle(), rotation_.x, rotation_.y, rotation_.z, m_previewZoom);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setPreviewZoom(float zoom_, bool update_)
{
	ITextDraw::setPreviewZoom(zoom_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetPreviewRot(m_owner.getIndex(), this->getHandle(), m_previewRotation.x, m_previewRotation.y, m_previewRotation.z, zoom_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void PlayerTextDraw::setPreviewVehicleColors(std::array<Int32, 2> vehColors_, bool update_)
{
	ITextDraw::setPreviewVehicleColors(vehColors_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_PlayerTextDrawSetPreviewVehCol(m_owner.getIndex(), this->getHandle(), vehColors_[0], vehColors_[1]);
	}
}


////////////////////////////////////////////////////////////////////////////////////
bool PlayerTextDraw::isShown() const
{
	return m_shown;
}

}
