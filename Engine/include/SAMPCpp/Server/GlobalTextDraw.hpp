#pragma once
#include SAMPCPP_PCH



#include <SAMPCpp/Server/TextDraw.hpp>

namespace samp_cpp
{

/// <summary>
/// A single textdraw for every player in game.
/// </summary>
/// <seealso cref="ITextDraw" />
class GlobalTextDraw
	: public ITextDraw
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="GlobalTextDraw"/> class.
	/// </summary>
	GlobalTextDraw(class IGameMode& gameMode_);

	/// <summary>
	/// Finalizes an instance of the <see cref="GlobalTextDraw"/> class.
	/// </summary>
	virtual ~GlobalTextDraw() override;

	/// <summary>
	/// Creates the textdraw.
	/// </summary>
	/// <param name="show_">if set to <c>true</c> shows to everyone after creation.</param>
	void create(bool show_ = false);

	/// <summary>
	/// Destroys this instance.
	/// </summary>
	void destroy();

	/// <summary>
	/// Recreates this instance.
	/// </summary>
	void recreate();

	/// <summary>
	/// Shows textdraw to the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void show(Player & player_);

	/// <summary>
	/// Hides textdraw from the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void hide(Player & player_);

	/// <summary>
	/// Shows to everyone.
	/// </summary>
	void showToEveryone();

	/// <summary>
	/// Hides from everyone.
	/// </summary>
	void hideFromEveryone();

	/// <summary>
	/// Hides and shows again textdraw to every player that had the textdraw visible before.
	/// </summary>
	void reapplyVisibility();

	/// <summary>
	/// Sets the text.
	/// </summary>
	/// <param name="text_">The text.</param>
	virtual void setText(std::string text_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the font.
	/// </summary>
	/// <param name="font_">The font.</param>
	virtual void setFont(Font font_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the location.
	/// </summary>
	/// <param name="location_">The location.</param>
	virtual void setLocation(math::Vector2f const &location_) override;
	
	/// <summary>
	/// Sets the color of the text.
	/// </summary>
	/// <param name="textColor_">Color of the text.</param>
	virtual void setTextColor(Color const &textColor_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the color of the box.
	/// </summary>
	/// <param name="boxColor_">Color of the box.</param>
	virtual void setBoxColor(Color const &boxColor_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the color of the background.
	/// </summary>
	/// <param name="bgColor_">Color of the bg.</param>
	virtual void setBackgroundColor(Color const &bgColor_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the text align.
	/// </summary>
	/// <param name="align_">The align.</param>
	virtual void setTextAlign(TextAlign align_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the size of the letter.
	/// </summary>
	/// <param name="letterSize_">Size of the letter.</param>
	virtual void setLetterSize(math::Vector2f const &letterSize_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the size of the text.
	/// </summary>
	/// <param name="textSize_">Size of the text.</param>
	virtual void setTextSize(math::Vector2f const &textSize_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the size of the outline.
	/// </summary>
	/// <param name="outlineSize_">Size of the outline.</param>
	virtual void setOutlineSize(Int32 outlineSize_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the size of the shadow.
	/// </summary>
	/// <param name="shadowSize_">Size of the shadow.</param>
	virtual void setShadowSize(Int32 shadowSize_, bool update_ = true) override;
	
	/// <summary>
	/// Sets whether the textdraw uses box.
	/// </summary>
	/// <param name="useBox_">if set to <c>true</c> [use box].</param>
	virtual void setUseBox(bool useBox_, bool update_ = true) override;
	
	/// <summary>
	/// Sets whether the textdraw is proportional or not.
	/// </summary>
	/// <param name="proportional_">if set to <c>true</c> [proportional].</param>
	virtual void setProportional(bool proportional_, bool update_ = true) override;
	
	/// <summary>
	/// Sets whether textdraw is selectable.
	/// </summary>
	/// <param name="selectable_">if set to <c>true</c> [selectable].</param>
	virtual void setSelectable(bool selectable_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the preview.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	/// <param name="rotation_">The rotation.</param>
	/// <param name="zoom_">The zoom.</param>
	/// <param name="vehColors_">The veh colors.</param>
	virtual void setPreview(Int32 modelIndex_, math::Vector3f const &rotation_, float zoom_, std::array<Int32, 2> vehColors_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the preview model.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	virtual void setPreviewModel(Int32 modelIndex_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the preview rotation.
	/// </summary>
	/// <param name="rotation_">The rotation.</param>
	virtual void setPreviewRotation(math::Vector3f const &rotation_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the preview zoom.
	/// </summary>
	/// <param name="zoom_">The zoom.</param>
	virtual void setPreviewZoom(float zoom_, bool update_ = true) override;
	
	/// <summary>
	/// Sets the preview vehicle colors.
	/// </summary>
	/// <param name="vehColors_">The veh colors.</param>
	virtual void setPreviewVehicleColors(std::array<Int32, 2> vehColors_, bool update_ = true) override;


	/// <summary>
	/// Event reaction designed to be called when player clicks textdraw.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void whenPlayerClicks(Player & player_)
	{
		// Nothing by default.
	}

	/// <summary>
	/// Event reaction designed to be called when player disconnects.
	/// </summary>
	/// <param name="player_">The player.</param>
	void notifyPlayerDisconnected(Player const & player_);

	bool isShownForPlayer(Player const & player_) const;

	bool isShownForPlayer(Int32 playerIndex_) const;

private:

	class Visibility
	{
	public:
		constexpr static int GrowRate = 32;

		void add(std::size_t playerIndex_);
		void remove(std::size_t playerIndex_);

		void addAll();
		void removeAll();

		bool contains(Int32 playerIndex_) const;

		std::vector<char> 	ctr;
		std::size_t 		maxIndex = 0;

	private:
		void resizeToFit(std::size_t index_);
	} _visibility;

	IGameMode& m_gameMode;
};

}
