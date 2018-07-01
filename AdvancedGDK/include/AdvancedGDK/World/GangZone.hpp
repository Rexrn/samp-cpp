#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/Core/Color.hpp>
#include <AdvancedGDK/Core/TypesAndDefinitions.hpp>

namespace agdk
{
class Player;

/// <summary>
/// A single gang zone.
/// </summary>
class GangZone
{
public:
	static constexpr Color DefaultColor			= colors::Red;
	static constexpr Color DefaultFlashingColor = colors::Blue;
	static constexpr Int32 InvalidHandle		= INVALID_GANG_ZONE;

	/// <summary>
	/// Initializes a new instance of the <see cref="GangZone"/> class.
	/// </summary>
	GangZone();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="GangZone"/> class.
	/// </summary>
	/// <param name="startLoc_">The start (minimal) location.</param>
	/// <param name="endLoc_">The end (maximal) location.</param>
	/// <param name="color_">The color.</param>
	GangZone(math::Vector2f const & startLoc_, math::Vector2f const & endLoc_, Color const & color_, Color const & flashingColor = DefaultFlashingColor);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="GangZone"/> class.
	/// </summary>
	/// <param name="movedZone_">The moved zone.</param>
	GangZone(GangZone && movedZone_);

	/// <summary>
	/// Initializes a new instance of the <see cref="GangZone"/> class.
	/// </summary>
	/// <param name="otherZone_">The other zone.</param>
	GangZone(GangZone const & otherZone_);

	/// <summary>
	/// Finalizes an instance of the <see cref="GangZone"/> class.
	/// </summary>
	~GangZone();
	
	/// <summary>
	/// Move-assignment operator.
	/// </summary>
	/// <param name="movedZone_">The moved zone.</param>
	/// <returns>
	///		ref to self.
	/// </returns>
	GangZone& operator=(GangZone && movedZone_);

	/// <summary>
	/// Copy-assignment operator.
	/// </summary>
	/// <param name="otherZone_">The other zone.</param>
	/// <returns>
	///		ref to self.
	/// </returns>
	GangZone& operator=(GangZone const & otherZone_);
	
	/// <summary>
	/// Creates this gang zone.
	/// </summary>
	/// <returns>
	///		<c>true</c> if gang zone was created successfully; otherwise, <c>false</c>.
	/// </returns>
	bool create();

	/// <summary>
	/// Creates this gang zone with specified bounds.
	/// </summary>
	/// <param name="startLoc_">The start (minimal) location.</param>
	/// <param name="endLoc_">The end (maximal) location.</param>
	bool create(math::Vector2f const & startLoc_, math::Vector2f const & endLoc_);
	
	/// <summary>
	/// Destroys this gang zone;
	/// </summary>
	/// <returns>
	///		<c>true</c> if gang zone was destroyed successfully; otherwise, <c>false</c>.
	/// </returns>
	bool destroy();
	
	/// <summary>
	/// Recreates this gang zone.
	/// </summary>
	/// <returns>
	///		<c>true</c> if gang zone was created successfully; otherwise, <c>false</c>.
	/// </returns>
	bool recreate()
	{
		this->destroy();
		return this->create();
	}

	/// <summary>
	/// Shows this gang zone to everyone (reuses previous color).
	/// </summary>
	void show();
	
	/// <summary>
	/// Shows this gang zone (and sets its new color) to everyone.
	/// </summary>
	/// <param name="color_">The color.</param>
	void show(Color const & color_);
	
	/// <summary>
	/// Shows this gang zone to specified player (reuses previous color).
	/// </summary>
	/// <param name="player_">The player.</param>
	void show(Player & player_);
	
	/// <summary>
	/// Shows this gang zone (and sets its new color) to specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="color_">The color.</param>
	void show(Player & player_, Color const & color_);

	/// <summary>
	/// Makes this gang zone flash to everyone (reuses previous flashing color).
	/// </summary>
	void flash();

	/// <summary>
	/// Makes this gang zone flash (and sets its flashing color) to everyone.
	/// </summary>
	/// <param name="flashingColor_">The new flashing color.</param>
	void flash(Color const & flashingColor_);

	/// <summary>
	/// Makes this gang zone flash to specified player (reuses previous flashing color).
	/// </summary>
	/// <param name="player_">The player.</param>
	void flash(Player & player_);

	/// <summary>
	/// Makes this gang zone flash (and sets its flashing color) to specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="flashingColor_">The color.</param>
	void flash(Player & player_, Color const & flashingColor_);
	
	/// <summary>
	/// Hides this gang zone from everyone.
	/// </summary>
	void hide();
	
	/// <summary>
	/// Hides this gang zone from specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void hide(Player & player_);

	/// <summary>
	/// Stops this gang zone to flash.
	/// </summary>
	void stopFlashing();

	/// <summary>
	/// Stops this gang zone to flash for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void stopFlashing(Player & player_);

	/// <summary>
	/// Sets the default color for this gang zone. You need to manually hide and show it for players to see difference.
	/// </summary>
	/// <param name="color_">The color.</param>
	void setColor(Color const & color_);

	/// <summary>
	/// Sets the default flashing color for this gang zone. You need to manually stop and start flashing it for players to see difference.
	/// </summary>
	/// <param name="color_">The color.</param>
	void setFlashingColor(Color const & flashingColor_);
	
	/// <summary>
	/// Returns the start (minimal) location of this gang zone.
	/// </summary>
	/// <returns>
	///		The start (minimal) location of this gang zone.
	/// </returns>
	math::Vector2f getStartLocation() const;

	/// <summary>
	/// Returns the end (maximal) location of this gang zone.
	/// </summary>
	/// <returns>
	///		The end (maximal) location of this gang zone.
	/// </returns>
	math::Vector2f getEndLocation() const;

	/// <summary>
	/// Returns the default color of this gang zone.
	/// </summary>
	/// <returns>
	///		The default color of this gang zone.
	/// </returns>
	Color getColor() const;

	/// <summary>
	/// Returns the default flashing color of this gang zone.
	/// </summary>
	/// <returns>
	///		The default flashing color of this gang zone.
	/// </returns>
	Color getFlashingColor() const;

	/// <summary>
	/// Returns the bounds of this gang zone as a `std::pair` (first = start, second = end)..
	/// </summary>
	/// <returns>
	///		The bounds of this gang zone as a `std::pair` (first = start, second = end).
	/// </returns>
	auto getBounds() const {
		return std::make_pair(this->getStartLocation(), this->getEndLocation());
	}

private:
	
	/// <summary>
	/// Ensures that start location is lower than end location.
	/// </summary>
	void fixBounds();

	Color			m_color;
	Color			m_flashingColor;
	math::Vector2f	m_startLocation;
	math::Vector2f	m_endLocation;
	Int32			m_handle;
};

}
