#pragma once
#include SAMPCPP_PCH



#include <SAMPCpp/Core/Color.hpp>
#include <SAMPCpp/Core/TypesAndDefinitions.hpp>

#include <SAMPCpp/Dependencies/QuickMaffs.hpp>

#include <SAMPCpp/Dependencies/SampGDK.hpp>

namespace samp_cpp
{

class Player;

/// <summary>
/// Class (interface) representing in-game textdraw.
/// Textdraw is 2D text / texture / model render or shape.
/// There are two types of textdraws - player td and global td.
/// Player textdraw is only created for specific player,
/// globals are created for everyone at once.
/// </summary>
class ITextDraw
{
public:
	constexpr static Int32 InvalidHandle = INVALID_TEXT_DRAW;

	enum TextAlign
	{
		Left = 1,
		Center = 2,
		Right = 3
	};
	enum Font
	{
		Decorative = 0,
		Clear = 1,
		ClearCaps = 2,
		GTATitle = 4
	};
	
	/// <summary>
	/// Initializes a new instance of the <see cref="ITextDraw"/> class.
	/// </summary>
	ITextDraw();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="ITextDraw"/> class.
	/// </summary>
	virtual ~ITextDraw();

	/// <summary>
	/// Sets the text.
	/// </summary>
	/// <param name="text_">The text.</param>
	virtual void setText(std::string_view text_, bool update_ = true);
	
	/// <summary>
	/// Sets the font.
	/// </summary>
	/// <param name="font_">The font.</param>
	virtual void setFont(Font font_, bool update_ = true);
	
	/// <summary>
	/// Sets the location.
	/// </summary>
	/// <param name="location_">The location.</param>
	virtual void setLocation(math::Vector2f const &location_);
	
	/// <summary>
	/// Sets the color of the text.
	/// </summary>
	/// <param name="textColor_">Color of the text.</param>
	virtual void setTextColor(Color const &textColor_, bool update_ = true);
	
	/// <summary>
	/// Sets the color of the box.
	/// </summary>
	/// <param name="boxColor_">Color of the box.</param>
	virtual void setBoxColor(Color const &boxColor_, bool update_ = true);
	
	/// <summary>
	/// Sets the color of the background.
	/// </summary>
	/// <param name="bgColor_">Color of the bg.</param>
	virtual void setBackgroundColor(Color const &bgColor_, bool update_ = true);
	
	/// <summary>
	/// Sets the text align.
	/// </summary>
	/// <param name="align_">The align.</param>
	virtual void setTextAlign(TextAlign align_, bool update_ = true);
	
	/// <summary>
	/// Sets the size of the letter.
	/// </summary>
	/// <param name="letterSize_">Size of the letter.</param>
	virtual void setLetterSize(math::Vector2f const &letterSize_, bool update_ = true);
	
	/// <summary>
	/// Sets the size of the text.
	/// </summary>
	/// <param name="textSize_">Size of the text.</param>
	virtual void setTextSize(math::Vector2f const &textSize_, bool update_ = true);
	
	/// <summary>
	/// Sets the size of the outline.
	/// </summary>
	/// <param name="outlineSize_">Size of the outline.</param>
	virtual void setOutlineSize(Int32 outlineSize_, bool update_ = true);
	
	/// <summary>
	/// Sets the size of the shadow.
	/// </summary>
	/// <param name="shadowSize_">Size of the shadow.</param>
	virtual void setShadowSize(Int32 shadowSize_, bool update_ = true);
	
	/// <summary>
	/// Sets whether the textdraw uses box.
	/// </summary>
	/// <param name="useBox_">if set to <c>true</c> [use box].</param>
	virtual void setUseBox(bool useBox_, bool update_ = true);
	
	/// <summary>
	/// Sets whether the textdraw is proportional or not.
	/// </summary>
	/// <param name="proportional_">if set to <c>true</c> [proportional].</param>
	virtual void setProportional(bool proportional_, bool update_ = true);
	
	/// <summary>
	/// Sets whether textdraw is selectable.
	/// </summary>
	/// <param name="selectable_">if set to <c>true</c> [selectable].</param>
	virtual void setSelectable(bool selectable_, bool update_ = true);
	
	/// <summary>
	/// Sets the preview.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	/// <param name="rotation_">The rotation.</param>
	/// <param name="zoom_">The zoom.</param>
	/// <param name="vehColors_">The veh colors.</param>
	virtual void setPreview(Int32 modelIndex_, math::Vector3f const &rotation_, float zoom_ = 1.0f, std::array<Int32, 2> vehColors_ = { -1, -1 }, bool update_ = true);
	
	/// <summary>
	/// Sets the preview model.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	virtual void setPreviewModel(Int32 modelIndex_, bool update_ = true);
	
	/// <summary>
	/// Sets the preview rotation.
	/// </summary>
	/// <param name="rotation_">The rotation.</param>
	virtual void setPreviewRotation(math::Vector3f const &rotation_, bool update_ = true);
	
	/// <summary>
	/// Sets the preview zoom.
	/// </summary>
	/// <param name="zoom_">The zoom.</param>
	virtual void setPreviewZoom(float zoom_, bool update_ = true);
	
	/// <summary>
	/// Sets the preview vehicle colors.
	/// </summary>
	/// <param name="vehColors_">The veh colors.</param>
	virtual void setPreviewVehicleColors(std::array<Int32, 2> vehColors_, bool update_ = true);
	
	/// <summary>
	/// Sets the layer.
	/// </summary>
	/// <param name="layer_">The layer.</param>
	virtual void setLayer(Int32 layer_);

	
	/// <summary>
	/// Returns the handle.
	/// </summary>
	/// <returns>The handle.</returns>
	Int32 getHandle() const;

	/// <summary>
	/// Determines whether this instance is created.
	/// </summary>
	/// <returns>
	///		<c>true</c> if this instance is created; otherwise, <c>false</c>.
	/// </returns>
	bool isCreated() const;

	/// <summary>
	/// Returns the text.
	/// </summary>
	/// <returns>The text.</returns>
	std::string getText() const { return m_text; }
	
	/// <summary>
	/// Returns the font.
	/// </summary>
	/// <returns>The font.</returns>
	Font getFont() const;

	/// <summary>
	/// Returns the location.
	/// </summary>
	/// <returns>The location.</returns>
	math::Vector2f getLocation() const;

	/// <summary>
	/// Returns the color of the text.
	/// </summary>
	/// <returns>The color of the text.</returns>
	Color getTextColor() const;

	/// <summary>
	/// Returns the color of the box.
	/// </summary>
	/// <returns>The color of the box.</returns>
	Color getBoxColor() const;

	/// <summary>
	/// Returns the color of the background.
	/// </summary>
	/// <returns>The color of the background.</returns>
	Color getBackgroundColor() const;

	/// <summary>
	/// Returns the text alignment.
	/// </summary>
	/// <returns>The text alignment.</returns>
	TextAlign getTextAlign() const;

	/// <summary>
	/// Returns the size of the letter.
	/// </summary>
	/// <returns>The size of the letter.</returns>
	math::Vector2f getLetterSize() const;

	/// <summary>
	/// Returns the size of the text.
	/// </summary>
	/// <returns>Returns the size of the text.</returns>
	math::Vector2f getTextSize() const;

	/// <summary>
	/// Returns the size of the outline.
	/// </summary>
	/// <returns>The size of the outline.</returns>
	Int32 getOutlineSize() const;

	/// <summary>
	/// Returns the size of the shadow.
	/// </summary>
	/// <returns>The size of the shadow.</returns>
	Int32 getShadowSize() const;

	/// <summary>
	/// Determines whether textdraw is using box.
	/// </summary>
	/// <returns>
	///		<c>true</c> if is using box; otherwise, <c>false</c>.
	/// </returns>
	bool isUsingBox() const;

	/// <summary>
	/// Determines whether this textdraw is proportional.
	/// </summary>
	/// <returns>
	///		<c>true</c> if this textdraw is proportional; otherwise, <c>false</c>.
	/// </returns>
	bool isProportional() const;

	/// <summary>
	/// Determines whether this textdraw is selectable.
	/// </summary>
	/// <returns>
	///		<c>true</c> if this textdraw is selectable; otherwise, <c>false</c>.
	/// </returns>
	bool isSelectable() const;

	/// <summary>
	/// Determines whether this instance has preview.
	/// </summary>
	/// <returns>
	///		<c>true</c> if this instance has preview; otherwise, <c>false</c>.
	/// </returns>
	bool hasPreview() const;

	/// <summary>
	/// Returns the preview model.
	/// </summary>
	/// <returns>The preview model.</returns>
	Int32 getPreviewModel() const;

	/// <summary>
	/// Returns the preview rotation.
	/// </summary>
	/// <returns>The preview rotation.</returns>
	math::Vector3f getPreviewRotation() const;

	/// <summary>
	/// Returns the preview zoom.
	/// </summary>
	/// <returns>The preview zoom.</returns>
	float getPreviewZoom() const;

	/// <summary>
	/// Returns the color of the preview vehicle.
	/// </summary>
	/// <param name="first_">if set to <c>true</c> returns first color.</param>
	/// <returns>Color of the preview vehicle - either first or second, depending on argument.</returns>
	Int32 getPreviewVehicleColor(bool first_) const;
	
	/// <summary>
	/// Returns the layer.
	/// </summary>
	/// <returns>The layer.</returns>
	Int32 getLayer() const;

	friend class GlobalTextDrawPanel;
	friend class PlayerTextDrawPanel;
protected:

	// Stores handle to SAMP textdraw.
	Int32						m_handle;

	// Stores text content.
	std::string					m_text;
	// Stores font index.
	Font						m_font;
	// Stores 2d screen space location.
	math::Vector2f				m_location;
	// Stores text color.
	Color						m_textColor;
	// Stores box color.
	Color						m_boxColor;
	// Stores background color.
	Color						m_bgColor;
	// Stores text align.
	TextAlign					m_textAlign;
	// Stores letter size.
	math::Vector2f				m_letterSize;
	// Stores text size.
	math::Vector2f				m_textSize;
	// Stores outline size.
	Int32						m_outlineSize;
	// Stores shadow size.
	Int32						m_shadowSize;
	// Flag used to determine whether textdraw uses box or not.
	bool						m_useBox;
	// Flag used to determine whether textdraw is proportional or not.
	bool						m_proportional;
	// Flag used to determine whether textdraw is selectable or not.
	bool						m_selectable;

	// Stores textdraw layer index.
	Int32						m_layer;

	// Stores textdraw preview model index.
	Int32						m_previewModelIndex;
	// Stores textdraw preview model rotation.
	math::Vector3f				m_previewRotation;
	// Stores textdraw preview model zoom.
	float						m_previewZoom;
	// Stores textdraw preview model vehicle colors.
	std::array<Int32, 2>		m_previewVehicleColors;
};

}
