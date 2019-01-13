#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/GlobalTextDraw.hpp>

#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////////////////
GlobalTextDraw::GlobalTextDraw(IGameMode &gameMode_)
	: m_gameMode{ gameMode_ }
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

		if (m_handle != InvalidHandle)
		{
			m_gameMode.bindTextDraw(m_handle, *this);

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
		m_gameMode.unbindTextDraw(m_handle);
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

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setText(std::string_view text_, bool update_)
{
	ITextDraw::setText(text_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetString(this->getHandle(), std::string(text_).c_str()); // TODO: optimize?
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setFont(Font font_, bool update_)
{
	ITextDraw::setFont(font_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawFont(this->getHandle(), static_cast<Int32>(font_));
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setLocation(math::Vector2f const &location_)
{
	ITextDraw::setLocation(location_);
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setTextColor(Color const &textColor_, bool update_)
{
	ITextDraw::setTextColor(textColor_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawColor(this->getHandle(), textColor_.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setBoxColor(Color const &boxColor_, bool update_)
{
	ITextDraw::setBoxColor(boxColor_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawBoxColor(this->getHandle(), boxColor_.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setBackgroundColor(Color const &bgColor_, bool update_)
{
	ITextDraw::setBackgroundColor(bgColor_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawBackgroundColor(this->getHandle(), bgColor_.toInt32());
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setTextAlign(TextAlign align_, bool update_)
{
	ITextDraw::setTextAlign(align_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawAlignment(this->getHandle(), static_cast<Int32>(align_));
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setLetterSize(math::Vector2f const &letterSize_, bool update_)
{
	ITextDraw::setLetterSize(letterSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawLetterSize(this->getHandle(), letterSize_.x, letterSize_.y);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setTextSize(math::Vector2f const &textSize_, bool update_)
{
	ITextDraw::setTextSize(textSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawTextSize(this->getHandle(), textSize_.x, textSize_.y);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setOutlineSize(Int32 outlineSize_, bool update_)
{
	ITextDraw::setOutlineSize(outlineSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetOutline(this->getHandle(), outlineSize_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setShadowSize(Int32 shadowSize_, bool update_)
{
	ITextDraw::setShadowSize(shadowSize_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetShadow(this->getHandle(), shadowSize_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setUseBox(bool useBox_, bool update_)
{
	ITextDraw::setUseBox(useBox_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawUseBox(this->getHandle(), useBox_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setProportional(bool proportional_, bool update_)
{
	ITextDraw::setProportional(proportional_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetProportional(this->getHandle(), proportional_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setSelectable(bool selectable_, bool update_)
{
	ITextDraw::setSelectable(selectable_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetSelectable(this->getHandle(), selectable_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setPreview(Int32 modelIndex_, math::Vector3f const &rotation_, float zoom_, std::array<Int32, 2> vehColors_, bool update_)
{
	ITextDraw::setPreview(modelIndex_, rotation_, zoom_, vehColors_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetPreviewModel(this->getHandle(), modelIndex_);
		sampgdk_TextDrawSetPreviewRot(this->getHandle(), rotation_.x, rotation_.y, rotation_.z, zoom_);
		sampgdk_TextDrawSetPreviewVehCol(this->getHandle(), vehColors_[0], vehColors_[1]);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setPreviewModel(Int32 modelIndex_, bool update_)
{
	ITextDraw::setPreviewModel(modelIndex_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetPreviewModel(this->getHandle(), modelIndex_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setPreviewRotation(math::Vector3f const &rotation_, bool update_)
{
	ITextDraw::setPreviewRotation(rotation_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetPreviewRot(this->getHandle(), rotation_.x, rotation_.y, rotation_.z, m_previewZoom);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setPreviewZoom(float zoom_, bool update_)
{
	ITextDraw::setPreviewZoom(zoom_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetPreviewRot(this->getHandle(), m_previewRotation.x, m_previewRotation.y, m_previewRotation.z, zoom_);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void GlobalTextDraw::setPreviewVehicleColors(std::array<Int32, 2> vehColors_, bool update_)
{
	ITextDraw::setPreviewVehicleColors(vehColors_, update_);

	if (update_ && this->isCreated()) {
		sampgdk_TextDrawSetPreviewVehCol(this->getHandle(), vehColors_[0], vehColors_[1]);
	}
}

}
