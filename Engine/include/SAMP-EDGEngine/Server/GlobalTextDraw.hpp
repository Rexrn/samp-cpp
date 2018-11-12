#pragma once

#include <SAMP-EDGEngine/Server/TextDraw.hpp>

namespace samp_edgengine
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
	GlobalTextDraw();

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
	/// Event reaction designed to be called when player clicks textdraw.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void whenPlayerClicks(Player & player_)
	{
		// Nothing by default.
	}
};

}
