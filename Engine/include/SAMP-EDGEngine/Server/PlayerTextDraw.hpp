#pragma once

#include <SAMP-EDGEngine/Server/TextDraw.hpp>

namespace samp_edgengine
{

class Player;

/// <summary>
/// A separate textdraw to single player.
/// </summary>
/// <seealso cref="ITextDraw" />
class PlayerTextDraw
	: public ITextDraw
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="PlayerTextDraw"/> class.
	/// </summary>
	/// <param name="player_">The player.</param>
	PlayerTextDraw(Player & player_);

	/// <summary>
	/// Finalizes an instance of the <see cref="PlayerTextDraw"/> class.
	/// </summary>
	virtual ~PlayerTextDraw() override;

	/// <summary>
	/// Creates the textdraw.
	/// </summary>
	/// <param name="show_">if set to <c>true</c> textdraw will be shown to player after creating.</param>
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
	/// Shows this instance.
	/// </summary>
	void show();

	/// <summary>
	/// Hides this instance.
	/// </summary>
	void hide();

	/// <summary>
	/// Determines whether this instance is shown.
	/// </summary>
	/// <returns>
	///		<c>true</c> if this instance is shown; otherwise, <c>false</c>.
	/// </returns>
	bool isShown() const;

	/// <summary>
	/// Returns the owner.
	/// </summary>
	/// <returns>Reference to owner.</returns>
	Player& getOwner() const { return m_owner; }
	
	/// <summary>
	/// Event reaction designed to be called when player clicks textdraw.
	/// </summary>
	virtual void whenPlayerClicks()
	{
		// Nothing by default.
	}

	friend class PlayerTextDrawPanel;
private:

	//	Reference to owning player.
	Player & m_owner;

	//	Determines whether textdraw is shown or not.
	bool m_shown;
};

}
